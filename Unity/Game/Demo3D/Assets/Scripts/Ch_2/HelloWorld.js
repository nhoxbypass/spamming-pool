#pragma strict

function Start () {
	//print "Hello World" to the Console using the print function
	print("Hello World!");
	
	//print "Hello World" to the Console using the Debug.Log function
	Debug.Log("Hello World!");
	
	//print "Hello World" to the Console using the Debug.Log function, including the gameObject reference
	Debug.Log("HelloWorld!", gameObject); 
}