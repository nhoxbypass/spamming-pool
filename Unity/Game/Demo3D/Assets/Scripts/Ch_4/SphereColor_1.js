#pragma strict

// Declare the variables to contain the color values.
private var red : float;
private var green : float;
private var blue : float;
private var alpha : float;

public var waitTime : float = 5f;

function Start () {
// Turn the sphere red
//	gameObject.renderer.material.color = Color.red;
	
// On Start, set the color property values by calling a random-number generating function.
    red = RandomColorValue();
    green = RandomColorValue();
    blue = RandomColorValue();
    alpha = RandomColorValue();
    gameObject.GetComponent.<Renderer>().material.color = Color(red, green, blue, alpha);
        
// Print the random color values to the Console.
    print(gameObject.GetComponent.<Renderer>().material.color);

}

// Generate a random value between 0.000 and 1.000.
function RandomColorValue() {
     var randomValue : float;
     randomValue = Random.Range(0.000, 1.000);
     return randomValue;
}


function Update () {
     waitTime -= Time.deltaTime;
     if (waitTime < 0.0f) {
        gameObject.GetComponent.<Renderer>().material.color = Color.blue;
     }
     
     if(Input.GetKey(KeyCode.N)) {
        red = RandomColorValue();
        green = RandomColorValue();
        blue = RandomColorValue();
        alpha = RandomColorValue();
        gameObject.GetComponent.<Renderer>().material.color = Color(red, green, blue, alpha);
        waitTime = 5;
      }       
    

}