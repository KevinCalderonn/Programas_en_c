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
void filtrarbusqueda();
void registrocontador();
void eliminardatos();
void edadmaximayprom();
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
        printf( "1. Crear registro.\n"
                "2. Leer registro.\n"
                "3. Actualizar registro.\n"
                "4. Eliminar registro.\n"
                "5. Filtrar Busqueda.\n"
                "6. Contador de registros.\n"
                "7. Eliminar todos los registros.\n"
                "8. Edad Maxima.\n"
                "9.- Salir.\n"
                "Seleccione una opción: ");
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
        filtrarbusqueda();
        break;
        case 6:
        registrocontador();
        break;
        case 7:
        eliminardatos();
        break;
        case 8:
        edadmaximayprom();
        break;
        case 9:
        printf("Saliendo...\n");
        break;
        default:
        printf("Opción inválida.\n");
            break;
        }
    } while (opcion != 9);
}
void crear(){
    int id_nuevo;
    printf("Ingrese el ID: ");
    scanf("%d",&id_nuevo);
    getchar();
    FILE *f = fopen(ARCHIVO,"r");
    if (f == NULL){
        perror("No se pudo abrir el archivo\n");
    }
    char linea[MAX],*token;
    while (fgets(linea, MAX, f)) {
        token = strtok(linea, ",");
        if (token && strcmp(token, "id") == 0) continue;
        if (atoi(token) == id_nuevo) {
            printf("El id ya existe, no se puede agregar al registro.\n");
            fclose(f);
            return;
        }
    }
    fclose(f);
    
    
    f = fopen(ARCHIVO,"a");
    if (f == NULL){
        perror("No se pudo abrir el archivo\n");
        return;
    }
    int edad;
    char nombre[MAX];
    printf("Ingrese nombre: ");
    fgets(nombre,MAX,stdin);
    nombre[strcspn(nombre,"\n")] = '\0';
    printf("Ingrese edad: ");
    scanf("%d",&edad);
    getchar();
    fprintf(f,"%d,%s,%d\n",id_nuevo,nombre,edad);
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
            printf("Ingrese nueva edad: ");
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
void filtrarbusqueda() {
    int edad_minima, id_nuevo,edad,encontrado = 0;
    printf("Introduzca la edad mínima para realizar la busqueda: ");
    scanf("%d",&edad_minima);
    getchar();
    FILE *f = fopen(ARCHIVO, "r");
    if (f == NULL) {
        perror("No se pudo abrir el archivo\n");
        return;
    }
    char linea[MAX],*token, nombre[MAX];
    
    while (fgets(linea,MAX,f))
    {
        linea[strcspn(linea, "\n")] = '\0';
        token = strtok(linea, ",");
        if (token && strcmp(token, "id") == 0) continue;
        id_nuevo = atoi(token);

        token = strtok(NULL, ",");
        if (token != NULL)
        {
            strncpy(nombre,token,MAX);
        }
        token = strtok(NULL, ",");
        if (token != NULL)
        {
            edad = atoi(token);
        }
        if(edad >= edad_minima)
        {
             printf("%d,%s,%d\n",id_nuevo,nombre,edad);
             encontrado = 1;
        }
    }
    if (encontrado == 0)
    {
        printf("No hay registros encontrados.\n");
    }
    fclose(f);
    
    
}
void registrocontador(){
    FILE *f = fopen(ARCHIVO, "r");
    if (f==NULL)
    {
        perror("No se ha encontrado el archivo");
        return;
    }    
    int contador = 0;
    char linea[MAX], *token;
    while (fgets(linea,MAX,f))
    {
        linea[strcspn(linea, "\n")] = '\0';
        token = strtok(linea, ",");
        if (token && strcmp(token, "id") == 0) continue;        
            contador++;
    }
    if (contador != 0)
    {
        printf("La cantidad de registros es: %d\n",contador);
    }
    else
        printf("Registros no encontrados.\n");
    fclose(f);
}
void eliminardatos(){
    char confirmacion;
    printf("¿Estás seguro de que deseas eliminar todos los registros? (s/n): ");
    scanf(" %c", &confirmacion);
    if (confirmacion != 's' && confirmacion != 'S') {
    printf("Operación cancelada.\n");
    return;
}   
    else {
        FILE *f = fopen(ARCHIVO,"w");
        if (f==NULL)
        {
            perror("No se ha encontrado el archivo");
            return;
        }
        fprintf(f,"id,nombre,edad\n");
        fclose(f);
    }
}
void edadmaximayprom(){
    FILE *f = fopen(ARCHIVO,"r");
    char linea[MAX],*token;
    int edad,edadmaxima=0;
    if (f==NULL)
    {
        perror("No se ha encontrado el archivo");
        return;
    }
    
    while(fgets(linea,MAX,f)){
        linea[strcspn(linea, "\n")] = '\0';
        token = strtok(linea,",");
        if (token && strcmp(token, "id") == 0) continue;
            token = strtok(NULL, ",");
            token = strtok(NULL,",");
                if (token!=NULL)
                {
                    edad = atoi(token);
                    if (edad > edadmaxima)
                    {
                        edadmaxima=edad;
                    }
                }
            }
              printf("La edad maxima es %d\n",edadmaxima);
    fclose(f);
        }