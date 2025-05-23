#include <stdio.h>
#include <string.h>
int main(){
    FILE *file;
    int totalpersonas, i,edad;
    char nombrearchivo[100], nombreusuario[100], nombre[100], linea[100];
    char *token;

    printf("Introduzca el nombre del archivo: ");
    scanf("%s",nombreusuario);
    snprintf(nombrearchivo,sizeof(nombrearchivo),"%s.csv",nombreusuario);
    file = fopen(nombrearchivo, "w");
    if (file == NULL)
    {
        printf("No se ha encontrado el archivo\n");
        return 1;
    }
    printf("Introduzca el número de personas que desea registrar: \n");
    scanf("%d", &totalpersonas);
    getchar();
    for(i=0;i<totalpersonas;i++){
        printf("Introduzca el nombre de la persona %d: ",i+1);
        fgets(nombre,sizeof(nombre),stdin);
        nombre[strcspn(nombre,"\n")] = 0;
        printf("Introduzca la edad de la persona %d: ", i+1);
        scanf("%d",&edad);
        getchar();
        fprintf(file,"%s,%d\n",nombre,edad);
    }
    fclose(file);
    printf("Archivo %s creado exitosamente\n",nombrearchivo);
    file =fopen(nombrearchivo,"r");
    if (file == NULL)
    {
        printf("No se ha encontrado el archivo.\n");
        return 1;
    }
    printf("\n%-20s|%-6s|","Nombre", "Edad");
    printf("--------------------|------\n");
    while(fgets(linea,sizeof(linea),file)){
        linea[strcspn(linea,"\n")]= 0;
        token = strtok(linea,",");
        if (token != NULL)
        {
            strncpy(nombre,token,sizeof(nombre));
        }
        token = strtok(NULL, ",");
        if (token != NULL)
        {
            strncpy(edad,token,sizeof(edad));
        }
        printf("%-20s | %-6s\n",nombre,edad);  
    }
    fclose(file);
    return 0;
}