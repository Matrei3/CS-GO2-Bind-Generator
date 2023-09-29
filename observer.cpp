#pragma once
#include <vector>
#include <qdebug.h>
using namespace std;

class Observer {
public:
	virtual void update() = 0;
};
class Observable {
private:
	vector<Observer*> interesati;

public:
	void notify() {
		for (auto& obs : interesati)
			qDebug() << "am notificat", obs->update();
	}
	void addObserver(Observer* o) {
		interesati.push_back(o);
	}
	void removeObserver(Observer* o) {
		interesati.erase(remove(interesati.begin(), interesati.end(), o));
	}
};