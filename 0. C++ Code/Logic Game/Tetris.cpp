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
        case 1: //MOdo normal
        {
            m_partida.inicialitza(false, "data/Games/partida.txt", "", ""); //Modo normal
            int puntos = m_partida.partidaBucle(pantalla);
            string jugador;
            cout << "Escriba su nombre: ";
            cin >> jugador;
            insertaPuntuacionOrdenada(jugador, puntos);

            break;
        }
        case 2: //Modo test
        {
            string partida, figures, moviments;
            cout << "Nom del fitxer amb l'estat inicial del tauler: ";
            cin >> partida;
            cout << "Nom del fitxer amb la sequencia de figures: ";
            cin >> figures;
            cout << "Nom del fitxer amb la sequencia de moviments: ";
            cin >> moviments;

            m_partida.inicialitza(true, partida, figures, moviments); //Modo test, le paso los ficheros
            int puntos = m_partida.partidaBucle(pantalla);
            string jugador;
            cout << "Escriba su nombre: ";

            cin >> jugador;
            insertaPuntuacionOrdenada(jugador, puntos);
            break;
        }
        case 3: //Mostrar puntuaciones
        {
            mostraPuntuacio();
            break;
        }
        case 4:
        default:
            break;
        }
    } while (opcio != 4);   
    guardaPuntuacion("puntuacion.txt"); //Al final para que se guarde una vez clice '4'
   
}
 
void Tetris::mostraPuntuacio() const //Si clica 3, se mostraran las puntuaciones con el nombre del jugador
{
    list<Puntos>::const_iterator iter = m_puntuaciones.begin();
    cout << "------PUNTUACIONES------" << endl;
    int i = 0;
    while (iter != m_puntuaciones.end() && i <= 10) //Mostrar solo 10 puntos
    {
        cout << i+1 <<  ".  " << iter->jugador << "   " << iter->puntos << endl;
        iter++;
        i++;
    }

}

void Tetris::insertaPuntuacionOrdenada(const string& jugador, int puntos) //De mayor a menor
{
    //inserta de forma ordenada en una lista , mayor a menor
    list<Puntos>::iterator iter = m_puntuaciones.begin();
    
    bool trobat = false;
    //Usamos un while y va comparando para encontrar el mayor
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

    Puntos nuevoPunto; //Agrega el nuevo punto en la lista
    nuevoPunto.jugador = jugador;
    nuevoPunto.puntos = puntos;
    m_puntuaciones.insert(iter, nuevoPunto);
    
}

void Tetris::guardaPuntuacion(const string& nomFitxer) const //Guarda los puntos de una nueva partida con el nombre del jugaador
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

void Tetris::leerPuntuacion(const string& nomFitxer) //pasa los datos que hay en el fichero a la lista
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
