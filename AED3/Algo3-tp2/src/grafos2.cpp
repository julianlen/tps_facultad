#include "grafos2.h"

using namespace std;

int altura[1000000];
int padre[1000000];

bool esNumero(char chr) {
	return isdigit(chr) && (chr - '0') > 0 && (chr - '0') < 10;
}

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
	return padre[x];
}

void uni(int x, int y) {
	x = find(x);
	y = find(y);
	// union es una palabra reservada en C++, por eso usamos "uni"
	if (altura[x] < altura[y]) {
		padre[x] = y;
	}
	else {
		padre[y] = x;
	}

	if (altura[x] == altura[y])
		altura[x]++;
}