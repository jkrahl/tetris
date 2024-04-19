#pragma once
#include "Figura.h"
#define N_FILES 8
#define N_COLUMNES 8

typedef enum {
	BUIDA = 0,
	OCUPADA,
	OCUPADA_PER_FIGURA,
} EstatCasilla;

class Tauler
{
public:
	Tauler();
	bool HiHaColisions(const Figura& figura);
	void FixarFigura(const Figura& figura);
private:
	ColorFigura m_tauler[N_FILES][N_COLUMNES];
};
