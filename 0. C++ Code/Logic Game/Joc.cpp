#include <iostream>
#include <fstream>
#include "Joc.h"
#include "InfoJoc.h"

const int MAX_FILES = N_FILES_TAULER;
const int MAX_COLUMNES = N_COL_TAULER;

void Joc::inicialitza(const string& nomFitxer)
{
	ifstream f;
	f.open(nomFitxer);

	if (f.is_open())
	{
		// Leer figura actual
		int tipus, y, x, nGirs;
		// REVIEW: Se lee fila,columna no x,y
		f >> tipus >> y >> x >> nGirs;
		//		if (tipus == FIGURA_I) // REVIEW: No hace falta
		//			x -= 2;
		//		else
		//			x -= 1;

		x -= 1;
		y -= 1;
		m_figura_actual = Figura((TipusFigura)tipus, { x, y });

		for (int i = 0; i < nGirs; i++)
			m_figura_actual.girar(GIR_HORARI);

		// Leer tauler
		for (int i = 0; i < N_FILES_TAULER; i++)
		{
			for (int j = 0; j < N_COL_TAULER; j++)
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
	Figura aux(m_figura_actual);
	aux.girar(direccio);
	if (m_tauler.HiHaColisions(aux))
		return false;

	m_figura_actual.girar(direccio);
	return true;
}

bool Joc::mouFigura(int dirX)
{
	Figura aux(m_figura_actual);
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
	Figura aux(m_figura_actual);
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
	m_figura_actual = Figura();

	return nFilCompl;
}

int Joc::baixaTotalmentFigura()
{
	int res = 0;
	while (res != -1)
	{
		res = baixaFigura();
	}
	return res;
}

void Joc::escriuTauler(const string& nomFitxer)
{
	ofstream fitxer;

	Tauler taulerAmbFigura = m_tauler;

	taulerAmbFigura.FixarFigura(m_figura_actual);

	fitxer.open(nomFitxer);

	if (fitxer.is_open())
	{
		for (int i = 0; i < N_FILES_TAULER; i++)
		{
			for (int j = 0; j < N_COL_TAULER; j++)
				fitxer << taulerAmbFigura.getCasella(i, j);

			fitxer << endl;
		}

		fitxer.close();
	}
}

#include "GraphicManager.h"

void Joc::draw() const
{
	for (size_t i = 0; i < N_FILES_TAULER; i++)
	{
		for (size_t j = 0; j < N_COL_TAULER; j++)
		{
			ColorFigura color = m_tauler.getCasella(i, j);
			if (color != COLOR_NEGRE && color != NO_COLOR)
			{
				GraphicManager::getInstance()->drawSprite((IMAGE_NAME)(color + 1),
					POS_X_TAULER + ((j + 1) * MIDA_QUADRAT), POS_Y_TAULER + ((i)*MIDA_QUADRAT), false);
			}
		}
	}
	
	
	for (size_t i = 0; i < m_figura_actual.getNCostats(); i++)
	{
		for (size_t j = 0; j < m_figura_actual.getNCostats(); j++)
		{
			ColorFigura color = m_figura_actual.getMatriu()[i][j];
			if (color != COLOR_NEGRE)
			{
				auto pos = m_figura_actual.getPosicioUpperLeft();
				GraphicManager::getInstance()->drawSprite((IMAGE_NAME)(color + 1),
					POS_X_TAULER + ((j + pos.x + 1) * MIDA_QUADRAT), POS_Y_TAULER + ((i + pos.y)*MIDA_QUADRAT), false);
			}
		}
	}


}

void Joc:: creaNovaFigura()
{
	m_figura_actual.allibera();
	Posicio pos;
	pos.x = std::rand() % N_COL_TAULER;
	pos.y = 0;
	TipusFigura tipus = (TipusFigura)(std::rand() % (N_TIPUS_FIGURES - 1) + 1);
	m_figura_actual = Figura(tipus, pos);
}
#include "GraphicManager.h"
void Joc::actualitza(double deltaTime)
{

}
