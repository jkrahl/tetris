#include "Tauler.h"

// True si la figura colisiona. False si no colisiona.
bool Tauler::HiHaColisions(const Figura& figura)
{
	int x = figura.getPosicioUpperLeft().x;
	int y = figura.getPosicioUpperLeft().y;

	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			if (figura.getMatriu(i, j) != 0)
				if (figura.getMatriu(i, j) 
}
