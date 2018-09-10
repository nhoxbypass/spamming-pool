#pragma strict

var skyIsClear : boolean = true;
var sunIsUp: boolean = true;
var diceRoll : float;

 function Start () {
	Debug.Log(skyIsClear);
	
	if (skyIsClear == true) {
		Debug.Log("I will go out and play");
	}
	
	// logic operator
	if (skyIsClear == true && sunIsUp == true) {
		Debug.Log("I will go out and play");
	}
	
	// multiple conditionals
	 	if (sunIsUp) {
		Debug.Log("I will get out of bed");
	}
 	if (skyIsClear) {
		Debug.Log("I do not need an umbrella");
	}
	else {
		Debug.Log("I am staying in bed");
	}
	
// switch-case
	diceRoll = Random.Range(1, 6);
	
	switch (diceRoll) {
		case 1:
			print ("You rolled a 1!");
		break;
		case 2:
			print ("You rolled a 2!");
		break;
		case 3:
			print ("You rolled a 3!");
		break;
		case 4:
			print ("You rolled a 4!");
		break;
		case 5:
			print ("You rolled a 5!");
		break;
		case 6:
			print ("You rolled a 6!");
		break;
		default:
			print ("It's your turn - roll!");
		break;
	}

}