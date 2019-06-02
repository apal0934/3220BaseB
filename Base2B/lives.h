#ifndef LIVES_H
#define LIVES_H
#include "score.h"
class Lives : Score {
public:
    Lives(int initial_lives);

    void increment();
    void decrement();
    void render(Renderer &renderer);

    int getLives();
    void setLives(int l);
private:
    unsigned int curr_lives;
    unsigned int init_lives;
    QPixmap digits[10];
};

#endif // LIVES_H
