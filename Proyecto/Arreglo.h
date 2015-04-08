#ifndef ARREGLO_H_INCLUDED
#define ARREGLO_H_INCLUDED


class Arreglo{
    public:
        TPais paises[CANTPAISES];
        int cant;
    public:

        Arreglo(const Arreglo &a){
            cant=a.cant;
            for(int i=0;i<cant;i++)
                paises[i]=a.paises[i];
        };
        Arreglo(){
            cant=0;
        };
        Arreglo(TPais *p){
            int i=0;
            while(p[i]!=NOPAIS)
                i++;
            cant=i;
            for(i=0;i<cant;i++)
                paises[i]=p[i];
        };
        Arreglo &operator=(const Arreglo &a){
            cant=a.cant;
            for(int i=0;i<cant;i++)
                paises[i]=a.paises[i];
        };

        const TPais &operator[](int i) const {return paises[i%cant];};
        TPais &operator[](int i) {return paises[i%cant];};
        int Buscar(TPais elem){
            for(int i=0;i<cant;i++)
                if(paises[i]==elem)
                    return i;
            return -1;
        };
        bool Borrar(TPais elem){
            int pos=Buscar(elem);
            if(pos>=0){
                for(;pos<cant-1;pos++)
                    paises[pos]=paises[pos+1];
                cant--;
                return true;
            }else
                return false;
        };
        void Agregar(TPais elem){
            int i=0;
            while(paises[i]<elem && i<cant)
                i++;
            for(int j=cant;j>i;j--)
                paises[j]=paises[j-1];
            paises[i]=elem;
            cant++;
        };
};


#endif // ARREGLO_H_INCLUDED
