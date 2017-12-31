#include <iostream>
#include <stdio.h>      /* printf, fgets */
#include <stdlib.h>     /* atol */
#include <fstream>
#include <utility>
#include <vector>
#include <tuple>
#include <list>
#include <string>
#include <chrono>
#include <random>
#include "ejercicio1.h"
#include "ejercicio2.h"
#include "ejercicio3.h"
#include "ejercicio4.h"


using namespace std;

static chrono::time_point<chrono::high_resolution_clock> start_time;

void start_timer() {
	start_time = chrono::high_resolution_clock::now();
}

double stop_timer() {
	chrono::time_point<chrono::high_resolution_clock> end_time = chrono::high_resolution_clock::now();
    return double(chrono::duration_cast<chrono::nanoseconds>(end_time - start_time).count());
}

typedef tuple<double, int, vector<int> > solucion;

tuple<vector<vector<double> >, vector<Estacion> > cargar_input(int n, int m);

double distTrigonometrica(tuple<int, int, int> a, tuple<int, int, int> b);

void imprimir_res(tuple<double,int,vector<int > > res);

tuple<vector<vector<double> >, vector<Estacion> > dataentry(int & n, int & m, int & k);

tuple<vector<vector<double> >, vector<Estacion> > dataentry2(int & n, int & m, int & k);
tuple<vector<vector<double> >, vector<Estacion>, pair<int, bool>, bool, int> dataentry3(int & n, int & m, int & k);


int main(int argc, char *argv[]) {
    int numeroDeEjercicio = 0;
    bool experimentos = false;
    bool random = false;
    int instancias;
    char vecindarioExp;
    if (argc == 2) {
      numeroDeEjercicio = atoi(argv[1]);
    }
    else if (argc == 3 || argc == 4 || argc == 5) {
        numeroDeEjercicio = atoi(argv[1]);
        string exp = argv[2];
        if (exp == "-exp") {
            experimentos = true;
        }
        if (argc == 4) {
            if (exp == "-expRandom") {
                experimentos = true;
                random = true;
            }
            instancias = atoi(argv[3]);
        }

        if (argc == 5){
            if (exp == "-expRandom") {
                experimentos = true;
                random = true;
            }
            instancias = atoi(argv[3]);
            vecindarioExp = argv[4][0];
        }
    }
    else {
        cout << "Modo de uso: \n tp3 númeroDeEjercicio \n Opcional luego del número de ejercicio: " << endl;
        cout << "   -exp para experimentos" << endl;
        cout << "   -exp n para experimentos de n instancias" << endl;
        cout << "   -exp n a/b para experimentos de n instancias con el vecindario a o b" << endl;
        cout << "   -expRandom n para generar n instancias random" << endl;
        return -1;
    }

    if (numeroDeEjercicio == 1) {
        if (!experimentos) {
            cout << "ingrese la cantidad de gimnasios, paradas y el tamaño de la mochila" << endl;
            int n,m,k;
            cin >> n >> m >> k;
            cout << "ingrese en las siguientes " << n << " lineas xg, yg, pg, ubicacion y cantidad de posiones necesarias de los gym" << endl;
            cout << "luego, en las siguientes " << m << " lineas xp, yp ubicacion de las paradas" << endl;
            tuple<vector<vector<double> >, vector<Estacion> > input = cargar_input(n,m);
            vector<vector<double> > distancias = get<0>(input);
            vector<Estacion> estaciones = get<1>(input);
            std::tuple<double, int, std::vector<int> > res = solverEj1(estaciones, distancias, n, m, k);
            imprimir_res(res);
        }
        else if(experimentos && !random) {
            for (int inputs = 0; inputs < instancias; ++inputs) {
                int n,m,k;
                cin >> n >> m >> k;
                tuple<vector<vector<double> >, vector<Estacion> > input = cargar_input(n,m);
                vector<vector<double> > distancias = get<0>(input);
                vector<Estacion> estaciones = get<1>(input);
                for (int repeticiones = 0; repeticiones < 1; ++repeticiones) {
                    start_timer();
                    std::tuple<double, int, std::vector<int> > res = solverEj1(estaciones, distancias, n, m, k);
                        cout << stop_timer() << ", " << n << ", " << m << ", " << k << ", " << get<0>(res) << ", " << get<1>(res) << endl;
                }
            }
        }
        else {
            random_device rd;
            mt19937 gen(rd());
            uniform_int_distribution<> gyms(1,10);
            uniform_int_distribution<> cantPosiones(0,10);
            uniform_int_distribution<> x(0,1000);
            uniform_int_distribution<> y(0,1000);
            vector<tuple<int,int,int> > gimnasios;
            for (int i = 0; i < instancias; ++i) {
                int n = gyms(gen);
                gimnasios.clear();
                for (int i = 0; i < n; ++i) {
                    gimnasios.push_back(make_tuple(x(gen), y(gen), cantPosiones(gen)));
                }
                int sumPosiones = 0;
                for (int i = 0; i < n; ++i) {
                    sumPosiones += get<2>(gimnasios[i]);
                }
                int m = (sumPosiones / 3) + 1;

                cout << n << " " << m << " " << sumPosiones << endl;
                for (int i = 0; i < n; ++i) {
                    cout << get<0>(gimnasios[i]) << " " << get<1>(gimnasios[i]) << " " << get<2>(gimnasios[i]) << endl;
                }
                for (int i = 0; i < m; ++i) {
                    cout << x(gen) << " " << y(gen) << endl;
                }
                cout << endl;
            }
        }
    }
    else if (numeroDeEjercicio == 2) {
        if (!experimentos) {
            cout << "ingrese la cantidad de gimnasios, paradas y el tamaño de la mochila" << endl;
            int n,m,k;
            cin >> n >> m >> k;
            cout << "ingrese en las siguientes " << n << " lineas xg, yg, pg, ubicacion y cantidad de posiones necesarias de los gym" << endl;
            cout << "luego, en las siguientes " << m << " lineas xp, yp ubicacion de las paradas" << endl;
            tuple<vector<vector<double> >, vector<Estacion> > input = cargar_input(n,m);
            vector<vector<double> > distancias = get<0>(input);
            vector<Estacion> estaciones = get<1>(input);
            std::tuple<double, int, std::vector<int> > res = solverEj2(estaciones, distancias, n, m, k);
            imprimir_res(res);
        }
        else if(experimentos && !random){
            for (int inputs = 0; inputs < instancias; ++inputs) {
                int n,m,k;
                cin >> n >> m >> k;
                tuple<vector<vector<double> >, vector<Estacion> > input = cargar_input(n,m);
                vector<vector<double> > distancias = get<0>(input);
                vector<Estacion> estaciones = get<1>(input);
                for (int repeticiones = 0; repeticiones < 30; ++repeticiones) {
                    vector<Estacion> copiaEstaciones = estaciones;
                    start_timer();
                    std::tuple<double, int, std::vector<int> > res = solverEj2(copiaEstaciones, distancias, n, m, k);
                    cout << stop_timer() << ", " << n << ", " << m << ", " << k << ", " << get<0>(res) << ", " << get<1>(res) << endl;
                }
            }
        }
        else {
            int k = 100;
            for (int i = 1; i < 102; ++i) {
                cout << 5 << " " << i << " " << k << endl;
                cout << 0 << " " << 0 << " " << 3 << endl;
                cout << 1 << " " << 1 << " " << 3 << endl;
                cout << 2 << " " << 2 << " " << 3 << endl;
                cout << 3 << " " << 3 << " " << 3 << endl;
                cout << 4 << " " << 4 << " " << 3 << endl;
                for (int j = 0; j < i; ++j) {
                    cout << j+6 << " " << j+6 << endl;
                }
            }
            for (int i = 1; i < 102; ++i) {
                cout << 10 << " " << i << " " << k << endl;
                cout << 0 << " " << 0 << " " << 3 << endl;
                cout << 1 << " " << 1 << " " << 3 << endl;
                cout << 2 << " " << 2 << " " << 3 << endl;
                cout << 3 << " " << 3 << " " << 3 << endl;
                cout << 4 << " " << 4 << " " << 3 << endl;
                cout << 5 << " " << 5 << " " << 3 << endl;
                cout << 6 << " " << 6 << " " << 3 << endl;
                cout << 7 << " " << 7 << " " << 3 << endl;
                cout << 8 << " " << 8 << " " << 3 << endl;
                cout << 9 << " " << 9 << " " << 3 << endl;
                for (int j = 0; j < i; ++j) {
                    cout << j+11 << " " << j+11 << endl;
                }
            }
            for (int i = 1; i < 102; ++i) {
                cout << 15 << " " << i << " " << k << endl;
                cout << 0 << " " << 0 << " " << 3 << endl;
                cout << 1 << " " << 1 << " " << 3 << endl;
                cout << 2 << " " << 2 << " " << 3 << endl;
                cout << 3 << " " << 3 << " " << 3 << endl;
                cout << 4 << " " << 4 << " " << 3 << endl;
                cout << 5 << " " << 5 << " " << 3 << endl;
                cout << 6 << " " << 6 << " " << 3 << endl;
                cout << 7 << " " << 7 << " " << 3 << endl;
                cout << 8 << " " << 8 << " " << 3 << endl;
                cout << 9 << " " << 9 << " " << 3 << endl;
                cout << 10 << " " << 10 << " " << 3 << endl;
                cout << 11 << " " << 11 << " " << 3 << endl;
                cout << 12 << " " << 12 << " " << 3 << endl;
                cout << 13 << " " << 13 << " " << 3 << endl;
                cout << 14 << " " << 14 << " " << 3 << endl;
                for (int j = 0; j < i; ++j) {
                    cout << j+16 << " " << j+16 << endl;
                }
            }
        }
    }
    else if (numeroDeEjercicio == 3) {
        if(!experimentos){
            char vecindario;
            int n,m,k;
            cout << "Ingrese 'a' para vecindario de swapear paradas, o 'b' para swapear gym's " << endl;
            cin >> vecindario;
            tuple<vector<vector<double> >, vector<Estacion> > input = dataentry(n, m, k);
            vector<vector<double> > distancias = get<0>(input);
            vector<Estacion> estaciones = get<1>(input);
            solucion res = solverEj3(estaciones, distancias, n, m, k, vecindario == 'a');
            imprimir_res(res);
        }
        else{
            int n,m,k;
            for (int inputs = 0; inputs < instancias; ++inputs) {
                tuple<vector<vector<double> >, vector<Estacion> > input = dataentry2(n, m, k);
                vector<vector<double> > distancias = get<0>(input);
                vector<Estacion> estaciones = get<1>(input);
                for (int repeticiones = 0; repeticiones < 30; ++repeticiones) {
                    start_timer();
                    solucion res = solverEj3(estaciones, distancias, n, m, k, vecindarioExp == 'a');
                    cout << stop_timer() << ", " << n << ", " << m << ", " << k << ", " << get<0>(res) << ", " << get<1>(res) << endl;
                }                
            }
        }
    }
    else if (numeroDeEjercicio == 4) {
        int n,m,k;
        int grasp = 0;
        bool criterio = false;
        int limite = 0;
        int iCriterio = 0;
        int iBusqLocal = 0;
        bool busqLocal = false;
        tuple<int, bool> critParada;
        if(!experimentos){
            tuple<vector<vector<double> >, vector<Estacion> > input = dataentry(n, m, k);
            while (1 > grasp || grasp > n+m) {
                cout << "Elija un valor menor o igual a " << n+m << " para limitar el tamaño de RCL " << endl;
                cin >> grasp;
            }
            cout << "Elija el criterio de parada (1 o 2) y su límite" << endl;
            cin >> iCriterio >> limite;
            criterio = iCriterio == 2;
            cout << "Elija si la búsqueda local será por pokeparadas o por gimnasios (1 o 2) " << endl;
            cin >> iBusqLocal;
            busqLocal = iBusqLocal == 2;
            vector<vector<double> > distancias = get<0>(input);
            vector<Estacion> estaciones = get<1>(input);
            solucion res = solverEj4(estaciones, distancias, n, m, k, grasp, { limite, criterio }, busqLocal);
            imprimir_res(res);
        } 
        else if (experimentos && !random) {
            for (int inputs = 0; inputs < instancias; ++inputs) {
                auto input = dataentry3(n, m, k);
                vector<vector<double> > distancias = get<0>(input);
                vector<Estacion> estaciones = get<1>(input);
                pair<int, bool> criterio = get<2>(input);
                bool busqLocalAux = get<3>(input);
                
                for (grasp = 1; grasp <= 15; grasp++) {
                    for (int repeticiones = 0; repeticiones < 20; ++repeticiones) {
                        start_timer();
                        solucion res = solverEj4(estaciones, distancias, n, m, k, grasp, criterio, busqLocalAux);
                        cout << stop_timer() << ", " << get<0>(res) << ", " << grasp << endl;
                    }
                }
            }
            

            // for (int inputs = 0; inputs < instancias; ++inputs) {
            //     auto input = dataentry3(n, m, k);
            //     vector<vector<double> > distancias = get<0>(input);
            //     vector<Estacion> estaciones = get<1>(input);
            //     pair<int, bool> criterio = get<2>(input);
            //     bool busqLocalAux = get<3>(input);
            //     grasp = get<4>(input);

            //     // grasp = get<4>(input);
            //     for (int crit = 1; crit <= 15; crit++) {            
            //         criterio.first = crit;

            //         for (int repeticiones = 0; repeticiones < 20; ++repeticiones) {
            //             start_timer();
                        
            //             solucion res = solverEj4(estaciones, distancias, n, m, k, grasp, criterio, busqLocalAux);

            //             cout << stop_timer() << ", " << get<0>(res) << ", " << criterio.first << endl;
            //         }
            //     }
            // }

        } else
            {
	            random_device rd;
	            mt19937 gen(rd());
	            uniform_int_distribution<> gyms(1,15);
	            uniform_int_distribution<> cantPosiones(0,20);
	            uniform_int_distribution<> x(0,1000);
	            uniform_int_distribution<> y(0,1000);
	            vector<tuple<int,int,int> > gimnasios;

                vector<int> ns;
                vector<int> xs;
                vector<int> ys;
                vector<int> cantPoss;

                vector<int> xs2;
                vector<int> ys2;

                int sumPosiones = 0;
                int m;
                int index;
                int pos;
                int n;
                int contadorMagico;
                int contadorMagico2;
                int pocionesParaConqGimnasio;

                for (int i = 0; i < instancias; ++i) {
                    n = gyms(gen);
                    ns.push_back(n);

                    sumPosiones = 0;
                    for (int j = 0; j < n; ++j) {
                        xs.push_back(x(gen));
                        ys.push_back(y(gen));
                        pos = cantPosiones(gen);
                        cantPoss.push_back(pos);
                        sumPosiones += pos;
                        
                    }

                    m = (sumPosiones / 3) + 1;
                    
                    for (int j = 0; j < m; ++j) {
                        xs2.push_back(x(gen));
                        ys2.push_back(y(gen));
                    }
                }

                for (int ju = 0; ju < 4; ju++) {
                    contadorMagico = 0;
                    contadorMagico2 = 0;
    	            for (int i = 0; i < instancias; ++i) {
    	                n = ns[i];

    	                gimnasios.clear();
                        sumPosiones = 0;
    	                for (int j = 0; j < n; ++j) {
                            pocionesParaConqGimnasio = cantPoss[contadorMagico];
                            gimnasios.push_back(make_tuple(xs[contadorMagico], ys[contadorMagico], pocionesParaConqGimnasio));
                            sumPosiones = sumPosiones + pocionesParaConqGimnasio;
                            contadorMagico++;
                        }

                        m = (sumPosiones / 3) + 1;
                        
                        cout << n << " " << m << " " << sumPosiones << endl;

                        for (int j = 0; j < n; ++j) {
                            cout << get<0>(gimnasios[j]) << " " << get<1>(gimnasios[j]) << " " << get<2>(gimnasios[j]) << endl;
                        }
                        for (int j = 0; j < m; ++j) {

                            cout << xs2[contadorMagico2] << " " << ys2[contadorMagico2] << endl;
                            contadorMagico2++;
                        }
                        
                        int cantEstacion = 0;
                        int crit = 15;
                        if (ju == 0)
                            cout << cantEstacion << " " << 1 << " " << crit << " " << 1 << endl;
                        else if (ju == 1)
                            cout << cantEstacion << " " << 1 << " " << crit << " " << 2 << endl;
                        else if (ju == 2)
                            cout << cantEstacion << " " << 2 << " " << crit << " " << 1 << endl;
                        else if (ju == 3)
                            cout << cantEstacion << " " << 2 << " " << crit << " " << 2 << endl;

                        cout << endl;
    	            }
                }
            }
        }
  return 0;
}

tuple<vector<vector<double> >, vector<Estacion> > dataentry(int & n, int & m, int & k){
    cout << "ingrese la cantidad de gimnasios, paradas y el tamaño de la mochila" << endl;
    cin >> n >> m >> k;
    cout << "ingrese en las siguientes " << n << " lineas xg, yg, pg, ubicacion y cantidad de posiones necesarias de los gym" << endl;
    cout << "luego, en las siguientes " << m << " lineas xp, yp ubicacion de las paradas" << endl;
    return cargar_input(n,m);
}

tuple<vector<vector<double> >, vector<Estacion> > dataentry2(int & n, int & m, int & k){
    cin >> n >> m >> k;
    return cargar_input(n,m);
}

tuple<vector<vector<double> >, vector<Estacion>, pair<int, bool>, bool, int> dataentry3(int & n, int & m, int & k){
    tuple<vector<vector<double> >, vector<Estacion> > input = dataentry2(n, m, k);
    int grasp = 0;
    bool criterio = false;
    int limite = 0;
    bool busqLocal = false;
    int icriterio;
    int ibusqLocal;
    
    cin >> grasp >> icriterio >> limite >> ibusqLocal;

    criterio = icriterio == 2;
    busqLocal = ibusqLocal == 2;

    vector<vector<double> > distancias = get<0>(input);
    vector<Estacion> estaciones = get<1>(input);
    pair<int, bool> crit = {limite, criterio};

    return make_tuple(distancias, estaciones, crit, busqLocal, grasp);
}
/*
lodesiempre
grasp criterio(1 o 2) limite busqLocal(1 o 2)
*/

tuple<vector<vector<double> >, vector<Estacion> > cargar_input(int n, int m){
  vector< tuple <int, int, int> > gimnasios_y_paradas;

  for (int i = 0; i < n; i++) {
    int x,y,p;
    cin >> x >> y >> p;
    p = 0-p;
    tuple<int,int,int> gym = make_tuple(x,y,p);
    gimnasios_y_paradas.push_back(gym);
  }

  for (int i = 0; i < m; i++) {
    int x,y;
    cin >> x >> y;
    tuple<int,int,int> pp = make_tuple(x,y,3);
    gimnasios_y_paradas.push_back(pp);
  }

  vector<vector<double> > distancias(n+m);
  for (int i = 0; i < n+m; ++i) {
    for (int k = 0; k < n+m; ++k) {
      double dist_ik = distTrigonometrica(gimnasios_y_paradas[i], gimnasios_y_paradas[k]);
      distancias[i].push_back(dist_ik);
    }
  }
  vector<Estacion> estaciones(n+m);
  for (int i = 0; i < gimnasios_y_paradas.size(); i++){
    bool esGimnasio = i < n;
    int potas = get<2>(gimnasios_y_paradas[i]);
    estaciones[i] = Estacion(esGimnasio, potas, i);
  }
  return make_tuple(distancias,estaciones);
}


double distTrigonometrica(tuple<int, int, int> a, tuple<int, int, int> b){
  int xa = get<0>(a);
  int ya = get<1>(a);
  int xb = get<0>(b);
  int yb = get<1>(b);
  int x = (abs(xa - xb))*(abs(xa - xb));
  int y = (abs(ya - yb))*(abs(ya - yb));
  return sqrt(x+y);
}

void imprimir_res(tuple<double,int,vector<int > > res){
  cout << "D= " << get<0>(res) << " k= " << get<1>(res) << " i= ";
    for (int i = 0; i < get<1>(res); ++i) {
      cout << get<2>(res)[i]+1 << " ";
    }
    cout << endl;
}
