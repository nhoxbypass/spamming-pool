#include <iostream>
using namespace std;


class Singleton {
public:
	static Singleton* Instance();
	void printValue()
	{
		cout << key << endl;
	}

	void setValue(int val)
	{
		key = val;
	}
protected:
	Singleton() {};
private:
	static Singleton* _instance;
	int key;
};

Singleton* Singleton::_instance = 0;

Singleton* Singleton::Instance() {
	if (_instance == 0)
		_instance = new Singleton();
	return _instance;
}


int main()
{
	//Rrror
	//Singleton newInstance;
	//Singleton* newInstance = new Singleton;

	//Can tao doi tuong thong qua ham Instance

	Singleton* newInstance = Singleton::Instance();
	Singleton* secondInstance = Singleton::Instance();
	
	newInstance->printValue();
	secondInstance->printValue();

	newInstance->setValue(5);

	newInstance->printValue();
	secondInstance->printValue();

	system("pause");
	return 0;
}