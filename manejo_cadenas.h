#ifndef MANEJO_CADENAS_H
#define MANEJO_CADENAS_H
char* obtener_linea_pos(FILE*, int);
char* leer_palabra(int, char*);
int nro_linea_con_palabra(FILE*, char*);
int cant_palabras(char*);
int palabra_existe_en_linea(char*, char*);
char* cadena_sin_tabs(char*);
int contiene_solo_nros(char*);
int pos_caracter_en_cadena(char,char*);
#endif
