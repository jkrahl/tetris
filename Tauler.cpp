#include "Tauler.h"

// True si la figura colisiona. False si no colisiona.
bool Tauler::HiHaColisions(const Figura& figura)
{
	if (figura.getMatriu() == nullptr)
		return false;
	
	int x = figura.getPosicioUpperLeft().x;
	int y = figura.getPosicioUpperLeft().y;

	for (int i = 0; i < figura.getNCostats(); i++)
		for (int j = 0; j < figura.getNCostats(); j++)
			if (figura.getMatriu()[i][j] != NO_COLOR)
				if (m_tauler[y + i][x + j] != NO_COLOR)
					return true;

}
