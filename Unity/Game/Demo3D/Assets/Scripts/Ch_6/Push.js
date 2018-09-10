#pragma strict

public var aForce : float = 50; 

function OnMouseDown () {
       GetComponent.<Rigidbody>().AddForce (Vector3.forward * aForce);
}