#pragma strict

var textFieldString : String = "A one-line text field";
var textAreaString : String = "A multi-line text field";

function OnGUI () {
	textFieldString = GUI.TextField (Rect (0, 130, 120, 30), textFieldString);
    textAreaString = GUI.TextArea (Rect (0, 175, 75, 75), textAreaString);
}