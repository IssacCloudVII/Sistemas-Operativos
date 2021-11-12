#include <iostream>
#include <sstream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <vector>
#define N_Nodos 28
#define Max_Peso 15

using namespace std;

string generar_nombre();
//Devuelve un nombre al azar.

int buscar_conexion(vector<string> con1, vector<string> con2, string s1, string s2, int n);
//Tiene un arreglo de conexiones y dice si esa conexión está presente en el arreglo. Devuelve un entero dependiendo si sí o no.

int main()
{
    //generar nombres
    srand(time(0));
    ofstream FOUT;
    FOUT.open("archivo.txt");
    FOUT << N_Nodos << "\n";
    vector<string> nombres;

    for(int i = 0; i < N_Nodos; ++i)
    {
        nombres.push_back(generar_nombre());
        FOUT << nombres[i] << "\n";
    }

    //generar conexiones

    for(int i = 0; i < N_Nodos; ++i)
        for(int j = i; j < N_Nodos; ++j)
        	if(i != j)
                	FOUT << nombres[i] << "," << nombres[j] << "," << 10000 - rand() % Max_Peso << "\n";

    FOUT.close();

    cout << "YEI";

    return 0;
}

string generar_nombre()
{
    string nombres[10] = {"Bob", "Don", "Pat",
                          "Cal", "Are", "Pla", "Gar", "Kar", "Lar", "Per"};

    int n = rand() % 10;

    string nombre = nombres[n];

    int x = rand() % 10000;

    stringstream ss;
    string aux;

    ss << x;
    ss >> aux;

    nombre += aux;

    return nombre;
}

int buscar_conexion(vector<string> con1, vector<string> con2, string s1, string s2, int n)
{
    for(int i = 0; i < n; ++i)
        if((s1 == con1[i] && s2 == con2[i]) || (s2 == con1[i] && s1 == con2[i]))
            return 1;
    return -1;
}

