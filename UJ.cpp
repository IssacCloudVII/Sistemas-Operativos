//Entrega Final Ejecutable
//Equipo: Estaban Ayala Mayen, Octavio De Marcelo Chang, José Manuel Méndez Albarrán, Héctor Quezada Alanís

//Librerías
#include <iostream>
#include <cstring>
#include <fstream>
#include <string>
#include <sstream>
#include <limits>
#include <vector>
#include <algorithm>
#include <climits>
#include <iterator>
#include <cstdio>
#include <queue>
#include <omp.h>
using namespace std;

//Prototipos de función
bool checarRepetido (vector<string>&, string&);
//Recibe un vector de nombres y un nombre, regresa un booleano si está o no repetido. 
bool insertarAdyacencia(int, int, vector<vector<int>>&);
//Recibe un dos enteros y un vector de vectores de entero. Busca conexiones entre nodos y pone su peso. Regresa booleano. 

int buscarIndice(string, vector <string>);
//Recibe una cadena y un vector de nombres. Regresa el indice de ese nombre, -1 si no lo encuentra. 
int distanciaMinima (int[], bool[], int);
//Recibe un arreglo de enteros, de booleanos y un entero. Regresa la distancia minima. 
int noVisitado(int, vector<int>&);
//Recibe un entero de un nodo, y un vector de enteros para modificar. Regresa un entero. 

string mayusculas(string &s);
//Recibe una cadena y la modifica. Regresa una cadena. 

void DFS(vector<vector<int> >&, int, int, vector<vector<int> >&);
//Recibe un vector de vectores de enteros, un nodo origen, nodo destino, y un vector de rutas para modificarse. No regresa nada.
void DFSNP(vector<vector<int> >&, int, int, vector<vector<int> >&);
//Recibe un vector de vectores de enteros, un nodo origen, nodo destino, y un vector de rutas para modificarse. No regresa nada.
void dijkstra(vector<vector<int> >, int, int, vector<string>, int[], int[]);
//Recibe un vector de vectores de enteros, un nodo origen, nodo destino, un vector de nombres, y dos arreglos de enteros. No regresa nada.
void dijkstraNP(vector<vector<int> >, int, int, vector<string>, int[], int[]);
//Recibe un vector de vectores de enteros, un nodo origen, nodo destino, un vector de nombres, y dos arreglos de enteros. No regresa nada.
void imprimirCamino (int[], int, vector<string>);
//Recibe un vector de enteros, un entero y un arreglo de nombres para imprimir una ruta. No regresa nada.
void imprimeDFS(vector<vector<int> >, vector<string>);
//Recibe un vector de vectores de enteros y un arreglo de nombres para imprimir una ruta.  No regresa nada.
void imprimirDijkstra(int[], vector<string>, int, int, int[]);
//Recibe un arreglo de enteros, un vector de nombres, un nodo origen y destino, y un arreglo de enteros.  No regresa nada.
void imprimirMatriz(vector<vector<int> > &, int);
//Recibe un vector de vector de enteros, y un entero.  No regresa nada.
void imprimirNombres(vector<string>&);
//Recibe un vector de vector de enteros, y un entero.  No regresa nada.
void iniciarMatriz(vector<vector<int> > &, int);
//Recibe un vector de vector de enteros, y un entero.  No regresa nada.
void imprimirTodosCaminos(int, int, int, vector<vector<int> >, vector<string>, bool&);
//Recibe tres enteros, un vector de vector de enteros, un vector de nombres, y un booleano para modificar. No regresa nada. 
void imprimirTodosCaminosAux(int, int, vector<vector<int> >, vector<string>, bool [], int[], int&, bool&);
//Recibe dos enteros, un vector de vector de enteros, un vector de nombres, un vector de booleanos, un arreglo de enteros y un entero y un boleano, ambos para modificar. No regresa nada. 

int main()
{
    bool ruta = false;
    int opcion1;
    string origen, destino;
    string texto;
    
    vector<string> nombres;
    int renglon, opcion, lectura, origenval, destinoval, peso;
    int cuantos;
    vector <vector<int>> matriz;
    string dato;
    ifstream archivo;
    lectura = 0;
    opcion = 0;
    renglon = 0;
    cuantos = 0;
    archivo.open("TFXIV.txt");
    if(archivo.is_open())
    {
        while (archivo.good())
        {
            if (renglon == 0)
            {
                getline(archivo, dato);
                cuantos = stoi(dato);
                matriz.resize(cuantos, vector<int>(cuantos, 0));
            }
            else if (renglon >= 1 && renglon <= cuantos)
            {
                getline(archivo, dato);
                mayusculas(dato);
                nombres.push_back(dato);
            }
            else
            {
                getline(archivo, dato);
                istringstream aux (dato);
                while(aux)
                {
                    if (!getline(aux, dato, ','))
                        break;
                    if(lectura == 0)
                    {
                        mayusculas(dato);
                        origenval = buscarIndice(dato, nombres);
                        if (origenval != -1)
                            lectura++;
                        else
                        {
                            cout << "El nodo de origen no existe, por favor reviselo" << endl;
                            return 0;
                        }
                    }
                    else if(lectura == 1)
                    {
                        mayusculas(dato);
                        destinoval = buscarIndice(dato, nombres);
                        if (destinoval != -1)
                            lectura++;
                        else
                        {
                            cout << "El nodo de destino no existe, por favor reviselo";
                            return 0;
                        }
                    }
                    else
                    {
                        peso = stoi(dato);
                        matriz[origenval][destinoval] = peso;
                        lectura = 0;
                    }
                }

            }
            renglon++;
        }
    }
    else 
    {
    	cout << "Error en la apertura del archivo. Inténtelo de nuevo" << endl;
    	return 0; 
    } 
    int padre[cuantos], distancia[cuantos];
    do
    {
        system("clear");
        puts ("Bienvenido a Manejador de Grafos!");
        puts ("1.- Imprimir Matriz Adyacencias.");
        puts ("2.- Imprimir Vector de Nombres.");
        puts ("3.- Dijkstra Paralelo.");
        puts ("4.- Revisar todos los caminos a un destino.");
        puts ("5.- DFS Paralelo.");
        puts ("6.- Dijkstra No Paralelo.");
        puts ("7.- DFS No Paralelo.");
        puts ("0.- Salir.");
        cout << "Seleccione opcion deseada: ";
        cin >> opcion1;
        switch (opcion1)
        {
            case 1:
                system("clear");
                imprimirMatriz(matriz, cuantos);
                cout << " " << endl;
            break;
            case 2:
                system("clear");
                imprimirNombres(nombres);
                cout << " " << endl;
            break;
            case 3:
                system("clear");
                int indice;
                cout << "Indique que ciudad sera el origen: ";
                cin >> origen;
                mayusculas(origen);
                indice = buscarIndice(origen, nombres);
                if (indice != -1)
                {
                	dijkstra(matriz, cuantos, indice, nombres, padre, distancia);
                	imprimirDijkstra(distancia, nombres, indice, cuantos, padre);
                }
                else
                    cout << "Esa ciudad no existe, por favor, intentelo de nuevo." << endl;
            break;
            case 4:
                system("clear");
                int indiceOrigen, indiceFinal;
                cout << "Indique que ciudad sera el origen: ";
                cin >> origen;
                indiceOrigen = buscarIndice(mayusculas(origen), nombres);
                cout << "Indique que ciudad sera el destino: ";
                cin >> destino;
                indiceFinal = buscarIndice(mayusculas(destino), nombres);
                if (indiceOrigen != -1 && indiceFinal != -1)
                {
                    imprimirTodosCaminos(indiceOrigen, indiceFinal, cuantos, matriz, nombres, ruta);
                    if (ruta == false)
                        cout << "No hay ruta de " << nombres[indiceOrigen] << " a " << nombres[indiceFinal] << endl;
                }
                else
                    cout << "Alguna de las ciudades no existe, por favor intentelo de nuevo." << endl;
            break;
            case 5:
            {
           
                vector <vector<int> > caminosDFS;
                int id;
                vector<int>ruta;
                vector<vector<int>>rutas;
                int indiceOrigen, indiceFinal;
                cout << "Indique que ciudad sera el origen: ";
                cin >> origen;
                indiceOrigen = buscarIndice(mayusculas(origen), nombres);
                cout << "Indique que ciudad sera el destino: ";
                cin >> destino;
                indiceFinal = buscarIndice(mayusculas(destino), nombres);
                if (indiceOrigen != -1 && indiceFinal != -1)
			DFS(matriz, indiceOrigen, indiceFinal, caminosDFS);  
                else
                	cout << "Alguno de los puntos no existe." << endl;
            }
            break;
            case 6:
            	system("clear");
                cout << "Indique que ciudad sera el origen: ";
                cin >> origen;
                mayusculas(origen);
                indice = buscarIndice(origen, nombres);
                if (indice != -1)
                {
                	dijkstraNP(matriz, cuantos, indice, nombres, padre, distancia);
                	imprimirDijkstra(distancia, nombres, indice, cuantos, padre);
                }
                else
                    cout << "Esa ciudad no existe, por favor, intentelo de nuevo." << endl;
            break;
            case 7:
            	{
           
		        vector <vector<int> > caminosDFS;
		        int id;
		        vector<int>ruta;
		        vector<vector<int>>rutas;
		        int indiceOrigen, indiceFinal;
		        cout << "Indique que ciudad sera el origen: ";
		        cin >> origen;
		        indiceOrigen = buscarIndice(mayusculas(origen), nombres);
		        cout << "Indique que ciudad sera el destino: ";
		        cin >> destino;
		        indiceFinal = buscarIndice(mayusculas(destino), nombres);
		        if (indiceOrigen != -1 && indiceFinal != -1)
				DFSNP(matriz, indiceOrigen, indiceFinal, caminosDFS);
		        else
		        	cout << "Alguno de los puntos no existe." << endl;
            	}
            break;
            case 0:
                cout << "De nada, vuelva pronto." << endl;
                break;
            default:
                cout << "Opcion no valida, intente de nuevo por favor." << endl;
                break;
        }
	cin.get();
	cin.ignore();
    }while(opcion1 != 0);
    return 0;
}

//Funciones
bool checarRepetido(vector<string> &nombres, string &texto)
{
    for (auto i = nombres.begin(); i != nombres.end(); ++i)
    {
        if (*i == texto)
            return false;
    }
    return true;
}

bool insertarAdyacencia(int num1, int num2, vector<vector<int> > &matriz)
{
    if (num1 == -1 || num2 == -1)
        return false;
    matriz[num1][num2] = 1;
    return true;
}

int buscarIndice(string nombre, vector<string> nombres)
{
    int num = 0;
    for (auto i = nombres.begin(); i != nombres.end(); ++i)
    {
        if (*i == nombre)
            return num;
        num++;
    }
    return -1;
}

int distanciaMinima(int distancia[], bool aux[], int cuantos)
{
    int minimo = INT_MAX, indiceMinimo;
    for (int i = 0; i < cuantos; i++)
    {
        if(aux[i] == false && distancia[i] <= minimo)
        {
            minimo = distancia[i];
            indiceMinimo = i;
        }
    }
    return indiceMinimo;
}

int noVisitado(int x, vector<int>& camino)
{
	int t = camino.size();
	for (int i = 0; i < t; i++)
		if (camino[i] == x)
			return 0;
	return 1;
}

string mayusculas(string &s)
{
    s.erase(remove(s.begin(), s.end(), '\r'), s.end());
    s.erase(remove(s.begin(), s.end(), '\n'), s.end());
    transform(s.begin(), s.end(), s.begin(),
              [] (unsigned char c){ return toupper(c); });
    return s;
}

void DFS(vector<vector<int>> &matriz, int origen, int destino, vector<vector<int>> &caminos)
{
    double start, end;
    start = omp_get_wtime();
    #pragma omp parallel num_threads(2) shared (caminos)
    {
    	    int id;
            id = omp_get_thread_num();
	    cout << "ID: " << id << endl;
	    queue<vector<int>> q; 
	    vector<int> camino; //Se inserta el nodo origen. 
	    camino.push_back(origen); 
	    q.push(camino); //Se ingresa el nuevo camino.
	    while(!q.empty()) //Se verifica que el queue no esté vacío.
	    {
	    	camino = q.front();  //Se saca el primer nodo de q y se guarda en camino.
	    	q.pop(); //Se saca el primer nodo de la queue.
	    	int last = camino[camino.size() - 1]; //last = último nodo del arreglo camino.
	    	if (last == destino) //Si es igual al destino, se encontró la ruta.
	    	{
	    		/*for (int x:camino)
	    			cout << x << "-->";
	    		cout << endl;*/
	    	}
	    	for (int i = 0; i < matriz[last].size(); i++)  //Si no es así, se itera con los nodos que tenga conexión.
	    	{
	    		if (noVisitado(i, camino) && matriz[last][i] > 0)
	    		{ 
	    			vector<int> nuevo(camino);
	    			nuevo.push_back(i);
	    			q.push(nuevo);
	    		}
	    	}
	    }
    }
    end = omp_get_wtime();
    cout << "TIEMPO: " << end - start << endl;
}

void DFSNP(vector<vector<int>> &matriz, int origen, int destino, vector<vector<int>> &caminos)
{
    double start, end;
    start = omp_get_wtime();
    queue<vector<int>> q; 
    vector<int> camino; //Se inserta el nodo origen. 
    camino.push_back(origen);
    q.push(camino);//Se ingresa el nuevo camino.
    while(!q.empty())//Se verifica que el queue no esté vacío.
    {
    	camino = q.front(); //Se saca el primer nodo de q y se guarda en camino.
    	q.pop();//Se saca el primer nodo de la queue.
    	int last = camino[camino.size() - 1];//last = último nodo del arreglo camino.
    	if (last == destino) 
    	{
    		/*for (int x:camino)
    			cout << x << "-->";
    		cout << endl;*/
    	}
    	for (int i = 0; i < matriz[last].size(); i++)  //Si no es así, se itera con los nodos que tenga conexión.
    	{
    		if (noVisitado(i, camino) && matriz[last][i] > 0)
    		{ 
    			vector<int> nuevo(camino);
    			nuevo.push_back(i);
    			q.push(nuevo);
    		}
    	}
    }
    end = omp_get_wtime();
    cout << "TIEMPO: " << end - start << endl;
}
void dijkstra(vector<vector<int> > matriz, int cuantos, int indiceOrigen, vector<string> nombres, int padre[], int distancia[])
{
    bool aux[cuantos];
    int id;
    double start, end;
    
    for (int i = 0; i < cuantos; ++i) //Se inicializan los nodos, ningun ha sido visitado. 
    {
        padre[i] = -1;
        distancia[i] = INT_MAX;
        aux[i] = false;
    }
    start = omp_get_wtime();
    #pragma omp parallel num_threads(2)
    {
            id = omp_get_thread_num();
            cout << "ID: " << id << endl;
	    distancia[indiceOrigen] = 0; //La distancia hacia mi mismo nodo es 0. 
	    for (int i = 0; i < cuantos - 1; ++i) 
	    {
		int u = distanciaMinima(distancia, aux, cuantos); //u es la posición del nodo más cercano desde donde estoy. 
		aux[u] = true; //marco ese nodo como visitado. 
		for (int j = 0; j < cuantos; ++j) //Iterar cada nodo con el que tenga conexión.
		{
		    if(!aux[j] && matriz[u][j] && distancia[u] != INT_MAX && distancia[u] + matriz[u][j] < distancia[j]) //Si no lo he visitado y existe la conexión entre ellos; y la distancia hacia ese nodo es diferente de la distancia MAXIMA y la de donde vengo hacia donde voy es menor hacia donde voy, le sumo la distancia a donde voy a ir, y mi anterior se convierte a donde estaba para pasar al siguiente nodo que tengo conexión.
		    {
		        padre[j] = u;
		        distancia[j] = distancia[u] + matriz[u][j];
		    }
		}
	    }
    }
    end = omp_get_wtime();
    cout << "TIEMPO: " << end - start << endl;
}

void dijkstraNP(vector<vector<int> > matriz, int cuantos, int indiceOrigen, vector<string> nombres, int padre[], int distancia[])
{
    bool aux[cuantos];
    double start, end;
    
    for (int i = 0; i < cuantos; ++i) //Se inicializan los nodos, ningun ha sido visitado. 
    {
        padre[i] = -1;
        distancia[i] = INT_MAX;
        aux[i] = false;
    }
    start = omp_get_wtime();
    distancia[indiceOrigen] = 0; //La distancia hacia mi mismo nodo es 0.
    for (int i = 0; i < cuantos - 1; ++i)
    {
	int u = distanciaMinima(distancia, aux, cuantos);  //u es la posición del nodo más cercano desde donde estoy. 
	aux[u] = true;  //marco ese nodo como visitado. 
	for (int j = 0; j < cuantos; ++j)
	{
	    if(!aux[j] && matriz[u][j] && distancia[u] != INT_MAX && distancia[u] + matriz[u][j] < distancia[j]) //Si no lo he visitado y existe la conexión entre ellos; y la distancia hacia ese nodo es diferente de la distancia MAXIMA y la de donde vengo hacia donde voy es menor hacia donde voy, le sumo la distancia a donde voy a ir, y mi anterior se convierte a donde estaba para pasar al siguiente nodo que tengo conexión.
	    {
	        padre[j] = u;
	        distancia[j] = distancia[u] + matriz[u][j];
	    }
	}
    }
    end = omp_get_wtime();
    cout << "TIEMPO: " << end - start << endl;
}

void imprimirCamino(int padre[], int posicion, vector<string> nombres)
{
    if(padre[posicion] < 0)
        return;
    imprimirCamino(padre, padre[posicion], nombres);
    cout << "-->" << nombres[posicion];
}

void imprimeDFS(vector<vector<int> > caminos, vector<string> nombres) 
{
	for (int i = 0; i < caminos.size() / 2; i++)
	{
		for (int j = 0; j < caminos[i].size(); j++)
		{
			if (j == caminos[i].size() - 1)
				cout << nombres[caminos[i][j]];
			else
				cout << nombres[caminos[i][j]] << " --> ";
		}
		cout << endl; 
	}
}

void imprimirDijkstra(int distancia[], vector<string> nombres, int indice, int cuantos, int padre[])
{
    cout << "Ciudad \t\t\t            Distancia desde " << nombres[indice] << " \t Camino" << endl;
    for (int i = 0; i < cuantos; ++i)
    {
        printf ("\n");
        if (distancia[i] != INT_MAX)
        {
            cout << nombres[indice] << " --> " << nombres[i] << " \t\t\t          " << distancia[i] << "\t\t  " << nombres[indice];
            imprimirCamino(padre, i, nombres);
            cout << "" << endl;
        }
        else
            cout << nombres[i] << " \t\t" << "No hay ruta hacia esta ciudad" << "\t  " << "Al no haber ruta, no se muestra un camino" << endl;
    }

}

void imprimirMatriz(vector<vector<int> > &matriz, int cuantos)
{
    for (int i = 0; i < cuantos; ++i)
    {
        cout << endl;
        for (int j = 0; j < cuantos; ++j)
            cout << " | " << matriz[i][j] << " | ";
    }
}

void imprimirNombres(vector<string> &nombres)
{
    for (auto i = nombres.begin(); i != nombres.end(); ++i)
        cout << *i << endl;
}

void iniciarMatriz(vector<vector<int> > &matriz, int cuantos)
{
    for (int i = 0; i < cuantos; ++i)
    {
        for (int j = 0; j < cuantos; ++j)
            matriz[i][j] = 0;
    }
}

void imprimirTodosCaminos(int origen, int destino, int cuantos, vector<vector<int> > matriz, vector<string> nombres, bool& ruta)
{
    bool* visitados = new bool[cuantos];
    int* camino = new int [cuantos];
    int indiceCamino = 0;

    for(int i = 0; i < cuantos; ++i)
        visitados[i] = false;
    imprimirTodosCaminosAux(origen, destino, matriz, nombres, visitados, camino, indiceCamino, ruta);
}

void imprimirTodosCaminosAux(int origen, int destino, vector<vector<int> > matriz, vector<string> nombres, bool visitados[], int camino[], int& indiceCamino, bool& ruta)
{
    visitados[origen] = true;
    camino[indiceCamino] = origen;
    indiceCamino++;
    if(origen == destino)
    {
        ruta = true;
        cout << nombres[camino[0]];
        for(int i = 1; i < indiceCamino; ++i)
            cout << " --> " << nombres[camino[i]];
        cout << endl;
    }
    else
    {
        int j = 0;
        for(auto i = matriz[origen].begin(); i != matriz[origen].end(); ++i, ++j)
        {
            if(!visitados[j] && *i != 0)
                imprimirTodosCaminosAux(j, destino, matriz, nombres, visitados, camino, indiceCamino, ruta);
        }
    }

    indiceCamino--;
    visitados[origen] = false;
}


