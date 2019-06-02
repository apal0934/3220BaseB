#pragma once
#include "subject.h"

class Observer {
public:
    virtual void updateObserver(bool state) = 0;
    int i;
protected:
    Subject *subject;
};
