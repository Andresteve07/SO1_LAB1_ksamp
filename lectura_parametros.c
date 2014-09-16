#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <getopt.h>


#include "manejo_cadenas.h"
#include "manejo_cadenas.c"

#include "lectura_parametros.h"

#define TAM_CONT 256


void leer_CPU(){
	
	FILE *f;
	
	f = fopen("/proc/cpuinfo","r");
	printf("Tipo de CPU:      %s\n",leer_palabra(1,obtener_linea_pos(f,nro_linea_con_palabra(f,"vendor_id"))));
	printf("Modelo de CPU:    ");
	int i;
	int cant_pal=cant_palabras(obtener_linea_pos(f,nro_linea_con_palabra(f,"model name")));
	for(i=2;i<cant_pal;i++){
		printf("%s ",leer_palabra(i,obtener_linea_pos(f,nro_linea_con_palabra(f,"model name"))));
	}
	printf("\n");
	fclose(f);
	
}
void leer_Kernel(){
	FILE *f;
	
	f = fopen("/proc/sys/kernel/osrelease","r");
	printf("Kernel:           %s",obtener_linea_pos(f,0));	
	fclose(f);
}

void leer_TiempoT(){
	FILE *f;
	
	f = fopen("/proc/uptime","r");
	char* aux = obtener_linea_pos(f,0);
	//printf("_______%s________\n",aux);
	char* num=leer_palabra(0,aux);
	int segundos=atoi( num );
	int dias, horas, minutos;
    dias = segundos/(3600*24);
    horas = segundos/(60*60);
    segundos %= 60*60;
    minutos = segundos / 60;
    segundos %= 60;

	/*------TÉCNICA DE DIVISION DE ENTERO-----------
	dias = segundos / ( 24 * 60 * 60 );
	segundos -= ( dias * ( 24 * 60 * 60 ) );
	
	horas = segundos / ( 60 * 60 );
	segundos -= ( horas * ( 60 * 60 ) );
	
	minutos = segundos / 60;
	segundos -= ( minutos * 60 );*/

	printf("Up Time:          %i:%i:%i:%i\n",dias,horas,minutos,segundos);
	fclose(f);	
}
void cabecera(){
	FILE *f;
	f = fopen("/proc/sys/kernel/hostname","r");
	printf("************************************************************\n");
	printf("Nombre:                    %s",obtener_linea_pos(f,0));
	time_t rawtime;
	time ( &rawtime );
	printf("Fecha y hora actual:       %s",ctime(&rawtime));
	printf("************************************************************\n\n");
	
	fclose(f);
}
void FyHInicio(){
	FILE *f;
	f=fopen("/proc/uptime","r");
	
	char* linea=obtener_linea_pos(f,0);
	//printf("Fecha y hora de inicio:   %s",linea);
	char* tiempo_str=leer_palabra(0,linea);
	
	int tiempo_int=atoi(tiempo_str);
	
	time_t tiempo_t; // declare a time_t variable
	tiempo_t = (time_t) tiempo_int; // case the time_t variable to a long int
	
	time_t tiempo_actual =time(0);
	time_t tiempo_ini=tiempo_actual-tiempo_t;
	printf("Fecha y hora de inicio:   %s",ctime(&tiempo_ini));
	fclose(f);
}
	
void leer_CPUT(){
	FILE *f;
	
	f = fopen("/proc/stat","r");
	//char* aux = obtener_linea_pos(f,nro_linea_con_palabra(f,"cpu "));
	//printf("_____________%i___________\n",nro_linea_con_palabra(f,"cpu"));
	printf("Tiempo de Usuario:        %s USER_HZ (jiffies)\n",leer_palabra(1,obtener_linea_pos(f,nro_linea_con_palabra(f,"cpu"))));
	printf("Tiempo de Sistema:        %s USER_HZ (jiffies)\n",leer_palabra(3,obtener_linea_pos(f,nro_linea_con_palabra(f,"cpu"))));
	printf("Tiempo sin uso:           %s USER_HZ (jiffies)\n",leer_palabra(4,obtener_linea_pos(f,nro_linea_con_palabra(f,"cpu"))));
	fclose(f);
	
	
	
}

void leer_CCCONTEXTO(){
	FILE *f;
	f = fopen("/proc/stat","r");
	printf("Cambios de Contexto:      %s\n", leer_palabra(1,obtener_linea_pos(f,nro_linea_con_palabra(f,"ctxt"))));
	fclose(f);
}
void leer_NumProc(){
	FILE *f;
	f = fopen("/proc/stat","r");
	printf("Nro Procesos:             %s\n", leer_palabra(1,obtener_linea_pos(f,nro_linea_con_palabra(f,"processes"))));
	fclose(f);
}
void leer_NumPetD(){
	FILE *f;
	f = fopen("/proc/diskstats","r");
	
	printf("Peticiones a disco:                     %s\n", leer_palabra(3,obtener_linea_pos(f,nro_linea_con_palabra(f,"sda"))));
	fclose(f);
}
void leer_promCar(){
	FILE *f;
	f = fopen("/proc/loadavg","r");
	printf("Promedio de carga en el último minuto:  %s\n", leer_palabra(0,obtener_linea_pos(f,0)));
	fclose(f);
}
void leer_TotalMEM(){
	FILE *f;
	f = fopen("/proc/meminfo","r");
	int memt=atoi(leer_palabra(1,obtener_linea_pos(f,0)));
	printf("Memoria Total:                          %i KB\n",memt);
	fclose(f);
}
void leer_TotalMEMPH(){
	FILE *f;
	f = fopen("/proc/meminfo","r");
	int memt=atoi(leer_palabra(1,obtener_linea_pos(f,0)));
	printf("Memoria Total:                          %i MB\n",memt/1024);
	fclose(f);
}
void leer_MEMDisp(){
	FILE *f;
	f = fopen("/proc/meminfo","r");
	int memd=atoi(leer_palabra(1,obtener_linea_pos(f,1)));
	printf("Memoria Disponible:                     %i KB\n",memd);
	fclose(f);
}
void leer_MEMDispPH(){
	FILE *f;
	f = fopen("/proc/meminfo","r");
	int memd=atoi(leer_palabra(1,obtener_linea_pos(f,1)));
	printf("Memoria Disponible:                     %i MB\n",memd/1024);
	fclose(f);
}
