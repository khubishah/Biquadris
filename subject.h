#ifndef SUBJECT_H
#define SUBJECT_H
#include <vector>


template <typename InfoType> class Observer;

template <typename InfoType> class Subject {
	std::vector<Observer<InfoType>*> observers;

  public:
	void attach(Observer<InfoType> *obs);	
	void notifyObservers();
	void detach(Observer<InfoType> *obs);
	std::vector<Observer<InfoType>*> getObservers();
	virtual InfoType getInfo() const = 0;
};

template <typename InfoType>
void Subject<InfoType>::attach(Observer<InfoType> *obs) {
	observers.emplace_back(obs);
}

template <typename InfoType>
std::vector<Observer<InfoType>*> Subject<InfoType>::getObservers() {
	return observers;
}

template <typename InfoType>
void Subject<InfoType>::detach(Observer<InfoType> *obs) {
	int count = observers.size();
	int i = 0;
	for (i = 0; i < count; i++) {
		if(observers[i] == obs) {
			break;
		}
	}

	if (i < count) {
		observers.erase(observers.begin() + i);
	}
}

template <typename InfoType>
void Subject<InfoType>::notifyObservers() {
	for (auto &ob : observers) {
		ob->notify(*this);
	}
}

#endif












