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
modulo modelo.c
    Representación del modelo
    Funciones de dibujo
    Función Idle

*/
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <GL/glut.h>		// Libreria de utilidades de OpenGL
#include "practicasIG.h"
#include <vector>
#include "file_ply_stl.h"
#include "estructura.h"
#include "lector-jpg.h"


using namespace std;


/****************************************PRACTICA1*************************************************/
int modo = GL_FILL;
bool luz;

vector <float> normal(float x1, float y1, float z1, float x2, float y2, float z2, float x3, float y3, float z3){
  vector<float> A, B, N;
  A.push_back(x2-x1);
  A.push_back(y2-y1);
  A.push_back(z2-z1);
  B.push_back(x3-x2);
  B.push_back(y3-y2);
  B.push_back(z3-z2);

  float x, y, z;
  x = (A[1]*B[2]-A[2]*B[1]);
  y = (A[0]*B[2]-B[0]*A[1]);
  z = (A[0]*B[1]-A[1]*B[0]);

  float modulo = sqrt(x*x + y*y + z*z);

  N.push_back(x/modulo);
  N.push_back(y/modulo);
  N.push_back(z/modulo);

  return N;
}

void iluminacion(){
  if(luz)
    luz = false;
  else
    luz = true;
}

void setModo(int m){
  modo = m;
}

class Ejes:Objeto3D 
{ 
public: 
    float longitud = 30;
// Dibuja el objeto
void draw( )
{
  glDisable (GL_LIGHTING);
  glBegin (GL_LINES);
  {
    glColor3f (0, 1, 0);
    glVertex3f (0, 0, 0);
    glVertex3f (0, longitud, 0);

    glColor3f (1, 0, 0);
    glVertex3f (0, 0, 0);
    glVertex3f (longitud, 0, 0);

    glColor3f (0, 0, 1);
    glVertex3f (0, 0, 0);
    glVertex3f (0, 0, longitud);
  }
  glEnd ();
  glEnable (GL_LIGHTING);

}
};

class Cubo:public Objeto3D
{
  public:
    float lado;

		Cubo(float lado){
			this->lado = lado;
		}

		virtual void draw(){
      vector<float> n1,n2,n3,n4,n5,n6;

      glBegin( GL_QUADS ) ;
          glColor3f(1.0,0,0);
          n1 = normal(lado,0,0,lado,lado,0,lado,lado,lado);
          glNormal3f( n1[0] , n1[1], n1[2] ) ;
          glVertex3f( lado , 0 , 0 ) ;
          glVertex3f( lado , lado , 0 ) ;
          glVertex3f( lado , lado , lado ) ;
          glVertex3f( lado , 0 , lado ) ;
      glEnd();


      glBegin(GL_QUADS);
          glColor3f(1.0,0,0);
          n2 = normal(0,0,0,0,0,lado,0,lado,lado);
          glNormal3f( n2[0], n2[1], n2[2]) ;
          glVertex3f( 0 , 0 , 0 ) ;
          glVertex3f( 0 , 0 , lado) ;
          glVertex3f( 0 , lado , lado ) ;
          glVertex3f( 0 , lado , 0 ) ;
      glEnd();

      glBegin(GL_QUAD_STRIP);
          glColor3f(1.0,0,0);
          n3 = normal(lado,lado,lado,0,lado,lado,lado,0,lado);
          glNormal3f( n3[0] , n3[1], n3[2] ) ;
          glVertex3f (lado, lado, lado);
          glVertex3f (0, lado, lado);
          glVertex3f (lado, 0, lado);
          glVertex3f (0, 0, lado);
          n4 = normal(0,0,lado,lado,0,0,0,0,0);
          glNormal3f( n4[0] , n4[1], n4[2] ) ;
          glVertex3f (lado, 0, 0);
          glVertex3f (0, 0, 0);
          n5 = normal(0,0,0,0,lado,0,lado,lado,0);
          glNormal3f( n5[0] , n5[1], n5[2] ) ;
          glVertex3f (lado, lado, 0);
          glVertex3f (0, lado, 0);
          n6 = normal(0,lado,0,lado,lado,0,lado,lado,lado);
          glNormal3f( n6[0] , n6[1], n6[2] ) ;
          glVertex3f (lado, lado, lado);
          glVertex3f (0, lado, lado);
      glEnd();
  
		}

};

class Piramide:public Objeto3D
{
  public:
    float lado, altura;

    Piramide(float lado, float altura){
      this->lado = lado;
      this->altura = altura;
    }

    virtual void draw(){
       vector<float> n;
     
      glBegin(GL_QUADS);
        glColor3f(0,1,0);
        n = normal(lado,0,0,lado,0,0,0,0,lado);
        glNormal3f(n[0],n[1],n[2]);
        glVertex3f(0,0,0);
        glVertex3f(lado,0,0);
        glVertex3f(lado,0,lado);
        glVertex3f(0,0,lado);
      glEnd();

      glBegin(GL_TRIANGLES);
        glColor3f(0,1,0);
        n = normal(lado/2,altura,lado/2,0,0,lado,lado,0,lado);
        glNormal3f(n[0],n[1],n[2]);
        glVertex3f(lado/2, altura,lado/2);
        glVertex3f(0,0,lado);
        glVertex3f(lado,0,lado);
        
        n = normal(lado/2,altura,lado/2,0,0,0,0,0,lado);
        glNormal3f(n[0],n[1],n[2]);
        glVertex3f(lado/2, altura,lado/2);
        glVertex3f(0,0,0);
        glVertex3f(0,0,lado);
        
        n = normal(lado/2,altura,lado/2,lado,0,0,0,0,0);
        glNormal3f(n[0],n[1],n[2]);
        glVertex3f(lado/2, altura,lado/2);
        glVertex3f(lado,0,0);
        glVertex3f(0,0,0);
        
        n = normal(lado/2,altura,lado/2,lado,0,lado,lado,0,0);
        glNormal3f(n[0],n[1],n[2]);
        glVertex3f(lado/2, altura,lado/2);
        glVertex3f(lado,0,lado);
        glVertex3f(lado,0,0);
        
      glEnd();
        
  
    }
};

class Octaedro:public Objeto3D
{
  public:
    float lado;
    float altura;

    Octaedro(float lado){
      this->lado = lado;
      this->altura = (lado*sqrt(2))/2;
    }

    virtual void draw(){
      vector<float> n;

      glBegin(GL_TRIANGLES);
        glColor3f(0.5,0.5,1);
        n = normal(lado/2,altura,lado/2,0,0,lado,lado,0,lado);
        glNormal3f(n[0],n[1],n[2]);
        glVertex3f(lado/2, altura,lado/2);
        glVertex3f(0,0,lado);
        glVertex3f(lado,0,lado);
        
        n = normal(lado/2,altura,lado/2,0,0,0,0,0,lado);
        glNormal3f(n[0],n[1],n[2]);
        glVertex3f(lado/2, altura,lado/2);
        glVertex3f(0,0,0);
        glVertex3f(0,0,lado);
        
        n = normal(lado/2,altura,lado/2,lado,0,0,0,0,0);
        glNormal3f(n[0],n[1],n[2]);
        glVertex3f(lado/2, altura,lado/2);
        glVertex3f(lado,0,0);
        glVertex3f(0,0,0);
        
        n = normal(lado/2,altura,lado/2,lado,0,lado,lado,0,0);
        glNormal3f(n[0],n[1],n[2]);
        glVertex3f(lado/2, altura,lado/2);
        glVertex3f(lado,0,lado);
        glVertex3f(lado,0,0);
        
      glEnd();


      glBegin(GL_TRIANGLES);
        glColor3f(0.5,0.5,1);
        n = normal(lado/2,-altura,lado,0,lado,lado/2,0,0,lado);
        glNormal3f(n[0],n[1],n[2]);
        glVertex3f(lado/2, -altura,lado/2);
        glVertex3f(lado,0,lado);
        glVertex3f(0,0,lado);
        
        
        n = normal(lado/2,-altura,lado/2,0,0,lado,0,0,0);
        glNormal3f(n[0],n[1],n[2]);
        glVertex3f(lado/2, -altura,lado/2);
        glVertex3f(0,0,lado);
        glVertex3f(0,0,0);
        
        
        n = normal(lado/2,-altura,0,0,0,lado/2,lado,0,0);
        glNormal3f(n[0],n[1],n[2]);
        glVertex3f(lado/2, -altura,lado/2);
        glVertex3f(0,0,0);
        glVertex3f(lado,0,0);
        
        
        n = normal(lado/2,-altura,lado/2,lado,0,0,lado,0,lado);
        glNormal3f(n[0],n[1],n[2]);
        glVertex3f(lado/2, -altura,lado/2);
        glVertex3f(lado,0,0);
        glVertex3f(lado,0,lado);
        
      glEnd();

    }
};

class Prisma:public Objeto3D
{
public:
  float lado, altura;

  Prisma(float lado,float altura){
    this->lado = lado;
    this->altura = altura;
  }

  virtual void draw(){
    vector<float> n;

    glBegin(GL_TRIANGLES);
      glColor3f(0.7,0.5,0.5);
      n = normal(0,0,0,0,0,lado,lado,0,0);
      glNormal3f(n[0],n[1],n[2]);
      glVertex3f(0,0,0);
      glVertex3f(lado,0,0);
      glVertex3f(0,0,lado);
      

      n = normal(0,altura,0,lado,altura,0,0,altura,lado);
      glNormal3f(n[0],n[1],n[2]);
      glVertex3f(0,altura,0);
      glVertex3f(0,altura,lado);
      glVertex3f(lado,altura,0);
    glEnd();

    glBegin(GL_QUADS);
      glColor3f(0.7,0.5,0.5);
      n = normal(0,0,0,0,0,lado,0,altura,lado);
      glNormal3f(n[0],n[1],n[2]);
      glVertex3f(0,0,0);
      glVertex3f(0,0,lado);
      glVertex3f(0,altura,lado);
      glVertex3f(0,altura,0);

      n = normal(0,0,lado,lado,0,0,lado,altura,0);
      glNormal3f(n[0],n[1],n[2]);
      glVertex3f(0,0,lado);
      glVertex3f(lado,0,0);
      glVertex3f(lado,altura,0);
      glVertex3f(0,altura,lado);

      n = normal(lado,altura,0,lado,0,0,0,0,0);
      glNormal3f(n[0],n[1],n[2]);
      glVertex3f(lado,altura,0);
      glVertex3f(lado,0,0);
      glVertex3f(0,0,0);
      glVertex3f(0,altura,0);
    glEnd();
  }
};

void initModel()
{
  Cubo cubo(1.5);
  float color1[4]={1.0,0,0,1};
  glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, color1);
  cubo.draw();

  Piramide piramide(1.5,2.5);
  float color2[4]={0,1,0,1};
  glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, color2);
  glTranslatef(3,0,0);
  piramide.draw();

  Octaedro octaedro(1);
  float color3[4]={0.5,0.5,1,1};
  glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, color3);
  glTranslatef(0,1,3);
  octaedro.draw();

  Prisma prisma(1,1.5);
  float color4[4]={0.7,0.5,0.5,1};
  glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, color4);
  glTranslatef(-2,-1,0);
  prisma.draw();

}

/****************************************PRACTICA2*************************************************/

class Malla:public Objeto3D{
  public:
    vector<v3> vertices;
    vector<i3> caras;
    vector<v3> normal_vertices;
    vector<v3> normal_caras;
    int n_ver, n_car;

    void calculoNCaras(){
        normal_caras.resize(n_car);
        for(int i = 0; i < n_car; i++){
          normal_caras[i] = normalP2(vertices[caras[i].uno], vertices[caras[i].dos], vertices[caras[i].tres]);
        }
    }

    void calculoNVertices(){
      normal_vertices.resize(n_ver);
      for(int i = 0; i< n_ver; i++){
        normal_vertices[i].x = 0;
        normal_vertices[i].y = 0;
        normal_vertices[i].z = 0;
      }
      for(int i = 0; i < n_car; i++){
        normal_vertices[caras[i].uno] += normal_caras[i];
        normal_vertices[caras[i].dos] += normal_caras[i];
        normal_vertices[caras[i].tres] += normal_caras[i];
      }
      for(int i = 0; i < n_ver; i++){
        normal_vertices[i] = normalizar(normal_vertices[i]);
      }
      
    }

    void draw(){
      glShadeModel(GL_FLAT);
      glBegin(GL_TRIANGLES);
      for(int i = 0; i < n_car; i++){
      
        glNormal3f(normal_caras[i].x, normal_caras[i].y, normal_caras[i].z);
        glVertex3f(vertices[caras[i].uno].x, vertices[caras[i].uno].y, vertices[caras[i].uno].z);
        glVertex3f(vertices[caras[i].dos].x, vertices[caras[i].dos].y, vertices[caras[i].dos].z);
        glVertex3f(vertices[caras[i].tres].x, vertices[caras[i].tres].y, vertices[caras[i].tres].z);
        
       }
       glEnd();
    }


    void draw_smooth(){
      glShadeModel(GL_SMOOTH);
      glBegin(GL_TRIANGLES);
      for(int i = 0; i < n_car; i++){

        glNormal3f(normal_vertices[caras[i].uno].x, normal_vertices[caras[i].uno].y, normal_vertices[caras[i].uno].z);
        glVertex3f(vertices[caras[i].uno].x, vertices[caras[i].uno].y, vertices[caras[i].uno].z);
        glNormal3f(normal_vertices[caras[i].dos].x, normal_vertices[caras[i].dos].y, normal_vertices[caras[i].dos].z);
        glVertex3f(vertices[caras[i].dos].x, vertices[caras[i].dos].y, vertices[caras[i].dos].z);
        glNormal3f(normal_vertices[caras[i].tres].x, normal_vertices[caras[i].tres].y, normal_vertices[caras[i].tres].z);
        glVertex3f(vertices[caras[i].tres].x, vertices[caras[i].tres].y, vertices[caras[i].tres].z);
    
    }
    glEnd();
    }
    
};

class readPLY: public Malla{
  public:
  vector<float> vertices_ply;
  vector<int> caras_ply;

    readPLY(const char* archivo){
        ply::read(archivo, vertices_ply, caras_ply);
        n_ver = vertices_ply.size()/3;
        n_car = caras_ply.size()/3;


        for(int i = 0; i < n_ver; i++){
          v3 v;
          v.x = vertices_ply[3*i];
          v.y = vertices_ply[3*i + 1];
          v.z = vertices_ply[3*i + 2];
          vertices.push_back(v);
        }

        for(int i = 0; i < n_car; i++){
          i3 c;
          c.uno = caras_ply[3*i];
          c.dos = caras_ply[3*i + 1];
          c.tres = caras_ply[3*i + 2];
          caras.push_back(c);
        }
        
        calculoNCaras();
        calculoNVertices();
    }
};

class revolucion:public Malla{
  public:
  vector<float> vertices_ply;

  revolucion(const char *archivo, int vueltas){
    ply::read_vertices(archivo, vertices_ply);
    n_ver = vertices_ply.size()/3;

    v3 nuevo;
    for(int i = 0; i < vueltas; i++){
      for(int j = 0; j < n_ver; j++){
          float grados = 2*M_PI*i/(vueltas-1);
          nuevo.x = vertices_ply[3*j] * cos(grados);
          nuevo.y = vertices_ply[3*j+1];
          nuevo.z = vertices_ply[3*j] *(-sin(grados));
          vertices.push_back(nuevo);
      }
    }                                                                                                                                                                                                                   

    int k;
    i3 nueva;
    for(int i = 0; i < vueltas-1; i++){
      for(int j = 0; j < n_ver - 1; j++){
          k = n_ver*i+j;                                                                                          
          nueva.uno = k;
          nueva.dos = k + n_ver;
          nueva.tres = k+ n_ver + 1;
          caras.push_back(nueva);
          nueva.uno = k;
          nueva.dos = k + n_ver + 1;
          nueva.tres = k+1;
          caras.push_back(nueva);
      }
    }

    n_car = caras.size();
    n_ver = vertices.size();
    calculoNCaras();
    calculoNVertices();
  }

};

v3 normalizar(v3 v){
  v3 N;

  float x,y,z;
  x = v.x;
  y = v.y;
  z = v.z;

  float modulo = sqrt(x*x + y*y + z*z);

  if(modulo>0){
    N.x = x/modulo;
    N.y = y/modulo;
    N.z = z/modulo;
  }

  return N;
}

v3 normalP2(v3 uno, v3 dos, v3 tres){
  v3 A, B, N;

  A.x = dos.x - uno.x;
  A.y = dos.y - uno.y;
  A.z = dos.z - uno.z;
  B.x = tres.x - dos.x;
  B.y = tres.y - dos.y;
  B.z = tres.z - dos.z;

  float x, y, z;
  x = (A.y*B.z-A.z*B.y);
  y = (A.z*B.x-A.x*B.z);
  z = (A.x*B.y-A.y*B.x);

  float modulo = sqrt(x*x + y*y + z*z);

  if(modulo>0){
    N.x = x/modulo;
    N.y = y/modulo;
    N.z = z/modulo;
  }

  return N;
}


void initModel2(){
  revolucion peon("perfil.ply",10);
  float color2[4]={0.94,0,0.97,1};
  glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, color2);
  peon.draw();

  glTranslatef(-7,0,0);
  readPLY beethoven("beethoven.ply");
  float color1[4]={0.6,0.8,0.2,1};
  glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, color1);
  beethoven.draw_smooth();

  glTranslatef(18,0,0);
  readPLY coche("big_dodge.ply");
  float color3[4]={0.9,0.2,0.2,1};
  glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, color3);
  coche.draw_smooth();
}

/*******************************************PRACTICA3*****************************************************/


  float ang1=0, ang2=0, alturaGancho = 6;
  float color1[4]={0.6,0.8,0.2,1}; //verde
  float color2[4]={0.94,0,0.97,1}; //rosa
  float color3[4]={0.5,0.5,1,1};   //lila

  void estructura(){
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, color3);
    creaEstructura(0,0,0,0,10,0,2,2,5);
  }

  void brazo(){
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, color2);
    creaBrazo(-10,0,0,-1,0,0,1.6,5);
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, color1);
    creaTorre(0,0,0,0,4,0,2,2,3);
  }

  void gancho(){
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, color1);
    creaGancho(0,-alturaGancho,0,1);
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, color3);
    cilindro(0,0,0,0,-alturaGancho,0,0.1);
  }

  void cabeza(){
    glPushMatrix();
      brazo();
    glPopMatrix();
    glTranslatef(-9.5,0,0);
    glPushMatrix();
      gancho();
    glPopMatrix();
  }

  void grua(){
    glRotatef(ang2, 0,1,0);
    glPushMatrix();
      estructura();
    glPopMatrix();
    glTranslatef(0,10,0);
    glRotatef(ang1,0,1,0);
    glPushMatrix();
      cabeza();
    glPopMatrix();
  }

void incrementarAlturaGancho(){
  alturaGancho += 1;
  if(alturaGancho >= 11){
    alturaGancho = 11;
  }
}

void disminuirAlturaGancho(){
  alturaGancho -= 1;
  if(alturaGancho <= 0){
    alturaGancho = 0;
  }
}

void incrementarGradoBrazo(){
  ang1 += 1;
}

void disminuirGradoBrazo(){
  ang1 -= 1;
  if(ang1 == 360){
    ang1 = 0;
  }
}

void incrementarGradoEstructura(){
  ang2 += 1;
  if(ang2 == 360){
    ang2 = 0;
  }
}

void disminuirGradoEstructura(){
  ang2 -= 1;
  if(ang2 == 360){
    ang2 = 0;
  }
}

void initModel3(){
  grua();
}

//Animacion
bool animacion = false;
float v_gancho = 1.0;
float v_ang1 = 2.0;
float v_ang2 = 1.0;

void activarAnimacion(){
    if(animacion) 
      animacion = false;
    else  
      animacion = true;
}

void Animacion(){
  alturaGancho += v_gancho;
  if(alturaGancho >= 11){
    alturaGancho = 0;
  }
  ang2 += v_ang2;
  ang1 += v_ang1; 
}

void incrementarVGancho(){
  v_gancho += 1;
}

void disminuirVGancho(){
  v_gancho = v_gancho/2.0;
}

void incrementarVAng1(){
  v_ang1 += 2;
}

void disminuirVAng1(){
  v_ang1 = v_ang1/2.0;
}

void incrementarVAng2(){
  v_ang2 += 1;
}

void disminuirVAng2(){
  v_ang2 = v_ang2/2.0;
}


/*******************************************PRACTICA4**************************************************************/

class Dado:public Objeto3D{
  public: 
  GLuint texID;
  unsigned int ancho, alto;
  GLfloat ambient[4], difuse[4], specular[4], shininess, emission[4];

  Dado(float Mar, float Mag, float Mab,float Mdr, float Mdg, float Mdb, float Msr, 
          float Msg, float Msb,float e, float Mer, float Meg, float Meb){
    setAmbient(Mar, Mag, Mab);
    setDifuse(Mdr, Mdg, Mdb);
    setSpecular(Msr, Msg, Msb);
    setShininess(e);
    setEmission(Mer, Meg, Meb);
    }
  
  void textura(const char *nombre_arch){
   

    unsigned char* image = nullptr;
    image = LeerArchivoJPEG(nombre_arch, ancho, alto);

    glGenTextures(1, &texID);
    glBindTexture(GL_TEXTURE_2D, texID);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, ancho, alto,0, GL_RGB, GL_UNSIGNED_BYTE, image);

    delete image;
    image = nullptr;
  }

  void setAmbient(float Mar,float Mag,float Mab){
    ambient[0] = Mar;
    ambient[1] = Mag;
    ambient[2] = Mab;
    ambient[3] = 1.0;
  }

  void setDifuse(float Mdr,float Mdg,float Mdb){
    difuse[0] = Mdr;
    difuse[1] = Mdg;
    difuse[2] = Mdb;
    difuse[3] = 1.0;
  }
  void setSpecular(float Msr,float Msg, float Msb){
    specular[0] = Msr;
    specular[1] = Msg;
    specular[2] = Msb;
    specular[3] = 1.0;
  }

  void setShininess(float e){
    shininess = e;
  }

  void setEmission(float Mer, float Meg,float Meb){
    emission[0] = Mer;
    emission[1] = Meg;
    emission[2] = Meb;
    emission[3] = 1.0;
  }

  void setMaterial(){
    glMaterialfv(GL_FRONT, GL_AMBIENT, ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, difuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, &shininess);
    glMaterialfv(GL_FRONT, GL_EMISSION, emission);
  }


  void draw(){
    setMaterial();

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texID);

      int lado = 3;
      vector<float> n1,n2,n3,n4,n5,n6;

      glBegin( GL_QUADS ) ;
        glColor3f(1,1,1);

        //CARA NUMERO 4 (izq)
        n2 = normal(0,0,0,0,0,lado,0,lado,lado);
        glNormal3f( n2[0], n2[1], n2[2]) ;
        glTexCoord2f(0.75,1);
        glVertex3f( 0 , 0 , 0 ) ;
        glTexCoord2f(0.75,0.75);
        glVertex3f( 0 , 0 , lado) ;
        glTexCoord2f(0.5,0.75);
        glVertex3f( 0 , lado , lado ) ;
        glTexCoord2f(0.5,1);
        glVertex3f( 0 , lado , 0 ) ;

        //CARA NUMERO 5(trasera)
        n5 = normal(0,0,0,0,lado,0,lado,lado,0);
        glNormal3f( n5[0] , n5[1], n5[2] ) ;
        glTexCoord2f(0,0.75);
        glVertex3f (0, 0, 0);
        glTexCoord2f(0.25,0.75);
        glVertex3f (0, lado, 0);
        glTexCoord2f(0.25,0.5);
        glVertex3f (lado, lado, 0);
        glTexCoord2f(0,0.5);
        glVertex3f (lado, 0, 0);

        //CARA NUMERO 1 (superior)
        n6 = normal(lado,lado,lado,0,lado,lado,0,lado,0);
        glNormal3f( n6[0] , n6[1], n6[2] ) ;
        glTexCoord2f(0.25,0.75);
        glVertex3f (0, lado, lado);
        glTexCoord2f(0.5,0.75);
        glVertex3f (lado, lado, lado);
        glTexCoord2f(0.5,0.5);
        glVertex3f (lado, lado, 0);
        glTexCoord2f(0.25,0.5);
        glVertex3f (0, lado, 0);
        
        //CARA NUMERO 2 (frontal)
        n3 = normal(lado,lado,lado,0,lado,lado,0,0,lado);
        glNormal3f( n3[0] , n3[1], n3[2] ) ;
        glTexCoord2f(0.5,0.5);
        glVertex3f (lado, lado, lado);
        glTexCoord2f(0.7,0.5);
        glVertex3f (0, lado, lado);
        glTexCoord2f(0.75,0.75);
        glVertex3f (0, 0, lado);
        glTexCoord2f(0.5,0.75);
        glVertex3f (lado, 0, lado);

         //CARA NUMERO 6(inferior)
        n4 = normal(0,0,lado,0,0,0,lado,0,0);
        glNormal3f( n4[0] , n4[1], n4[2] ) ;
        glTexCoord2f(1,0.75);
        glVertex3f (0, 0, lado);
        glTexCoord2f(0.75,0.75);
        glVertex3f (0, 0, 0);
        glTexCoord2f(0.75,0.5);
        glVertex3f (lado, 0, 0);
        glTexCoord2f(1,0.5);
        glVertex3f (lado, 0, lado);

        //CARA NUMERO 3(derecha)
        n1 = normal(lado,0,0,lado,lado,0,lado,lado,lado);
        glNormal3f( n1[0] , n1[1], n1[2] ) ;
        glTexCoord2f(0.5,0.25);
        glVertex3f( lado , 0 , 0 ) ;
        glTexCoord2f(0.5,0.5);
        glVertex3f( lado , lado , 0 ) ;
        glTexCoord2f(0.75,0.5);
        glVertex3f( lado , lado , lado ) ;
        glTexCoord2f(0.75,0.25);
        glVertex3f( lado , 0 , lado ) ;
      glEnd();

    glDisable(GL_TEXTURE_2D);
  }
};

class RevolucionTextura:public Malla{
  public:
  vector<float> vertices_ply;
  vector<f2> coordTextura;
  GLuint texID = 0;
  unsigned int ancho, alto;
  int vueltas;
  int v_perfil;
  GLfloat ambient[4], difuse[4], specular[4], shininess, emission[4];

  RevolucionTextura(const char *archivo, int vueltas, float Mar, float Mag, float Mab,
                      float Mdr, float Mdg, float Mdb, float Msr, float Msg, float Msb,
                      float e, float Mer, float Meg, float Meb){
    setAmbient(Mar, Mag, Mab);
    setDifuse(Mdr, Mdg, Mdb);
    setSpecular(Msr, Msg, Msb);
    setShininess(e);
    setEmission(Mer, Meg, Meb);

    ply::read_vertices(archivo, vertices_ply);
    n_ver = vertices_ply.size()/3;
    this->vueltas = vueltas;

    v3 nuevo;
    for(int i = 0; i < vueltas; i++){
      for(int j = 0; j < n_ver; j++){
          float grados = 2*M_PI*i/(vueltas-1);
          nuevo.x = vertices_ply[3*j] * cos(grados);
          nuevo.y = vertices_ply[3*j+1];
          nuevo.z = vertices_ply[3*j] *(-sin(grados));
          vertices.push_back(nuevo);
      }
    }                                                                                                                                                                                                                   

    int k;
    i3 nueva;
    for(int i = 0; i < vueltas-1; i++){
      for(int j = 0; j < n_ver - 1; j++){
          k = n_ver*i+j;                                                                                          
          nueva.uno = k;
          nueva.dos = k + n_ver;
          nueva.tres = k+ n_ver + 1;
          caras.push_back(nueva);
          nueva.uno = k;
          nueva.dos = k + n_ver + 1;
          nueva.tres = k+1;
          caras.push_back(nueva);
      }
    }

    v_perfil = n_ver;
    n_car = caras.size();
    n_ver = vertices.size();
    calculoNCaras();
    calculoNVertices();

  }

  void textura(const char *nombre_arch){
    unsigned char* image = nullptr;
    image = LeerArchivoJPEG(nombre_arch, ancho, alto);
    coordTextura.resize(n_ver);

    glGenTextures(1, &texID);
    glBindTexture(GL_TEXTURE_2D, texID);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, ancho, alto,0, GL_RGB, GL_UNSIGNED_BYTE, image);

    delete image;
    image = nullptr;
    calculoCoordenadas();
  }

  void calculoCoordenadas(){
    int contador = 0;
    float desplazamiento = 0;
    float angulo = 0;
    float incremento_angulo = ancho / (vueltas + 3);
    float dmax = 0;
   
      for(int j = 0; j < n_ver; j++){
        //Si no es el primer vértice del perfil, calculamos la distancia entre este vértice y el anterior
        if(contador > 1){
            float distancia = sqrt(pow(vertices[j].y - vertices[j-1].y, 2));
            // Acumulamos la distancia en el desplazamiento
            desplazamiento += distancia;
        }

        coordTextura[j].x = angulo/360.0;
        coordTextura[j].y =desplazamiento/dmax;

        contador++;

        if(contador == v_perfil){
          dmax = desplazamiento;
          desplazamiento = 0;
          contador = 0;
          angulo += incremento_angulo;
        }

        
    }
    
  }

  void setAmbient(float Mar,float Mag,float Mab){
    ambient[0] = Mar;
    ambient[1] = Mag;
    ambient[2] = Mab;
    ambient[3] = 1.0;
  }

  void setDifuse(float Mdr,float Mdg,float Mdb){
    difuse[0] = Mdr;
    difuse[1] = Mdg;
    difuse[2] = Mdb;
    difuse[3] = 1.0;
  }
  void setSpecular(float Msr,float Msg, float Msb){
    specular[0] = Msr;
    specular[1] = Msg;
    specular[2] = Msb;
    specular[3] = 1.0;
  }
  void setShininess(float e){
    shininess = e;
  }

  void setEmission(float Mer, float Meg,float Meb){
    emission[0] = Mer;
    emission[1] = Meg;
    emission[2] = Meb;
    emission[3] = 1.0;
  }

  void setMaterial(){
    glMaterialfv(GL_FRONT, GL_AMBIENT, ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, difuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, &shininess);
    glMaterialfv(GL_FRONT, GL_EMISSION, emission);
  }


  void draw(){
    
    setMaterial();
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texID);

    glShadeModel(GL_SMOOTH);
      glBegin(GL_TRIANGLES);
      for(int i = 0; i < n_car; i++){
        glTexCoord2f(coordTextura[caras[i].uno].x, coordTextura[caras[i].uno].y);
        glNormal3f(normal_vertices[caras[i].uno].x, normal_vertices[caras[i].uno].y, normal_vertices[caras[i].uno].z);
        glVertex3f(vertices[caras[i].uno].x, vertices[caras[i].uno].y, vertices[caras[i].uno].z);
        glTexCoord2f(coordTextura[caras[i].dos].x, coordTextura[caras[i].dos].y);
        glNormal3f(normal_vertices[caras[i].dos].x, normal_vertices[caras[i].dos].y, normal_vertices[caras[i].dos].z);
        glVertex3f(vertices[caras[i].dos].x, vertices[caras[i].dos].y, vertices[caras[i].dos].z);
        glTexCoord2f(coordTextura[caras[i].tres].x, coordTextura[caras[i].tres].y);
        glNormal3f(normal_vertices[caras[i].tres].x, normal_vertices[caras[i].tres].y, normal_vertices[caras[i].tres].z);
        glVertex3f(vertices[caras[i].tres].x, vertices[caras[i].tres].y, vertices[caras[i].tres].z);
      }
    glEnd();

    glDisable(GL_TEXTURE_2D);
  }

};


  Dado dado(1,1,1,0.3,0.4,0.8,0.6,0.2,0.1,15,0.3,0.3,0.3);
  RevolucionTextura cuerpoLata("lata-pcue.ply",10,1,1,1,0.9,0.3,1,0,0.2,0.4,25,0.2,0.3,0.2);
  RevolucionTextura inferiorLata("lata-pinf.ply",10,1,1,1,0.9,0.3,1,0,0.2,0.4,25,0.2,0.3,0.2);
  RevolucionTextura superiorLata("lata-psup.ply",10,1,1,1,0.9,0.3,1,0,0.2,0.4,25,0.2,0.3,0.2);
  Dado cubo1(0.5,0.5,0.5,0.5,0.5,0.5,0.5,0.5,0.5,50,0.5,0.5,0.5); 
  Dado cubo2(0.8,0.2,0.3,0.2,0.8,0.8,0.5,0.3,1,80,0.8,0.9,0.2);

  bool inicio = true;
  
 void inicializar4(){
    float color[4] = {1,1,1,1};
    dado.textura("dado.jpg");
    cuerpoLata.textura("lata.jpg");
    inferiorLata.textura("tapas.jpg");
    superiorLata.textura("tapas.jpg");
    cubo1.textura("dado.jpg");
    cubo2.textura("dado.jpg");
    inicio = false;
 } 

void initModel4(){
  if(inicio){
    inicializar4();
  }
   dado.draw();
   glTranslatef(-3,0,0);
   cuerpoLata.draw();
   inferiorLata.draw();
   superiorLata.draw();
   glTranslatef(8,0,0);
   cubo1.draw();
   glTranslatef(5,0,0);
   cubo2.draw();
}

//luces
void setLuz1(){

  // Configurar la luz 1
  GLfloat pos1[] = {1.0, -1.0, -1.0, 0.0};
  GLfloat intensidad1[] = {1.0, 1.0, 1.0, 1.0};
  GLfloat color1[] = {1.0, 1.0, 1.0, 1.0};
  glLightfv(GL_LIGHT1, GL_POSITION, pos1);
  glLightfv(GL_LIGHT1, GL_DIFFUSE, intensidad1);
  glLightfv(GL_LIGHT1, GL_SPECULAR, color1);

  //Configurar luz 2
  GLfloat pos2[] = {1.0, 1.0, 1.0, 0.0};
  GLfloat intensidad2[] = {0.7, 0.7, 0.7, 1.0};
  GLfloat color2[] = {1.0, 0.0, 0.0, 1.0};
  glLightfv(GL_LIGHT2, GL_POSITION, pos2);
  glLightfv(GL_LIGHT2, GL_DIFFUSE, intensidad2);
  glLightfv(GL_LIGHT2, GL_SPECULAR, color2);

  //Habilitamos las dos luces
  glEnable(GL_LIGHT2);
  glEnable(GL_LIGHT1);
}

void setLuz2(){
  //Desabilitamos las dos luces
  glDisable(GL_LIGHT2);
  glDisable(GL_LIGHT1);
}

/*************************************PRACTICA5*******************************************/

//creamos las diferentes vistas
void vistaFrente() {
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(45.0, 1.0, 1.0, 1000.0);

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  gluLookAt(10.0, 10.0, 2.0,0.0, 0.0, 0.0,0.0, 1.0, 0.0);  
}

void vistaAlzado() {
  // Cambiar a proyección ortogonal
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(-10, 10, -10, 10, -10, 10);

  // Cambiar a vista de alzado
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  gluLookAt(0, 10, 0, 0, 0, 0, 1, 0, 0);  
}

void vistaPerfil() {
  // Cambiar a proyección ortogonal
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(-10, 10, -10, 10, -10, 10);

  // Cambiar a vista de perfil
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  gluLookAt(10, 0, 0,0, 0, 0,0, 1, 0);  
}


/*
void colorSeleccion(int i , int componente ){
  unsigned char r = ( i & 0xFF);
  unsigned char g = (componente & 0xFF);
  glColor3ub(r.g.0);
}

void dibujoEscena(){
  int peon, coche, beethoven;
  //Obejtos practica 2
  glPushMatrix();
    glPushName(peon);
      revolucion peon("perfil.ply",10);
      float color2[4]={0.94,0,0.97,1};
      glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, color2);
      peon.draw();
    glPopName();
  glPopMatrix();

  glPushMatrix();
    glPushName(beethoven);
      glTranslatef(-7,0,0);
      readPLY beethoven("beethoven.ply");
      float color1[4]={0.6,0.8,0.2,1};
      glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, color1);
      beethoven.draw_smooth();
    glPopName();
  glPopMatrix();

  glPushMatrix();
    glPushName(coche);
      glTranslatef(18,0,0);
      readPLY coche("big_dodge.ply");
      float color3[4]={0.9,0.2,0.2,1};
      glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, color3);
      coche.draw_smooth();
    glPopName();
  glPopMatrix();


  //OBjetos practica 3

  //Obejtos practica 4
}

*/
int pick(int x, int y, int *i ){
  GLint viewport[4];
  unsigned char data[4];

  glGetIntegerv (GL_VIEWPORT, viewport);
  glDisable(GL_DITHER);
  glDisable(GL_LIGHTING);
  //dibujoEscena();
  glEnable(GL_LIGHTING);
  glEnable(GL_DITHER);
  glFlush();
  glFinish();

  glReadPixels(x, viewport[3] - y, 1,1, GL_RGBA, GL_UNSIGNED_BYTE, data);

  *i=data[0];

  glutPostRedisplay();
  return *i;
}


/*****************************************************************************************/

Ejes ejesCoordenadas;

/**	void Dibuja( void )

Procedimiento de dibujo del modelo. Es llamado por glut cada vez que se debe redibujar.

**/

void Dibuja (void)
{
  // glEnable(GL_COLOR_MATERIAL);

  glPushMatrix ();		// Apila la transformacion geometrica actual

  glClearColor (0.0, 0.0, 0.0, 1.0);	// Fija el color de fondo a negro

  glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	// Inicializa el buffer de color y el Z-Buffer

  transformacionVisualizacion ();	// Carga transformacion de visualizacion

  ejesCoordenadas.draw();			// Dibuja los ejes

  float color2[4] = { 0.8, 0.0, 1, 1 };
  glMaterialfv (GL_FRONT, GL_AMBIENT_AND_DIFFUSE, color2);

  //Luz por defecto, proporcionada por profesores
  static GLfloat  pos2[4] = { 5.0, 5.0, 10.0, 0.0 };
  glLightfv (GL_LIGHT0, GL_POSITION, pos2);	
  glEnable(GL_LIGHT0);

  glPolygonMode(GL_FRONT_AND_BACK, modo ) ;

  if(luz)
    glEnable(GL_LIGHTING);
  else
    glDisable(GL_LIGHTING);


  //initModel();

  //initModel2();

  //initModel3();

  initModel4();

  /***************************************************************/

  glPopMatrix ();		// Desapila la transformacion geometrica

  //dibujoEscena();

  glutSwapBuffers ();		// Intercambia el buffer de dibujo y visualizacion

  
}


/**	void idle()

Procedimiento de fondo. Es llamado por glut cuando no hay eventos pendientes.

**/
void idle (int v)
{

  glutPostRedisplay ();		// Redibuja
  glutTimerFunc (30, idle, 0);	// Vuelve a activarse dentro de 30 ms

  //Animación práctica 3
  if(animacion){
    Animacion();
  }
  
}
