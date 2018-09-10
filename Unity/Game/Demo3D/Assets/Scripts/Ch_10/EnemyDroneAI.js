#pragma strict

public var playerTransform : Transform;
public var speed : float = 3.0f;

private var drone : Vector3;
private var target : Vector3;
private var distance : float;

function Update () {
	if (playerTransform.position.z > 128 && playerTransform.position.z < 145) {
    	transform.LookAt(playerTransform);

       	drone = transform.position;
        target = playerTransform.position + Vector3(0, 0.6, 0);
        distance = speed * Time.deltaTime;
        transform.position = Vector3.MoveTowards(drone, target, distance);
    }
}
