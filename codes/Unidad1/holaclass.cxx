#include<iostream>
#include<string>

using namespace std;

string mensaje="mensaje global";

class Saludo
{
    private:
    string mensaje;
    
    public:
    Saludo(string mensaje)
    {
        this->mensaje = mensaje;
        cout<<"Constructor llamado"<<endl;
    }

    ~Saludo(){
        cout<<"Destructor llamado"<<endl;
    }

    void saludar()
    {
        cout<<mensaje<<endl;
    }
};

int main()
{
    Saludo s("hola clase");
    s.saludar();
    //cout<<s.mensaje<<endl; //mensaje es privado, no puedo acceder desde aquí al atributo, sólo a lo público
    return 0;

}