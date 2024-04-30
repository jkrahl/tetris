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
			if (figura.getMatriu()[i][j] != NO_COLOR
				&& m_tauler[y + i][x + j] != NO_COLOR)
				return true;

}

void Tauler::FixarFigura(const Figura& figura)
{
	if (figura.getMatriu() != nullptr) //En el caso que no sea nullptr
	{
		int x = 0, y = 0;
		x = figura.getPosicioUpperLeft().x;
		y = figura.getPosicioUpperLeft().y;

		for (int i = 0; i < figura.getNCostats(); i++)
		{
			for (int j = 0; j < figura.getNCostats(); j++)
			{
				if (figura.getMatriu()[i][j] != NO_COLOR) //Entra al if solo si hay un color v�lido
				{
					m_tauler[i + x][j + y] = figura.getMatriu()[i][j]; 
					// A m_tauler de debo sumar x e y. De esta manera, aseguro que en la tabla se ubique bien las piezas de la figura
				}
			}
		}
	}
}

void Tauler::inicialitzarMatrix()
{
	for (int i = 0; i < N_FILES; i++)
		for (int j = 0; j < N_COLUMNES; j++)
			m_tauler[i][j] = NO_COLOR;
}
