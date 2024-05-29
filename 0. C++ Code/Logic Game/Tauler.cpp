#include "Tauler.h"

// True si la figura colisiona. False si no colisiona.
bool Tauler::HiHaColisions(const Figura& figura)
{
	if (figura.getMatriu() == nullptr)
		return false;

	int x = figura.getPosicioUpperLeft().x;
	int y = figura.getPosicioUpperLeft().y;

	for (int i = 0; i < figura.getNCostats(); i++)
	{
	   
		for (int j = 0; j < figura.getNCostats(); j++)
		{
		   
		    if (figura.getMatriu()[i][j] != COLOR_NEGRE)
		    {
			if (x + j >= MAX_COL || y + i >= MAX_FILA || y + i < 0 || x + j < 0)
			{
			    return true;
			}
			if (figura.getMatriu()[i][j] != COLOR_NEGRE
			    && m_tauler[y + i][x + j] != COLOR_NEGRE)
			{
			    return true;
			}
		    }
		}
	}
	return false;
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
			if (figura.getMatriu()[i][j] != COLOR_NEGRE) // REVIEW: No usar NO_COLOR
			{
				if (x + j < MAX_COL && i + y < MAX_FILA &&
					x + j >= 0 && i + y >= 0)
				{
					m_tauler[y + i][x + j] = figura.getMatriu()[i][j];
				}
			}
		}
}

int Tauler::eliminaFilesCompl()
{
	int nFilCompl = -1;

	for (int i = 0; i < N_FILES_TAULER; i++)
	{
		bool filCompl = true;
		for (int j = 0; j < N_COL_TAULER; j++)
		{
		   // REVIEW: es i,j, no j,i
			if (m_tauler[i][j] == COLOR_NEGRE) //Si detecta alguna casilla sin color es que no es completa
			{
				filCompl = false;
				break;
			}
		}
		if (filCompl)
		{
			for (int k = i; k > 0; k--) //Eliminar la fila que esta completa
			{
				for (int j = 0; j < N_COL_TAULER; j++)
				{
				   // REVIEW: es k,j no j,k
					m_tauler[k][j] = m_tauler[k-1][j];
				   
				}
			}
			// REVIEW: Siempre eliminar la fila de arriba del todo
			for (int j = 0; j < N_COL_TAULER; j++)
			{
			    m_tauler[0][j] = COLOR_NEGRE;
				   
			}
			// REVIEW: Volver una fila para atrás
			i--;
			nFilCompl++;
		}
	}

	return nFilCompl;
}

Tauler& Tauler::operator=(const Tauler& tauler)
{
	if (this != &tauler)
	{
		for (int i = 0; i < N_FILES_TAULER; i++)
			for (int j = 0; j < N_COL_TAULER; j++)
				m_tauler[i][j] = tauler.m_tauler[i][j];
	}
	return *this;
}

void Tauler::inicialitzarMatrix()
{
	for (int i = 0; i < N_FILES_TAULER; i++)
		for (int j = 0; j < N_COL_TAULER; j++)
			m_tauler[i][j] = NO_COLOR;
}
