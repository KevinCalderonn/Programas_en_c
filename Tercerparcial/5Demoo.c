#include <stdio.h>

#include <stdlib.h>

#include </Applications/XAMPP/xamppfiles/include/mysql.h>

#include <string.h>

#define MAX 100
MYSQL *con;



void finish_with_error() {

 fprintf(stderr, "%s\n", mysql_error(con));

 mysql_close(con);

 exit(1);

}



void conectar() {

 con = mysql_init(NULL);

 if (con == NULL) {

 fprintf(stderr, "mysql_init() falló\n");

 exit(1);

 }



 if (mysql_real_connect(con, "localhost", "root", NULL , "vasosxd", 

 3306, "/tmp/mysql.sock", 0) == NULL) {

 finish_with_error();

 }

}



void crear_persona(const char *material, int capacidad, const char *altura, const char *diametro, const char *color, const char *forma, const char *peso, const char *textura) {

 char query[512];

 snprintf(query, sizeof(query),
 "INSERT INTO vasos(material, capacidad, altura, diametro, color, forma, peso, textura) VALUES('%s', %d, '%s', '%s', '%s', '%s', '%s', '%s')",
 material, capacidad, altura, diametro, color, forma, peso, textura);

 if (mysql_query(con, query)) {

 finish_with_error();

 } else {

 printf("Datos ingresados correctamente.\n");

 }

}



void leer_personas_parcial() {

 if (mysql_query(con, "SELECT id, material, capacidad,altura FROM vasos")) {

 finish_with_error();

 }



 MYSQL_RES *result = mysql_store_result(con);

 if (result == NULL) {

 finish_with_error();

 }



 int num_fields = mysql_num_fields(result);

 MYSQL_ROW row;



 while ((row = mysql_fetch_row(result))) {

 for (int i = 0; i < num_fields; i++) {

 printf("%s\t", row[i] ? row[i] : "NULL");

 }

 printf("\n");

 }



 mysql_free_result(result);

}

void leer_personas() {

 if (mysql_query(con, "SELECT id, material, capacidad,altura,diametro,color,forma,peso,textura FROM vasos")) {

 finish_with_error();

 }



 MYSQL_RES *result = mysql_store_result(con);

 if (result == NULL) {

 finish_with_error();

 }



 int num_fields = mysql_num_fields(result);

 MYSQL_ROW row;



 while ((row = mysql_fetch_row(result))) {

 for (int i = 0; i < num_fields; i++) {

 printf("%s\t", row[i] ? row[i] : "NULL");

 }

 printf("\n");

 }



 mysql_free_result(result);

}


void actualizar_persona(int id, const char *nuevo_material, int nueva_capacidad,const char *nueva_altura, const char *nuevo_diametro, const char *nuevo_color, const char *nueva_forma,const char *nuevo_peso, const char *nueva_textura) {

 char query[256];

snprintf(query, sizeof(query),
 "UPDATE vasos SET material='%s', capacidad=%d, altura='%s', diametro='%s', color='%s', forma='%s', peso='%s', textura='%s' WHERE id=%d",
 nuevo_material, nueva_capacidad, nueva_altura, nuevo_diametro, nuevo_color, nueva_forma, nuevo_peso, nueva_textura, id);

 if (mysql_query(con, query)) {

 finish_with_error();

 } else {

 printf("Datos actualizados.\n");

 }

}



void eliminar_persona(int id) {

 char query[128];

 snprintf(query, sizeof(query), "DELETE FROM vasos WHERE id=%d", id);

 if (mysql_query(con, query)) {

 finish_with_error();

 } else {

 printf("Datos eliminados.\n");

 }

}



int main() {

 conectar();
int opc,id_borrar,capacidad,id_actualizar,nueva_capacidad,id_parcial;
char material[MAX], textura[MAX],altura[MAX],diametro[MAX],color[MAX],forma[MAX],peso[MAX];
char nuevo_material[MAX],nueva_altura[MAX],nuevo_diametro[MAX],nuevo_color[MAX], nueva_forma[MAX],nuevo_peso[MAX], nueva_textura[MAX];
do
{
   printf("===MENU VASOS===\n"
       "1.-Insertar datos.\n"
       "2.-Listar datos.\n"
       "3.-Borrar datos.\n"
       "4.-Actualizar datos.\n"
       "5.-Salir.\n");
scanf("%d",&opc);
getchar();

switch (opc)
{
case 1:
printf("Introduzca el material del vaso: \n");
fgets(material, MAX, stdin);
material[strcspn(material,"\n")] = '\0';
printf("Introduzca la capacidad del vaso: \n");
scanf("%d",&capacidad);
getchar();
printf("Introduzca la altura del vaso: \n");
fgets(altura,MAX,stdin);
altura[strcspn(altura,"\n")] = '\0';
printf("Introduzca el diametro del vaso: \n");
fgets(diametro,MAX,stdin);
diametro[strcspn(diametro,"\n")] = '\0';
printf("Introduzca el color del vaso: \n");
fgets(color,MAX,stdin);
color[strcspn(color,"\n")] = '\0';
printf("Introduzca la forma del vaso: \n");
fgets(forma,MAX,stdin);
forma[strcspn(forma,"\n")] = '\0';
printf("Introduzca el peso del vaso: \n");
fgets(peso,MAX,stdin);
peso[strcspn(peso,"\n")] = '\0';
printf("Introduzca la textura del vaso: \n");
fgets(textura,MAX,stdin);
textura[strcspn(textura,"\n")] = '\0';


crear_persona(material,capacidad,altura,diametro,color,forma,peso,textura);
    break;
case 2:{
leer_personas();
    break; }
case 3:{
leer_personas_parcial();
printf("Ingrese el id que pertenece a los datos que desea borrar:\n");
scanf("%d",&id_borrar);
getchar();
break;}
case 4:{
leer_personas_parcial();
printf("Introduzca el id que corresponde a los datos que desea actualizar:\n");
scanf("%d",&id_actualizar);
getchar();
printf("Introduzca el material del vaso: \n");
fgets(nuevo_material, MAX, stdin);
nuevo_material[strcspn(nuevo_material,"\n")] = '\0';
printf("Introduzca la capacidad del vaso: \n");
scanf("%d",&nueva_capacidad);
getchar();
printf("Introduzca la altura del vaso: \n");
fgets(nueva_altura,MAX,stdin);
nueva_altura[strcspn(nueva_altura,"\n")] = '\0';
printf("Introduzca el diametro del vaso: \n");
fgets(nuevo_diametro,MAX,stdin);
nuevo_diametro[strcspn(nuevo_diametro,"\n")] = '\0';
printf("Introduzca el color del vaso: \n");
fgets(nuevo_color,MAX,stdin);
nuevo_color[strcspn(nuevo_color,"\n")] = '\0';
printf("Introduzca la forma del vaso: \n");
fgets(nueva_forma,MAX,stdin);
nueva_forma[strcspn(nueva_forma,"\n")] = '\0';
printf("Introduzca el peso del vaso: \n");
fgets(nuevo_peso,MAX,stdin);
nuevo_peso[strcspn(nuevo_peso,"\n")] = '\0';
printf("Introduzca la textura del vaso: \n");
fgets(nueva_textura,MAX,stdin);
nueva_textura[strcspn(nueva_textura,"\n")] = '\0';
actualizar_persona(id_actualizar, nuevo_material,nueva_capacidad,nueva_altura,nuevo_diametro,nuevo_color,nueva_forma,nuevo_peso,nueva_textura);
break;}
case 5:{
 mysql_close(con);
 return 0;
break;}
default:{
    printf("Opción no válida.\n");
    break;
}
}
} while (opc!=5);

}