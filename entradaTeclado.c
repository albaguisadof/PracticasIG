/*	Prácticas de Informática Gráfica

	Grupo C					Curso 2022-23
 	
	Codigo base para la realización de las practicas de IG
	
	Estudiante: 

=======================================================
	G. Arroyo, J.C. Torres 
	Dpto. Lenguajes y Sistemas Informticos
	(Univ. de Granada)

 This program is free software; you can redistribute it and/or
 modify it under the terms of the GNU General Public License
 as published by the Free Software Foundation; either version 2
 of the License, or (at your option) any later version.

 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details 
 http://www.gnu.org/copyleft/gpl.html

=======================================================/
modulo entradaTeclado.c
	Gestion de eventos de teclado
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <GL/glut.h>		// Libreria de utilidades de OpenGL
#include "practicasIG.h"


/** 

Imprime en la consola las instrucciones del programa

**/
void printHelp ()
{

  printf ("\n\n     Prácticas de Informática Gráfica	Curso 2022-2023");
  printf ("\n\n Dpto. Lenguajes y Sistemas Informaticos");
  printf ("\n E.T.S.I. Informatica		Univ. de Granada ");
  printf ("\n");
  printf ("\n Opciones: \n\n");
  printf ("h, H: Imprime informacion de ayuda \n");
  printf ("PgUp, PgDn: avanza y retrocede la cámara \n\n");
  printf ("+,-: avanza y retrocede la cámara \n\n");
  printf ("Teclas de movimiento de cursor: giran la camara\n");

  // PRACTICA1
  printf ("\np: muestra los puntos del modelo\n");  
  printf ("l: muestra elas líneas del modelo\n");   
  printf ("f: muestra el modelo completo\n");  
  printf ("i: muestra el modelo con iluminación\n\n");

  // PRACTICA3
  printf ("\nc: Disminuye la altura del gancho de la grúa\n");
  printf ("C: Aumenta la altura del gancho de la grúa\n");
  printf ("b: Disminuye los grados del brazo de la grúa\n");
  printf ("B: Aumenta los grados del brazo de la grúa\n");
  printf ("v: Disminuye los grados de la estructura de la grúa\n");
  printf ("V Aumenta los grados de la estructura de la grúa\n");
  printf ("\na: inicia/termina el movimiento de la grúa\n");
  printf ("G: Aumenta la velocidad del gancho de la grúa\n");
  printf ("g: Disminuye la velocidad del gancho de la grúa\n");
  printf ("K: Aumenta la velocidad de giro del brazo de la grúa\n");
  printf ("k: Disminuye la velocidad de giro del brazo de la grúa\n");
  printf ("J: Aumenta la velocidad de giro de toda la grúa\n");
  printf ("j: Disminuye la velocidad de giro de toda la grúa\n\n");

  //PRACTICA4
  printf ("1:Activa los dos focos de luz de la práctica 4\n");
  printf ("2:Desactiva los focos añadidos, nos quedaría la luz por defecto de la práctica.\n\n");

  //Practica5
  printf("F1: Activa la vista de frente\n");
  printf("F2: Activa la vista de alzado\n");
  printf("F3: Activa la vista de perfil\n");

  printf ("\n Escape: Salir");
  printf ("\n\n\n");
}




/* @teclado ---------------------------------------------------------------- */

/** 		void letra (unsigned char k, int x, int y)

Este procedimiento es llamado por el sistema cuando se pulsa una tecla normal
El codigo k es el ascii de la letra

Para anyadir nuevas ordenes de teclado coloca el correspondiente case.

Parametros de entrada:

k: codigo del caracter pulsado

x:

y:

**/

float rotxCamara = 30, rotyCamara = 45;
float dCamara = 10;
float ccx = 0, ccy = 0, ccz = 0;
float incrementoz = 0, incrementox = 0;


void letra (unsigned char k, int x, int y)
{

  switch (k)
    {
    case 'h':
    case 'H':
      printHelp ();		// H y h imprimen ayuda
      break;
    case '+':			// acerca la cámara
      dCamara -= 5.0;
      break;
    case '-':			// aleja la cámara
      dCamara += 5.0;
      break;
    case 27:			// Escape  Terminar
      exit (0);
    case 'p':
      setModo(GL_POINT);
      break;
    case 'l':
      setModo(GL_LINE);
      break;
    case 'f':
      setModo(GL_FILL);
      break;
    case 'i':
      iluminacion();
      break;
    case 'c':
      disminuirAlturaGancho();
      break;
    case 'C':
      incrementarAlturaGancho();
      break;
    case 'b':
      disminuirGradoBrazo();
      break;
    case 'B':
      incrementarGradoBrazo();
      break;
    case 'v':
      disminuirGradoEstructura();
      break;
    case 'V':      
      incrementarGradoEstructura();
      break;
    case 'a':
      activarAnimacion();
      break;
    case 'G':
      incrementarVGancho();
      break;
    case 'g':
      disminuirVGancho();
      break;
    case 'K':
      incrementarVAng1();
      break;
    case 'k':
      disminuirVAng1();
      break;
    case 'J':
      incrementarVAng2();
      break;
    case 'j':
      disminuirVAng2();
      break;
    case '1':
      setLuz1();
      break;
    case '2':
      setLuz2();
      break;
    case 'S':
      ccz--;
      incrementoz++;
      break;
    case 'W':
      ccz++;
      incrementoz--;
      break;
    case 'D':
       ccx--;
       incrementox++;
       break;
    case 'A':
      ccx++;
      incrementox--;
      break;
    case 'R':
      ccx = incrementox;
      ccy = 0;
      ccz = incrementoz;
      incrementox = 0;
      incrementoz = 0;
      break;
    default:
      return;
    }
  setPos(ccx,ccy,ccz);
  setCamara (rotxCamara, rotyCamara, dCamara);
  glutPostRedisplay ();		// Algunas de las opciones cambian paramentros
}				// de la camara. Es necesario actualziar la imagen

/**		void especial(int k, int x, int y)
Este procedimiento es llamado por el sistema cuando se pulsa una tecla
especial. El codigo k esta definido en glut mediante constantes

Parametros de entrada:

k: codigo del caracter pulsado (definido en glut mediante constantes).

x:

y:

**/
void especial (int k, int x, int y)
{

  switch (k)
    {
    case GLUT_KEY_UP:
      rotxCamara += 5.0;	// Cursor arriba + rotacion x
      if (rotxCamara > 360)
	rotxCamara -= 360;
      break;
    case GLUT_KEY_DOWN:
      rotxCamara -= 5.0;
      if (rotxCamara < 0)
	rotxCamara += 360;
      break;
    case GLUT_KEY_LEFT:
      rotyCamara += 5.0;
      if (rotyCamara > 360)
	rotyCamara -= 360;
      break;
    case GLUT_KEY_RIGHT:
      rotyCamara -= 5.0;
      if (rotyCamara < 0)
	rotyCamara += 360;
      break;
    case GLUT_KEY_PAGE_DOWN:	// acerca la cámara
      dCamara -= 5.0;
      break;
    case GLUT_KEY_PAGE_UP:	// aleja la cámara
      dCamara += 5.0;
      break;
    case GLUT_KEY_F1:
      vistaFrente();
      break;
    case GLUT_KEY_F2:
      vistaAlzado();
      break;
    case GLUT_KEY_F3:
      vistaPerfil();
      break;
    default:
      return;
    }
  setCamara (rotxCamara, rotyCamara, dCamara);
  glutPostRedisplay ();		// Actualiza la imagen (ver proc. letra)
}
