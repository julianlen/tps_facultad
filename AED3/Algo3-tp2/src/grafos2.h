#include <iostream>
#include <algorithm>
#include <vector>
#include <stdbool.h>
#include <ctype.h>

using namespace std;



bool esNumero(char chr);
void init(int n);
int find(int x);
void uni(int x, int y);

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