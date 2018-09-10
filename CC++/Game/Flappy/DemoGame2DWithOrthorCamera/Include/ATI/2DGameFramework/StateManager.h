#include <vector>
#include "State.h"
using namespace std;


class StateManager
{
private:
	vector<State*> mListState;
	StateManager();
	static StateManager* instance;
	State* currentState;
protected:
public:
	~StateManager();
	static StateManager* GetInstance();
	State* GetCurrentState(){return currentState;};
	void AddState(State*);
	void SwitchState(State*,bool);
	State* FindState(string Name);
};