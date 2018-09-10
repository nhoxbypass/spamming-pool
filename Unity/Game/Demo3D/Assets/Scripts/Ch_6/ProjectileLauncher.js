#pragma strict

public var projectile : GameObject;
public var cameraSpeed : float = 5;

function Update () {
	var horiz : float = Input.GetAxis("Horizontal") * Time.deltaTime * cameraSpeed;
    var verti : float = Input.GetAxis("Vertical") * Time.deltaTime * cameraSpeed;
        
    transform.Translate(horiz, verti, 0);
        
    if(Input.GetButtonUp("Fire1")) {
    	var projectileInstance : GameObject = Instantiate(projectile, transform.position, transform.rotation);
        Destroy(projectileInstance, 2);
    }
}