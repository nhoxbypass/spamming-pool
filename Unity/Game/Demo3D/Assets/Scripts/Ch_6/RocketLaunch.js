#pragma strict

public var rocket : GameObject;

function Update () {
    if(Input.GetButtonUp("Fire1")) {
    	var rocketInstance : GameObject = Instantiate(rocket);
    }
	Destroy(rocketInstance, 2); 
}