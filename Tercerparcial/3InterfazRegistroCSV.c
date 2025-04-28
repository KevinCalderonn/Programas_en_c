#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_LINE 1024

#define MAX 100

void gotoxy(int x, int y) {
    printf("\033[%d;%dH", y, x);
}

void setColor(const char* color) {
    printf("%s", color);
}

void limpiarPantalla() {
    printf("\033[2J");
}
void interfaz(){
    printf("\033[%d;%dH", 5,10);
    printf(" **************************************************************");
    printf("\033[%d;%dH", 6,10);
    printf(" *                                                            *");
    printf("\033[%d;%dH", 7,10);
    printf(" *                                                            *");
    printf("\033[%d;%dH", 8,10);
    printf(" *                                                            *");
    printf("\033[%d;%dH", 9,10);
    printf(" *                                                            *");
    printf("\033[%d;%dH", 10,10);
    printf(" *                                                            *");
    printf("\033[%d;%dH", 11,10);
    printf(" *                                                            *");
    printf("\033[%d;%dH", 12,10);
    printf(" *                                                            *");
    printf("\033[%d;%dH", 13,10);
    printf(" *                                                            *");
    printf("\033[%d;%dH", 14,10);
    printf(" *                                                            *");
    printf("\033[%d;%dH", 15,10);
    printf(" *                                                            *");
    printf("\033[%d;%dH", 16,10);
    printf(" *                                                            *");
    printf("\033[%d;%dH", 17,10);
    printf(" *                                                            *");
    printf("\033[%d;%dH", 18,10);
    printf(" *                                                            *");
    printf("\033[%d;%dH", 19,10);
    printf(" *                                                            *");
    printf("\033[%d;%dH", 20,10);
    printf(" **************************************************************");
}

int main(){
    FILE *file;
    char nombre[MAX];
    int edad;
    char pais[MAX];
    int cantidad,i;
    char nombrearch[MAX];
    limpiarPantalla();
    interfaz();
    printf("\033[%d;%dH", 7,15);
    printf("Ingresa el nombre del archivo: ");
    setColor("\033[7;32m");
    scanf("%s",&nombrearch);
    getchar();
    setColor("\033[0;37m");
    limpiarPantalla();
    file = fopen(nombrearch, "w");
    if(file==NULL){
        perror("Error al abrir el archivo");
        return 1;
    }
    //Escribir encabezados

    fprintf(file,"Nombre,Edad,Pais\n");
    limpiarPantalla();
    interfaz();
    printf("\033[%d;%dH", 7,15);
    printf("¿Cuantas personas quieres registrar? ");
    setColor("\033[7;32m");
    scanf("%d",&cantidad);
    getchar();
    setColor("\033[0;37m");
    limpiarPantalla();
    printf("\033[%d;%dH", 6,15);
    for (i = 0; i< cantidad; i++){
        interfaz(10, 5);
        printf("\033[%d;%dH", 7,15);
        setColor("\033[7;32m");
        printf("Persona %d", i + 1);
        setColor("\033[0;37m");
        printf("\033[%d;%dH", 8,15);
        setColor("\033[7;34m");
        printf("Nombre: ");
        fgets(nombre, MAX, stdin);
        nombre[strcspn(nombre,"\n")] =0;
        setColor("\033[0;37m");
        printf("\033[%d;%dH", 9,15);
        setColor("\033[7;31m");
        printf("Edad: ");
        scanf("%d",&edad);
        getchar();
        setColor("\033[0;37m");
        printf("\033[%d;%dH", 10,15);
        setColor("\033[7;35m");
        printf("Pais: ");
        fgets(pais,MAX, stdin);
        pais[strcspn(pais, "\n")] =0;

        fprintf(file,"%s,%d,%s\n", nombre,edad, pais);
        setColor("\033[0;37m");
        limpiarPantalla();

    }
    printf("\narchivo '%s' creado exitosamente.\n",nombrearch);
     fclose(file);
    file = fopen(nombrearch, "r");
    char line[MAX_LINE];
    char *token;
    if (file == NULL){
        perror("Error al abrir el archivo");
        return 1;
    }
    
    printf("%-15s %-10s %-15s \n", "Nombre", "Edad", "País");

    printf("-------------------------------------------------\n");

    while(fgets(line, sizeof(line), file)){
        line[strcspn(line, "\n")] = 0;
        token = strtok(line, ",");
        if (token != NULL) printf("%-15s |", token);

        token = strtok(NULL, ",");
        if (token !=NULL) printf("%-10s |", token);

        token = strtok(NULL, ",");
        if (token != NULL) printf("%-15s |", token);
        
        printf("\n");
    }

    fclose(file);
    
    return 0;
}