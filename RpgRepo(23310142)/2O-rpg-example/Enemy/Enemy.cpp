//
// Created by Victor Navarro on 13/02/24.
//
#include "Enemy.h"
#include <iostream>
#include <string>
#include <utility>


using namespace std;

//TODO: Check the circular dependency
int getRolledAttack(int attack) {
    int lowerLimit = attack * .65;
    return (rand() % (attack - lowerLimit)) + lowerLimit;
}

Enemy::Enemy(char name[], int health, int attack, int defense, int speed, int ExpReward) : Character(name, health, attack, defense, speed, ExpReward, false) {
}
    //Determina un numero aleatorio de daño y defensa del enemigo
void Enemy::doAttack(Character *target) {
    int rolledAttack = getRolledAttack(getAttack());
    int trueDamage = target->getDefense() > rolledAttack ? 0 : rolledAttack - target->getDefense();
    if (health > 0) {
        target->takeDamage(trueDamage);
    }
}
    //Obtiene la vida del enemigo para saber si aplicar el daño o si ya esta muerto
void Enemy::takeDamage(int damage) {
    setHealth(getHealth() - damage);
    if(getHealth() <= 0) {
        cout << getName() << " ha recibido un manotazo de " << damage << " de damage" << " (Hp " << health << ")" << endl;
        cout<<"\n-- " << getName() << " ha muerto (+"<<ExpReward<<" Exp) -- " << endl;
    }
    else {
        cout<<getName()<<" ha recibido un manotazo ( Hp -" << damage << ") | (Hp restante "<<health<< ")" << endl;
    }
}

Character* Enemy::getTarget(vector<Player *> teamMembers) {
    // Obtiene el miembro del equipo con menos vida
    int targetIndex = 0;
    int lowestHealth = INT_MAX;
    for(int i=0; i < teamMembers.size(); i++) {
        if(teamMembers[i]->getHealth() < lowestHealth) {
            lowestHealth = teamMembers[i]->getHealth();
            targetIndex = i;
        }
    }

    return teamMembers[targetIndex];
}
    //Obtiene el character con mas velocidad
Action Enemy::takeAction(vector<Player *> player) {
    Action myAction;
    myAction.speed = getSpeed();
    myAction.subscriber = this;
    Character* target = getTarget(player);
    myAction.target = target;
    myAction.action = [this, target]() {
        doAttack(target);
    };

    return myAction;
}

int Enemy::getExpReward() {
    return ExpReward;
}

void Enemy::uploadStatistics() {
    setAttack(getAttack() + 6);
    setDefense(getDefense() + 2);
    setSpeed(getSpeed() + 2);
    cout <<"-- " << getName() << " ha subido sus estadisticas (+10 puntos de habilidad) --" << endl;
}
