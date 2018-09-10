#pragma once
#include "2DGameFramework\Sprite.h"
#include "2DGameFramework\State.h"
#include "Zombie.h"
#include "Hero.h"

class GamePlayState:public State
{
private:
	float spawnTime;
	vector<Zombie*> zombies;
	vector<Hero*> heroes;
	char loadName[255];
protected:
public:
	GamePlayState();
	~GamePlayState();
	void Init();
	void Mouse(MouseData mouse, bool bIsDown);
	void Key(unsigned char key, bool bIsPressed);
	void onTouch(int id,float x,float y);
	void Update(float deltatime);
	void Draw();
	bool CheckCollision(Bound, Bound);
};