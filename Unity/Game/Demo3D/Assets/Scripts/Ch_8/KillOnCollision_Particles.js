#pragma strict

function OnCollisionEnter(other : Collision) {
	if (other.gameObject.name == "Third Person Character Ragdoll") {
        other.gameObject.GetComponent(GoRagdoll).GotoRagdoll();
    }
}

function OnParticleCollision(other : GameObject)
{
    if (other.gameObject.name == "Third Person Character Ragdoll") {
        other.gameObject.GetComponent(GoRagdoll).GotoRagdoll();
    }
}