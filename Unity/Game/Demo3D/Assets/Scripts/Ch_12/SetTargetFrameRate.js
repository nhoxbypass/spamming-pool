#pragma strict

public var frameRate : int = 50;

function Awake () {
	Application.targetFrameRate = frameRate;
}