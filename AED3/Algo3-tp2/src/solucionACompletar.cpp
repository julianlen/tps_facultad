#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

int altura[1000000];
int padre[1000000];

void init(int n) {
	for (int i = 0; i < n; ++i)
	{
		padre[i] = i;
		altura[i] = 1;
	}
}

int find(int x) {
	if (padre[x] != x) {
		padre[x] = find(padre[x]);
	}
	return x;
}

void uni(int x, int y) {
	// union es una palabra reservada en C++, por eso usamos "uni"
	if (altura[x] > altura[y]) {
		padre[y] = padre[x];
	}
	else {
		padre[x] = padre[y];
	}

	if (altura[x] == altura[y])
		altura[x]++;
}

struct arista {
	int inicio;
	int fin;
	int costo;
	
	bool operator<(const arista a) const
	{
		if (costo != a.costo)
			return costo < a.costo;
		if (inicio != a.inicio)
			return inicio < a.inicio;
		return fin < a.fin;
	}
};

int main() {
	int V, E;
	cin >> V >> E;
	init (V);
	vector<arista> aristas;
	long long costoTotal = 0;
	for (int i = 0; i < E; i++) {
		arista a;
		cin >> a.inicio >> a.fin >> a.costo;
		costoTotal += a.costo;
		aristas.push_back(a);
	}
	
	sort(aristas.begin(), aristas.end()); // ordeno las aristas por peso de menor a mayor
	for (int i = 0; i < E; i++) {
		arista a = aristas[i];
		if (find(a.inicio) != find(a.fin)) {
			costoTotal += a.costo;
			uni(a.inicio, a.fin);
		} 
	}
	
	cout << costoTotal << endl;
}
