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

Player::Player(string name, int health, int attack, int defense, int speed) : Character(name, health, attack, defense,
                                                                                        speed, true) {
    experience = 0;
    level = 1;
}
//Obtenemos el daño verdadero restando la defensa
void Player::doAttack(Character *target) {
    int rolledAttack = getRolledAttack(getAttack());
    int trueDamage = target->getDefense() > rolledAttack ? 0 : rolledAttack - target->getDefense();
    target->takeDamage(trueDamage);
    gainExperience(30);
}

void Player::takeDamage(int damage) {
    setHealth(health - damage);
    cout << "Haz recibido un plomazo de " << damage << " damage, te quedan "<<health<<" puntos de vida" << endl;
    if (health <= 0) {
        cout << "Has muerto" << endl;

    }
}

void Player::flee(vector<Enemy *> enemies) {
    std::sort(enemies.begin(), enemies.end(), compareSpeed);
    Enemy *fastestEnemy = enemies[0];
    bool fleed = false;
    //Si eres mas rapido que los enemigos siempre escapas
    if (this->getSpeed() > fastestEnemy->getSpeed()) {
        cout << "Eres mas rapido que los enemigos, escapaste sin problemas, velocidad: " << speed << endl;
        fleed = true;
    }
    else {
        //Hacemos una probabilidad del 50% en caso de que seas mas lento que el enemigo
        srand(time(NULL));
        int chance = rand() % 100;
        cout << "Eres mas lento velocidad: "<<speed<<"\nChance de huir: 50%" << endl;
        fleed = chance > 50;
    }

    this->fleed = fleed;
}

//Se burla del enemigo
void Player::emote() {
    cout << "*Se burla del enmigo*\n" << endl;
}

void Player::levelUp() {
    level++;
    setHealth(getHealth() + 10);
    cout << "\n---Has subido de nivel---" << endl;
    cout << "Tu nivel de personaje es: lvl " << level <<" - Exp ("<<experience<<"/100)" << endl;
    cout << "\n + 10 de Vida: ("<<health <<")"<< endl;
    setAttack(getAttack() + 4);
    cout << " + 4 de Ataque: ("<<attack <<")" << endl;
    setDefense(getDefense() + 1);
    cout << " + 1 de Defensa: ("<<defense <<")"<< endl;
    setSpeed(getSpeed() + 5);
    cout << " + 5 de Velocidad: ("<<speed<<")\n"<< endl;
}

void Player::gainExperience(int exp) {
    experience += exp;
    if (experience >= 100) {
        experience -= 100;
        levelUp();
    }
}

Character *Player::getTarget(vector<Enemy *> enemies) {
    cout << "\n========= Elige un objetivo =========" << endl;
    int targetIndex = 0;
    for (int i = 0; i < enemies.size(); i++) {
        cout << i << ". " << enemies[i]->getName() << endl;
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
    cout << "2. Huir" << endl;
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