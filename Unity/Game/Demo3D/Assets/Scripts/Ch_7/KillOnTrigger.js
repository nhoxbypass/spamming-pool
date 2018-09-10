#pragma strict

function OnTriggerEnter(other : Collider) {
	if (other.gameObject.name == "Third Person Character Ragdoll") {
    	other.gameObject.GetComponent(GoRagdoll).GotoRagdoll();
    }
}
