#include <iostream>
#include <string>
using namespace std;
class itemFAT{
  public:
    string nombre;
    int tamano_arch;
    int x,y,estado;
    int c;
    itemFAT(){
      estado=2;
    }
    itemFAT(string _nombre, int tamano, int _x, int _y,int _estado,char _c){
      nombre = _nombre;
      tamano_arch = tamano;
      x = _x;
      y = _y;
      estado = _estado;
      c = _c;
    }
};
class FAT {
   private:
     itemFAT FATarray[20];
     char Almacena[25][25];
     bool Almacena2[25][25];
     bool abc[26];
     int tamanio;
     int tamanio_FAT;
     int restante;
   public:
      FAT(int _tamanio){
        tamanio = _tamanio;
        tamanio_FAT = 20;
        restante = tamanio*tamanio;
        for(int i=0;i<26;i++)abc[i]=0;
        for(int i=0;i<tamanio;i++){
          for(int j=0;j<tamanio;j++){
            Almacena[i][j]=' ';
            Almacena2[i][j]=0;
          }
        }
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
      void MostrarAlmacenamiento(){
        cout<<"\tAlmacenamiento"<<endl;
        for(int i=0;i<tamanio+1;i++)cout<<"--";
        cout<<endl;
        for(int i=0;i<tamanio;i++){
            cout<<"|";
            for(int j=0;j<tamanio;j++){
                cout<<Almacena[i][j]<<" ";
            }
            cout<<"|";
            cout<<endl;
        }
        for(int i=0;i<tamanio+1;i++)cout<<"--";
        cout<<endl;
      }
      int Existe_archivo(string name){
        for(int i=0;i<tamanio_FAT;i++){
          if(FATarray[i].estado!=2 && FATarray[i].nombre==name){
            return i;
          }
        }
        return -1;
      }
      void get_Posicion(int &x,int &y,int tamano,int &pos){
        for(int i=0;i<tamanio_FAT;i++){
          if(FATarray[i].estado==2){
            if(i==0){
              if(tamanio*tamanio>=tamano){
                x=0;
                y=0;
                pos=0;
              }else{
                  cout<<"No hay espacio suficiente"<<endl;
              }
              return ;
            }
            if(restante>=tamano){
              int total = FATarray[i-1].y + FATarray[i-1].x*tamanio;
              y=(total+FATarray[i-1].tamano_arch)%tamanio;
              x=(total+FATarray[i-1].tamano_arch)/tamanio;
              pos=i;
            }else{
              x=-1;
              cout<<"No hay espacio suficiente"<<endl;
            }
            return ;
          }else if(FATarray[i].estado==0){
            if(restante>=tamano){
              x = FATarray[i].x;
              y = FATarray[i].y;
              pos = i;
            }else{
              cout<<"No hay espacio suficiente"<<endl;
            }
            return ;
          }
        }
      }
      void Registrar_archivo(){
        string name;
        int tamano;
        int x,y,pos;
        char c;
        cout<<"Ingrese el nombre del archivo: ";
        getline(cin,name);
        getline(cin,name);
        cout<<name<<endl;
        if(Existe_archivo(name)!=-1){
          cout<<"El nombre \""<<name<<"\" ya existe. Retornando al menu principal."<<endl;
          return ;
        }
        cout<<"Ingrese el tamano del archivo: ";
        cin>>tamano;
        get_Posicion(x,y,tamano,pos);
        cout<<"Comienzo registro x:"<<x<<" y:"<<y<<endl;
        if(x==-1){
          cout<<"No hay espacio suficiente..."<<endl;
        }else{
          for(int i=0;i<26;i++){
            if(!abc[i]){
              c=i+'a';
              abc[i]=1;
              break;
            }
          }
          int cont=tamano;
          for(int i=x;i<tamanio && cont>0;i++){
            int begin=0;
            if(x==i)begin=y;
            for(int j=begin;j<tamanio && cont>0;j++){
              if(!Almacena2[i][j]){
                Almacena[i][j]=c;
                Almacena2[i][j]=1;
                cont--;
                restante--;
              }
            }
          }
          FATarray[pos] = itemFAT(name,tamano,x,y,1,c);
        }
      }
      void Eliminar_Archivo(){
        string name;
        cout<<"Ingrese el nombre del archivo a eliminar: ";
        getline(cin,name);
        getline(cin,name);
        int pos=Existe_archivo(name);
        if(pos==-1){
          cout<<"El archivo \""<<name<<"\" no existe. Retornando al menu principal."<<endl;
          return ;
        }
        int x=FATarray[pos].x;
        int y=FATarray[pos].y;
        char c=Almacena[x][y];
        FATarray[pos].estado=0;
        for(int i=0;i<tamanio;i++){
          for(int j=0;j<tamanio;j++){
            if(c==Almacena[i][j]){
              Almacena2[i][j]=0;
              restante++;
            }
          }
        }
        cout<<"Archivo Eliminado"<<endl;
      }
      void anterior(int &x,int &y,int k){
        int total=x*tamanio+y-k;
        x=total/tamanio;
        y=total%tamanio;
      }
      void Eliminar_Vacios(){
        for(int i=0;i<tamanio;i++){
          for(int j=0;j<tamanio;j++){
            if(Almacena[i][j]!=' ' && Almacena2[i][j]==0){
              int k=0;
              int total=tamanio*i+j;
              int x=i,y=j;
              while(Almacena2[x][y]==0 && total+k<=tamanio*tamanio){
                k++;
                x=(total+k)/tamanio;
                y=(total+k)%tamanio;
              }
              char c=Almacena[i][j];
              for(int i=0;i<tamanio;i++){
                for(int j=0;j<tamanio;j++){
                  if(Almacena[i][j]==c){
                    Almacena2[i][j]=0;
                    Almacena[i][j]=' ';
                  }
                }
              }
              for(int i=x;i<tamanio;i++){
                int begin=0;
                if(x==i)begin=y;
                for(int j=begin;j<tamanio;j++){
                  int nx=i,ny=j;
                  anterior(nx,ny,k);
                  Almacena[nx][ny]=Almacena[i][j];
                  Almacena2[nx][ny]=Almacena2[i][j];
                }
              }
            }
          }
        }
        for(int i=0;i<tamanio_FAT;i++){
          if(FATarray[i].estado==0){
            for(int j=i;j<tamanio_FAT-1;j++){
              FATarray[j]=FATarray[j+1];
            }
            FATarray[tamanio_FAT-1].estado==2;
            i--;
          }
        }
        for(int i=0;i<tamanio_FAT;i++){
          bool ok=0;
          if(FATarray[i].estado==1){
            for(int j=0;j<tamanio && !ok;j++){
              for(int k=0;k<tamanio && !ok;k++){
                if(FATarray[i].c==Almacena[j][k]){
                  ok=1;
                  FATarray[i].x=j;
                  FATarray[i].y=k;
                }
              }
            }
          }
        }
      }
};
int main(){
  cout<<"Administracion de memoria"<<endl;
  cout<<"Ingrese el tamanio del FAT (max 20): ";
  int tamano;
  cin>>tamano;
  tamano = max(0, min(tamano,20));
  FAT x = FAT(tamano);
  int opcion=0;
  bool ok=1;
  while(ok){
      cout<<endl;
      cout<<"1.- Ver FAT"<<endl;
      cout<<"2.- Ver Almacenamiento"<<endl;
      cout<<"3.- Insertar un archivo"<<endl;
      cout<<"4.- Eliminar un archivo"<<endl;
      cout<<"5.- Eliminar vacios"<<endl;
      cout<<"6.- Salir"<<endl;
      cout<<"Ingrese una opcion: ";
      cin>>opcion;
      switch (opcion){
        case 1:
            x.MostrarFAT();
            break;
        case 2:
            x.MostrarAlmacenamiento();
            break;
        case 3:
            x.Registrar_archivo();
            break;
        case 4:
            x.Eliminar_Archivo();
          break;
        case 5:
            x.Eliminar_Vacios();
          break;
        case 6:
            ok=0;
            break;
      }

  }
  x.MostrarFAT();
}
