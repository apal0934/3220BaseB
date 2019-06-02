#include "stagefactory.h"
#include "collisiontest.h"
#include "jumptest.h"
#include "flyingobstacletest.h"
#include "swaprendererstage.h"
#include "testingdialog.h"
#include "stage2dialog.h"
#include "dialog.h"
#include "moon.h"
#include "background.h"

StageFactory::StageFactory(Config config) : config(config) {

}

std::unique_ptr<GameStage> StageFactory::createStage() {
    if (config.stage == 3) {
        if (config.testMode) {
            // Stage 3 test mode

        } else {
            // Stage 3 non-test mode
            auto player = std::make_unique<JumpingStickman>(config.coord.getYCoordinate());
            player->setSize(config.size);
            player->setCoordinate(config.coord);
            player->setSprite(":sprites/sprite0.png");
            player->setSubject(config.subject);

            auto factory = std::make_unique<EntityFactory>();
            factory->setVelocity(config.velocity);
            Lives lives(config.lives);
            auto stage = std::make_unique<Stage2Dialog>(*config.game, std::move(player), std::move(factory), std::move(*config.obstacles), std::move(lives));
            genericDialogInitializer(*stage);
            return std::make_unique<SwapRendererStage>(std::move(stage));
        }
    } else if (config.stage == 2) {
        if (config.testMode) {

        } else {
            // Stage 2 non-test mode
            auto player = std::make_unique<JumpingStickman>(config.coord.getYCoordinate());
            player->setSize(config.size);
            player->setCoordinate(config.coord);
            player->setSprite(":sprites/sprite0.png");

            auto factory = std::make_unique<EntityFactory>();
            factory->setVelocity(config.velocity);

            auto stage = std::make_unique<Stage2Dialog>(*config.game, std::move(player), std::move(factory), std::move(*config.obstacles), std::move(config.lives));
            genericDialogInitializer(*stage);
            return std::make_unique<SwapRendererStage>(std::move(stage));
        }
    } else {
        // Stage 1
        auto player = std::make_unique<Stickman>();
        player->setSize(config.size);
        player->setCoordinate(config.coord);
        player->setSprite(":sprites/sprite0.png");

        auto factory = std::make_unique<EntityFactory>();
        factory->setVelocity(config.velocity);

        auto stage = std::make_unique<Dialog>(*config.game, std::move(player), std::move(factory), std::move(config.lives));
        genericDialogInitializer(*stage);
        return std::move(stage);
    }
}

// Avoid duplicating the same common initialization code across stage 1, 2 and (probably) 3
void StageFactory::genericDialogInitializer(Dialog &dialog) {
    Background bg;
    bg.setCoordinate(Coordinate(0, 150, 450));
    bg.setSprite(config.background);
    bg.setVelocity(config.velocity);
    bg.setSubject(config.subject);

    dialog.setBackground(bg);
    dialog.setMoon(Moon(Coordinate(400, -140, 450), 181.0, 550));
}
