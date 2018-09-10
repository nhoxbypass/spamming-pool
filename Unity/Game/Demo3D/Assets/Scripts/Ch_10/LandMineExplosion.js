#pragma strict

public var victim : GameObject;
public var explosionPrefab : GameObject;
 
function Start () {
	victim = GameObject.FindWithTag("Player");
}

function OnTriggerEnter (collider : Collider) {         
    if (collider.gameObject == victim) {
    	Explosion();
    }                                
}

function Explosion () {
     victim.GetComponent(GoRagdoll).GotoRagdoll();
     Instantiate (explosionPrefab, transform.position, Quaternion.identity);
     Destroy(gameObject);
}