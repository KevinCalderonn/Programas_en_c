#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define ARCHIVO "../4datos.csv"
#define TEMP "temp.csv"
#define MAX 100
void crear();
void leer();
void actualizar();
void eliminar();
void menu();
int main(){
    FILE *f = fopen(ARCHIVO,"r");
    if (f == NULL)
    {
        f = fopen(ARCHIVO, "w");   
    }
    if (f != NULL)
    {
        fprintf(f,"id,nombre,edad\n");
        fclose(f);
    }
    else{
        fclose(f);
    }
    menu();
    return 0;
}
void menu(){
    int opcion;
    do{
        printf("\n=== CRUD CON CSV EN C === \n");
        printf( "1. Crear registro\n"
                "2. Leer registro\n"
                "3. Actualizar registro\n"
                "4. Eliminar registro\n"
                "5. Salir\n"
                "Seleeccione una opción: ");
                scanf("%d",&opcion);
                getchar();
        switch (opcion)
        {
        case 1:
            crear();
            break;
        case 2:
            leer();
            break;
        case 3:
        actualizar();
        break;
        case 4:
        eliminar();
        break;
        case 5:
        printf("Saliendo...\n");
        break;
        default:
        printf("Opción inválida.\n");
            break;
        }
    } while (opcion != 5);
}
void crear(){
    FILE *f = fopen(ARCHIVO,"a");
    if (f == NULL){
        perror("No se pudo abrir el archivo\n");
        return;
    }
    int id, edad;
    char nombre[MAX];
    printf("Ingrese ID: ");
    scanf("%d", &id);
    getchar();
    printf("Ingrese nombre: ");
    fgets(nombre,MAX,stdin);
    nombre[strcspn(nombre,"\n")] = '\0';
    printf("Ingrese edad: ");
    scanf("%d",&edad);
    getchar();
    fprintf(f,"%d,%s,%d\n",id,nombre,edad);
    fclose(f);
    printf("Registro agregado con exito.\n");
}
void leer(){
    FILE *f = fopen(ARCHIVO,"r");
    if (f == NULL)
    {
        perror("No se pudo abrir el archivo\n");
        return; //Cuando se usa una función void no es necesario escribir 1 o 0 en return
    }
    char linea[100];
    printf("\n---- REGISTROS ---\n");
    while (fgets(linea,MAX,f))
    {
        printf("%s",linea);
    }
    fclose(f);
}
void actualizar(){
    int id_buscar,id,edad, encontrado = 0;
    char nombre[MAX],linea[100],*token;
    printf("Ingrese el ID a actualizar: ");
    scanf("%d",&id_buscar);

    FILE *f = fopen(ARCHIVO,"r");
    FILE *tmp = fopen(TEMP,"w");
    if (f==NULL)
    {
        perror("No se pudo abrir el archivo\n");
        return;
    }
    while(fgets(linea,MAX,f)){
        char copia[MAX];
        strcpy(copia,linea);
        token = strtok(copia,",");
        if (token && strcmp(token,"id")== 0 )
        {
            fputs(linea,tmp);
            continue;
        }
        id = atoi(token);
        if (id == id_buscar)
        {
            printf("Ingrese nuevo nombre: ");
            fgets(nombre,MAX,stdin);
            nombre[strcspn(nombre,"\n")] = '\0';
            scanf("%d",&edad);
            getchar();
            fprintf(tmp, "%d,%s,%d\n", id, nombre, edad);
            encontrado = 1;
        }
         else
            fputs(linea,tmp);
    }
    fclose(f);
    fclose(tmp);
    remove(ARCHIVO);
    rename(TEMP, ARCHIVO);
    if (encontrado)
    {
        printf("Registro actualizado.\n");
    }
    else{
        printf("ID no encontrado.\n");
    }
}
void eliminar() {
            int id_buscar, id;
            char linea[MAX], *token;
            int encontrado = 0;
         
            printf("Ingrese el ID a eliminar: ");
            scanf("%d", &id_buscar);
            getchar();
         
            FILE *f = fopen(ARCHIVO, "r");
            FILE *tmp = fopen(TEMP, "w");
            if (f == NULL || tmp == NULL) {
                perror("No se pudo abrir archivo");
                return;
            }
         
            while (fgets(linea, MAX, f)) {
                char copia[MAX];
                strcpy(copia, linea);
                token = strtok(copia, ",");
                if (token && strcmp(token, "id") == 0) {
                    fputs(linea, tmp);
                    continue;
                }
         
                id = atoi(token);
                if (id == id_buscar) {
                    encontrado = 1;
                    continue;
                } else {
                    fputs(linea, tmp);
                }
            }
         
            fclose(f);
            fclose(tmp);
            remove(ARCHIVO);
            rename(TEMP, ARCHIVO);
         
            if (encontrado){
                printf("Registro eliminado.\n");}
            else
                printf("ID no encontrado.\n");
        }
