#include <iostream>
#include <string>
using namespace std;
class itemFAT{
  public:
    string nombre;
    int tamano_arch;
    int x,y,estado;
    itemFAT(){
      estado=2;
    }
    itemFAT(string _nombre, int tamano, int _x, int _y,int _estado){
      nombre = _nombre;
      tamano_arch = tamano;
      x = _x;
      y = _y;
      estado = _estado;
    }
};
class FAT {
   private:
     itemFAT FATarray[100];
     char Almacena[25][25];
     int tamanio;
     int restante;
   public:
      FAT(int _tamanio){
        tamanio = _tamanio;
        restante = 25*25;
      }
      void MostrarFAT(){
        cout<<"\tFAT"<<endl;
        for(int i=0;i<tamanio;i++){
          if(FATarray[i].estado==2){
            cout<<0<<endl;
          }else{
            cout<<FATarray[i].nombre<<"\t"<<FATarray[i].tamano_arch<<" ";
            cout<<FATarray[i].x<<", "<<FATarray[i].y<<" "<<FATarray[i].estado<<endl;
          }
        }
      }
      bool Existe_archivo(string name){
        for(int i=0;i<tamanio;i++){
          if(FATarray[i].estado!=2 && FATarray[i].nombre==name){
            return 1;
          }
        }
        return 0;
      }
      void get_Posicion(int &x,int &y,int tamano,int &pos){
        for(int i=0;i<tamanio;i++){
          if(FATarray[i].estado==2){
            if(i==0){
              if(25*25>=tamano){
                x=0;
                y=0;
                pos=0;
              }else{
                return ;
              }
            }
            int tamano_restante = 25-FATarray[i-1].y+(25*25-FATarray[i-1].x)-FATarray[i-1].tamano_arch;
            if(restante>=tamano){
              y=FATarray[i-1].y+FATarray[i-1].tamano_arch%25;
              x=FATarray[i-1].x+(FATarray[i-1].y+FATarray[i-1].tamano_arch)/25;
              pos=i;
            }
            return ;
          }else if(FATarray[i].estado==0){
            if(restante==tamano){
              x = FATarray//////////////////////////////////////////
            }
          }
        }
      }
      void Registrar_archivo(){
        string name;
        int tamano;
        int x,y,pos;
        char c;
        cout<<"Ingrese el nombre del archivo: ";
        cin>>name;
        if(Existe_archivo(name)){
          cout<<"El nombre \""<<name<<"\" ya existe."<<endl;
          return ;
        }
        cout<<"Ingrese el tamano del archivo: ";
        cin>>tamano;
        get_Posicion(x,y,tamano,pos);
        c=(tamano%26)+'a';
      }
};
int main(){
  cout<<"Ingrese el tamanio del FAT (max 20)";
  int tamano;
  cin>>tamano;
  tamano = max(0, min(tamano,20));
  FAT x = FAT(tamano);
  x.MostrarFAT();
}
