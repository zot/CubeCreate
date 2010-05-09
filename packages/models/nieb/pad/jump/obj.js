Model.objLoad("../model.obj");

Model.objSkin("base", "../base.jpg", "../base_masks.png", 0.1, 0.0);
Model.objBumpmap("base", "../base_normal.png");
Model.objSkin("light", "light.jpg", "../light_masks.png", 0.2, 0.1);
Model.objBumpmap("light", "../light_normal.png");

Model.scale(1000);
Model.collide(1);
Model.ambient(125);
Model.spec(50);
Model.cullface(1);
