#pragma strict

public var projectile : GameObject;
public var force : float = 25;
public var frequency : float = 2.0;
private var nextLaunch : float = 0.0;

function Start () {
	frequency = Random.Range(0.5, 2.5);
}

function Update () {
    if (Time.time > nextLaunch) {
    	nextLaunch = Time.time + frequency;
        var projectileInstance : GameObject = Instantiate(projectile, 
                transform.position, transform.rotation);
        projectileInstance.GetComponent.<Rigidbody>().AddForce (projectileInstance.transform.forward 
                * force, ForceMode.Impulse);
        Destroy(projectileInstance, 2);
    }
}
