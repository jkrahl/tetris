#pragma once
#include <string>
#include <iostream>
#include <fstream>
using namespace std;

const int N_FILES_MAX = 4;
const int N_COLUMNES_MAX = 4;

typedef enum {
	COLOR_NEGRE = 0,
	COLOR_GROC,
	COLOR_BLAUCEL,
	COLOR_MAGENTA,
	COLOR_TARONJA,
	COLOR_BLAUFOSC,
	COLOR_VERMELL,
	COLOR_VERD,
	NO_COLOR
} ColorFigura;

typedef enum {
	NO_FIGURA = 0,
	FIGURA_O,
	FIGURA_I,
	FIGURA_T,
	FIGURA_L,
	FIGURA_J,
	FIGURA_Z,
	FIGURA_S
} TipusFigura;

typedef struct
{
	int x;
	int y;
} Posicio;

int nCostatsSegonsTipus(const TipusFigura& tipus);

typedef enum { GIR_HORARI = 0, GIR_ANTI_HORARI } DireccioGir;

class Figura
{
public:
	Figura() : m_tipus(NO_FIGURA), m_nCostats(0), m_posicio({ 0,0 }), m_matriu(nullptr) {  }
	Figura(TipusFigura tipus, const Posicio& posicio)
		: m_tipus(tipus),
		m_nCostats(nCostatsSegonsTipus(tipus)),
		m_posicio(posicio),
		m_matriu(nullptr)
	{
		inicialitzarMatriu();
	}
	Figura(const Figura& other);
	~Figura();
	void allibera();

	ColorFigura** getMatriu() const { return m_matriu; }
	Posicio getPosicioUpperLeft() const { return m_posicio; }
	int getNCostats() const { return m_nCostats; }

	void setPosicio(const Posicio& posicio) { m_posicio = posicio; }
	void girar(const DireccioGir& direccio);

	Figura operator=(const Figura& other);

private:
	void transposarMatriuFigura();
	void invertir(const bool& columnes, const bool& files);
	void inicialitzarMatriu();
	ColorFigura** creaMatriu(int nFiles, int nColumnes);

	TipusFigura m_tipus;
	int m_nCostats;
	ColorFigura** m_matriu;
	// Coordenadas de la esquina superior izquierda de la figura
	Posicio m_posicio;
};



ostream& operator<<(ostream& os, const Figura& f);
