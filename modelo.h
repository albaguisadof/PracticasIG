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

=======================================================

	 modelo.h
*/

#include <vector>
using namespace std;

/**
	Funcion de redibujado. Se ejecuta con los eventos postRedisplay
**/
void Dibuja (void);

/**
	Funcion de fondo
**/
void idle (int v);

/*************************************PRACTICA1***********************************************/

/**
	Funcion de inicializacion del modelo y de las variables globales
**/
void initModel();

void iluminacion();

vector <float> normal(float x1, float y1, float z1, float x2, float y2, float z2, float x3, float y3, float z3);

void dibujar_normal(vector<float> n, int x, int y , int z);

void setModo(int m);

class Objeto3D 
{ 
public: 

virtual void draw( ) = 0; // Dibuja el objeto
} ; 


/*****************************************PRACTICA2**************************************************/

struct v3{
  float x;
  float y;
  float z;

	v3& operator=(const v3 &v2){
		this->x = v2.x;
		this->y = v2.y;
		this->z = v2.z;
		return *this;
	}

	v3& operator+=(const v3 &v2){
		this->x = this->x + v2.x;
		this->y = this->y + v2.y;
		this->z = this->z + v2.z;
		return *this;
	}

};


struct i3{
  int uno;
  int dos;
  int tres;
};

v3 normalizar(v3 v);

v3 normalP2(v3 uno, v3 dos, v3 tres);

void initModel2();

/*********************************PRACTICA3*************************************/

void initModel3();
void estructura();
void brazo();
void gancho();
void cabeza();
void grua();
void incrementarAlturaGancho();
void disminuirAlturaGancho();
void incrementarGradoBrazo();
void disminuirGradoBrazo();
void incrementarGradoEstructura();
void disminuirGradoEstructura();
void activarAnimacion();
void Animacion();
void incrementarVGancho();
void disminuirVGancho();
void incrementarVAng1();
void disminuirVAng1();
void disminuirVAng2();
void incrementarVAng2();


/*********************************PRACTICA4*************************************/

struct f2{
	float x;
	float y;
};

void inicializar4();
void initModel4();

void setLuz1();
void setLuz2();

/*********************************PRACTICA4*************************************/
/*
void colorSleccion(int i, int componente);
void dibujoEscena();
*/
int pick(int x, int y, int *i, int *parte);

void vistaFrente();
void vistaAlzado();
void vistaPerfil();
