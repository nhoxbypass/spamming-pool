#pragma strict

public var musicLoop : AudioClip;
private var introMusicIsPlaying : boolean = true;
private var looping : boolean = false;
public var victoryMusic : AudioClip;

function Start () {
	PlayBackgroundMusic();
}

function Update() {
	if (!GetComponent.<AudioSource>().isPlaying) {
    	introMusicIsPlaying = false;
    }
    if (!introMusicIsPlaying && !looping) {
        looping = true;
        LoopBackgroundMusic();
    }
}

function PlayBackgroundMusic () {
    if(GetComponent.<AudioSource>().isPlaying == true) {
    	GetComponent.<AudioSource>().Stop();
    }
    GetComponent.<AudioSource>().Play();
}

function LoopBackgroundMusic () {
	if(GetComponent.<AudioSource>().isPlaying == true) {
    	GetComponent.<AudioSource>().Stop();
    }
    GetComponent.<AudioSource>().clip = musicLoop;
    GetComponent.<AudioSource>().loop = enabled;
    GetComponent.<AudioSource>().Play();
}

function PlayVictoryMusic () {
	if(GetComponent.<AudioSource>().isPlaying == true) {
    	GetComponent.<AudioSource>().Stop();
    }
    GetComponent.<AudioSource>().clip = victoryMusic;
    GetComponent.<AudioSource>().Play();
}
