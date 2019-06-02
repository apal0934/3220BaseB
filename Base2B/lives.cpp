#include "lives.h"

Lives::Lives(int initial_lives) {
    init_lives = initial_lives;
    curr_lives = initial_lives;
    for (int i = 0; i < 10; i++) {
        std::string spritePath = ":sprites/" + std::to_string(i) + ".png";
        QPixmap sprite(QString::fromStdString(spritePath));
        digits[i] = sprite;
    }
}

void Lives::increment() {
    curr_lives++;
}

void Lives::decrement() {
   curr_lives--;
}

int Lives::getLives() {
    return curr_lives;
}

void Lives::setLives(int life) {
    curr_lives = life;
}

void Lives::render(Renderer &renderer) {
    std::stack<int> number;
    unsigned int life = curr_lives;
    while (life > 0) {
        number.push(life % 10);
        life = life / 10;
    }

    int length = number.size();
    for (int i = 0; i < length; i++) {
        renderer.draw(200+i*10, 20, digits[number.top()]);
        number.pop();
    }
}
