using UnityEngine;
using System.Collections;
using UnityEngine.UI;

public class Score : MonoBehaviour {

	static int score = 0;
	static int highScore = 0;
	Text scoreText;
	BirdMovement bird;
	static Score instance;

	// Use this for initialization
	void Start () {
		instance = this;
		score = 0;

		GameObject player = GameObject.FindGameObjectWithTag ("PlayerBird");
		if (player == null) {
			Debug .Log("Khong the tim thay object voi tag la PlayerBird");
			return;
		}

		bird = player.GetComponent<BirdMovement>();
		highScore = PlayerPrefs.GetInt ("highscore", 0);
		scoreText = (Text)this.GetComponent<Text>();
	}
	
	// Update is called once per frame
	void Update () {
		scoreText.text = "Score: " + score + "\nHigh Score: " + highScore;
	}

	void OnDestroy()
	{
		PlayerPrefs.SetInt ("highscore",highScore);
		instance = null;
	}

	static public void AddPoint() {

		if (instance.bird.dead)
			return;
		
		score++;
		Debug.Log (score + " " + highScore);
		if(score > highScore) {
			highScore = score;
		}
	}
}
