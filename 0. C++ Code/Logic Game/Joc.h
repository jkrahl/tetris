#pragma once
#include "Tauler.h"

/*
▪ Ha de servir per poder gestionar el funcionament global del joc.
* Ha de poder guardar i gestionar el tauler de joc (utilitzant la classe Tauler), la figura actual que està caient (utilitzant la classe Figura), la informació de l’estat de la partida (puntuació, nivell, etc. ) i qualsevol altra informació que considereu necessària per gestionar la partida.
* Ha de tenir aquesta interfície pública:
*/
class Joc
{
public:
	Joc(){}
	int baixaTotalmentFigura(); //PAra baja la figura de golpe si se presiona space
	bool creaNovaFigura(); //Crear figura nueva
	bool setNovaFigura(Figura& fig);

	void actualitza(double deltaTime);

	/*
	* Aquest mètode el farem servir només pel test automàtic del lliurament parcial.
	* Servirà per inicialitzar la partida a partir de la informació que llegirem del fitxer que es passa com a paràmetre.
	* Permetrà inicialitzar el tauler de joc amb algunes caselles ja ocupades per figures col·locades i fixar el tipus, forma i posició de la figura actual que està caient.
	*/
	void inicialitza(const string& nomFitxer);

	/*
	* Gira la figura actual en la direcció indicada, només si el gir és vàlid (la figura no col·lisiona ni amb els límits del tauler ni amb altres figures ja col·locades al tauler).
	* Retorna un booleà en funció de si el gir és vàlid segons la posició de la figura i el contingut del tauler.
	*/
	bool giraFigura(DireccioGir direccio);

	void draw() const;

	/*
	* Desplaça la figura lateralment en la direcció indicada (+1 cap a la dreta, -1 cap a l’esquerra), només si el moviment és vàlid (la figura no col·lisiona ni amb els límits del tauler ni amb altres figures ja col·locades al tauler).
	* Retorna un booleà en funció de si el moviment és vàlid segons la posició de la figura i el contingut del tauler
	*/
	bool mouFigura(int dirX);

	/*
	* Desplaça la figura verticalment una posició cap a baix.
	* Si el desplaçament provoca que la figura col·lisioni amb altres figures ja col·locades al tauler s’ha de col·locar la figura al tauler, comprovar si es completa alguna fila i, si és el cas, eliminar les files completades.
	* Retorna el nombre de files completades.
	*/
	int baixaFigura();

	/*
	* Ha de escriure l’estat actual del tauler en el fitxer que es passa com a paràmetre, seguint el mateix format que hem descrit pel mètode inicialitza. Només ha d’escriure els valors actuals del tauler, no la informació de la figura actual.
	* La figura s’ha de mostrar com si estigués col·locada al tauler a la seva posició actual.
	*/
	void escriuTauler(const string& nomFitxer);
private:
	Tauler m_tauler;
	Figura m_figura_actual;
	// Falta implementar més atributs
};

