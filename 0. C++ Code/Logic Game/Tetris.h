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
	Partida getPartida() { return m_partida; }
	void mostraPuntuacio()const;
	void jugaPartida(Screen& pantalla);
	void guardaPuntuacion(const string& jugador, int puntos);

private:
	Partida m_partida;
	std::list<Puntos> m_puntuaciones;
};
#endif TETRIS_H
