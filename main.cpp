#include <iostream>
#include "Figura.h"

void menu()
{
	cout << "1. Girar sentit horari" << endl;
	cout << "2. Girar sentit antihorari" << endl;
	cout << "0: Sortir" << endl;
}

int main()
{
	int a = -1;
	int tipus = -1;

	cout << "Introdueix tipus:" << endl;
	cin >> tipus;

	Figura f = Figura((TipusFigura)tipus);

	cout << f;

	do
	{
		menu();
		cin >> a;
		switch (a)
		{
		case 1:
			f.girar(GIR_HORARI);
			break;
		case 2:
			f.girar(GIR_ANTI_HORARI);
			break;
		default:
			break;
		}
	} while (a != 0);
}
