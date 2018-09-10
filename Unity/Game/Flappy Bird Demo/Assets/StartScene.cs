using UnityEngine;
using System.Collections;

public class StartScene : MonoBehaviour {

	static bool seen = false;
	// Use this for initialization
	void Start () {
		if (!seen) {
			this.GetComponent<SpriteRenderer> ().enabled = true;
			Time.timeScale = 0;
		}
		seen = true;
	}
	
	// Update is called once per frame
	void Update () {

		if(Time.timeScale == 0 && (Input.GetKeyDown(KeyCode.Space) || Input.GetMouseButtonDown(0)))
		{
			Time.timeScale = 1;
			this.GetComponent<SpriteRenderer> ().enabled = false;
		}
	}
}
