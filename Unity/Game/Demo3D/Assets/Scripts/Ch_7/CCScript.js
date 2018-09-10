#pragma strict

private var contr : CharacterController;
private var moveVector : Vector3 = Vector3.zero;
public var speed : float = 10.0f;
public var pushPower : float = 2.0;

function Start () {
	contr = gameObject.GetComponent.<CharacterController>();
}

function Update () {
    moveVector.x = Input.GetAxis("Horizontal") * speed;
    moveVector.z = Input.GetAxis("Vertical") * speed;
    contr.Move(moveVector * Time.deltaTime);
}

// for the Box Pile to respond to impact from the Cube:
/*
function OnControllerColliderHit (hit : ControllerColliderHit) {
    var body : Rigidbody = hit.collider.attachedRigidbody;

    if (body == null || body.isKinematic)
    	return;
    if (hit.moveDirection.y < -0.3) 
        return;
                
    var pushDir : Vector3 = Vector3 (hit.moveDirection.x, 0, 
    hit.moveDirection.z);
    body.velocity = pushDir * pushPower;
}
*/
