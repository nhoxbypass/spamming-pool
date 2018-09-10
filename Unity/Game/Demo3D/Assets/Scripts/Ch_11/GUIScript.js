#pragma strict

public var fadeDuration : float = 3;
//var guiStyle : GUIStyle;
var myGuiSkin : GUISkin;

// display a simple label
//function OnGUI() {
//	GUI.Label(Rect(0, 0, 125, 25), "A label displays text");
//}

function OnGUI() {
	var fadingColor : Color;        
	fadingColor = GUI.contentColor; 
	var fading : float = (Time.time/fadeDuration);
	GUI.contentColor.a = Mathf.Lerp(1, 0, fading);
	GUI.skin = myGuiSkin;
        
	//GUI.Label(Rect(0, 0, 250, 25), "Press C to crouch or Space to jump");      
	//GUI.Box(Rect (0, 75, 100, 50), "This is a box");
        
	//GUI.Label(Rect(Screen.width/2, Screen.height/2, 250, 25), "Press C to crouch or Space to jump");
	//GUI.Label(Rect(Screen.width/2 - 125, Screen.height/2 - 12.5, 250, 25), "Press C to crouch or Space to jump");
	//GUI.Label(Rect(Screen.width/2 - 125, Screen.height/2 - 12.5, 250, 25), "Press C to crouch or Space to jump", guiStyle);
	GUI.Label(Rect(Screen.width/2 - 125, Screen.height/2 - 12.5, 250, 25), "Press C to crouch or Space to jump");
}
