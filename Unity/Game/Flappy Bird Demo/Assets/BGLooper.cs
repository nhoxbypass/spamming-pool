using UnityEngine;
using System.Collections;

public class BGLooper : MonoBehaviour {

	private int numberOfBG = 6;
	private float pipeMaxY = 1.33f;
	private float pipeMinY = 0.47f;

	// Use this for initialization
	void Start () {
		pipeInit ();
	}
	
	void OnTriggerEnter2D(Collider2D col)
	{
		Debug.Log ("Triggered " + col.name);

		float widthOfObject = ((BoxCollider2D)col).size.x;

		Vector3 vect = col.transform.position;

		vect.x += widthOfObject * numberOfBG;

		col.transform.position = vect;

		if(col.tag == "Pipe")
		{
		}
	}

	void pipeInit()
	{
		GameObject[] pipes = GameObject.FindGameObjectsWithTag ("Pipe");

		foreach (GameObject pipe in pipes) {
			float y = Random.Range (pipeMinY, pipeMaxY);

			Vector3 vect = pipe.transform.position;
			vect.y = y;
			pipe.transform.position = vect;
		}
	}
}
