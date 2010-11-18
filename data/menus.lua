-- Standard menu definitions
-- do not modify

-- Cubescript ugliness to replace
CV:run([[
	bind ESCAPE [
		menu_key_click_trigger
		if (cleargui 1) [] [
			save_mouse_pos // Useful for New Light GUI and so forth.
			showgui main
		]
	]
]])

-- Main menu - has two forms, for logging into the master, or for entering an instance

function setup_main_menu()
	if CV.logged_into_master == 0 then
		GUI.new("main", [[
			GUI.button("log in...", [=[ show_login() ]=], "menu")
			GUI.bar()
			GUI.button("plugins...", [=[ GUI.show("plugins") ]=])
			GUI.button("options...", [=[ GUI.show("options") ]=])
			GUI.button("help...", [=[ GUI.show("help") ]=])
			GUI.button("quit", [=[ CV:run("quit") ]=], "exit")
		]])
	end
	if CV.logged_into_master == 1 then
		GUI.new("main", [[
			if CV.have_master ~= 0 then
				GUI.button("^f2connect to lobby...^f~", "CV:run('connect_to_lobby')")
				GUI.bar()
				GUI.button("connect to selected...", "CV:run('connect_to_selected_instance')")
			end
			GUI.button("local connection...", "CV:run('connect 127.0.0.1 28787')")
			GUI.button("manual connection...", "GUI.show('manual_connect')")
			GUI.bar()
			GUI.button("plugins...", [=[ GUI.show("plugins") ]=])
			GUI.button("options...", [=[ GUI.show("options") ]=])
			GUI.button("special...", [=[ GUI.show("special") ]=])
			GUI.button("help...", [=[ GUI.show("help") ]=])
			GUI.button("quit", [=[ CV:run("quit") ]=], "exit")
		]])
	end
end

setup_main_menu()
--[[
setup_main_menu = [
			guibutton "manual connection..." "showgui manual_connect"
			guibar
			if ( (& (= $can_edit 1) (isconnected)) ) [
				if (= (private_edit_mode) 0) [
					guibutton "request private edit mode..." "request_private_edit_mode"
				] [
					guitext "(in private edit mode)"
				]
				guibutton "restart map..." "showgui restart_map"
				guibutton "upload map..." "showgui upload"
				guibutton "editing commands..." "showgui editing"
				guibutton "export entities..." "showgui exportentities"
				guibar
			]
			guibutton "plugins..."		"showgui plugins"
]

setup_main_menu
]]
