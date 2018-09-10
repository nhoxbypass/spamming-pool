#pragma strict

public var prefab : GameObject;
public var amount : int = 10;

function Start () {
	for (var i : int = 0; i < amount; i++) {
    	var position: Vector3 = Vector3(5, Random.Range(9.0, 11.0), 
        Random.Range(44, 53));
        Instantiate(prefab, position, Quaternion.Euler(0, 0, 90));
    }
}