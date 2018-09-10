#pragma strict

function OnCollisionEnter() {
	var cameraScript : PointCamera = GameObject.Find("Main Camera").GetComponent(PointCamera);
    cameraScript.cameraTarget = GameObject.Find("Cube").transform;
}