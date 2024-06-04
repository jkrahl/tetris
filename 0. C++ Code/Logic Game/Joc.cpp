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
		f >> m_figura_actual;
		// Leer tablero
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

//Se crea figura auxiliar para ver si hay colisiones,
//si no hay colisiones, gira la figura en la direccion indicada
//el metodo devuelve un bool de si se ha podido girar
bool Joc::giraFigura(DireccioGir direccio) 
{
	Figura aux(m_figura_actual);
	aux.girar(direccio);
	if (m_tauler.HiHaColisions(aux))
		return false;

	m_figura_actual.girar(direccio);
	return true;
}

//devuelve bool de si es posible moverse lateralmente
//(-1)->left          (1)-> right
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
/*
nFilesCompletes Aproposito = -1 para que el metodo baixaTotalmentFigures sepa que si no colisiona aun nFilesCompletes sera - 1
int Joc::baixaFigura()
*/
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

//Mientras que res sea -1 quiere decir que esta bajando, aun sin colisionar
//res-> cantidad de filas eliminadas
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

void Joc::draw() const //Dibuja la figura
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
		ombra.dibuixaFantasma();
	}

	m_figura_actual.dibuixa();


}

/*
Devuelve un bool indicando si se ha podido colocar o no la figura.
*/
bool Joc::creaNovaFigura() //Crea figura nueva
{
	Posicio pos;
	pos.x = 5;
	pos.y = 0;
	TipusFigura tipus = (TipusFigura)(std::rand() % (N_TIPUS_FIGURES - 1) + 1);
	Figura novaFigura(tipus, pos); //Preparo la figrua nueva
	
	if (m_tauler.HiHaColisions(novaFigura))
	{
		return false; //Si hay colison, no se crea y dedvuelve false 
	}
	else
	{
		m_figura_actual = novaFigura; //se crea nueva y asigna a la figura actual la nueva figura preparada
		return true;
	}
}


bool Joc::setNovaFigura(Figura& fig) //Compruba que en el tablero se pueda poner la figrua
{
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
