#pragma strict

// Declare the variables to contain the color values.
private var red : float;
private var green : float;
private var blue : float;
private var alpha : float;
public var waitTime : float = 5f;
private var sphereCollider : Collider;

function Start()
{       
// On Start, set a random color for the sphere material.
        NewColor();
        
// Print the random color values to the Console.
        print(gameObject.GetComponent.<Renderer>().material.color);
// Assign the sphere's collider component to the sphereCollider variable.
        sphereCollider = GetComponent(Collider);
}

// Generate a random value between 0.000 and 1.000.
function RandomColorValue() {
        var randomValue : float;
        randomValue = Random.Range(0.000, 1.000);
        return randomValue;
}

function Update()
{
        waitTime -= Time.deltaTime;
        if (waitTime < 0.0f) {
            gameObject.GetComponent.<Renderer>().material.color = Color.blue;
            // Destroy(gameObject);
        }
        
        if(Input.GetKey(KeyCode.N)) {
            NewColor();
        }
        
        if(Input.GetKey(KeyCode.C)) {
            sphereCollider.enabled = !sphereCollider.enabled;
        }   

		if(Input.GetKey(KeyCode.D)) {
        	Destroy(gameObject);
		}
}

function NewColor() {
        red = RandomColorValue();
        green = RandomColorValue();
        blue = RandomColorValue();
        alpha = RandomColorValue();
        gameObject.GetComponent.<Renderer>().material.color = Color(red, green, blue, alpha);
        waitTime = 5;
}

function OnMouseDown() {
        NewColor();
}