#pragma once
#include <vector>

class Observer;

class Subject {
public:
    Subject();

    bool getState();
    void setState(bool newState);
    void attach(Observer *observer);
    void notify(bool state);

private:
    std::vector<Observer*> observers;
    bool state;
};


