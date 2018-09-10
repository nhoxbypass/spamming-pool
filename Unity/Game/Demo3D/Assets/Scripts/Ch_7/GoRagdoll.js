#pragma strict

private var childRigidBodies : Rigidbody[];
private var childColliders : Collider[];
public var invincible : boolean = false;

function Start () 
{
	childRigidBodies = gameObject.GetComponentsInChildren.<Rigidbody>();
	childColliders = gameObject.GetComponentsInChildren.<Collider>();
}

function GotoRagdoll ()
{ 
	if (!invincible) {
		if (childRigidBodies != null) {
    		for (var childRigidBody : Rigidbody in childRigidBodies) {
        		childRigidBody.isKinematic = false;
        	}
    	}
     	if (childColliders != null) {
       		for (var childCollider : Collider in childColliders) {
            	childCollider.enabled = true;
        	}
     	}  
                        
     	gameObject.GetComponent.<Collider>().enabled = false;
     	gameObject.GetComponent.<Rigidbody>().isKinematic = true;
     	gameObject.GetComponent(Animator).enabled = false;
     	gameObject.GetComponent(ThirdPersonCharacter).enabled = false;
     	gameObject.GetComponent(ThirdPersonUserControl).enabled = false;
	}
}

function ExitRagdoll () {
     if (childRigidBodies != null) {
     	for (var childRigidBody : Rigidbody in childRigidBodies) {
        	childRigidBody.isKinematic = true;
        }
     }
     if (childColliders != null) {
        for (var childCollider : Collider in childColliders) {
            childCollider.enabled = false;
        }
     }  
                        
     gameObject.GetComponent.<Collider>().enabled = true;
     gameObject.GetComponent.<Rigidbody>().isKinematic = false;
     gameObject.GetComponent(Animator).enabled = true;
     gameObject.GetComponent(ThirdPersonCharacter).enabled = true;
     gameObject.GetComponent(ThirdPersonUserControl).enabled = true;
}

function Invincibility () {
	invincible = !invincible;
}
