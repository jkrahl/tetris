#pragma once
#include "Figura.h"
#define N_FILES 8
#define N_COLUMNES 8

const int MAX_FILA = 8;
const int MAX_COL = 8;

typedef enum {
	BUIDA = 0,
	OCUPADA,
	OCUPADA_PER_FIGURA,
} EstatCasilla;

class Tauler
{
public:
	Tauler() { inicialitzarMatrix(); }

	ColorFigura getCasella(int x, int y) const { return m_tauler[x][y]; }

	void setCasella(int x, int y, ColorFigura color) { m_tauler[x][y] = color; }
	bool HiHaColisions(const Figura& figura);
	void FixarFigura(const Figura& figura);
	int eliminaFilesCompl();

	Tauler& operator=(const Tauler& tauler);
private:
	void inicialitzarMatrix();
	ColorFigura m_tauler[N_FILES][N_COLUMNES];
};
