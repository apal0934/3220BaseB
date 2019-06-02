#include "subject.h"
#include "observer.h"
#include <iostream>
Subject::Subject() {
    state = true;
}

bool Subject::getState() {
    return state;
}

void Subject::setState(bool newState) {
    state = newState;
    notify(state);
}

void Subject::attach(Observer *observer) {
    observers.push_back(observer);
}

void Subject::notify(bool state) {
    for (auto ob : observers) {
       std::cout << ob->i << std::endl;

    }
}
