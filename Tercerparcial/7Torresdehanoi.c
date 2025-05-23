#include <stdio.h>

void hanoi(char torre1, char torre2, char torre3, int disco) {
    if (disco == 1) {
        printf("Mover disco 1 desde torre %c a torre %c\n", torre1, torre3);
    } else {
        hanoi(torre1, torre3, torre2, disco - 1);
        printf("Mover disco %d desde torre %c a torre %c\n", disco, torre1, torre3);
        hanoi(torre2, torre1, torre3, disco - 1);
    }
}

int main() {
    int discos;
    char torre1, torre2, torre3;

    printf("Nombre de la Torre 1: ");
    scanf(" %c", &torre1);
    printf("Nombre de la Torre 2: ");
    scanf(" %c", &torre2);
    printf("Nombre de la Torre 3: ");
    scanf(" %c", &torre3);
    printf("Número de discos: ");
    scanf("%d", &discos);

    hanoi(torre1, torre2, torre3, discos);
    return 0;
}