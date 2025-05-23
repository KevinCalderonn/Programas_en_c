#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100
int main(){
    FILE *file;
    char nombre[MAX];
    int edad;
    char pais[MAX];
    int cantidad,i;
   

    //Abrir el archivo en modo lectura
    file= fopen("../2salida.csv","w");
    if(file==NULL){
        perror("error al abrir el archivo");
        return 1;
    }
    //escribir encabezados
    fprintf(file,"nombre,edad,pais\n");

    printf("cuantas personas quieres registrar? ");
    scanf("%d",&cantidad);
    getchar();

    for (i = 0; i< cantidad; i++){
        printf("\npersona %d\n", i + 1);

        printf("nombre: ");
        fgets(nombre, MAX, stdin);
        nombre[strcspn(nombre,"\n")] =0;

        printf("edad: ");
        scanf("%d",&edad);
        getchar();

        printf("pais: ");
        fgets(pais,MAX, stdin);
        pais[strcspn(pais, "\n")] =0;

        fprintf(file,"%s,%d,%s\n", nombre,edad, pais);
    }
    //cerrar eñ archivo 
    fclose(file);

    printf("\narchivo 'salida.csv' creado exitosamente.\n");
    return 0;
}