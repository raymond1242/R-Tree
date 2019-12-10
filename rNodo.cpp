#include "otros.cpp"

using namespace otros;


template <int N>
struct rNodo{
    box caja;
    rNodo<N>* rHijos[N];
    objeto* oHijos[N];
    int ocupados;
    rNodo<N>* padre;
    bool hojaFlag;
    rNodo(bool hoja=0){
        ocupados=0;
        padre=0;
        hojaFlag=hoja;
    }
    void insertar(rNodo<N>*E){
        if(ocupados<N){
            rHijos[ocupados]=E;
            E->padre=this;
            ++ocupados;
            caja.minX=min(caja.minX,E->caja.minX);
            caja.minY=min(caja.minY,E->caja.minY);
            caja.maxX=max(caja.maxX,E->caja.maxX);
            caja.maxY=max(caja.maxY,E->caja.maxY);
        }
    }
    void insertar(objeto*E){
        //cout<<"\niiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiii\n";
        if(hojaFlag){
            if(ocupados<N){
                //cout<<"\n111111111111111111111111111111111111111111111111111111111111111111111111111111111111111\n";
                if(ocupados){
                    caja.minX=min(caja.minX,E->caja.minX);
                    caja.minY=min(caja.minY,E->caja.minY);
                    caja.maxX=max(caja.maxX,E->caja.maxX);
                    caja.maxY=max(caja.maxY,E->caja.maxY);
                }else{
                    caja.minX=E->caja.minX;
                    caja.minY=E->caja.minY;
                    caja.maxX=E->caja.maxX;
                    caja.maxY=E->caja.maxY;
                }
                oHijos[ocupados]=E;
                ++ocupados;
                ajustar();
            }else if(padre){
                //cout<<"\n2222222222222222222222222222222222222222222222222222222222222222222222222222222\n";
                int i=0;
                while(padre->rHijos[i]!=this){
                    ++i;
                }
                padre->splitHoja(i,E);
            }else{
                //cout<<"\n33333333333333333333333333333333333333333333333333333333333333333333333333333\n";
                padre=new rNodo();
                padre->ocupados=1;
                padre->rHijos[0]=this;
                padre->caja=caja;
                padre->splitHoja(0,E);
            }
        }
    }
    void splitHoja(int i,objeto*E){
        rNodo<N>*aux=new rNodo<N>(1);
        vector<objeto*>objetosAux(1,E);
        double areaMin=HUGE_VAL;
        for(int j=0;j<N;++j){
            objetosAux.push_back(rHijos[i]->oHijos[j]);
        }
        objeto *o1,*o2;
        pickSeeds(objetosAux,o1,o2);
        aux->oHijos[0]=o1;
        aux->ocupados=1;
        aux->caja=o1->caja;
        rHijos[i]->oHijos[0]=o2;
        rHijos[i]->ocupados=1;
        rHijos[i]->caja=o2->caja;

        pickNext(aux,rHijos[i],objetosAux);
        if(ocupados<N){
            rHijos[ocupados]=aux;
            rHijos[ocupados]->padre=this;
            ++ocupados;
            ajustar();
        }else if(padre){
            int i=0;
            while(padre->rHijos[i]!=this){
                ++i;
            }
            padre->splitNodo(i,aux);
        }else{
            padre=new rNodo();
            padre->ocupados=1;
            padre->rHijos[0]=this;
            padre->splitNodo(0,aux);
        }
    }
    void pickSeeds(vector<objeto*>&objetosAux,objeto*&o1,objeto*&o2){
        double maxi=0.0;
        int i1,i2;
        for(int i=0;i<objetosAux.size();++i){
            for(int j=i+1;j<objetosAux.size();++j){
                double x=max(objetosAux[i]->caja.maxX,objetosAux[j]->caja.maxX)-min(objetosAux[i]->caja.minX,objetosAux[j]->caja.minX);
                double y=max(objetosAux[i]->caja.maxY,objetosAux[j]->caja.maxY)-min(objetosAux[i]->caja.minY,objetosAux[j]->caja.minY);
                double a1=(objetosAux[i]->caja.maxX-objetosAux[i]->caja.minX)*(objetosAux[i]->caja.maxY-objetosAux[i]->caja.minY);
                double a2=(objetosAux[j]->caja.maxX-objetosAux[j]->caja.minX)*(objetosAux[j]->caja.maxY-objetosAux[j]->caja.minY);
                double area=x*y-a1-a2;
                if(area>maxi){
                    maxi=area;
                    i1=i;
                    i2=j;
                }
            }
        }
        o1=objetosAux[i1];
        o2=objetosAux[i2];
        objetosAux.erase(objetosAux.begin()+i2);
        objetosAux.erase(objetosAux.begin()+i1);
    }
    void pickNext(rNodo<N>*n1,rNodo<N>*n2,vector<objeto*>&objetosAux){
        while(n1->ocupados<((float)N/2) && n2->ocupados<((float)N/2) ){
            double area1=n1->caja.diferenciaArea(objetosAux[0]->caja.minX,objetosAux[0]->caja.minY,objetosAux[0]->caja.maxX,objetosAux[0]->caja.maxY);
            double area2=n2->caja.diferenciaArea(objetosAux[0]->caja.minX,objetosAux[0]->caja.minY,objetosAux[0]->caja.maxX,objetosAux[0]->caja.maxY);
            if(area1<area2){
                n1->insertar(objetosAux[0]);
            }else{
                n2->insertar(objetosAux[0]);
            }
            objetosAux.erase(objetosAux.begin());
        }
        //cout<<"pickNext"<<n1->ocupados<<n2->ocupados;
        if(n1->ocupados<((float)N/2)){
            for(int i=0;i<objetosAux.size();++i)
                n1->insertar(objetosAux[i]);
        }else{
            for(int i=0;i<objetosAux.size();++i)
                n2->insertar(objetosAux[i]);
        }
    }
    void splitNodo(int i,rNodo<N>*E){
        //cout<<endl<<1;
        rNodo<N>*aux=new rNodo<N>(0);
        vector<rNodo<N>*>objetosAux(1,E);
        double areaMin=HUGE_VAL;
        //cout<<endl<<2;
        for(int j=0;j<N;++j){
            objetosAux.push_back(rHijos[i]->rHijos[j]);
        }
        //cout<<endl<<3;
        rNodo<N> *o1,*o2;
        //cout<<endl<<4;
        pickSeedsNodo(objetosAux,o1,o2);
        aux->rHijos[0]=o1;
        aux->ocupados=1;
        aux->caja=o1->caja;
        rHijos[i]->rHijos[0]=o2;
        rHijos[i]->ocupados=1;
        rHijos[i]->caja=o2->caja;
        //cout<<endl<<5;
        pickNextNodo(aux,rHijos[i],objetosAux);
        //cout<<endl<<6;
        for(int j=0;j<aux->ocupados;++j)
            aux->rHijos[j]->padre=aux;
        for(int j=0;j<rHijos[i]->ocupados;++j)
            rHijos[i]->rHijos[j]->padre=rHijos[i];
        if(ocupados<N){
            rHijos[ocupados]=aux;
            rHijos[ocupados]->padre=this;
            ++ocupados;
            ajustar();
        }else if(padre){
            int i=0;
            while(padre->rHijos[i]!=this){
                ++i;
            }
            padre->splitNodo(i,aux);
        }else{
            padre=new rNodo();
            padre->ocupados=1;
            padre->rHijos[0]=this;
            padre->splitNodo(0,aux);
        }
        //cout<<endl<<7;
    }
    void pickSeedsNodo(vector<rNodo<N>*>&objetosAux,rNodo<N>*&o1,rNodo<N>*&o2){
        double maxi=0.0;
        int i1,i2;
        for(int i=0;i<objetosAux.size();++i){
            for(int j=i+1;j<objetosAux.size();++j){
                double x=max(objetosAux[i]->caja.maxX,objetosAux[j]->caja.maxX)-min(objetosAux[i]->caja.minX,objetosAux[j]->caja.minX);
                double y=max(objetosAux[i]->caja.maxY,objetosAux[j]->caja.maxY)-min(objetosAux[i]->caja.minY,objetosAux[j]->caja.minY);
                double a1=(objetosAux[i]->caja.maxX-objetosAux[i]->caja.minX)*(objetosAux[i]->caja.maxY-objetosAux[i]->caja.minY);
                double a2=(objetosAux[j]->caja.maxX-objetosAux[j]->caja.minX)*(objetosAux[j]->caja.maxY-objetosAux[j]->caja.minY);
                double area=x*y-a1-a2;
                if(area>maxi){
                    maxi=area;
                    i1=i;
                    i2=j;
                }
            }
        }
        o1=objetosAux[i1];
        o2=objetosAux[i2];
        objetosAux.erase(objetosAux.begin()+i2);
        objetosAux.erase(objetosAux.begin()+i1);
    }
    void pickNextNodo(rNodo<N>*n1,rNodo<N>*n2,vector<rNodo<N>*>&objetosAux){
        while(n1->ocupados<((float)N/2) &&n2->ocupados<((float)N/2)){
            double area1=n1->caja.diferenciaArea(objetosAux[0]->caja.minX,objetosAux[0]->caja.minY,objetosAux[0]->caja.maxX,objetosAux[0]->caja.maxY);
            double area2=n2->caja.diferenciaArea(objetosAux[0]->caja.minX,objetosAux[0]->caja.minY,objetosAux[0]->caja.maxX,objetosAux[0]->caja.maxY);
            if(area1<area2){
                n1->insertar(objetosAux[0]);
            }else{
                n2->insertar(objetosAux[0]);
            }
            objetosAux.erase(objetosAux.begin());
        }
        if(n1->ocupados<((float)N/2)){
            for(int i=0;i<objetosAux.size();++i)
                n1->insertar(objetosAux[i]);
        }else{
            for(int i=0;i<objetosAux.size();++i)
                n2->insertar(objetosAux[i]);
        }
    }
    void draw(int c){
        //cout<<ocupados;
        //cout<<"\n impresion "<<this<<' ' << c<<' '<< hojaFlag<<' '<< ocupados<<" padre "<<padre;
        caja.draw(c);
        c++;
        if(c==colores.size())
            c=0;
        if(!hojaFlag){
            for(int i=0;i<ocupados;++i){
                rHijos[i]->draw(c);
            }
        }else{
            /*for(int i=0;i<ocupados;++i){
                cout<<' '<<oHijos[i];
            }*/
            for(int i=0;i<ocupados;++i){
                oHijos[i]->draw(c);
            }
        }
    }
    void ajustar(){
        if(hojaFlag){
            caja=oHijos[0]->caja;
            for(int i=1;i<ocupados;++i){
                caja.minX=min(oHijos[i]->caja.minX,caja.minX);
                caja.minY=min(oHijos[i]->caja.minY,caja.minY);
                caja.maxX=max(oHijos[i]->caja.maxX,caja.maxX);
                caja.maxY=max(oHijos[i]->caja.maxY,caja.maxY);
            }
        }else{
            caja=rHijos[0]->caja;
            for(int i=1;i<ocupados;++i){
                caja.minX=min(rHijos[i]->caja.minX,caja.minX);
                caja.minY=min(rHijos[i]->caja.minY,caja.minY);
                caja.maxX=max(rHijos[i]->caja.maxX,caja.maxX);
                caja.maxY=max(rHijos[i]->caja.maxY,caja.maxY);
            }
        }
        if(padre)
            padre->ajustar();
    }
    void buscarCircle(double xi,double yi,double xf,double yf){
        if(hojaFlag){
            for(int i=0;i<ocupados;++i){
                if(xi<=oHijos[i]->caja.maxX&&yi<=oHijos[i]->caja.maxY && xf>=oHijos[i]->caja.minX&&yf>=oHijos[i]->caja.minY)
                    oHijos[i]->buscarCircle(xi,yi,xf,yf);
            }
            return;
        }
        for(int i=0;i<ocupados;++i){
            if(xi<=rHijos[i]->caja.maxX&&yi<=rHijos[i]->caja.maxY && xf>=rHijos[i]->caja.minX&&yf>=rHijos[i]->caja.minY)
                rHijos[i]->buscarCircle(xi,yi,xf,yf);
        }
    }
};
