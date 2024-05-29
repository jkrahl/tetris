#pragma once
#include "Figura.h"
#include "InfoJoc.h"

const int MAX_FILA = N_FILES_TAULER;
const int MAX_COL = N_COL_TAULER;

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

	void printTauler()
	{
		for (size_t i = 0; i < N_FILES_TAULER; i++)
		{
			for (size_t i = 0; i < N_COL_TAULER; i++)
			{
			
			}
		}
	}
	Tauler& operator=(const Tauler& tauler);
private:
	void inicialitzarMatrix();
	ColorFigura m_tauler[N_FILES_TAULER][N_COL_TAULER];
};
