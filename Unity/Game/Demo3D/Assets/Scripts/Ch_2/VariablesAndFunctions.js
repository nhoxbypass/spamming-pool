#pragma strict

// declare the variable myVar of type integer and give it a value of 8.
var myVar : int = 8;

// string variables
var myString1 : String = "Hello ";
var myString2 : String = "World!";
var myNewString: String;

function Start () {
	Debug.Log(myVar);

// arithmetic operators
print(6+2);
print(6-2);
print(6*2);
print(6/2);
print(6%2);
	
// order of operations
print(6+2*4);
print((6+2)*4);

// using variables and arithmetic operators
print(myVar + myVar);

// concatenation of string variables
myNewString = String.Concat(myString1, myString2);
Debug.Log(myNewString);

// using functions
myVar = AddFive(myVar);
Debug.Log(myVar);

// using Mathf
Debug.Log(Mathf.PI);
}

function AddFive (numberFromStartFunction : int) {
	var newVar : int;
	newVar = numberFromStartFunction + 5;
	return newVar;
}

