#include <iostream>
#include <fstream>
#include "Joc.h"

const int MAX_FILES = 8;
const int MAX_COLUMNES = 8;

void Joc::inicialitza(const string& nomFitxer)
{
    ifstream fitxer;
    fitxer.open(nomFitxer);

    int tipus = 0, x = 0, y = 0, gir = 0;

    if (fitxer.is_open())
    {
        fitxer >> tipus >> x >> y >> gir;
        m_figura_actual.setTipus(static_cast<TipusFigura>(tipus));
        m_figura_actual.setPosicio(x, y);
        m_figura_actual.setGir(static_cast<DireccioGir>(gir));

        for (int i = 0; i < MAX_FILES; i++)
        {
            for (int j = 0; j < MAX_COLUMNES; j++)
            {
                int pixel;
                fitxer >> pixel;
                m_tauler.setPixel(i, j, pixel);
            }
        }
    }

    fitxer.close();
}


bool Joc::giraFigura(DireccioGir direccio)
{
    bool si_girar = true;

    if (m_figura_actual.getTipus() != FIGURA_O)
    {
        if (direccio == GIR_HORARI) //
        {
            m_figura_actual.transposarMatriuFigura();
            m_figura_actual.invertir(true, false);
        }
        else
        {
            m_figura_actual.transposarMatriuFigura();
            m_figura_actual.invertir(false, true);
        }

        for (int i = 0; i < m_figura_actual.getNCostats(); i++)
        {
            for (int j = 0; j < m_figura_actual.getNCostats(); j++)
            {
                if (m_figura_actual.getPixel(i, j) != COLOR_NEGRE &&
                    m_tauler.getPixel(i + m_figura.getX(), j + m_figura.getY()))
                {
                    if (direccio == GIR_HORARI)
                    {
                        m_figura_actual.transposarMatriuFigura();
                        m_figura_actual.invertir(false, true);
                    }
                    else
                    {
                        m_figura_actual.transposarMatriuFigura();
                        m_figura_actual.invertir(true, false);
                    }
                    return false;
                }
            }
        }
    }
    return si_girar;
}



bool Joc::mouFigura(int dirX)
{
    bool si_mou = true;

    m_figura_actual.setX(m_figura_actual.getX() + dirX);   
    
    for (int i = 0; i < m_figura_actual.getNCostats(); i++)
    {
        for (int j = 0; j < m_figura_actual.getNCostats(); j++)
        {
            if ((m_figura_actual.getPixel(i, j) != COLOR_NEGRE &&
                m_tauler.getPixel(i + m_figura.getX(), j + m_figura.getY())) || m_figura_actual.getX() + j < 0 ||
                m_figura_actual.getX() +j > MAX_FILES)
            {
                m_figura_actual.setX(m_figura_actual.getX() - dirX);
                return false;
            }
        }
    }

    return si_mou;
}

int Joc::baixaFigura()
{
    m_figura_actual.setY(m_figura_actual.getY()+1);



    return 0;
}

void Joc::escriuTauler(const string& nomFitxer)
{
    ofstream fitxer;
    fitxer.open(nomFitxer);

    for (int i = 0; i < MAX_FILES; i++)
    {
        for (int j = 0; j < MAX_COLUMNES; j++)
        {
            fitxer << m_tauler.getPixel(i, j);
        }
    }

    fitxer.close();
}
