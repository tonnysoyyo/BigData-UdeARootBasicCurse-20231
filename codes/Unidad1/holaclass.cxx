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
        cout<<"Contructor llamado"<<endl;
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
    Saludo s("hola clases");
    s.saludar();
    //cout<<s.mensaje<<endl;
    return 0;

}