#pragma strict

private var toolbarSelectedButton = 0;
private var toolbarButtonNames : String[] = ["TB Button 1", "TB Button 2", "TB Button 3"];

function OnGUI () {
	//if (GUI.Button (Rect (25, 260, 100, 30), "Click Me")) {
	if (GUI.Button (Rect (Screen.width - 100, 0, 100, 30), "Click Me")) {
    	Debug.Log("Button has been clicked");
    }
        
    //if (GUI.RepeatButton (Rect (25, 300, 100, 30), "Click and Hold")) {
    if (GUI.RepeatButton (Rect (Screen.width - 100, 50, 100, 30), "Click and Hold")) {
        Debug.Log("The repeat button is being pressed");
    }
    toolbarSelectedButton = GUI.Toolbar (Rect (25, 25, 250, 30), toolbarSelectedButton, toolbarButtonNames);
}
