#pragma once
#ifndef  TETRIS_H
#define TETRIS_H
#include "Partida.h"
#include <string>
#include <list>
#include "GraphicManager.h"
#include <iostream>
#include <list>

struct Puntos
{
	string jugador;
	int puntos;
};
class Tetris
{
public:
	void mostraPuntuacio()const;
	void jugaPartida(Screen& pantalla);

private:
	void insertaPuntuacionOrdenada(const string& jugador, int puntos);
	void guardaPuntuacion(const string& nomFitxer) const;
	void leerPuntuacion(const string& nomFitxer);

	Partida m_partida;
	std::list<Puntos> m_puntuaciones;
};
#endif TETRIS_H
