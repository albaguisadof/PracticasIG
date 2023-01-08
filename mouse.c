/*	Prácticas de Informática Gráfica

	Grupo C					Curso 2022-23
 	
	Codigo base para la realización de las practicas de IG
	
	Estudiante: Alba Guisado Farnes

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
	modulo mouse.c
	Gestion de eventos de raton

*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <GL/glut.h>		// Libreria de utilidades de OpenGL
#include "practicasIG.h"
//#include "visual.c"

/**	 void clickRaton( int boton, int estado, int x, int y )

Procedimiento para gestionar los eventos de pulsacion de los botones del raton.

Argumentos:

boton: Codigo glut del boton que ha manipulado el usuario.

estado: Estado en el que esta el boton que se ha pulsado.

x,y: Posicion, en coordenadas de pantalla, en que se encuantra el cursor.

**/

float Xref, Yref;

bool RatonPulsado = GL_FALSE;

void clickRaton (int boton, int estado, int x, int y)
{
	if(boton == GLUT_MIDDLE_BUTTON){
		if(estado == GLUT_DOWN){
			//se entra en el estado "moviendo camara"
			Xref = x;
			Yref = y;
			RatonPulsado = GL_TRUE;
		}else{
			//Se sale del estado "moviendo camara"
			RatonPulsado = GL_FALSE;
		}
	}
}


/**	void RatonMovido( int x, int y )

Procedimiento para gestionar los eventos de movimiento del raton.

Argumentos:

x,y: Posicion, en coordenadas de pantalla, en que se encuantra el cursor.

**/

void RatonMovido (int x, int y)
{
	if(RatonPulsado){
		setViewRoty(getViewRoty() - ((Yref -y)/100.0));
		setViewRotx(getViewRotx() + ((Xref -x)/100.0));
		Xref = x;
		Yref = y;
		transformacionVisualizacion();
		glutPostRedisplay();
	}
}
