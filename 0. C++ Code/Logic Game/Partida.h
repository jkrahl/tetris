#ifndef PARTIDA_H
#define PARTIDA_H
#include "ColaFigura.h"
#include "ColaMoviments.h"
#include "GraphicManager.h"
#include <stdio.h>
#include <string>
#include "InfoJoc.h"
#include "Joc.h"

using namespace std;

class Partida 
{
public:
    Partida();
    void inicialitza(int mode, const string& fitxerInicial, const string& fitxerFigures,
        const string& fitxerMoviments);
    void actualitzaModoTest(double deltaTime);
    void actualitzaModoNormal(double deltaTime);
    void actualitza(double deltaTime);
    int partidaBucle(Screen& pantalla);
    bool getIsGameOver()const { return m_gameOver; }
private:
    double m_temps;
    Joc m_joc;
    bool m_gameOver;
    ColaFigura m_colaFigura;
    ColaMoviments m_colaMoviment;
    int m_puntuacio;
    int m_nivell;
    float m_velocitat;
    bool m_modoTest;
    //no te deja ir a figura
};

#endif 
