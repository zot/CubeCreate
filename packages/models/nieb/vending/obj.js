Model.objLoad("model.obj");

Model.objSkin("base", "base.jpg");
Model.objSkin("label", "label.jpg", "masks.png");
Model.objSkin("button", "button.jpg", "masks.png");
Model.objSkin("chrome", "base.jpg", "chrome_masks.png", 0.4, 0.2);

Model.scale(1000);
Model.collide(1);
Model.ambient(125);
Model.spec(45);
Model.cullface(1);
