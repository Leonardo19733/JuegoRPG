//
// Created by Victor Navarro on 13/02/24.
//

#ifndef RPG_CHARACTER_H
#define RPG_CHARACTER_H
#include<string>
#include "../Combat/Action.h"

using namespace std;

class Character {
protected:
    char name [30];
    int health;
    int attack;
    int defense;
    int speed;
    bool isPlayer;
    bool fleed;
    int ExpReward;

public:
    Character(char [], int, int, int, int, int, bool);

    virtual void doAttack(Character *target) = 0;
    virtual void takeDamage(int damage) = 0;

    void setName(char[]);
    char* getName();
    void setHealth(int);
    int getHealth();
    void setAttack(int);
    int getAttack();
    void setDefense(int);
    int getDefense();
    void setSpeed(int);
    int getSpeed();
    string toString();
    bool getIsPlayer();
    bool hasFleed();
    int getExpReward();
    void setExpReward(int);
};


#endif //RPG_CHARACTER_H
