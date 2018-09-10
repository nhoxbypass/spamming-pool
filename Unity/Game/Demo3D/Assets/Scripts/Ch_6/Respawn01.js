#pragma strict

public var respawnPosition: Transform;

function OnTriggerEnter(other : Collider) {
	other.gameObject.transform.position = respawnPosition.position;
}
