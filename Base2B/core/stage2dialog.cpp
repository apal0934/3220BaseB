#include "stage2dialog.h"
#include "collision.h"
#include "debugrenderer.h"

Stage2Dialog::Stage2Dialog(Game &game, std::unique_ptr<Stickman> stickman, std::unique_ptr<EntityFactory> factory, std::vector<std::pair<std::unique_ptr<Entity>, int>> obstacleLayout, Lives lives) :
    Dialog(game, std::move(stickman), std::move(factory), std::move(lives)), obstacleLayout(std::move(obstacleLayout)), distanceToSpawn(0), nextObstacle(0) {
    once = false;
}

void Stage2Dialog::spawnObstacles(unsigned int counter) {
    // Check if it's time to spawn an obstacle
    if (counter != -1) {
        nextObstacle = 0;
        clear();
    }
    if (obstacleLayout.size() == 0 || distanceToSpawn > 0) return;

    auto &e = obstacleLayout[nextObstacle];

    // Check for collisions between next obstacle and current obstacles
    bool isOverlapping = false;
    for (auto &o : obstacles) {
        if (Collision::overlaps(*e.first, *o)) {
            isOverlapping = true;
            break;
        }
    }

    // Only spawn the obstacle if it isn't colliding with anything
    if (!isOverlapping) {
        auto obs = e.first->clone();
        obs->setVelocity(background.getVelocity());
        addObstacle(std::move(obs));
    }

    // Set next obstacle in sequence
    distanceToSpawn = e.second;
    nextObstacle = (nextObstacle + 1) % obstacleLayout.size();
}

void Stage2Dialog::update() {
    stickman->update(obstacles);
    if (!stickman->isColliding()) {
        // Reduce distance to next obstacle
        distanceToSpawn -= background.getVelocity();
        background.update();
        speedUp(counter);
        score.increment();
        once = false;
    } else {
        if (!once && stickman->height() != 96){
            lives.decrement();
            spawnObstacles(0);
            if (lives.getLives() == 0) {
                // extension
            }
            once = true;
        }

    }
    spawnObstacles(-1);

    for (auto &c : clouds) {
        c->collisionLogic(*stickman);
    }

    for (auto &o : obstacles) {
        o->collisionLogic(*stickman);
    }
}
