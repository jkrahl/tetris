#pragma once
#include <string>
using namespace std;

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

typedef enum { GIR_HORARI = 0, GIR_ANTI_HORARI } DireccioGir;
// Ha de servir per poder gestionar figures que van caient.
// Ha de poder guardar tota la informació necessària per gestionar la caiguda de la figura: tipus i color de la figura, posició actual, forma actual de la figura.
class Figura
{
public:
	Figura() : m_tipus(NO_FIGURA), m_color(NO_COLOR), m_nCostats(0) {}
	Figura(TipusFigura tipus, ColorFigura color);

	TipusFigura getTipus() const { return m_tipus; }
	ColorFigura getColor() const { return m_color; }
	int getNCostats() const { return m_nCostats; }

	bool transposarMatriuFigura();
	bool invertir(const bool &columnes, const bool &files);
private:
	void inicialitzarMatriu();
	TipusFigura m_tipus;
	ColorFigura m_color;
	// nCostats canvia segons tipus de figura
	int m_nCostats;
	// matriuFigura es un punter a una matriu de booleans que representa la figura.
	// La dimensió de la matriu depen del tipus de figura.
	bool m_matriu[4][4];
};

