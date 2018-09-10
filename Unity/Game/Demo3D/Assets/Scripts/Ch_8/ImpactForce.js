#pragma strict

function Start () {
	Invoke ("ImpactForce", 0.75);
}

function ImpactForce () {
	var colliders : Collider[] = Physics.OverlapSphere(transform.position - Vector3(0, 4, 0), 10);
        
    for(var cldr : Collider in colliders) {
    	if(cldr.GetComponent.<Rigidbody>() == null) continue;
    	cldr.GetComponent.<Rigidbody>().AddExplosionForce(10, transform.position - Vector3(0, 4, 0), 10, 0, ForceMode.Impulse);
    }
}
