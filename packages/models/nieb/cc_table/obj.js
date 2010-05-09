Model.objLoad("model.obj");

Model.objSkin("base", "base.jpg", "masks.png", 0.2, 0.1);

Model.scale(1000);
Model.collide(0);
Model.ambient(100);
Model.spec(125);
Model.cullface(1);
