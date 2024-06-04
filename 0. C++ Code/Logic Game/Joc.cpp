#include <iostream>
#include <fstream>
#include "Joc.h"
#include "InfoJoc.h"

const int MAX_FILES = N_FILES_TAULER;
const int MAX_COLUMNES = N_COL_TAULER;

void Joc::inicialitza(const string& nomFitxer)
{
	*this = Joc();
	ifstream f;
	f.open(nomFitxer);

	if (f.is_open())
	{
		// Leer figura actual
		int tipus, y, x, nGirs;
		// REVIEW: Se lee fila,columna no x,y
		f >> m_figura_actual;
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

	int nFilesCompl;
	if (!m_tauler.HiHaColisions(aux))
	{
		m_figura_actual.setPosicio(pos);
		nFilesCompl = -1;
	}
	else
	{
		m_tauler.FixarFigura(m_figura_actual);
		nFilesCompl = m_tauler.eliminaFilesCompl();
		m_figura_actual = Figura();

	}
	return nFilesCompl;
}

int Joc::baixaTotalmentFigura()
{
	int res;
	do 
	{
		res = baixaFigura();
	} while (res == -1);
	return res; //DEvuelve la cantidad de filas completas
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

	m_tauler.dibuixa();

	Figura ombra = m_figura_actual;
	
	if (!ombra.esBuida())
	{
		while (!m_tauler.HiHaColisions(ombra))
		{
			Posicio pos = ombra.getPosicioUpperLeft();
			pos.y++;
			ombra.setPosicio(pos);
		}
		Posicio pos = ombra.getPosicioUpperLeft();
		pos.y--;
		ombra.setPosicio(pos);
		ombra.dibuixaBordes();
	}

	m_figura_actual.dibuixa();


}
/*
Devuelve un bool indicando si se ha podido colocar o no la figura.
*/
bool Joc::creaNovaFigura()
{
	Posicio pos;
	pos.x = 5;
	pos.y = 0;
	TipusFigura tipus = (TipusFigura)(std::rand() % (N_TIPUS_FIGURES - 1) + 1);
	Figura novaFigura(tipus, pos);
	
	if (m_tauler.HiHaColisions(novaFigura))
	{
		return false;
	}
	else
	{
		m_figura_actual = novaFigura;
		return true;
	}
}


bool Joc::setNovaFigura(Figura& fig)
{
	Posicio pos;
	pos.x = 5;
	pos.y = 0;
	fig.setPosicio(pos);
	if (m_tauler.HiHaColisions(fig))
	{
		return false;
	}
	else
	{
		m_figura_actual = fig;
		return true;
	}

}
