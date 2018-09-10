#pragma strict

var cameraTarget : Transform; 

function Update () {
	transform.LookAt(cameraTarget);
}