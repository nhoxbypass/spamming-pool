#pragma strict

private var animator : Animator;

function Start () {
	animator = GetComponent(Animator);
}

function Update () {
	animator.SetFloat("Speed", Input.GetAxis("Vertical"));       
    var inputValue : float = Input.GetAxis("Vertical");
    Debug.Log(inputValue);
    
    animator.SetFloat("Direction", Input.GetAxis("Horizontal"));
    var directionInputValue : float = Input.GetAxis("Horizontal");
    Debug.Log(directionInputValue); 
}