#include "ejercicio3.h"

using namespace std;

salida Mochilero(int cantMochilas, int cantTesoros, vector<int> capacidades, vector<int> tesoroCant, vector<int> tesoroPeso, vector<int> tesoroValor) {
	//capacidades.size() == cantMochilas
	//tesoro = cantidad, peso, valor
	//pair<int, pair<int, int>> tesoro;
	//0 < cantMochilas <= 3
	/*
		SALIDA:
		valorTotal con el valor total de los tesoros guardados

		Y para la mochila i:
		mochila_i con mochila_i[0] indicando la cantidad de tesoros que tiene, mochila_i[1..N] indicando los tipos
	*/

	while(capacidades.size() < 3){
		capacidades.push_back(0);	
	} 

	int valorTesoro;
	int pesoTesoro;
	int cantidadPorTipoTesoro;
	int valorMochila1;
	int valorMochila2;
	int valorMochila3;
	int valorNingunaMochila;
	int iMochila1;
	int iMochila2;
	int iMochila3;
	bool metoEnMochila1;
	bool metoEnMochila2;
	bool metoEnMochila3;
	
	int valorAnterior1;
	int valorAnterior2;
	int valorAnterior3;
	bool entraEnMochila1;
	bool entraEnMochila2;
	bool entraEnMochila3;

	int valorTotal = 0;
	vector<int> mochila1;
	vector<int> mochila2;
	vector<int> mochila3;
	int cantTesorosMochila1 = 0;
	int cantTesorosMochila2 = 0;
	int cantTesorosMochila3 = 0;
	salida salida1;
	
	vector< vector<int> > mochilas;


	//Dimensiono el cubo e inicializo cada valor en 0

	// Arreglo de 4 dimensiones
	// primer vector (dimension 1) = cantidad de tesoros
	// segundo vector (dimesion 2) = mochila 1
	// tercer vector (dimesion 3) = mochila 2
	// cuarto vector (dimesion 4) = mochila 3
	vector< vector< vector< vector<int> > > > cuboMagico;

	//Dimensiono el cubo e inicializo cada valor en 0
	// Primero se establece el tamano del primer vector en cant de tesoros mas uno
	// Despues se establece el tamano de los vectores de dimension 2 en las capacidades de la mochila 1
	// Despues se establece el tamano de los vectores de dimension 3 en las capacidades de la mochila 2
	// Despues se establece el tamano de los vectores de dimension 4 en las capacidades de la mochila 3 
	cuboMagico.resize(cantTesoros + 1);
	for (int i = 0; i <= cantTesoros; ++i) {
		cuboMagico[i].resize(capacidades[0] + 1);
		for (int j = 0; j <= capacidades[0]; ++j) {
			cuboMagico[i][j].resize(capacidades[1] + 1);
			for (int k = 0; k <= capacidades[1]; ++k) {
				cuboMagico[i][j][k].resize(capacidades[2] + 1, 0);
			}
		}
	}

    // indice de la posicion en el vector de primera dimension (para recorrer todos los tesoros)
	int iTesoro = 0;

	// iteracion por todos los tesoros de distinto tipo
	for (unsigned int iTesoroPorTipo = 0; iTesoroPorTipo < tesoroValor.size(); ++iTesoroPorTipo) {
		valorTesoro = tesoroValor[iTesoroPorTipo];
		pesoTesoro = tesoroPeso[iTesoroPorTipo];
		cantidadPorTipoTesoro = tesoroCant[iTesoroPorTipo];


		// iteracion por la cantidad de tesoros de este tipo 
		for (int iTipoTesoro = 0; iTipoTesoro < cantidadPorTipoTesoro; ++iTipoTesoro) {

			for (iMochila1 = 0; iMochila1 <= capacidades[0]; ++iMochila1) {

				for (iMochila2 = 0; iMochila2 <= capacidades[1]; ++iMochila2) {

					for (iMochila3 = 0; iMochila3 <= capacidades[2]; ++iMochila3) {

						valorMochila1 = 0;
						valorMochila2 = 0;
						valorMochila3 = 0;
						valorNingunaMochila = 0;

						if (pesoTesoro <= iMochila1 || pesoTesoro <= iMochila2 || pesoTesoro <= iMochila3) {

							// Se interpreta como que no se puede poner tesoro
							valorNingunaMochila = cuboMagico[iTesoro][iMochila1][iMochila2][iMochila3];
							if (pesoTesoro <= iMochila1) {
								valorMochila1 = valorTesoro + cuboMagico[iTesoro][iMochila1 - pesoTesoro][iMochila2][iMochila3];
								////cout << "[" << iMochila1 << "][" << iMochila2 << "][" << iMochila3 << "] Entra en la mochila 1 el objeto con peso " << pesoTesoro << endl;
							}

							if (pesoTesoro <= iMochila2) {
								valorMochila2 = valorTesoro + cuboMagico[iTesoro][iMochila1][iMochila2 - pesoTesoro][iMochila3];
								////cout << "[" << iMochila1 << "][" << iMochila2 << "][" << iMochila3 << "] Entra en la mochila 2 el objeto con peso " << pesoTesoro << endl;
							}

							if (pesoTesoro <= iMochila3) {
								valorMochila3 = valorTesoro + cuboMagico[iTesoro][iMochila1][iMochila2][iMochila3 - pesoTesoro];
								////cout << "[" << iMochila1 << "][" << iMochila2 << "][" << iMochila3 << "] Entra en la mochila 3 el objeto con peso " << pesoTesoro << endl;
							}

							cuboMagico[iTesoro + 1][iMochila1][iMochila2][iMochila3] = max(max(max(valorNingunaMochila, valorMochila1), valorMochila2), valorMochila3);
						}
						else
						{
							cuboMagico[iTesoro + 1][iMochila1][iMochila2][iMochila3] = cuboMagico[iTesoro][iMochila1][iMochila2][iMochila3];
						}
						
						//cout << "[" << iMochila1 << "][" << iMochila2 << "][" << iMochila3 << "] = " << cuboMagico[iTesoro + 1][iMochila1][iMochila2][iMochila3] << ". Valor " << valorTesoro << endl;
					}
				}
			}
			iTesoro++;
		}
	}

	valorTotal = cuboMagico[cantTesoros][capacidades[0]][capacidades[1]][capacidades[2]];

	iMochila1 = capacidades[0];
	iMochila2 = capacidades[1];
	iMochila3 = capacidades[2];

	iTesoro = cantTesoros - 1;
	for (unsigned int iTesoroPorTipo = tesoroValor.size(); iTesoroPorTipo > 0; --iTesoroPorTipo) {
		valorTesoro = tesoroValor[iTesoroPorTipo - 1];
		pesoTesoro = tesoroPeso[iTesoroPorTipo - 1];
		cantidadPorTipoTesoro = tesoroCant[iTesoroPorTipo - 1];

		for (int iTipoTesoro = 0; iTipoTesoro < cantidadPorTipoTesoro; ++iTipoTesoro) {
			
			metoEnMochila1 = false;
			metoEnMochila2 = false;
			metoEnMochila3 = false;

			if (cuboMagico[iTesoro + 1][iMochila1][iMochila2][iMochila3] != cuboMagico[iTesoro][iMochila1][iMochila2][iMochila3]) {
				entraEnMochila1 = (pesoTesoro <= iMochila1);
				entraEnMochila2 = (pesoTesoro <= iMochila2);
				entraEnMochila3 = (pesoTesoro <= iMochila3);

				valorAnterior1 = 0;
				valorAnterior2 = 0;
				valorAnterior3 = 0;

				if (entraEnMochila1) {
					valorAnterior1 = cuboMagico[iTesoro][iMochila1 - pesoTesoro][iMochila2][iMochila3];
				}
				if (entraEnMochila2) {
					valorAnterior2 = cuboMagico[iTesoro][iMochila1][iMochila2 - pesoTesoro][iMochila3];
				}
				if (entraEnMochila3) {
					valorAnterior3 = cuboMagico[iTesoro][iMochila1][iMochila2][iMochila3 - pesoTesoro];
				}
				
				if (entraEnMochila1 && valorAnterior1 >= valorAnterior2 && valorAnterior1 >= valorAnterior3) {
					metoEnMochila1 = true;
				}
				else if (entraEnMochila2 && valorAnterior2 >= valorAnterior3) {
					metoEnMochila2 = true;	
				}
				else {
					metoEnMochila3 = true;	
				}

				if (metoEnMochila1) {
					//Meto el objeto (pesoTesoro, valor) en la mochila 1
					mochila1.push_back(iTesoroPorTipo);

					cantTesorosMochila1++;
					
					iMochila1 -= pesoTesoro;
					//cout << "iMochila1 = " << iMochila1 << endl;
				}
				else if (metoEnMochila2) {
					//Meto el objeto (pesoTesoro, valor) en la mochila 2
					mochila2.push_back(iTesoroPorTipo);

					cantTesorosMochila2++;
					
					iMochila2 -= pesoTesoro;
				}
				else if (metoEnMochila3) {
					//Meto el objeto (pesoTesoro, valor) en la mochila 3
					mochila3.push_back(iTesoroPorTipo);

					cantTesorosMochila3++;
					
					iMochila3 -= pesoTesoro;
				}
			}

			iTesoro--;
		}
	}

	mochila1.insert(mochila1.begin(), cantTesorosMochila1);
	mochila2.insert(mochila2.begin(), cantTesorosMochila2);
	mochila3.insert(mochila3.begin(), cantTesorosMochila3);

	mochilas.push_back(mochila1);
	mochilas.push_back(mochila2);
	mochilas.push_back(mochila3);

	salida1.first = valorTotal;
	salida1.second = mochilas;

	return salida1;
}