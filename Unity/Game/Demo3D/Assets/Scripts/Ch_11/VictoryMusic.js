#pragma strict

public var backgroundMusic : GameObject;

function OnTriggerEnter () {
        backgroundMusic.GetComponent(BackgroundMusic).PlayVictoryMusic();        
}