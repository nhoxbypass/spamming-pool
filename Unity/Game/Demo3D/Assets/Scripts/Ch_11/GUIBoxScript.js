#pragma strict 

public var boxTexture : Texture2D; 

// a simple box
//function OnGUI() {
//        GUI.Box(Rect (0, 75, 100, 50), "This is a box");
//}

function OnGUI() {
        GUI.Box(Rect (0, 75, 100, 50), boxTexture);
}
