//      SOI-TP1_2013.cpp
//      
//      Copyright 2011 Esteban Morales <steve07@steve07-desktop>
//      
//      This program is free software; you can redistribute it and/or modify
//      it under the terms of the GNU General Public License as published by
//      the Free Software Foundation; either version 2 of the License, or
//      (at your option) any later version.
//      
//      This program is distributed in the hope that it will be useful,
//      but WITHOUT ANY WARRANTY; without even the implied warranty of
//      MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//      GNU General Public License for more details.
//      
//      You should have received a copy of the GNU General Public License
//      along with this program; if not, write to the Free Software
//      Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
//      MA 02110-1301, USA.


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <getopt.h>

#include "lectura_parametros.h"
#include "lectura_parametros.c"

#define TAM_CONT 256

// Declaración de funciones.
void imprimirB();
void imprimirC();
void imprimirD(const char*,const char*);
void imprimirDPH(const char*,const char*);
void imprime_uso();

const char* nombre_programa;

int main(int argc, char** argv)
{
	int siguiente_opcion;
  
  /* Una cadena que lista las opciones cortas válidas */
  const char* const op_cortas = "Hhsl:" ;

  /* Una estructura de varios arrays describiendo los valores largos */
  const struct option op_largas[] =
  {
      { "help",         0,  NULL,   'H'},
      { "humanamente",  0,  NULL,   'h'},
      { "incisoC",      0,  NULL,   's'},
      { "incisoD",      1,  NULL,   'l'},
      { NULL,           0,  NULL,   0  }
  };

  /* El nombre del fichero que recibe la salida del programa */
  const char* tiempo = NULL ;
  const char* per = NULL ;
  

  /* Bandera a activar si hay que imprimir más información
   * en el modo verbose */
  //int verbose = 0;

  /* Guardar el nombre del programa para incluirlo a la salida */
  nombre_programa = argv[0];

  /* Si se ejecuta sin parámetros ni opciones */
  if (argc == 1)
  {
      imprimirB();
      exit(EXIT_SUCCESS);
  }
  int funcion_s=0;
  int funcion_l=0;
  int para_humanos=0;
  while (1)
  {
      /* Llamamos a la función getopt */
      if(optind>=argc)
      exit(1);
      else {
      char* aux=argv[optind];
      if((pos_caracter_en_cadena('-',aux)!=0) && !funcion_l){
		  printf("..::ERROR::..");
		  imprime_uso();
		  exit(1);}
     }
      siguiente_opcion = getopt_long (argc, argv, op_cortas, op_largas, NULL);
	  
      if (siguiente_opcion == -1)
          break; /* No hay más opciones. Rompemos el bucle */

      switch (siguiente_opcion)
      {
          case 'h' : /* -h o --help */
              funcion_l=0;
              if(argc==2){
				  imprime_uso();
				  exit(1);
			  }
              para_humanos=1;
              break;
          case 'H' : /* -h o --help */
              funcion_l=0;
              imprime_uso();
              exit(EXIT_SUCCESS);
			  
          case 's' : /* -s o --incisoC */
              funcion_s=1;
              funcion_l=0;
              imprimirC();
              break;
			  
          case 'l' : /* -l o --incisoD */
              { 
				funcion_l=1;
				if(funcion_s == 1){
					imprime_uso();
					exit(1);
				}		
				int i=0;
				int pos_l=0; 
				while( i<argc && pos_l==0 ){
					if(strcmp(argv[i],"-l")==0)
						pos_l=i;
					i++;
				}
				//printf("la posicion de -l es: %i",pos_l);
				if(argc!=pos_l+3){
					imprime_uso();
					exit(1);
				}				
				per = optarg; /* optarg contiene el argumento de -o */
				char* aux2 ;
				aux2=strdup(per);
				int arg_valido=contiene_solo_nros(aux2);
				//printf("!!!!!!!!!!!!! %i !!!!!!!!!",arg_valido);
					if(!arg_valido){
						imprime_uso();
						exit(1);
					}
					else
					{
							tiempo = argv[optind];
							char* aux3 = strdup(tiempo);
							if(!contiene_solo_nros(aux3)){
								imprime_uso();
								exit(1);
							}
							if(para_humanos)
							imprimirDPH(per,tiempo);
							else
							imprimirD(per,tiempo);
					}
				}
              break;
			  
          case '?' : /* opción no valida */
              funcion_l=0;
              imprime_uso(); /* código de salida 1 */
              exit(1);
		 
          case -1 : /* No hay más opciones */
              funcion_l=0;
              break;
			
          default : /* Algo más? No esperado. Abortamos */
              abort();
	  }
  }
  
  /* Salida del programa principal */
  return 0;

}

void imprimirB(){
	cabecera();
	leer_CPU();
	leer_Kernel();
	leer_TiempoT();
}

void imprimirC(){
	imprimirB();
	printf("____________________________________________________________\n");
	leer_CPUT();
	leer_CCCONTEXTO();
	FyHInicio();
	leer_NumProc();
	
}

void imprimirD(const char* p, const char* t){
	imprimirC();
	char* periodo=strdup(p);
	char* totalt=strdup(t);
	int per=atoi(periodo);
	int total=atoi(totalt);

	int i=0;
	while(i<(total/per)){	
	printf("____________________________________________________________\n");
	leer_NumPetD();
	leer_TotalMEM();
	leer_MEMDisp();
	leer_promCar();
	sleep(per);
	i++;
	}
}

void imprimirDPH(const char* p, const char* t){
	imprimirC();
	char* periodo=strdup(p);
	char* totalt=strdup(t);
	int per=atoi(periodo);
	int total=atoi(totalt);

	int i=0;
	while(i<(total/per)){	
	printf("____________________________________________________________\n");
	leer_NumPetD();
	leer_TotalMEMPH();
	leer_MEMDispPH();
	leer_promCar();
	sleep(per);
	i++;
	}
}

void imprime_uso ()
{
    printf("Uso: %s opciones [ argumentos ...]\n", nombre_programa);
    printf("    -H  --help                                        Enseña esta ayuda\n"
           "    -s  --incisoC                                     Imprime la información solicitada en el inciso (C)\n"
           "    -l  --incisoD <intervalo> <tiempo de evaluación>  Imprime la información solicitada en el inciso (D)\n"
           "    -h  --humanamente                                 Si se coloca antes del operador (-l) pasa los datos de memoria en MB\n" 
           );
}
