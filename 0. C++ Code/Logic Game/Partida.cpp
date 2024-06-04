#include "Partida.h"
#include "InfoJoc.h"
#include "GraphicManager.h"

int Partida::partidaBucle(Screen& pantalla)
{
    Uint64 NOW = SDL_GetPerformanceCounter();
    Uint64 LAST = 0;
    double deltaTime = 0;
    do
    {
        LAST = NOW;
        NOW = SDL_GetPerformanceCounter();
        deltaTime = (double)((NOW - LAST) / (double)SDL_GetPerformanceFrequency());


        // Captura tots els events de ratolí i teclat de l'ultim cicle
        pantalla.processEvents();

       actualitza(deltaTime);
        // Actualitza la pantalla
        pantalla.update();
    } while (!Keyboard_GetKeyTrg(KEYBOARD_ESCAPE) && !getIsGameOver());

    return m_puntuacio;

}
void Partida::inicialitza(int mode, const string& fitxerInicial, const string& fitxerFigures,
    const string& fitxerMoviments)
{
    m_gameOver = false;
    m_velocitat = VELOCITAT;
    m_puntuacio = 0;
    m_nivell = 1;
    m_modoTest = mode;
    m_joc.inicialitza(fitxerInicial);
    //vamos a dejarlo así;
    if (mode == true)
    {
        ifstream input; 
        input.open(fitxerFigures);
        if (input.is_open())
        {
            Figura figura;
            while (input >> figura)
            {
                m_colaFigura.afegeix(figura); 
            }
            input.close();
        }

        input.open(fitxerMoviments);
        if (input.is_open())
        {
            int moviment;
            input >> moviment;
            m_colaMoviment.afegeix((TipusMoviment)moviment);
            while (!input.eof())
            {
                input >> moviment;
                m_colaMoviment.afegeix((TipusMoviment)moviment);
            }
            input.close();
        }
    }
    
}
   

Partida::Partida()
{
    m_gameOver = false;
    m_temps = 0;
}

void Partida::actualitzaModoTest(double deltaTime)
{
    m_temps += deltaTime;
    if (m_temps > m_velocitat)
    {
        if (m_colaMoviment.esBuida())
        {
            m_gameOver = true;
        }
        else
        {
            TipusMoviment mov = m_colaMoviment.getPrimer();
            m_colaMoviment.treu();

            switch(mov)
            {
            case MOVIMENT_ESQUERRA:
                m_joc.mouFigura(-1);
                break;
            case MOVIMENT_DRETA:
                m_joc.mouFigura(1);
                break;
            case MOVIMENT_GIR_HORARI:
                m_joc.giraFigura(GIR_HORARI);
                break;
            case MOVIMENT_GIR_ANTI_HORARI:
                m_joc.giraFigura(GIR_ANTI_HORARI);
                break;
            case MOVIMENT_BAIXA:
            {
                int nFilesCompletes = m_joc.baixaFigura();
                if (nFilesCompletes != -1)
                {
                    if (!m_joc.creaNovaFigura())
                    {
                        m_gameOver = true;
                    }
                    m_puntuacio += (nFilesCompletes * PUNTUACIO_PER_FILA);
                    if (nFilesCompletes > 1)
                    {
                        m_puntuacio += (nFilesCompletes * PUNTS_EXTRA);
                    }
                    m_puntuacio += PUNTUACIO_PER_CAIGUDA;
                }
                break;
            }
            case MOVIMENT_BAIXA_FINAL:
            {
                int nFilesCompletes = m_joc.baixaTotalmentFigura();

                m_puntuacio += (nFilesCompletes * PUNTUACIO_PER_FILA);
                if (nFilesCompletes > 1)
                {
                    m_puntuacio += (nFilesCompletes * PUNTS_EXTRA);
                }
                m_puntuacio += PUNTUACIO_PER_CAIGUDA;

                if (m_colaFigura.esBuida())
                {
                    m_gameOver = true;

                }
                else
                { 
                    Figura figura = m_colaFigura.getPrimer();
                    m_colaFigura.treu();
                    if(!m_joc.setNovaFigura(figura))
                    {
                        m_gameOver = true;
                    }
                }
                break;
            }
            }
            m_temps = 0.0;
        }
    }
}

void Partida::actualitzaModoNormal(double deltaTime)
{
    if (Keyboard_GetKeyTrg(KEYBOARD_RIGHT))
        m_joc.mouFigura(1);

    if (Keyboard_GetKeyTrg(KEYBOARD_LEFT))
        m_joc.mouFigura(-1);

    if (Keyboard_GetKeyTrg(KEYBOARD_UP))
        m_joc.giraFigura(GIR_ANTI_HORARI);

    if (Keyboard_GetKeyTrg(KEYBOARD_DOWN))
        m_joc.giraFigura(GIR_HORARI);

    if (Keyboard_GetKeyTrg(KEYBOARD_SPACE))
    {
        int nFilesCompletes = m_joc.baixaTotalmentFigura();

        m_puntuacio += (nFilesCompletes * PUNTUACIO_PER_FILA);
        if (nFilesCompletes > 1)
        {
            m_puntuacio += (nFilesCompletes * PUNTS_EXTRA);
        }
        m_puntuacio += PUNTUACIO_PER_CAIGUDA;
        if (!m_joc.creaNovaFigura())
        {
            m_gameOver = true;
        }
    }

    m_temps += deltaTime;
    if (m_temps > m_velocitat)
    {
        int nFilesCompletes = m_joc.baixaFigura();
        if (nFilesCompletes != -1)
        {
            if (!m_joc.creaNovaFigura())
            {
                m_gameOver = true;
            }
            m_puntuacio += (nFilesCompletes * PUNTUACIO_PER_FILA);
            if (nFilesCompletes > 1)
            {
                m_puntuacio += (nFilesCompletes * PUNTS_EXTRA);
            }
            m_puntuacio += PUNTUACIO_PER_CAIGUDA;
        }
        m_temps = 0.0;

    }

}
void Partida::actualitza(double deltaTime)
{
    GraphicManager::getInstance()->drawSprite(GRAFIC_FONS, 0, 0, false);
    GraphicManager::getInstance()->drawSprite(GRAFIC_TAULER, POS_X_TAULER, POS_Y_TAULER, false);

    if (m_modoTest)
    {
        actualitzaModoTest(deltaTime);
    }
    else
    {
        actualitzaModoNormal(deltaTime);
    }
    
    if (m_puntuacio/(m_nivell*PUNTUACIO_PER_NIVELL) == 1)
    {
        m_nivell += 1;
        m_velocitat -= 0.1;
    }
    m_joc.draw();
   
    string msg = "Puntos: " + to_string(m_puntuacio) + "          Nivel: " + to_string(m_nivell);
    GraphicManager::getInstance()->drawFont(FONT_RED_30, POS_X_TAULER, POS_Y_TAULER - 50, 1.0, msg);

    if (m_gameOver)
    {
        string msg = "GAME OVER!";
        GraphicManager::getInstance()->drawFont(FONT_RED_30, POS_X_TAULER - 10, POS_Y_TAULER + 80, 2.0, msg);
  
    }
     

}

