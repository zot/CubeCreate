// menus.cpp: ingame menu system (also used for scores and serverlist)

#include "engine.h"

#define GUI_TITLE_COLOR  0xFFDD88
#define GUI_BUTTON_COLOR 0xFFFFFF
#define GUI_TEXT_COLOR   0xDDFFDD

static vec menupos;
static int menustart = 0;
static int menutab = 1;
static g3d_gui *cgui = NULL;

struct menu : g3d_callback
{
    char *name, *header, *contents, *onclear;

    menu() : name(NULL), header(NULL), contents(NULL), onclear(NULL) {}

    void gui(g3d_gui &g, bool firstpass)
    {
        cgui = &g;
        cgui->start(menustart, 0.03f, &menutab);
        cgui->tab(header ? header : name, GUI_TITLE_COLOR);
        lua::engine.exec(contents);
        cgui->end();
        cgui = NULL;
    }

    virtual void clear() 
    {
        DELETEA(onclear);
    }
};

class delayedUpdate
{
private:
    enum
    {
        INT,
        FLOAT,
        STRING,
        ACTION
    } type;

    EngineVariable *var;
    boost::any val;

public:
    delayedUpdate(): type(ACTION), val(NULL) {}

    void schedule(const std::string& s)
    {
        type = ACTION;
        val = s;
    }
    void schedule(EngineVariable *v, int i)
    {
        type = INT;
        var = v;
        val = i;

        // make sure they're registered in lua.
        // no kittens are hurt when registering variable that's already registered
        var->registerLuaIVAR();
    }
    void schedule(EngineVariable *v, float f)
    {
        type = FLOAT;
        var = v;
        val = f;

        var->registerLuaFVAR();
    }
    void schedule(EngineVariable *v, const std::string& s)
    {
        type = STRING;
        var = v;
        val = s;

        var->registerLuaSVAR();
    }

    int getInt()
    {
        switch (type)
        {
            case INT:
            case FLOAT:
            case STRING: return anyint(val);
            default: return 0;
        }
    }

    float getFloat()
    {
        switch (type)
        {
            case INT:
            case FLOAT:
            case STRING: return anyfloat(val);
            default: return 0;
        }
    }

    std::string getString()
    {
        switch (type)
        {
            case INT:
            case FLOAT:
            case STRING: return anystring(val);
            default: return std::string();
        }
    }

    void run()
    {
        if (type == ACTION)
        {
            if (!anystring(val).empty()) lua::engine.exec(anystring(val).c_str());
        }
        else if (var) switch (var->getType()[0])
        {
            case 'I': var->set(getInt(), true, true, true); break;
            case 'F': var->set(getFloat(), true, true, true); break;
            case 'S': var->set(getString(), true, true); break;
        }
    }
};

static std::vector<delayedUpdate> updateLater;
static hashtable<const char *, menu> guis;
static vector<menu *> guistack;
static bool shouldclearmenu = true, clearlater = false;

vec menuinfrontofplayer()
{ 
    vec dir;
    vecfromyawpitch(camera1->yaw, 0, 1, 0, dir);
    dir.mul(GETIV(menudistance)).add(camera1->o);
    dir.z -= player->eyeheight-1;
    return dir;
}

void popgui()
{
    menu *m = guistack.pop();
    m->clear();
}

void removegui(menu *m)
{
    loopv(guistack) if(guistack[i]==m)
    {
        guistack.remove(i);
        m->clear();
        return;
    }
}

void pushgui(menu *m, int pos = -1)
{
    if(guistack.empty())
    {
        menupos = menuinfrontofplayer();
        g3d_resetcursor();
    }
    if(pos < 0) guistack.add(m);
    else guistack.insert(pos, m);
    if(pos < 0 || pos==guistack.length()-1)
    {
        menutab = 1;
        menustart = totalmillis;
    }
}

void restoregui(int pos)
{
    int clear = guistack.length()-pos-1;
    loopi(clear) popgui();
    menutab = 1;
    menustart = totalmillis;
}

void showgui(const char *name)
{
    menu *m = guis.access(name);
    if(!m) return;
    int pos = guistack.find(m);
    if(pos<0) pushgui(m);
    else restoregui(pos);
}

int cleargui(int n)
{
    int clear = guistack.length();
    if(GETIV(mainmenu) && !isconnected(true) && clear > 0 && guistack[0]->name && !strcmp(guistack[0]->name, "main")) 
    {
        clear--;
        if(!clear) return 1;
    }
    if(n>0) clear = min(clear, n);
    loopi(clear) popgui(); 
    if(!guistack.empty()) restoregui(guistack.length()-1);
    return clear;
}

void guionclear(char *action)
{
    if(guistack.empty()) return;
    menu *m = guistack.last();
    DELETEA(m->onclear);
    if(action[0]) m->onclear = newstring(action);
}

void guistayopen(char *contents)
{
    bool oldclearmenu = shouldclearmenu;
    shouldclearmenu = false;
    lua::engine.exec(contents);
    shouldclearmenu = oldclearmenu;
}

void guinoautotab(char *contents)
{
    if(!cgui) return;
    cgui->allowautotab(false);
    lua::engine.exec(contents);
    cgui->allowautotab(true);
}

//@DOC name and icon are optional
void guibutton(char *name, char *action, char *icon)
{
    if(!cgui) return;
    bool hideicon = !strcmp(icon, "0");
    int ret = cgui->button(name, GUI_BUTTON_COLOR, hideicon ? NULL : (icon[0] ? icon : (strstr(action, "showgui") ? "menu" : "action")));
    if(ret&G3D_UP) 
    {
        updateLater.push_back(delayedUpdate());
        updateLater.back().schedule(action[0] ? std::string(action) : std::string(name));
        if(shouldclearmenu) clearlater = true;
    }
    else if(ret&G3D_ROLLOVER)
    {
        alias("guirollovername", name);
        alias("guirolloveraction", action);
    }
}

void guiimage(char *path, char *action, float *scale, int *overlaid, char *alt)
{
    if(!cgui) return;
    Texture *t = textureload(path, 0, true, false);
    if(t==notexture)
    {
        if(alt[0]) t = textureload(alt, 0, true, false);
        if(t==notexture) return;
    }
    int ret = cgui->image(t, *scale, *overlaid!=0);
    if(ret&G3D_UP)
    {
        if(*action)
        {
            updateLater.push_back(delayedUpdate());
            updateLater.back().schedule(std::string(action));
            if(shouldclearmenu) clearlater = true;
        }
    }
    else if(ret&G3D_ROLLOVER)
    {
        alias("guirolloverimgpath", path);
        alias("guirolloverimgaction", action);
    }
}

void guicolor(int *color)
{
    if(cgui) 
    {   
        defformatstring(desc)("0x%06X", *color);
        cgui->text(desc, *color, NULL);
    }
}

void guitextbox(char *text, int *width, int *height, int *color)
{
    if(cgui && text[0]) cgui->textbox(text, *width ? *width : 12, *height ? *height : 1, *color ? *color : 0xFFFFFF);
}

void guitext(char *name, char *icon)
{
    bool hideicon = !strcmp(icon, "0");
    if(cgui) cgui->text(name, !hideicon && icon[0] ? GUI_BUTTON_COLOR : GUI_TEXT_COLOR, hideicon ? NULL : (icon[0] ? icon : "info"));
}

void guititle(char *name)
{
    if(cgui) cgui->title(name, GUI_TITLE_COLOR);
}

void guitab(char *name)
{
    if(cgui) cgui->tab(name, GUI_TITLE_COLOR);
}

void guibar()
{
    if(cgui) cgui->separator();
}

void guistrut(float *strut, int *alt)
{
    if(cgui)
    {
        if(!*alt) cgui->pushlist();
        cgui->strut(*strut);
        if(!*alt) cgui->poplist();
    }
}

template<class T> static void updateval(const std::string& var, T val, const std::string& onchange)
{
    // try to lookup the variable in map too
    EngineVariable *ev = EngineVariables::get(var);
    if (!ev)
    {
        ev = new EngineVariable(var, val, true);
        EngineVariables::reg(var, ev); // when creating new, that means it should also get pushed into storage, and here we have to do it manually
        // registering into storage will also take care of further memory release
    }

    updateLater.push_back(delayedUpdate());
    updateLater.back().schedule(ev, val);
    if (onchange[0])
    {
        updateLater.push_back(delayedUpdate());
        updateLater.back().schedule(onchange);
    }
}

static int getval(char *var)
{
    if (!EngineVariables::get(std::string(var))) return 0;
    else
    {
        EngineVariable *ev = EngineVariables::get(std::string(var));
        switch (ev->getType()[0])
        {
            case 'I': return anyint(ev->getInteger()); break;
            case 'F': return (int)anyfloat(ev->getFloat()); break;
            case 'S': return 0; break;
        }
    }
    return 0;
}

static float getfval(char *var)
{
    if (!EngineVariables::get(std::string(var))) return 0;
    else
    {
        EngineVariable *ev = EngineVariables::get(std::string(var));
        switch (ev->getType()[0])
        {
            case 'I': return (float)anyint(ev->getInteger()); break;
            case 'F': return anyfloat(ev->getFloat()); break;
            case 'S': return 0; break;
        }
    }
    return 0;
}

static const char *getsval(char *var)
{
    if (!EngineVariables::get(std::string(var))) return "";
    else
    {
        EngineVariable *ev = EngineVariables::get(std::string(var));
        switch (ev->getType()[0])
        {
            case 'I': return intstr(anyint(ev->getInteger())); break;
            case 'F': return floatstr(anyfloat(ev->getFloat())); break;
            case 'S': return anystring(ev->getString()).c_str(); break;
        }
    }
    return "";
}

void guislider(char *var, int *min, int *max, char *onchange)
{
    if(!cgui) return;
    int oldval = getval(var), val = oldval, vmin = *max ? *min : getvarmin(var), vmax = *max ? *max : getvarmax(var);
    cgui->slider(val, vmin, vmax, GUI_TITLE_COLOR);
    if(val != oldval) updateval(var, val, onchange);
}

void guilistslider(char *var, char *list, char *onchange)
{
    if(!cgui) return;
    vector<int> vals;
    list += strspn(list, "\n\t ");
    while(*list)
    {
        vals.add(parseint(list));
        list += strcspn(list, "\n\t \0");
        list += strspn(list, "\n\t ");
    }
    if(vals.empty()) return;
    int val = getval(var), oldoffset = vals.length()-1, offset = oldoffset;
    loopv(vals) if(val <= vals[i]) { oldoffset = offset = i; break; }
    defformatstring(label)("%d", val);
    cgui->slider(offset, 0, vals.length()-1, GUI_TITLE_COLOR, label);
    if(offset != oldoffset) updateval(var, vals[offset], onchange);
}

void guinameslider(char *var, char *names, char *list, char *onchange)
{
    if(!cgui) return;
    vector<int> vals;
    list += strspn(list, "\n\t ");
    while(*list)
    {
        vals.add(parseint(list));
        list += strcspn(list, "\n\t \0");
        list += strspn(list, "\n\t ");
    }
    if(vals.empty()) return;
    int val = getval(var), oldoffset = vals.length()-1, offset = oldoffset;
    loopv(vals) if(val <= vals[i]) { oldoffset = offset = i; break; }
    char *label = indexlist(names, offset);
    cgui->slider(offset, 0, vals.length()-1, GUI_TITLE_COLOR, label);
    if(offset != oldoffset) updateval(var, vals[offset], onchange);
    delete[] label;
}

void guicheckbox(char *name, char *var, float *on, float *off, char *onchange)
{
    bool enabled = getfval(var)!=*off;
    if(cgui && cgui->button(name, GUI_BUTTON_COLOR, enabled ? "checkbox_on" : "checkbox_off")&G3D_UP)
    {
        updateval(var, enabled ? *off : (*on || *off ? *on : 1.0f), onchange);
    }
}

void guiradio(char *name, char *var, float *n, char *onchange)
{
    bool enabled = getfval(var)==*n;
    if(cgui && cgui->button(name, GUI_BUTTON_COLOR, enabled ? "radio_on" : "radio_off")&G3D_UP)
    {
        if(!enabled) updateval(var, *n, onchange);
    }
}

void guibitfield(char *name, char *var, int *mask, char *onchange)
{
    int val = getval(var);
    bool enabled = (val & *mask) != 0;
    if(cgui && cgui->button(name, GUI_BUTTON_COLOR, enabled ? "checkbox_on" : "checkbox_off")&G3D_UP)
    {
        updateval(var, enabled ? val & ~*mask : val | *mask, onchange);
    }
}

//-ve length indicates a wrapped text field of any (approx 260 chars) length, |length| is the field width
void guifield(char *var, int *maxlength, char *onchange, int *password) // INTENSITY: password
{   
    if(!cgui) return;
    const char *initval = getsval(var);
    char *result = cgui->field(var, GUI_BUTTON_COLOR, *maxlength ? *maxlength : 12, 0, initval, EDITORFOCUSED, password ? *password : false); // INTENSITY: password, and the default value before it - EDITORFOCUSED - also, as it is needed now
    if(result) updateval(var, result, onchange);
}

//-ve maxlength indicates a wrapped text field of any (approx 260 chars) length, |maxlength| is the field width
void guieditor(char *name, int *maxlength, int *height, int *mode)
{
    if(!cgui) return;
    cgui->field(name, GUI_BUTTON_COLOR, *maxlength ? *maxlength : 12, *height, NULL, *mode<=0 ? EDITORFOREVER : *mode);
    //returns a non-NULL pointer (the currentline) when the user commits, could then manipulate via text* commands
}

//-ve length indicates a wrapped text field of any (approx 260 chars) length, |length| is the field width
void guikeyfield(char *var, int *maxlength, char *onchange)
{
    if(!cgui) return;
    const char *initval = getsval(var);
    char *result = cgui->keyfield(var, GUI_BUTTON_COLOR, *maxlength ? *maxlength : -8, 0, initval);
    if(result) updateval(var, result, onchange);
}

//use text<action> to do more...


void guilist(char *contents)
{
    if(!cgui) return;
    cgui->pushlist();
    lua::engine.exec(contents);
    cgui->poplist();
}

void guialign(int *align, char *contents)
{
    if(!cgui) return;
    cgui->pushlist(clamp(*align, -1, 1));
    lua::engine.exec(contents);
    cgui->poplist();
}

void newgui(char *name, char *contents, char *header)
{
    menu *m = guis.access(name);
    if(!m)
    {
        name = newstring(name);
        m = &guis[name];
        m->name = name;
    }
    else
    {
        DELETEA(m->header);
        DELETEA(m->contents);
    }
    m->header = header && header[0] ? newstring(header) : NULL;
    m->contents = newstring(contents);
}

void guiservers()
{
    extern char *showservers(g3d_gui *cgui);
    if(cgui) 
    {
        char *command = showservers(cgui);
        if(command)
        {
            updateLater.push_back(delayedUpdate());
            updateLater.back().schedule(std::string(command));
            if(shouldclearmenu) clearlater = true;
        }
    }
}

struct change
{
    int type;
    const char *desc;

    change() {}
    change(int type, const char *desc) : type(type), desc(desc) {}
};
static vector<change> needsapply;

static struct applymenu : menu
{
    void gui(g3d_gui &g, bool firstpass)
    {
        if(guistack.empty()) return;
        g.start(menustart, 0.03f);
        g.text("the following settings have changed:", GUI_TEXT_COLOR, "info");
        loopv(needsapply) g.text(needsapply[i].desc, GUI_TEXT_COLOR, "info");
        g.separator();
        g.text("apply changes now?", GUI_TEXT_COLOR, "info");
        if(g.button("yes", GUI_BUTTON_COLOR, "action")&G3D_UP)
        {
            int changetypes = 0;
            loopv(needsapply) changetypes |= needsapply[i].type;
            if (changetypes & CHANGE_GFX)
            {
                updateLater.push_back(delayedUpdate());
                updateLater.back().schedule("Engine.resetGl()");
            }
            if (changetypes & CHANGE_SOUND)
            {
                updateLater.push_back(delayedUpdate());
                updateLater.back().schedule("Sound.reset()");
            }
            clearlater = true;
        }
        if(g.button("no", GUI_BUTTON_COLOR, "action")&G3D_UP)
            clearlater = true;
        g.end();
    }

    void clear()
    {
        menu::clear();
        needsapply.shrink(0);
    }
} applymenu;

static bool processingmenu = false;

void addchange(const char *desc, int type)
{
    if(!GETIV(applydialog)) return;
    loopv(needsapply) if(!strcmp(needsapply[i].desc, desc)) return;
    needsapply.add(change(type, desc));
    if(needsapply.length() && guistack.find(&applymenu) < 0)
        pushgui(&applymenu, processingmenu ? max(guistack.length()-1, 0) : -1);
}

void clearchanges(int type)
{
    loopv(needsapply)
    {
        if(needsapply[i].type&type)
        {
            needsapply[i].type &= ~type;
            if(!needsapply[i].type) needsapply.remove(i--);
        }
    }
    if(needsapply.empty()) removegui(&applymenu);
}

void menuprocess()
{
    processingmenu = true;
    int wasmain = GETIV(mainmenu), level = guistack.length();
    for (unsigned int i = 0; i < updateLater.size(); i++) updateLater[0].run();
    updateLater.clear();
    
    if(wasmain > GETIV(mainmenu) || clearlater)
    {
        if(wasmain > GETIV(mainmenu) || level==guistack.length()) 
        {
            loopvrev(guistack)
            {
                menu *m = guistack[i];
                if(m->onclear) 
                {
                    char *action = m->onclear;
                    m->onclear = NULL;
                    lua::engine.exec(action);
                    delete[] action;
                }
            }
            cleargui(level); 
        }
        clearlater = false;
    }
    if(GETIV(mainmenu) && !isconnected(true) && guistack.empty()) showgui("main");
    processingmenu = false;
}

void clearmainmenu()
{
    if(GETIV(mainmenu) && (isconnected() || haslocalclients()))
    {
        SETV(mainmenu, 0);
        if(!processingmenu) cleargui();
    }
}

void g3d_mainmenu()
{
    if(!guistack.empty()) 
    {   
        if(!GETIV(mainmenu) && !GETIV(gui2d) && camera1->o.dist(menupos) > GETIV(menuautoclose)) cleargui();
        else g3d_addgui(guistack.last(), menupos, GUI_2D | GUI_FOLLOW);
    }
}

