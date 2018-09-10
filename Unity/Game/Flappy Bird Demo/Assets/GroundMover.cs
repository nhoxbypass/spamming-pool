using UnityEngine;
using System.Collections;

public class GroundMover : MonoBehaviour {

	float speed = 0.3f;

	void FixedUpdate () {
		Vector3 vect = transform.position;
		vect.x += speed * Time.deltaTime;
		transform.position = vect;
	}
}
