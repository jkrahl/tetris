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
			if (figura.getMatriu()[i][j] != COLOR_NEGRE
				&& m_tauler[y + i][x + j] != COLOR_NEGRE)
				return true;

}

void Tauler::FixarFigura(const Figura& figura)
{
	if (figura.getMatriu() == nullptr)
		return;

	int x = 0, y = 0;
	x = figura.getPosicioUpperLeft().x;
	y = figura.getPosicioUpperLeft().y;

	for (int i = 0; i < figura.getNCostats(); i++)
		for (int j = 0; j < figura.getNCostats(); j++)
		{
			if (figura.getMatriu()[i][j] != NO_COLOR)
			{
				if (x + i < MAX_COL && j + y < MAX_FILA &&
					x + i >= 0 && j + y >= 0)
				{
					m_tauler[i + x][j + y] = figura.getMatriu()[i][j];
				}
			}
		}
}

int Tauler::eliminaFilesCompl()
{
	int nFilCompl = 0;

	for (int i = 0; i < N_FILES; i++)
	{
		bool filCompl = true;
		for (int j = 0; j < N_COLUMNES; j++)
		{
			if (m_tauler[j][i] == COLOR_NEGRE) //Si detecta alguna casilla sin color es que no es completa
			{
				filCompl = false;
				break;
			}
		}
		if (filCompl)
		{
			for (int k = i; k > 0; k--) //Eliminar la fila que esta completa
			{
				for (int j = 0; j < N_COLUMNES; j++)
					m_tauler[j][k] = m_tauler[j][k - 1];
			}
			nFilCompl++;
		}
	}

	return nFilCompl;
}

Tauler& Tauler::operator=(const Tauler& tauler)
{
	if (this != &tauler)
	{
		for (int i = 0; i < N_FILES; i++)
			for (int j = 0; j < N_COLUMNES; j++)
				m_tauler[i][j] = tauler.m_tauler[i][j];
	}
	return *this;
}

void Tauler::inicialitzarMatrix()
{
	for (int i = 0; i < N_FILES; i++)
		for (int j = 0; j < N_COLUMNES; j++)
			m_tauler[i][j] = NO_COLOR;
}
