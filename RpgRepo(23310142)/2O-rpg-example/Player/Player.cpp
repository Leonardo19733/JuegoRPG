//
// Created by Victor Navarro on 13/02/24.
//
#include "Player.h"
#include <iostream>
#include <algorithm>
#include "../Utils.h"

using namespace std;
using namespace combat_utils;

bool compareSpeed(Enemy *a, Enemy *b) {
    return a->getSpeed() > b->getSpeed();
}

Player::Player(char name[], int health, int attack, int defense, int speed) : Character(name, health, attack, defense, speed, ExpReward, true) {
    experience = 0;
    level = 1;
    leveledUp = false;
}
//Obtenemos el daño verdadero restando la defensa
void Player::doAttack(Character *target) {
    int rolledAttack = getRolledAttack(getAttack());
    int trueDamage = target->getDefense() > rolledAttack ? 0 : rolledAttack - target->getDefense();
    target->takeDamage(trueDamage);
                        
    if (target->getHealth()<=0) {
        gainExperience(target->getExpReward());
    }
}

void Player::takeDamage(int damage) {
    setHealth(health - damage);
    if ((health > 0) && (fleed == false)) {
        cout << "Haz recibido un plomazo (Hp -" << damage << ") | (Hp restante " << health << ")" << endl;
    }else{
        if (health <= 0) {
            cout << "=== Los enemigos te papearon - Game Over ===" << endl;
            return;
        }
    }
}

void Player::flee(vector<Enemy *> enemies) {
    std::sort(enemies.begin(), enemies.end(), compareSpeed);
    Enemy *fastestEnemy = enemies[0];
    bool fleed = false;
    //Si eres mas rapido que los enemigos siempre escapas
    if (this->getSpeed() > fastestEnemy->getSpeed()) {
        cout << "Eres mas rapido que los enemigos puedes huir sin problemas velocidad: " << speed << endl;
        fleed = true;
    }
    else {
        //Hacemos una probabilidad del 50% en caso de que seas mas lento que el enemigo
        srand(time(NULL));
        int chance = rand() % 100;
        cout << "Eres mas lento, velocidad: "<<speed<<"\nChance de huir: 40%" << endl;
        fleed = chance < 40;
    }

    this->fleed = fleed;
}

//Se burla del enemigo
void Player::emote() {
    cout << "*Se burla del enmigo*\n*El enemigo se enoja*" << endl;
}

void Player::levelUp() {
    level++;
    
    cout << "\n--- Has subido de nivel ---" << endl;
    cout << "Tu nivel de personaje es: lvl " << level <<" - Exp ("<<experience<<"/100)" << endl;

    cout << "\n + 10 de Vida: "<<health <<" -> ";
    setHealth(getHealth() + 10);
    cout << health << endl;

    cout << " + 4 de Ataque: "<<attack <<" -> ";
    setAttack(getAttack() + 4);
    cout << attack << endl;

    cout << " + 1 de Defensa: "<<defense <<" -> ";
    setDefense(getDefense() + 1);
    cout << defense << endl;

    cout << " + 5 de Velocidad: "<<speed <<" -> ";
    setSpeed(getSpeed() + 5);
    cout << speed << "\n" << endl;
    this->leveledUp = true;
}

void Player::gainExperience(int exp) {

    experience += exp;
    if (experience >= 100) {
        experience -= 100;
        levelUp();
    }
}

Character *Player::getTarget(vector<Enemy *> enemies) {
    cout << "\n========= Elige un objetivo =========\n" << endl;
    int targetIndex = 0;
    for (int i = 0; i < enemies.size(); i++) {
        cout << i << ". " << enemies[i]->getName() <<" (Hp " << enemies[i]->getHealth() <<")" << endl;
    }
    cout << "\n";
    cin >> targetIndex;
    return enemies[targetIndex];
    system("cls");
}

Action Player::takeAction(vector<Enemy *> enemies) {
    int option = 0;
    cout << "\n========= Elige una accion =========" << endl;
    cout << "1. Ataque" << endl;
    cout << "2. Huir        - "<<name<<" (Hp " << health <<")" << endl;
    cout << "3. Emote\n" << endl;
    cin >> option;
    system("cls");

    Character *target = nullptr;

    //Esta variable guarda
    //1. Que voy a hacer?
    //2. Con que velocidad/prioridad?
    Action myAction;

    myAction.speed = this->getSpeed();
    myAction.subscriber = this;

    switch (option) {
        case 1:
            target = getTarget(enemies);
            myAction.target = target;
            cout << "\n";
            myAction.action = [this, target]() {
                doAttack(target);
            };
            break;
        case 2:
            myAction.action = [this, enemies]() {
                flee(enemies);
            }; 
            break;
        case 3:
            target = getTarget(enemies);
            myAction.target = target;
            myAction.action = [this, target]() {
                doAttack(target); //Este deberia de ser remplazado por baja defensa
                };
            emote();
            break;
        default:
            cout << "Opcion invalida" << endl;
            break;
    }

    return myAction;
}

int Player::getLevel() {
    return level;
}

bool Player::isLeveledUp() {
    return leveledUp;
}

void Player::setLeveledUp(bool _leveledUp) {
    this->leveledUp = _leveledUp;
}