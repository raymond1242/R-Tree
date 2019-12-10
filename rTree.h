#ifndef RTREE_H_INCLUDED
#define RTREE_H_INCLUDED

#include "rNodo.h"
template<int N>
struct rTree{
    rNodo<N>*raiz;
    rTree(){
        raiz=new rNodo<N>(1);
    }
    void insertion(objeto&E){
        rNodo<N>*aux=chooseLeaf(E);
        aux->insertar(&E);
        while(raiz->padre){
            raiz=raiz->padre;
        }
        cout<<"insertion exitosa";
    }
    rNodo<N>*chooseLeaf(objeto E){
        rNodo<N>*aux=raiz;
        while(!aux->hojaFlag){
            int menor=0;
            float areaMenor;
            if(aux->ocupados){
                areaMenor=aux->rHijos[0]->caja.diferenciaArea(E.caja);
            }
            for(int i=1;i<aux->ocupados;++i){
                double areaAux=aux->rHijos[i]->caja.diferenciaArea(E.caja);
                if(areaAux<areaMenor){
                    menor=i;
                    areaMenor=areaAux;
                }
            }
            aux=aux->rHijos[menor];
        }
        return aux;
    }
    void draw(){
        //cout<<"\nraiz: "<< raiz;
        raiz->draw(0);

    }
    void buscar(double xi, double yi,double xf,double yf){
        if(raiz)
            raiz->buscar(xi,yi,xf,yf);
    }
};

#endif // RTREE_H_INCLUDED
