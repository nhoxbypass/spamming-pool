#pragma strict

public var line : LineRenderer;
public var sparks : GameObject;
public var victim : GameObject;
        
function Start () {
	victim = GameObject.Find("Third Person Character Ragdoll");
	//sparks = GameObject.Find("Flare");
	line = gameObject.GetComponent.<LineRenderer>();
	
	//optional setting laser colors from the script
	//line.material = new Material (Shader.Find("Particles/Additive"));
    //line.SetColors(Color.green, Color.blue);
}

function Update () {
	ShowLaser();
}

function ShowLaser () {
    var ray : Ray = Ray(transform.position, -transform.up);
    var hit : RaycastHit;
    
    line.SetPosition(0, ray.origin);
    if(Physics.Raycast(ray, hit, 50)) {
    	line.SetPosition(1, hit.point);
    	if (hit.collider == victim.GetComponent.<Collider>()) {
        	victim.GetComponent(GoRagdoll).GotoRagdoll();
        }        
    	 sparks.transform.position = hit.point;
    }  else {       
        line.SetPosition(1, ray.GetPoint(50)); 
    }
}