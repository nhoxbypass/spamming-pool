#pragma strict

private var red : float;
private var green : float;
private var blue : float;
private var color : Color;

// change the color of the sphere on collision
function OnCollisionEnter() {
        Debug.Log("OnCollisionEnter");
        color = GetRandomColor();
        gameObject.GetComponent.<Renderer>().material.color = color;
}

/*
// change the color of the cube on collision
function OnCollisionEnter(other : Collision) {
        Debug.Log("OnCollisionEnter");
        color = GetRandomColor();
        other.gameObject.renderer.material.color = color;
}
*/
    
function OnCollisionStay() {
        Debug.Log("OnCollisionStay");
}
        
function OnCollisionExit() {
        Debug.Log("OnCollisionExit");
        color = GetRandomColor();
        gameObject.GetComponent.<Renderer>().material.color = color;
}
        
function RandomColorValue() {
        var randomValue : float;
        randomValue = Random.Range(0.000, 1.000);
        return randomValue;
}
        
function GetRandomColor() {
        red = RandomColorValue();
        green = RandomColorValue();
        blue = RandomColorValue();
        color = Color(red, green, blue);
        return color;
}