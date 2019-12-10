#include "rNodo.cpp"
#include <windows.h>

template<int N>
struct rTree{
    rNodo<N>*raiz;
    rTree(){
        raiz=new rNodo<N>(1);
    }
    rTree(int loquesea){
        raiz=new rNodo<N>(1);
        ifstream myfile ("D:/R-Tree/resultado.txt");
        string line;
        if (myfile.is_open()){
            objeto* objAux=0;
            getline (myfile,line);
            double id=atof(line.substr(line.find(' ')).c_str()) ;
            getline (myfile,line);
            double n=atof(line.substr(0,line.find(' ')).c_str()) ;
            double m=atof(line.substr(line.find(' ')).c_str()) ;
            objAux=new objeto(id,punto2D(m,1.0-n));
            while ( getline (myfile,line) )
            {
                string aux=line.substr(0,line.find(' '));
                id=atof(line.substr(line.find(' ')).c_str()) ;
                if(aux=="Obj"){
                    cout<< objAux->caja.minX<<' '<< objAux->caja.minY<<' '<< objAux->caja.maxX<<' '<< objAux->caja.maxY<<endl;
                    insertion(*objAux);
                    getline (myfile,line);
                    n=atof(line.substr(0,line.find(' ')).c_str()) ;
                    m=atof(line.substr(line.find(' ')).c_str()) ;
                    objAux=new objeto(id,punto2D(m,1.0-n));
                    cout<<id<<endl;
                }else{
                    objAux->insertarPunto(punto2D(id,1.0-atof(aux.c_str())));
                }
            }
            insertion(*objAux);
            myfile.close();
          }

          else cout << "Unable to open file";
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
    void buscarCircle(double xi, double yi,double xf,double yf){
        if(raiz)
            raiz->buscarCircle(xi,yi,xf,yf);
    }
};
