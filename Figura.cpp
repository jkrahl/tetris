#include "Figura.h"

Figura::Figura(TipusFigura tipus, ColorFigura color)
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

	m_nCostats = nCostats;
	m_color = color;

	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			m_matriu[i][j] = false;
		}
	}

	inicialitzarMatriu();
}

bool Figura::transposarMatriuFigura()
{
	// To do
	return true;
}

void Figura::inicialitzarMatriu()
{
	switch (m_tipus)
	{
	case FIGURA_I:
		m_matriu[1][0] = true;
		m_matriu[1][1] = true;
		m_matriu[1][2] = true;
		m_matriu[1][3] = true;
		break;
	case FIGURA_J:
		m_matriu[0][0] = true;
		m_matriu[1][0] = true;
		m_matriu[1][1] = true;
		m_matriu[1][2] = true;
		break;
	case FIGURA_L:
		m_matriu[0][2] = true;
		m_matriu[1][0] = true;
		m_matriu[1][1] = true;
		m_matriu[1][2] = true;
		break;
	case FIGURA_O:
		m_matriu[0][0] = true;
		m_matriu[0][1] = true;
		m_matriu[1][0] = true;
		m_matriu[1][1] = true;
		break;
	case FIGURA_S:
		m_matriu[0][1] = true;
		m_matriu[0][2] = true;
		m_matriu[1][0] = true;
		m_matriu[1][1] = true;
		break;
	case FIGURA_T:
		m_matriu[0][1] = true;
		m_matriu[1][0] = true;
		m_matriu[1][1] = true;
		m_matriu[1][2] = true;
	case FIGURA_Z:
		m_matriu[0][0] = true;
		m_matriu[0][1] = true;
		m_matriu[1][1] = true;
		m_matriu[1][2] = true;
	default:
		break;
	}
}
