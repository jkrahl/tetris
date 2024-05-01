#include <iostream>
#include <fstream>
#include "Joc.h"

const int MAX_FILES = 8;
const int MAX_COLUMNES = 8;

void Joc::inicialitza(const string& nomFitxer)
{
	ifstream f;
	f.open(nomFitxer);

	if (f.is_open())
	{
		// Leer figura actual
		int tipus, x, y, nGirs;
		f >> tipus >> x >> y >> nGirs;
		if (tipus == FIGURA_I)
			x += 2;
		else
			x += 1;

		m_figura_actual = Figura((TipusFigura)tipus, { x + 1, y });

		for (int i = 0; i < nGirs; i++)
			m_figura_actual.girar(GIR_HORARI);

		// Leer tauler
		for (int i = 0; i < N_FILES; i++)
		{
			for (int j = 0; j < N_COLUMNES; j++)
			{
				int color;
				f >> color;
				m_tauler.setCasella(i, j, (ColorFigura)color);
			}
		}

		f.close();
	}
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

// Retorna el nombre de files completades
int Joc::baixaFigura()
{
	Figura aux = m_figura_actual;
	Posicio pos = aux.getPosicioUpperLeft();
	pos.y++;
	aux.setPosicio(pos);

	if (!m_tauler.HiHaColisions(aux))
	{
		m_figura_actual.setPosicio(pos);
		return 0;
	}

	m_tauler.FixarFigura(m_figura_actual);

	int nFilCompl = m_tauler.eliminaFilesCompl();

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
				fitxer << m_tauler.getCasella(i, j);

			fitxer << endl;
		}

		fitxer.close();
	}
}
