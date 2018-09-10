using UnityEngine;
using System.Collections;

public class BirdMovement : MonoBehaviour {

	Vector3 velocity = Vector3.zero;
	//public Vector3 gravity;
	//public Vector3 flapVelocity;
	//public float maxSpeed = 5f;
	public float forwardSpeed = 1f;
	public float flapSpeed = 100000f;
	public bool godMode = false;
	[HideInInspector]
	public bool dead = false;
	float deathCooldown;

	Animator animator;

	bool didFlap = false;

	// Use this for initialization
	void Start () {
		animator = transform.GetComponentInChildren<Animator> (); //thu bo transform
		if (animator == null)
			Debug.LogError ("Khong tim thay Animator!");
	}
	
	// Update is called once per frame
	void Update()
	{
		if (dead) {
			deathCooldown -= Time.deltaTime;
			if (deathCooldown <= 0 && (Input.GetKeyDown(KeyCode.Space) || Input.GetMouseButtonDown(0))) {
				Application.LoadLevel (Application.loadedLevel);
			}
			return;
		}
			
		
		if (Input.GetKeyDown(KeyCode.Space) || Input.GetMouseButtonDown(0)) {
			animator.SetTrigger ("doFlap");
			didFlap = true;
		}
	}


	void FixedUpdate () {

		if (dead)
			return;

		//velocity += gravity * Time.deltaTime;

		//velocity.x += forwardSpeed * Time.deltaTime;
		this.GetComponent<Rigidbody2D>().AddForce(Vector2.right*forwardSpeed);

		if (didFlap) {
			

			/*
			if (velocity.y < 0)
				velocity.y = 0;

			velocity += flapVelocity;
			*/
			this.GetComponent<Rigidbody2D> ().AddForce (Vector2.up * flapSpeed);
			didFlap = false;
		}



		//velocity = Vector3.ClampMagnitude (velocity, maxSpeed);


		//transform.position += velocity * Time.deltaTime;
		this.GetComponent<Rigidbody2D>().AddForce(velocity);

		float angle = 0;

		/*
		if (velocity.y < 0) {
		
			angle = Mathf.Lerp (0, -90, -velocity.y/maxSpeed);
		}
		*/
		if (this.GetComponent<Rigidbody2D> ().velocity.y < 0) {
			angle = Mathf.Lerp (0, -90, (-this.GetComponent<Rigidbody2D> ().velocity.y / 3f));
		} else {
			angle = 0;
		}

		transform.rotation = Quaternion.Euler (0, 0, angle);

	}

	void OnCollisionEnter2D(Collision2D coll)
	{
		if (godMode)
			return;

		//Debug.Log (coll.collider.name);
		animator.SetTrigger ("death");
		dead = true;
		deathCooldown = 0.5f;
	}
}
