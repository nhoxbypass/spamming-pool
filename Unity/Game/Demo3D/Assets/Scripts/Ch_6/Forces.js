#pragma strict

public var aForce : float = 5; 

/*
function FixedUpdate () {
	// apply a force to the right
	//rigidbody.AddForce (Vector3.right * aForce);
	
	// apply torque 
	rigidbody.AddTorque (Vector3.right * aForce);
}
*/

function OnMouseDown () {
	// apply torque with mouse
    //rigidbody.AddTorque (Vector3.forward * aForce);
    
    // apply force with mouse
    GetComponent.<Rigidbody>().AddForce (Vector3.forward * aForce);
}
