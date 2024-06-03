#include "Tetris.h"
#include "GraphicManager.h"

void Tetris::jugaPartida(Screen& pantalla)
{
    leerPuntuacion("puntuacion.txt"); //Se pone fuera del do..while para qque solo lea una vez
    int opcio;
    do
    {
        cout << "----------- MENU PRINCIPAL -----------" << endl;
        cout << "1. Joc en mode normal" << endl;
        cout << "2. Joc en mode test" << endl;
        cout << "3. Mostrar puntuacions" << endl;
        cout << "4. Sortir" << endl;
        cout << "--------------------------------------" << endl;

        cin >> opcio;
        
        switch (opcio)
        {
        case 1:
        {
            m_partida.inicialitza(false, "data/Games/partida.txt", "", ""); //Modo normal
            int puntos = m_partida.partidaBucle(pantalla);
            string jugador;
            cout << "Escriba su nombre: ";
            cin >> jugador;
            insertaPuntuacionOrdenada(jugador, puntos);


            break;
        }
        case 2:
        {
            m_partida.inicialitza(true, "data/Games/partida.txt", "data/Games/figures.txt", "data/Games/moviments.txt"); //Modo test, le paso los ficheros
            int puntos = m_partida.partidaBucle(pantalla);
            string jugador;
            cout << "Escriba su nombre: ";

            cin >> jugador;
            insertaPuntuacionOrdenada(jugador, puntos);

            break;
        }
        case 3:
        {
            mostraPuntuacio();
            break;
        }
        case 4:
        default:
            break;
        }
    } while (opcio != 4);   

    guardaPuntuacion("puntuacion.txt"); //Al final para que se guarde una vez
}

void Tetris::mostraPuntuacio() const 
{
    list<Puntos>::const_iterator iter = m_puntuaciones.begin();
    cout << "------PUNTUACIONES------" << endl;
    while (iter != m_puntuaciones.end())
    {
        cout << "Jugador: " << iter->jugador << "     Puntuacion: " << iter->puntos << endl;
        iter++;
    }

}

void Tetris::insertaPuntuacionOrdenada(const string& jugador, int puntos)
{
    //inserta de forma ordenada en una lista , mayor a menor
    list<Puntos>::iterator iter = m_puntuaciones.begin();
    
    bool trobat = false;

    while (iter != m_puntuaciones.end() && !trobat)
    {
        if (iter->puntos < puntos)
        {
            trobat = true;
        } 
        else 
        {
            iter++;
        }
    }

    Puntos nuevoPunto;
    nuevoPunto.jugador = jugador;
    nuevoPunto.puntos = puntos;
    m_puntuaciones.insert(iter, nuevoPunto);
    
}

void Tetris::guardaPuntuacion(const string& nomFitxer) const
{
    ofstream output;
    output.open(nomFitxer);
    list<Puntos>::const_iterator iter = m_puntuaciones.begin();
    while (iter != m_puntuaciones.end())
    {
        output << iter->jugador << " " << iter->puntos << endl;
        iter++;
    }
}

void Tetris::leerPuntuacion(const string& nomFitxer)
{
    ifstream input; 
    input.open(nomFitxer);

    if (input.is_open())
    {
        string jugador;
        int puntos;
        Puntos puntoNuevo;
        input >> puntoNuevo.jugador >> puntoNuevo.puntos;
        

        while (!input.eof())
        {
            m_puntuaciones.push_back(puntoNuevo);
            input >> puntoNuevo.jugador >> puntoNuevo.puntos;

        }

        input.close();
    }
}
