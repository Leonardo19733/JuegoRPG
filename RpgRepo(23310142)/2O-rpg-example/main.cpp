#include <iostream>
#include "Enemy/Enemy.h"
#include "Player/Player.h"
#include "Combat/Combat.h"
#include <queue>

using namespace std;

int main() {
    Player *player = new Player("Ash mostaza", 65, 14, 2, 6);
    Enemy *enemy = new Enemy("Puchaina", 45, 12, 2, 6, 230);
    Enemy *enemy2 = new Enemy("Vaporeon", 35, 9, 2, 2, 115);

    vector<Character*> participants;
    participants.push_back(player);
    participants.push_back(enemy);
    participants.push_back(enemy2);

    Combat* combat = new Combat(participants);
    combat->doCombat();

    delete player;
    delete enemy;
    delete enemy2;
    delete combat;

    return 0;
}
