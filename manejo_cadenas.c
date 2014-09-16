#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include <time.h>
#include <unistd.h>
#include <getopt.h>
#include <assert.h>

#define TAM_CONT 256

#include "manejo_cadenas.h"


int cant_palabras(char* linea){
	int tamanio_linea=strlen(linea);
	char linea_aux[tamanio_linea];
	strcpy(linea_aux, linea);
	char* ptr_linea=linea_aux;
	char separador[1];
	strcpy(separador," :\t\n");
	char* porcion_cadena=" ";//se inicializa con espacio porque se desea que ingrese al bucle while por lo menos una vez.
	char* ptr_resguardo;
	int nro_palabra=0;
		while(porcion_cadena!=NULL){
				porcion_cadena = strtok_r(ptr_linea, separador, &ptr_resguardo);
				//char* original, destino;
				//for (original=destino=porcion_cadena;*destino=*original;destino+=(*original++!='"'));
				if(porcion_cadena == NULL)
					break;
				//porcion_cadena = cadena_sin_tabs(porcion_cadena);//No se si es lo mas conveniente;
				//printf("_____%s_____\n",porcion_cadena);
				nro_palabra++;
				ptr_linea=NULL;
		}
	return nro_palabra;
}

char* cadena_sin_tabs(char* cadena){
	char *src, *dest;

	src = dest = cadena;    // both pointers point to the first char of input
	while(*src != '\0'){    // exit loop when null terminator reached
		if (*src != '\t' && *src != ':'){  // if source is not a " char
			*dest = *src;  // copy the char at source to destination
			dest++;        // increment destination pointer
		}
		src++;             // increment source pointer
	}
	*dest = '\0';          // terminate string with null terminator 
	return cadena;
}
char* obtener_linea_pos(FILE *archivo, int lineaD){
	char buffer[TAM_CONT+1];
	int lineaV=0;
	fseek(archivo, 0, SEEK_SET);

	while(!feof(archivo)){
		fgets(buffer,TAM_CONT,archivo);

		if(lineaV==lineaD){	
			break;
		}
		lineaV++;
	}
	return strdup(buffer);
}


char* leer_palabra(int pos, char* linea){
	int nro_palabras=cant_palabras(linea);
	//printf("cant_palabras: %i \n",nro_palabras);
	assert(pos<=nro_palabras && "Se intenta leer una palabra fuera del límite de la linea.");
	char* arreglo_linea[256];
	int tamanio_linea=strlen(linea);
	char linea_aux[tamanio_linea];
	strcpy(linea_aux, linea);
	char* ptr_linea;
	ptr_linea=linea_aux;
	char separador[1];
	strcpy(separador," :\t\n");
	char* porcion_cadena;
	char* ptr_resguardo;
	int i=0;
		while(porcion_cadena!=NULL){
				porcion_cadena = strtok_r(ptr_linea, separador, &ptr_resguardo);
				if(porcion_cadena == NULL)
					break;
				//porcion_cadena = cadena_sin_tabs(porcion_cadena);//No se si es lo mas conveniente;
				int entero=strlen(porcion_cadena);
				char aux[entero];
				strcpy(aux, porcion_cadena);
				arreglo_linea[i]=strdup(aux);//No se porque tengo que hacer el strdup pero solo funciona así.
				i++;
				ptr_linea=NULL;
		}
	return arreglo_linea[pos];
}

/*int palabra_existe_en_linea(char* palabra, char* linea){
	
	int tamanio_linea=strlen(linea);
	int tamanio_palabra=strlen(palabra);
	char linea_aux[tamanio_linea];
	char palabra_aux[tamanio_palabra];
	strcpy(linea_aux, linea);
	strcpy(palabra_aux, palabra);
	char* ptr_linea;
	ptr_linea=linea_aux;
	char separador[1];
	strcpy(separador," ");
	char* porcion_cadena;
	char* ptr_resguardo;
		while(porcion_cadena!=NULL){
				porcion_cadena = strtok_r(ptr_linea, separador, &ptr_resguardo);
				if(porcion_cadena == NULL)
					break;
				porcion_cadena = cadena_sin_tabs(porcion_cadena);//No se si es lo mas conveniente;
				int tam_porcion=strlen(porcion_cadena);
				char aux[tam_porcion];
				strcpy(aux,porcion_cadena);
				int comparacion=strcmp(porcion_cadena,palabra_aux);
				if(comparacion==0)
					return 1;
				ptr_linea=NULL;
		}
	return 0;
}*/

int palabra_existe_en_linea(char* palabra, char* linea){
	//podria ser un simple strtok de la linea con la palabra y si no es null evidentemente existe!
	//ademas que pasa si la palabra no existe algo de feedback wacho!!!
	
	int tamanio_linea=strlen(linea);
	int tamanio_palabra=strlen(palabra);
	char linea_aux[tamanio_linea];
	char palabra_aux[tamanio_palabra];
	strcpy(linea_aux, linea);
	strcpy(palabra_aux, palabra);
	char* porcion_cadena;
	porcion_cadena=strstr(linea_aux,palabra_aux);
	if(porcion_cadena != NULL)
		return 1;
	else
		return 0;
}

int cant_lineas(FILE* archivo){
	char buffer[TAM_CONT+1];
	int nro_linea=1;
	fseek(archivo, 0, SEEK_SET);

	while(!feof(archivo)){
		fgets(buffer,TAM_CONT,archivo);
		nro_linea++;
	}

	return nro_linea;
}

int nro_linea_con_palabra(FILE *archivo, char* palabra){
	int i=-1;
	int encontrado=0;
	int cantidad_lineas=cant_lineas(archivo);
	//assert(cantidad_lineas==0 && "Se intenta buscar en un archivo vacío.");
	
	while(encontrado==0 && i<cantidad_lineas){
		i++;
		if(palabra_existe_en_linea(palabra, obtener_linea_pos(archivo,i))==1){
			encontrado=1;
		}
	}
	return i;
}

int contiene_solo_nros(char* cadena){
	char* ptr_cadena=cadena;
	while(*ptr_cadena!='\0'){
		if(*ptr_cadena!='0'&&*ptr_cadena!='1'&&*ptr_cadena!='2'&&*ptr_cadena!='3'&&*ptr_cadena!='4'&&*ptr_cadena!='5'&&*ptr_cadena!='6'&&*ptr_cadena!='7'&&*ptr_cadena!='8'&&*ptr_cadena!='9'&&*ptr_cadena!='\n')
			return 0;
		ptr_cadena++;
	}
	return 1;
}

int pos_caracter_en_cadena(char caracter,char* cadena){
	char* ptr_cadena=cadena;
	int pos=0;
	while(*ptr_cadena!='\0'){
		if(*ptr_cadena==caracter)
		return pos;
		ptr_cadena++;
		pos++;
	}
	return -1;
}
