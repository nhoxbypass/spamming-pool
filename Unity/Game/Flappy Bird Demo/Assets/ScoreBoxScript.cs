using UnityEngine;
using System.Collections;

public class ScoreBoxScript : MonoBehaviour {

	// Use this for initialization
	void Start () {
	
	}
	
	// Update is called once per frame
	void Update () {
	
	}

	void OnTriggerEnter2D(Collider2D coll)
	{
		if (coll.tag == "PlayerBird") {
			Score.AddPoint ();
			//Debug.Log ("Them diem");
			//this.gameObject.SetActive (false);
		}
	}
}
