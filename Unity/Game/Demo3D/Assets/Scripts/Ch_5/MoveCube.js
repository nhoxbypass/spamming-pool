#pragma strict

public var rotationSpeed:float = 5;
public var travelSpeed:float = 5;
private var originPosition : Vector3 = new Vector3(0, 0, 0);
public var smoothing : float;

function Start () {

}

function Update () {
	// rotate the cube
	//transform.Rotate(Vector3.up);
	
	// adjust the rotation speed from the editor
	//transform.Rotate(Vector3.up * rotationSpeed);
	
	// make the rotation speed framerate independent
	//transform.Rotate(Vector3.up * rotationSpeed * Time.deltaTime);
	
    if(Input.GetKey(KeyCode.LeftArrow)) {
    	transform.Rotate(Vector3.up * rotationSpeed * Time.deltaTime);
    }
    if(Input.GetKey(KeyCode.RightArrow)) {
        transform.Rotate(Vector3.up * -rotationSpeed * Time.deltaTime);
    }
    if(Input.GetKey(KeyCode.UpArrow)) {
        transform.Translate(Vector3.up * Time.deltaTime * travelSpeed);
    }
    if(Input.GetKey(KeyCode.DownArrow)) {
        transform.Translate(Vector3.down * Time.deltaTime * travelSpeed);
    }
    if(Input.GetKey(KeyCode.O)) {
        transform.position = originPosition;
        // smooth the repositioning movement
        // transform.position = Vector3.Lerp(transform.position, originPosition, smoothing * Time.deltaTime);
    }
}