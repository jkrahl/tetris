#include <iostream>
#include <fstream>
#include "Joc.h"

const int MAX_FILES = 8;
const int MAX_COLUMNES = 8;

void Joc::inicialitza(const string& nomFitxer)
{
	ifstream input;

	input.open(nomFitxer);
	int x = 0, y = 0, 
	Tipus tipus = 0, 
	DireccioGir girar = 0;
	bool siGirar = false;
	if (input.is_open())
	{
		input >> tipus >> x >> y >> gir;
		m_figura_actual = Figura(tipus);
		Posicio	p_posicio(x, y);
		girar = gir;
		m_figura_actual.setPosicio(p_posicio);
		siGirar = m_figura_actual.girar(girar);
	}
	
	input.close();

	
}

bool Joc::giraFigura(DireccioGir direccio)
{
	Figura aux = m_figura_actual;
	aux.girar(direccio);
	if (m_tauler.HiHaColisions(aux))
		return false;

	m_figura_actual.girar(direccio);
	return true;
}

bool Joc::mouFigura(int dirX)
{
	Figura aux = m_figura_actual;
	Posicio pos = aux.getPosicioUpperLeft();
	pos.x += dirX;
	aux.setPosicio(pos);
	if (m_tauler.HiHaColisions(aux))
		return false;

	m_figura_actual.setPosicio(pos);
	return true;
}

int Joc::baixaFigura()
{
	int nFilCompl = 0;

	if (!m_tauler.HiHaColisions(m_figura_actual)) //CAso en que no hubiera colisiones
	{
		Posicio pos = m_figura_actual.getPosicioUpperLeft();
		pos.y++;
		m_figura_actual.setPosicio(pos);
	}
	else
	{
		m_tauler.FixarFigura(m_figura_actual);
		for (int i = 0; i < N_FILES; i++)
		{
			bool filCompl = true;
			for (int j = 0; j < N_COLUMNES; j++)
			{
				if (m_tauler.getCasella(j, i) == NO_COLOR) //Si detecta alguna casilla sin color es que no es completa
				{
					filCompl = false;
					filCompl = false;
				}
			}
			if (filCompl)
			{
				for (int k = i; k > 0; k--) //Eliminar la fila que esta completa
				{
					for (int j = 0; j < N_COLUMNES; j++)
					{
						m_tauler.setCasella(j, k, m_tauler.getCasella(j, k - 1));
					}
				}

				//DEspues de eliminar la fila completada hay que asignarle el color NO_COLOR
				for (int j = 0; j < N_COLUMNES; j++)
				{
					m_tauler.setCasella(j, 0, NO_COLOR);
				}
				nFilCompl++;

				m_figura_actual = Figura();
			}
		
	return nFilCompl;
}



void Joc::escriuTauler(const string& nomFitxer)
{
	ofstream fitxer;

	fitxer.open(nomFitxer);

	if (fitxer.is_open())
	{
		for (int i = 0; i < N_FILES; i++)
		{
			for (int j = 0; j < N_COLUMNES; j++)
			{
				fitxer << m_tauler.getCasella(i, j);  //Muestra la letra de cada casilla
			}

			fitxer << endl; //Para que se vea como una matriz. Cada 8 posiciones = endl
		}
	}
}
