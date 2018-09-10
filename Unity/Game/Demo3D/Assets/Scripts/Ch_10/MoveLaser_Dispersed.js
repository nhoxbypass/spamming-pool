#pragma strict

public var speed : float = 1;
public var offset : float;

function Start () {
	offset = transform.position.x - 0.2;
	speed = Random.Range(1.0, 3.0);
}

function Update () {
    transform.position = Vector3(Mathf.PingPong(Time.time * speed, 8) + offset, transform.position.y, transform.position.z);
}