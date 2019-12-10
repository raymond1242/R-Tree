#include <iostream>
#include <math.h>
using namespace std;

namespace otros{
    struct tripleta{
        int a,b,c;
        tripleta(int aa,int bb,int cc):a(aa),b(bb),c(cc){}
    };
    vector<tripleta>colores;
    int color=0;
    struct punto2D{
        double x,y;
        punto2D(double xx=0.0, double yy=0.0):x(xx),y(yy){}
    };
    struct box{
        double minX, minY;
        double maxX, maxY;
        box(double xi=0.0, double yi=0.0,double xf=0.0, double yf=0.0):minX(xi), minY(xf),maxX(yi), maxY(yf){}
        double diferenciaArea(box b){
            double xi=min(b.minX,minX);
            double yi=min(b.minY,minY);
            double xf=max(b.maxX,maxX);
            double yf=max(b.maxY,maxY);
            return ((xf-xi)*(yf-yi)) - ((maxY-minY)*(maxX-minX));
        }

        double diferenciaArea(double xi,double yi,double xf,double yf){
            xi=min(xi,minX);
            yi=min(yi,minY);
            xf=max(xf,maxX);
            yf=max(yf,maxY);
            return ((xf-xi)*(yf-yi)) - ((maxY-minY)*(maxX-minX));
        }
        void actualizar(double x, double y){
            minX=min(x,minX);
            minY=min(y,minY);
            maxX=max(x,maxX);
            maxY=max(y,maxY);
        }
        void operator=(box b){
            minX=b.minX;
            minY=b.minY;
            maxX=b.maxX;
            maxY=b.maxY;
        }
        void draw(int i=0){
            glBegin(GL_LINES);
            glColor3d(colores[i].a,colores[i].b,colores[i].c);
            glVertex2d(minX*300, minY*300);
            glVertex2d(minX*300, maxY*300);
            glVertex2d(minX*300, maxY*300);
            glVertex2d(maxX*300, maxY*300);
            glVertex2d(maxX*300, maxY*300);
            glVertex2d(maxX*300, minY*300);
            glVertex2d(maxX*300, minY*300);
            glVertex2d(minX*300, minY*300);
            glEnd();
        }
    };
    struct objeto{
        box caja;
        int id;
        vector<punto2D> puntos;
        objeto(int ID,punto2D p){
            id=ID;
            caja.minX=p.x;
            caja.minY=p.y;
            caja.maxX=p.x;
            caja.maxY=p.y;
            puntos.push_back(p);
        }
        void insertarPunto(punto2D p){
            caja.actualizar(p.x,p.y);
            puntos.push_back(p);
        }
        void draw(int c){
            //caja.draw(c);
            glColor3d(colores[c].a,colores[c].b,colores[c].c);
            glBegin(GL_QUADS);
                glVertex2d(caja.minX*300, caja.minY*300);
                glVertex2d(caja.maxX*300, caja.minY*300);
                glVertex2d(caja.maxX*300, caja.maxY*300);
                glVertex2d(caja.minX*300, caja.maxY*300);
            glEnd();
            glPointSize(3);
            glBegin(GL_POINTS);

            //glColor3d(255,255,255);
            glColor3d(255,255,255);
            for(int i=0;i<puntos.size();++i)
                glVertex2d(puntos[i].x*300, puntos[i].y*300);
            glEnd();

            glPointSize(1);
            glBegin(GL_POINTS);

            //glColor3d(255,255,255);
            glColor3d(0,0,0);
            for(int i=0;i<puntos.size();++i)
                glVertex2d(puntos[i].x*300, puntos[i].y*300);
            glEnd();

        }
        void buscarCircle(double xi,double yi,double xf,double yf){
            glPointSize(7);
            glBegin(GL_POINTS);
            //glColor3d(255,255,0);
            glColor3d(1,1,1);
            double h=(xi+xf)/2;
            double k=(yi+yf)/2;
            double r=(xf-xi)/2;
            for(int i=0;i<puntos.size();++i){
                if(hypot(puntos[i].x-h,puntos[i].y-k)<r)
                    glVertex2d(puntos[i].x*300, puntos[i].y*300);
            }
            glEnd();
        }
    };
}
