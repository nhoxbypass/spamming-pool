#pragma strict

public var WalkX:float = 0;
public var WalkZ:float = 0;

function OnAnimatorMove()
{
	var animator : Animator = GetComponent(Animator);
        
    if (animator) {
    	var newPosition:Vector3 = transform.position;
                
        newPosition.x += WalkX * Time.deltaTime;
        newPosition.z += WalkZ * Time.deltaTime;
                
        transform.position = newPosition;
     }
}
