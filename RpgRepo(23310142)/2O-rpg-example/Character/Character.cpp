//
// Created by Victor Navarro on 13/02/24.
//
#include "Character.h"
#include <string>
#include <sstream>

Character::Character(char _name[], int _health, int _attack, int _defense, int _speed, int _ExpReward, bool _isPlayer) {
    strcpy(name, _name);
    health = _health;
    attack = _attack;
    defense = _defense;
    speed = _speed;
    isPlayer = _isPlayer;
    fleed = false;
    ExpReward = _ExpReward;
}

void Character::setName(char _name[]) {
    strcpy(name, _name);
}

char* Character::getName() {
    return name;
}

void Character::setHealth(int _health) {
    health = _health;
}

int Character::getHealth() {
    return health;
}

void Character::setAttack(int _attack) {
    attack = _attack;
}

int Character::getAttack() {
    return attack;
}

void Character::setDefense(int _defense) {
    defense = _defense;
}

int Character::getDefense() {
    return defense;
}

void Character::setSpeed(int _speed) {
    speed = _speed;
}

int Character::getSpeed() {
    return speed;
}

string Character::toString() {
    std::string nameStr(name);
    std::stringstream ss;
    ss << "Name: " << nameStr << "\nHealth: " << getHealth() << "\nAttack: " << getAttack() << "\nDefense: " << getDefense() << "\nSpeed: " << getSpeed();
    return ss.str();
}

bool Character::getIsPlayer() {
    return isPlayer;
}

bool Character::hasFleed() {
    return fleed;
}

int Character::getExpReward() {
    return ExpReward;
}

void Character::setExpReward(int _ExpReward) {
    ExpReward = _ExpReward;
}