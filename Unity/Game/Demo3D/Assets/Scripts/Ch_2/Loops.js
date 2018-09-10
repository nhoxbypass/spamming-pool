#pragma strict

var targets : int = 4;
var numberOfTires : int = 0;

function Start () {

// for loop
	for(var i: int = 0; i < targets; i++)
	{
		Debug.Log("This is target #" + i);
	}	
	
// while loop
	while(numberOfTires < 4)
	{
		Debug.Log("I replaced an old tire on my car!");
		numberOfTires++;
	}

// do-while loop
	var someCondition : boolean = false;
	do
	{
		Debug.Log("Print something anyway");
	}  
while(someCondition == true);

}