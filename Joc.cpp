#include <iostream>
#include <fstream>
#include "Joc.h"

const int MAX_FILES = 8;
const int MAX_COLUMNES = 8;

void Joc::inicialitza(const string& nomFitxer)
{
	// Falta implementar
	return;
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
	// Falta implementar
	return 0;
}

void Joc::escriuTauler(const string& nomFitxer)
{
	// Falta implementar
	return;
}
