using UnityEngine;
using System.Collections;

public class CameraTracker : MonoBehaviour {

	Transform player;

	float offsetX;

	// Use this for initialization
	void Start () {
		
		GameObject player_go = GameObject.FindGameObjectWithTag ("Player");

		if (player_go == null) {
			Debug.LogError ("Khong the tim thay object voi tag la 'Player'");
			return;
		}

		player = player_go.transform;
	
		offsetX = transform.position.x - player.position.x;
	}
	
	// Update is called once per frame
	void Update () {
		if (player != null) {
			Vector3 vect = transform.position;

			vect.x = offsetX + player.position.x;

			transform.position = vect; 	 	
		}
	}

}
