#pragma strict

public var newSphere : GameObject;

function Start () {

}

function Update () {
	if(Input.GetKey(KeyCode.Space)) {
		var instance : GameObject = Instantiate(newSphere);
    }
}