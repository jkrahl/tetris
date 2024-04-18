#include "Figura.h"

void Figura::inicialitzaFigura()
{
	if (m_matriuFigura != nullptr)
	{
		for (int i = 0; i < m_nCostats; i++)
		{
			for (int j = 0; j < m_nCostats; j++)
			{
				m_matriuFigura[i][j] = 0;
			}
		}
	}
}
