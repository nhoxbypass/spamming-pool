#pragma strict

private var platformStartPosition : Vector3;
private var platformEndPosition : Vector3;
public var lowLevel : float = 6;
public var duration : float = 5.0f;
private var step : float = 0.0f;
private var movingBack : boolean = false;

function Start () {
	platformStartPosition = transform.position;
	platformEndPosition = (transform.position - Vector3(0, lowLevel, 0));
}

function FixedUpdate() {
    var delta : float = (Time.deltaTime / duration);
    if(movingBack) step -= delta;
    else step += delta;
    step = Mathf.Clamp01(step);
    GetComponent.<Rigidbody>().MovePosition(Vector3.Lerp(platformStartPosition, platformEndPosition, step));

    if(step == 1.0f) movingBack = true;
    else if(step == 0.0f) movingBack = false;
}
