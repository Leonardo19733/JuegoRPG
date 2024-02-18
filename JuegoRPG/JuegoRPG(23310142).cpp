#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Definición de la estructura del Personaje
typedef struct {
    char nombre[50];
    int vida;
    int ataque;
    int defensa;
    int agilidad;
} Personaje;

// Definición de la estructura del Enemigo
typedef struct {
    char nombre[50];
    int vida;
    int ataque;
    int defensa;
    int agilidad;
} Enemigo;

// Función para generar un número aleatorio dentro de un rango
int randInRange(int min, int max) {
    return min + rand() % (max - min + 1);
}

// Función para que el personaje ataque al enemigo
void personajeAtaca(Personaje *personaje, Enemigo *enemigo) {
    int daño = randInRange(personaje->ataque - 10, personaje->ataque + 10) - enemigo->defensa;
    daño = (daño > 0) ? daño : 0;
    enemigo->vida -= daño;
    printf("%s ataca a %s y le inflige %d puntos de daño\nVida de %s restante: %d, Vida de %s restante: %d\n----------------------------------------------------------------\n",
           personaje->nombre, enemigo->nombre, daño, personaje->nombre, personaje->vida, enemigo->nombre, enemigo->vida);
}

// Función para que el enemigo ataque al personaje
void enemigoAtaca(Enemigo *enemigo, Personaje *personaje) {
    int daño = randInRange(enemigo->ataque - 10, enemigo->ataque + 10) - personaje->defensa;
    daño = (daño > 0) ? daño : 0;
    // El personaje puede esquivar el ataque
    if (rand() % 100 < personaje->agilidad) {
        printf("%s esquiva el ataque de %s.\n", personaje->nombre, enemigo->nombre);
        return;
    }
    // El personaje puede bloquear el ataque
    if (rand() % 2 == 0) {
        printf("%s bloquea el ataque de %s y reduce el daño recibido.\n", personaje->nombre, enemigo->nombre);
        daño /= 2; // Reducir el daño a la mitad
    }
    personaje->vida -= daño;
    printf("%s ataca a %s y le inflige %d puntos de daño\nVida de %s restante: %d, Vida de %s restante: %d\n----------------------------------------------------------------\n",
           enemigo->nombre, personaje->nombre, daño, personaje->nombre, personaje->vida, enemigo->nombre, enemigo->vida);
}

// Función que simula la batalla entre el personaje y el enemigo
void batalla(Personaje *personaje, Enemigo *enemigo) {
    printf("Comienza la batalla entre %s y %s!\n----------------------------------------------\n", personaje->nombre, enemigo->nombre);
    while (personaje->vida > 0 && enemigo->vida > 0) {
        // Turno del personaje
        personajeAtaca(personaje, enemigo);
        if (enemigo->vida <= 0) {
            printf("%s ha sido derrotado.\n", enemigo->nombre);
            break;
        }
        // Turno del enemigo
        enemigoAtaca(enemigo, personaje);
        if (personaje->vida <= 0) {
            printf("%s ha sido derrotado.\n", personaje->nombre);
            break;
        }
    }
}

int main() {
    srand(time(NULL)); // Semilla para generar números aleatorios

    // Crear personaje y enemigo
    Personaje guerrero = {"Guerrero", 100, 20, 10, 50}; // Agilidad de 50%
    Enemigo dragon = {"Dragón", 200, 30, 5, 20}; // Agilidad de 20%

    // Comenzar la batalla
    batalla(&guerrero, &dragon);

    return 0;
}