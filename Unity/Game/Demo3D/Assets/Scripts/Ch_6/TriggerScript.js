#pragma strict

public var triggerForce : float = 10;

function OnTriggerEnter() {
	// Display OnTriggerEnter message in Console
    Debug.Log("OnTriggerEnter");
    
    // Trigger game object disappears
    var triggerRenderer : Renderer = GetComponent(Renderer);
    triggerRenderer.enabled = false;
    
    // toggle the boolean value of enabled
    //triggerRenderer.enabled = !triggerRenderer.enabled;
}

//function OnTriggerStay() {
//    Debug.Log("OnTriggerStay");
//}


function OnTriggerStay(other : Collider) {
	Debug.Log("OnTriggerStay");
    // apply an upward force to the sphere while it is in the trigger volume
    other.GetComponent.<Rigidbody>().AddForce(Vector3.up * triggerForce);
}


function OnTriggerExit() {
    Debug.Log("OnTriggerExit");
    
    // Trigger game object reappears
    var triggerRenderer : Renderer = GetComponent(Renderer);
    triggerRenderer.enabled = !triggerRenderer.enabled;
}