#pragma strict

public var aForce : float = 500;
private var redColor : Color = Color (1, 0, 0);
private var greenColor : Color = Color (0, 1, 0);

function FixedUpdate () {
	GetComponent.<Rigidbody>().AddForce (Vector3.forward * aForce);
}

function OnCollisionEnter(other : Collision) {
	var checkColor : Color = other.gameObject.GetComponent.<Renderer>().material.color;
     
	if (checkColor == greenColor) {
    	other.gameObject.GetComponent.<Renderer>().material.color = redColor;
    }  else {
        other.gameObject.GetComponent.<Renderer>().material.color = greenColor;
    }
}
