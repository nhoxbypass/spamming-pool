#pragma strict

public var rayLength : float = 2;

function Update () {
	// Display the ray being cast
	Debug.DrawRay(transform.position + Vector3(0, 0.5, 0), transform.forward * rayLength, Color.white);

	var hit : RaycastHit;
    if(Physics.Raycast(transform.position + Vector3(0, 0.5, 0), transform.forward, hit)) {
    	print ("Collided with game object " + 
        hit.collider.gameObject.name);
        //Destroy the object that the ray collides with
        Destroy(hit.collider.gameObject);
    }
}

/*
// Use tags to identify and destroy only Enemy spheres
function Update () {
	// Display the ray being cast
	Debug.DrawRay(transform.position + Vector3(0, 0.5, 0), transform.forward * rayLength, Color.white);

	var hit : RaycastHit;
    if(Physics.Raycast(transform.position + Vector3(0, 0.5, 0), transform.forward, hit)) {
    	print ("Collided with game object " + 
        hit.collider.gameObject.name);
        
        //Destroy the object that the ray collides with if it has an Enemy tag
        if (hit.collider.gameObject.tag == ("Enemy")) {
        	Destroy(hit.collider.gameObject);
        }       
    }
}
*/

/*
// Using Layers. Select Obstacles in the editor Hierarchy then in the Inspector select Ignore Raycast from the Layers dropdown menu.
function Update () {
    var hit : RaycastHit;
    if(Physics.Raycast(transform.position+ Vector3(0, 0.5, 0), transform.forward, hit)) {
    	print ("Collided with game object " + 
        hit.collider.gameObject.name);
        
        Destroy(hit.collider.gameObject);
        }
}
*/