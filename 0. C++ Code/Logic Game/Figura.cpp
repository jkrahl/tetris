﻿#include "Figura.h"
#include "GraphicManager.h"

ostream& operator<<(ostream& os, const Figura& f)
{
	for (int i = 0; i < f.getNCostats(); i++)
	{
		for (int j = 0; j < f.getNCostats(); j++)
		{
			if (f.getMatriu()[i][j] == NO_COLOR)
				os << "O";
			else
				os << "X";
		}
		os << endl;
	}
	os << endl;
	return os;
}

/*
Lee la figura, el 4444 es un numero random 
para assegurar que se lee (tipus no puede ser 
4444 nunca a no ser que lea mal in >> tipus)
*/
istream& operator>>(istream& in, Figura& f) 
{
	int tipus = 4444;
	int y, x, nGirs;
	in >> tipus >> y >> x >> nGirs;
	x -= 1;
	y -= 1;
	if (tipus != 4444)
	{
		f = Figura((TipusFigura)tipus, { x, y });
		for (int i = 0; i < nGirs; i++)
			f.girar(GIR_HORARI);
	}
	return in;
}

//copia shallow copy
Figura::Figura(const Figura& other)
	:m_matriu(nullptr)
{
	m_tipus = other.m_tipus;
	m_nCostats = other.m_nCostats;
	m_posicio = other.m_posicio;
	if (other.getMatriu() != nullptr)
	{
		inicialitzarMatriu();
		for (int i = 0; i < m_nCostats; i++)
			for (int j = 0; j < m_nCostats; j++)
				m_matriu[i][j] = other.getMatriu()[i][j];
	}
	else m_matriu = nullptr;
}

Figura::~Figura()
{
	allibera();
}

//Para liberar la figura
void Figura::allibera()
{
	if (m_matriu != nullptr)
	{
		for (int i = 0; i < m_nCostats; i++)
			delete[] m_matriu[i];
		delete[] m_matriu;
	}
	m_matriu = nullptr;
}


void Figura::dibuixa() const  //muestra la figura al tablero
{
	for (size_t i = 0; i < getNCostats(); i++)
	{
		for (size_t j = 0; j < getNCostats(); j++)
		{
			ColorFigura color = getMatriu()[i][j];
			if (color != COLOR_NEGRE)
			{
				auto pos = getPosicioUpperLeft();
				GraphicManager::getInstance()->drawSprite((IMAGE_NAME)(color + 1),
					POS_X_TAULER + ((j + pos.x + 1) * MIDA_QUADRAT), 
					POS_Y_TAULER + ((i + pos.y) * MIDA_QUADRAT), false);
			}
		}
	}
}

//Dibuja la sombra de la figura actual, se ha creado figura nueva (gris -> simula la sombra)
void Figura::dibuixaFantasma() const
{
	for (size_t i = 0; i < getNCostats(); i++)
	{
		for (size_t j = 0; j < getNCostats(); j++)
		{
			ColorFigura color = getMatriu()[i][j];
			if (color != COLOR_NEGRE) //Mientras que no sea negra == imprime la figura con la parte de colores
			{
				auto pos = getPosicioUpperLeft();
				GraphicManager::getInstance()->drawSprite((GRAFIC_QUADRAT_GRIS),
					POS_X_TAULER + ((j + pos.x + 1) * MIDA_QUADRAT),
					POS_Y_TAULER + ((i + pos.y) * MIDA_QUADRAT), false);
			}
		}
	}
}

/*
Dependiendo de si es horario(true) o antihorario(false)
girara de una manera u otra, en invertir ya tiene en cuenta eso
*/
void Figura::girar(const DireccioGir& direccio) 
{
	transposarMatriuFigura();
	if (direccio == GIR_HORARI)
		invertir(true, false);
	else
		invertir(false, true);
}

//Deep copy de la figura
Figura Figura::operator=(const Figura& other)
{
	if (this != &other)
	{
		allibera();
		m_tipus = other.m_tipus;
		m_nCostats = other.m_nCostats;
		m_posicio = other.m_posicio;
		if (other.getMatriu() != nullptr)
		{
			inicialitzarMatriu();
			for (int i = 0; i < m_nCostats; i++)
				for (int j = 0; j < m_nCostats; j++)
					m_matriu[i][j] = other.getMatriu()[i][j];
		}
		else m_matriu = nullptr;
	}
	return *this;
}


//(1)(2), esos dos metodos juntos hacen el trabajo de girar la figura de modo horario/antihorario

// (1)
void Figura::transposarMatriuFigura()
{
	ColorFigura matriuAux[N_FILES_MAX][N_COLUMNES_MAX];
	for (int i = 0; i < m_nCostats; i++)
		for (int j = 0; j < m_nCostats; j++)
			matriuAux[i][j] = m_matriu[j][i];

	for (int i = 0; i < m_nCostats; i++)
		for (int j = 0; j < m_nCostats; j++)
			m_matriu[i][j] = matriuAux[i][j];
}
//(2)
void Figura::invertir(const bool& columnes, const bool& files)
{
	ColorFigura matriuAux[N_FILES_MAX][N_COLUMNES_MAX];
	if (columnes)	
		for (int i = 0; i < m_nCostats; i++)
			for (int j = 0; j < m_nCostats; j++)
				matriuAux[i][j] = m_matriu[i][m_nCostats - 1 - j];

	else if (files)
		for (int i = 0; i < m_nCostats; i++)
			for (int j = 0; j < m_nCostats; j++)
				matriuAux[i][j] = m_matriu[m_nCostats - 1 - i][j];

	for (int i = 0; i < m_nCostats; i++)
		for (int j = 0; j < m_nCostats; j++)
			m_matriu[i][j] = matriuAux[i][j];
}

void Figura::inicialitzarMatriu()
{
	if (m_matriu != nullptr)
		return;

	if (m_tipus == NO_FIGURA)
		return;

	m_matriu = creaMatriu(m_nCostats, m_nCostats);

	switch (m_tipus)
	{
	case FIGURA_I:
		m_matriu[1][0] = COLOR_BLAUCEL;
		m_matriu[1][1] = COLOR_BLAUCEL;
		m_matriu[1][2] = COLOR_BLAUCEL;
		m_matriu[1][3] = COLOR_BLAUCEL;
		break;
	case FIGURA_J:
		m_matriu[0][0] = COLOR_BLAUFOSC;
		m_matriu[1][0] = COLOR_BLAUFOSC;
		m_matriu[1][1] = COLOR_BLAUFOSC;
		m_matriu[1][2] = COLOR_BLAUFOSC;
		break;
	case FIGURA_L:
		m_matriu[0][2] = COLOR_TARONJA;
		m_matriu[1][0] = COLOR_TARONJA;
		m_matriu[1][1] = COLOR_TARONJA;
		m_matriu[1][2] = COLOR_TARONJA;
		break;
	case FIGURA_O:
		m_matriu[0][0] = COLOR_GROC;
		m_matriu[0][1] = COLOR_GROC;
		m_matriu[1][0] = COLOR_GROC;
		m_matriu[1][1] = COLOR_GROC;
		break;
	case FIGURA_S:
		m_matriu[0][1] = COLOR_VERD;
		m_matriu[0][2] = COLOR_VERD;
		m_matriu[1][0] = COLOR_VERD;
		m_matriu[1][1] = COLOR_VERD;
		break;
	case FIGURA_T:
		m_matriu[0][1] = COLOR_MAGENTA;
		m_matriu[1][0] = COLOR_MAGENTA;
		m_matriu[1][1] = COLOR_MAGENTA;
		m_matriu[1][2] = COLOR_MAGENTA;
		break;
	case FIGURA_Z:
		m_matriu[0][0] = COLOR_VERMELL;
		m_matriu[0][1] = COLOR_VERMELL;
		m_matriu[1][1] = COLOR_VERMELL;
		m_matriu[1][2] = COLOR_VERMELL;
		break;
	default:
		break;
	}
}

ColorFigura** Figura::creaMatriu(int nFiles, int nColumnes)
{
	ColorFigura** matriu = new ColorFigura * [nFiles];
	for (int i = 0; i < nFiles; i++)
		matriu[i] = new ColorFigura[nColumnes];

	for (int i = 0; i < nFiles; i++)
		for (int j = 0; j < nColumnes; j++)
		    matriu[i][j] = COLOR_NEGRE; // REVIEW: Usa color negro en vez de no color.

	return matriu;
}

int nCostatsSegonsTipus(const TipusFigura& tipus) //Devuelve los nLados de la figrua
{
	int nCostats = -1;
	switch (tipus)
	{
	case FIGURA_J:
	case FIGURA_L:
	case FIGURA_T:
	case FIGURA_S:
	case FIGURA_Z:
		nCostats = 3;
		break;
	case FIGURA_I:
		nCostats = 4;
		break;
	case FIGURA_O:
		nCostats = 2;
		break;
	default:
		break;
	}

	return nCostats;
}