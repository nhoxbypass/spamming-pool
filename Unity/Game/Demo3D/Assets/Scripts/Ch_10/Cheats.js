#pragma strict

public var player : GameObject;
private var inputKey : String; 
private var relocationPoint : Vector3;

function Start () {
	//Could use hash code here
 	player = GameObject.FindWithTag("Player");
}

function Update () {
	CheckInput();
}

function CheckInput () {
	if(Input.GetKeyDown(KeyCode.Alpha1)) {
		relocationPoint = Vector3(0, 9, 18);
		//Debug.Log(KeyCode.Alpha1);
		
		//if (player != null) {
		//player.transform.position = Vector3(0, 9, 18);
		//player.gameObject.GetComponent(GoRagdoll).ExitRagdoll();
		//}
	RelocatePlayer();
	}	
	else if(Input.GetKeyDown(KeyCode.Alpha2)) {
		relocationPoint = Vector3(0, 9, 33.5);
		RelocatePlayer();
	}
	else if(Input.GetKeyDown(KeyCode.Alpha3)) {
		relocationPoint = Vector3(0, 9, 43);
		RelocatePlayer();
	}
	else if(Input.GetKeyDown(KeyCode.Alpha4)) {
		relocationPoint = Vector3(0, 9, 54);
		RelocatePlayer();
	}
	else if(Input.GetKeyDown(KeyCode.Alpha5)) {
		relocationPoint = Vector3(0, 9, 90);
		RelocatePlayer();
	}
	else if(Input.GetKeyDown(KeyCode.Alpha6)) {
		relocationPoint = Vector3(0, 9, 108);
		RelocatePlayer();
	}
	else if(Input.GetKeyDown(KeyCode.Alpha7)) {
		relocationPoint = Vector3(0, 9, 127);
		RelocatePlayer();
	}
	else if(Input.GetKeyDown(KeyCode.Alpha8)) {
		relocationPoint = Vector3(0, 9, 146);
		RelocatePlayer();
	}
	else if(Input.GetKeyDown(KeyCode.Alpha0)) {
		player.gameObject.GetComponent(GoRagdoll).Invincibility();
	}
}

function RelocatePlayer(){
			if (player != null) {
		player.transform.position = relocationPoint;
		player.gameObject.GetComponent(GoRagdoll).ExitRagdoll();
	}
}
