#pragma once

#include <vector>
#include "Player.h"

class Tropicamel {
public:
    Tropicamel();
    void start();
    void tick();
    void loop();
    
    void setSim(bool enabled);

private:
    void update();

    bool mSimulation = false;
    int mTimestampFromStart = 0;
    int mTick = 0;

    std::vector<Player> mPlayers;
    int mTurn = 0;
};
