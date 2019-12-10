#include <windows.h>
#ifdef __APPLE__
#else
#include <GL/glut.h>
#endif

#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <vector>
#include <time.h>
#include <math.h>
#define KEY_ESC 27

#include "rTree.cpp"

using namespace std;
const int N= 4;
int ID= 0;
bool flagObj=false;
objeto*nuevoObj;
float XX,YY,XX2,YY2;
bool flag=true;
//quad p( punto2D(0.0,0.0),punto2D(1.0,1.0),0);


rTree<N> p;



void OnMouseClick(int button, int state, int x, int y)
{
  if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
  {
    cout<<(float)x/600<<" "<<(float)y/600<<endl;
    if(flagObj)
        nuevoObj->insertarPunto(punto2D((float)x/600,1.0-(float)(y)/600));
    else{
        nuevoObj=new objeto(0,punto2D((float)x/600,1.0-(float)(y)/600));
        flagObj=true;
    }
  }else if (button == GLUT_RIGHT_BUTTON || button == GLUT_LEFT_BUTTON && state == GLUT_UP)
  {
      flag=false;
  }
}

void OnMouseMotion(int x, int y)
{
    XX=(float)x/600;
    YY=1.0-(float)y/600;
    XX2=XX+0.05;
    YY2=YY+0.05;
    XX=XX-0.05;
    YY=YY-0.05;
    flag=true;
     //opcional
	 //hacer algo x,z cuando se mueve el mouse
}



void idle(){ // AGREGAR ESTA FUNCION
	glutPostRedisplay();
}

//funcion llamada a cada imagen
void glPaint(void) {

	//El fondo de la escena al color initial
	glClear(GL_COLOR_BUFFER_BIT); //CAMBIO
	glLoadIdentity();
	glOrtho(0.0f, 300.0f,0.0f, 300.0f, -1.0f, 1.0f);

	//dibujar quadTree (qt->draw())
    p.draw();
    if(flag){
        //p.searchdraw2(XX,YY,XX2,YY2);
        //p.searchdraw2beta(XX,YY,XX2,YY2);
        glColor3d(255,0,0);
        int h=(XX+XX2)*150;
        int k=(YY+YY2)*150;
        int r=(YY2-YY)*150;
        double M_PI=3.14;
        double PI2=M_PI*2;
        glBegin(GL_LINE_LOOP);
        for(int i=0;i<=50;++i){
            glVertex2d(h+cos(i*PI2/50)*r,k+sin(i*PI2/50)*r);
        }
        glEnd();
        p.buscarCircle(XX,YY,XX2,YY2);
        //p.searchdrawcirculo(XX,YY,XX2,YY2);
	}//dibuja el gizmo
	//displayGizmo();

	//doble buffer, mantener esta instruccion al fin de la funcion
	glutSwapBuffers();
}

//
//inicializacion de OpenGL
//
void init_GL(void) {
	//Color del fondo de la escena
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f); //(R, G, B, transparencia) en este caso un fondo negro

	//modo projeccion
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
}

//en el caso que la ventana cambie de tamaño
GLvoid window_redraw(GLsizei width, GLsizei height) {
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();


}

GLvoid window_key(unsigned char key, int x, int y) {
	switch (key) {
	case KEY_ESC:
		exit(0);
		break;
    case 13:
        cout<<"enter"<<endl;
		if (flagObj){
            p.insertion(*nuevoObj);
            flagObj=false;
		}
		break;
	default:
		break;
	}

}

/* Program entry point */

int main(int argc, char *argv[])
{
    colores.push_back(tripleta(255,0,0));
    /*colores.push_back(tripleta(0,255,0));
    colores.push_back(tripleta(0,0,255));
    colores.push_back(tripleta(255,255,0));
    colores.push_back(tripleta(255,0,255));
    colores.push_back(tripleta(0,255,255));*/

    /*objeto algo(0,punto2D(0.3,0.00));
    algo.insertarPunto(punto2D(0.3,1.0));
    algo.insertarPunto(punto2D(0.4,0.1));
    p.insertion(algo);
    objeto algo2(0,punto2D(0.1,0.6));
    algo2.insertarPunto(punto2D(0.1,0.65));
    algo2.insertarPunto(punto2D(0.4,0.7));
    p.insertion(algo2);
    objeto algo3(0,punto2D(0.5,0.0));
    algo3.insertarPunto(punto2D(0.5,1));
    algo3.insertarPunto(punto2D(0.6,0.4));
    p.insertion(algo3);
    objeto algo4(0,punto2D(0.5,0.7));
    algo4.insertarPunto(punto2D(0.5,0.75));
    algo4.insertarPunto(punto2D(0.7,0.8));
    p.insertion(algo4);*/
    /*objeto algo5(0,punto2D(0.15,0.15));
    algo5.insertarPunto(punto2D(0.2,0.2));
    algo5.insertarPunto(punto2D(0.1,0.1));
    p.insertion(algo5);*/
    //srand(time(0));
    /*for(float i=0.0;i<1;i+=0.005){
        p.insertar(punto2D(i,i));
        p.insertar(punto2D(i,1.0-i));
    //p.imprimir();
    }
    */
    /*for(int i=0;i<1000000;++i){
        p.insertar(punto2D((float)rand()/RAND_MAX,(float)rand()/RAND_MAX));
    }*/
    //p.cargarImagen();
    glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(600, 600); //tamaño de la ventana
	glutInitWindowPosition(100, 100); //posicion de la ventana
	glutCreateWindow("R-Tree"); //titulo de la ventana

	init_GL(); //funcion de inicializacion de OpenGL

	glutDisplayFunc(glPaint);
	glutReshapeFunc(&window_redraw);
	// Callback del teclado
	glutKeyboardFunc(&window_key);
	glutMouseFunc(&OnMouseClick);
	glutMotionFunc(&OnMouseMotion);
	glutIdleFunc(&idle);


	//qt = new quadTree();
	glutMainLoop(); //bucle de rendering
	//no escribir nada abajo de mainloop
	return 0;
}
