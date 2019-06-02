#ifndef BACKGROUND_H
#define BACKGROUND_H

#include <string>
#include "coordinate.h"
#include "renderer.h"
#include "observer.h"
class Background : Observer {
public:
    Background();

    void setCoordinate(Coordinate coordinate);

    int getVelocity();
    void setVelocity(int velocity);

    void setSprite(std::string path);
    void setSubject(Subject *subject);
    void render(Renderer &renderer, unsigned int time);
    void update();
    void updateObserver(bool state) override;
private:
    Coordinate coordinate;
    int velocity;
    bool prev_state;
    QPixmap sprite;
};

#endif // BACKGROUND_H
