#pragma strict

public var playerTransform : Transform;
public var rateIncrease : float = 1;

private var rate : float;

function Update () {
	if (playerTransform.position.z > 109 && playerTransform.position.z < 126) {
    	rate = playerTransform.position.z - 104;
        gameObject.GetComponent.<ParticleSystem>().startSpeed = rate * rateIncrease;
    }
}