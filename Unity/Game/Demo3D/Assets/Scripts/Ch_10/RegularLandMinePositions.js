#pragma strict

public var prefab : GameObject;

public var xPos : float = -3.5;
public var yPos : float = 8.5;
public var zPos : float = 55.0;

public var numberWidth : int = 8;
public var numberLength : int = 34;

function Start () {
	for (var i : int = 0; i < numberLength; i++) {
	// for (var i : int = 0; i < numberLength/2; i++)                
    	for (var j : int = 0; j < numberWidth; j++) {  
        	var position: Vector3 = Vector3(xPos, yPos, zPos);
            Instantiate(prefab, position, Quaternion.identity);
            xPos++;
        }
        xPos = -3.5;
        yPos = yPos + 0.05;
        zPos = zPos + 1; 
        // zPos = zPos + 2;       
    }
}