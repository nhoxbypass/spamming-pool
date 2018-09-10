#pragma strict

public var prefab : GameObject;
public var amount : int = 10;

function Start () {
	for (var i : int = 0; i < amount; i++) {
    	var position: Vector3 = Vector3(Random.Range(-3.5, 3.5), 
        	Random.Range(8.5, 9.0), Random.Range(55, 89));
        Instantiate(prefab, position, Quaternion.identity);
    }
} 