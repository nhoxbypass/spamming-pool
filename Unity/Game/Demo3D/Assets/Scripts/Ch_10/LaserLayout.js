#pragma strict

public var prefab : GameObject;

public var zPos : float = 91.0;
public var numberLength : int = 16;

function Start () {
	for (var i : int = 0; i < numberLength * 2; i++) {                
    	var position: Vector3 = Vector3(-3.8, 12, zPos);
        Instantiate(prefab, position, Quaternion.identity);     
        zPos = zPos + 0.5;
    }
}