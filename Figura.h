#pragma once
#include <string>
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

typedef enum { GIR_HORARI = 0, GIR_ANTI_HORARI } DireccioGir;

// Ha de servir per poder gestionar figures que van caient.
// Ha de poder guardar tota la informació necessària per gestionar la caiguda de la figura: tipus i color de la figura, posició actual, forma actual de la figura.
class Figura
{
public:
	Figura() : m_tipus(NO_FIGURA), m_color(NO_COLOR), m_posicio({ 0,0 }) { inicialitzarMatriu(); }
	Figura(TipusFigura tipus, ColorFigura color) : m_tipus(tipus), m_color(color), m_posicio({ 0,0 }) { inicialitzarMatriu(); }

	/*TipusFigura getTipus() const { return m_tipus; }
	ColorFigura getColor() const { return m_color; }
	int getNCostats() const { return m_nCostats; }*/
	ColorFigura getMatriu(const int &fila, const int &columna) const { return m_matriu[fila][columna]; }
	Posicio getPosicioUpperLeft() const { return m_posicio; }

	void setPosicio(const Posicio &posicio) { m_posicio = posicio; }
	void girar(const DireccioGir &direccio);
	Figura& operator=(const Figura &figura);

private:
	void transposarMatriuFigura();
	void invertir(const bool &columnes, const bool &files);
	void inicialitzarMatriu();
	const TipusFigura m_tipus;
	const ColorFigura m_color;
	ColorFigura m_matriu[N_FILES_MAX][N_COLUMNES_MAX];
	Posicio m_posicio;
};

