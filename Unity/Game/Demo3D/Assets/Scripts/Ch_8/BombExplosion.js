#pragma strict

public var victim : GameObject;
public var prefab : GameObject;
 
function Start () {
	victim = GameObject.Find("Third Person Character Ragdoll");
}

function OnCollisionEnter (collision : Collision) {
    if (collision.gameObject.name == "Third Person Character Ragdoll") {
    	Explosion();
    }
}

function Explosion () {
     victim.GetComponent(GoRagdoll).GotoRagdoll();
     Instantiate (prefab, transform.position, Quaternion.identity);
     Destroy(gameObject);
}
