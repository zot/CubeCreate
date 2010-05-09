Model.objLoad("model.obj");

Model.objSkin("base", "../base.jpg");
Model.objSkin("screen", "screen.jpg", "../masks.png", 0.3, 0.1);

Model.scale(1000);
Model.collide(1);
Model.ambient(125);
Model.spec(10);
Model.cullface(1);
