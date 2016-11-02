#include <iostream>
#include <string>

using namespace std;

class datFAT{
  public:
    string nombre;
    int tamano_arch;
    int x,y,estado;
    int c;
    datFAT(string _nombre, int tamano, int _x, int _y,char _c,int _estado){
      nombre = _nombre;
      tamano_arch = tamano;
      x = _x;
      y = _y;
      estado = _estado;
      c = _c;
    }
    datFAT(){
      estado = 2;
    }
};
class FAT {
   private:
     datFAT arregloFAT[20];
     char Almacena[30][30];
     bool usado[30][30];
     bool letras[26];
     int tamanio;
     int arreglo_size;
     int restante;
   public:
      FAT(int _size){
        tamanio = _size;
        arreglo_size = 20;
        restante = tamanio*tamanio;
        for(int i=0;i<26;i++)letras[i]=0;
        for(int i=0;i<tamanio;i++){
          for(int j=0;j<tamanio;j++){
            Almacena[i][j]=' ';
            usado[i][j]=0;
          }
        }
      }
      void Mostrar_array_FAT(){
        cout<<"\tFAT"<<endl;
        for(int i=0;i<tamanio;i++){
          if(arregloFAT[i].estado==2){
            cout<<0<<endl;
          }else{
            cout<<arregloFAT[i].nombre<<"\t"<<arregloFAT[i].tamano_arch<<" (";
            cout<<arregloFAT[i].x<<","<<arregloFAT[i].y<<") "<<arregloFAT[i].estado<<endl;
          }
        }
      }
      void MostrarAlmacenamiento(){
        cout<<"\tAlmacenamiento"<<endl;
        for(int i=0;i<tamanio+1;i++){
          cout<<"--";
        }
        cout<<endl;
        for(int i=0;i<tamanio;i++){
            cout<<"|";
            for(int j=0;j<tamanio;j++){
                cout<<Almacena[i][j]<<" ";
            }
            cout<<"|";
            cout<<endl;
        }
        for(int i=0;i<tamanio+1;i++){
          cout<<"--";
        }
        cout<<endl;
      }
      int Existe_archivo(string name){
        for(int i=0;i<arreglo_size;i++){
          if(arregloFAT[i].estado!=2 && arregloFAT[i].nombre==name){
            return i;
          }
        }
        return -1;
      }
      void get_Posicion(int &x,int &y,int tamano,int &pos){
        for(int i=0;i<arreglo_size;i++){
          if(arregloFAT[i].estado==2){
            if(i==0){
              if(tamanio*tamanio>=tamano){
                x=0;
                y=0;
                pos=0;
              }else{
                  cout<<"No hay espacio en la memoria"<<endl;
              }
              return ;
            }
            if(restante>=tamano){
              int total = arregloFAT[i-1].y + arregloFAT[i-1].x*tamanio;
              y=(total+arregloFAT[i-1].tamano_arch)%tamanio;
              x=(total+arregloFAT[i-1].tamano_arch)/tamanio;
              pos=i;
            }else{
              x=-1;
              cout<<"No hay espacio en la memoria"<<endl;
            }
            return ;
          }else if(arregloFAT[i].estado==0){
            if(restante>=tamano){
              x = arregloFAT[i].x;
              y = arregloFAT[i].y;
              pos = i;
            }else{
              cout<<"No hay espacio en la memoria"<<endl;
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
          cout<<"El nombre \""<<name<<"\" ya existe."<<endl;
          return ;
        }
        cout<<"Ingrese el tamano del archivo: ";
        cin>>tamano;
        get_Posicion(x,y,tamano,pos);
        if(x==-1){
          cout<<"No hay espacio suficiente"<<endl;
        }else{
          for(int i=0;i<26;i++){
            if(!letras[i]){
              c=i+'a';
              letras[i]=1;
              break;
            }
          }
          int cont=tamano;
          for(int i=x;i<tamanio && cont>0;i++){
            int begin=0;
            if(x==i)begin=y;
            for(int j=begin;j<tamanio && cont>0;j++){
              if(!usado[i][j]){
                Almacena[i][j]=c;
                usado[i][j]=1;
                cont--;
                restante--;
              }
            }
          }
          arregloFAT[pos] = datFAT(name,tamano,x,y,c,1);
        }
      }
      void Eliminar_Archivo(){
        string name;
        cout<<"Ingrese el nombre del archivo a eliminar: ";
        getline(cin,name);
        getline(cin,name);
        int pos=Existe_archivo(name);
        if(pos==-1){
          cout<<"El archivo \""<<name<<"\" no existe"<<endl;
          return ;
        }
        int x=arregloFAT[pos].x;
        int y=arregloFAT[pos].y;
        char c=Almacena[x][y];
        arregloFAT[pos].estado=0;
        for(int i=0;i<tamanio;i++){
          for(int j=0;j<tamanio;j++){
            if(c==Almacena[i][j]){
              usado[i][j]=0;
              restante++;
            }
          }
        }
        cout<<"El Archivo \'"<<name<<"\' ha sido eliminado"<<endl;
      }
      void anterior(int &x,int &y,int k){
        int total=x*tamanio+y-k;
        x=total/tamanio;
        y=total%tamanio;
      }
      void Eliminar_Vacios(){
        for(int i=0;i<tamanio;i++){
          for(int j=0;j<tamanio;j++){
            if(Almacena[i][j]!=' ' && usado[i][j]==0){
              int k=0;
              int total=tamanio*i+j;
              int x=i,y=j;
              while(usado[x][y]==0 && total+k<=tamanio*tamanio){
                k++;
                x=(total+k)/tamanio;
                y=(total+k)%tamanio;
              }
              char c=Almacena[i][j];
              for(int i=0;i<tamanio;i++){
                for(int j=0;j<tamanio;j++){
                  if(Almacena[i][j]==c){
                    usado[i][j]=0;
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
                  usado[nx][ny]=usado[i][j];
                }
              }
            }
          }
        }
        for(int i=0;i<arreglo_size;i++){
          if(arregloFAT[i].estado==0){
            for(int j=i;j<arreglo_size-1;j++){
              arregloFAT[j]=arregloFAT[j+1];
            }
            arregloFAT[arreglo_size-1].estado==2;
            i--;
          }
        }
        for(int i=0;i<arreglo_size;i++){
          bool ok=0;
          if(arregloFAT[i].estado==1){
            for(int j=0;j<tamanio && !ok;j++){
              for(int k=0;k<tamanio && !ok;k++){
                if(arregloFAT[i].c==Almacena[j][k]){
                  ok=1;
                  arregloFAT[i].x=j;
                  arregloFAT[i].y=k;
                }
              }
            }
          }
        }
      }
};
int main(){
  cout<<"SISTEMA TAD"<<endl;
  cout<<"Ingrese el tamanio del registro FAT: ";
  int tamano=0;
  do{
      cin>>tamano;
  }while(tamano<0 || tamano>20);
  FAT fat = FAT(tamano);
  int opcion=0;
  bool ok=1;
  while(ok){
      cout<<endl;
      cout<<"\t1. Ver FAT"<<endl;
      cout<<"\t2. Ver Almacenamiento"<<endl;
      cout<<"\t3. Insertar un archivo"<<endl;
      cout<<"\t4. Eliminar un archivo"<<endl;
      cout<<"\t5. Quitar vacios"<<endl;
      cout<<"\t6.- Salir"<<endl;
      cout<<"\tIngrese una opcion: ";
      cin>>opcion;
      switch (opcion){
        case 1:
            fat.Mostrar_array_FAT();
            break;
        case 2:
            fat.MostrarAlmacenamiento();
            break;
        case 3:
            fat.Registrar_archivo();
            break;
        case 4:
            fat.Eliminar_Archivo();
          break;
        case 5:
            fat.Eliminar_Vacios();
          break;
        case 6:
            ok=0;
            break;
      }
  }
}
