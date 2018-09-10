#pragma strict

public var spinSpeed : float = 50;

function Update () {
	transform.Rotate(Vector3.up * spinSpeed * Time.deltaTime);
}