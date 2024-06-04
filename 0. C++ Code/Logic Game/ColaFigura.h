#pragma once
#pragma once
#include "InfoJoc.h"
#include "Figura.h"

class NodoFigura
{
public:
	NodoFigura() :m_next(nullptr), m_valor() {}
	NodoFigura(Figura valor);
	NodoFigura* getNext() { return m_next; }
	Figura& getValor() { return m_valor; }
	void setNext(NodoFigura* next) { m_next = next; }
	void setValor(Figura valor) { m_valor = valor; }
private:
	NodoFigura* m_next;
	Figura m_valor;
};

class ColaFigura
{
public:
	ColaFigura();
	~ColaFigura();
	void afegeix(Figura tipus);
	bool esBuida() const{ return m_primer == nullptr;}
	void treu();
	Figura& getPrimer() const { return m_primer->getValor();}
	Figura& getUltim() const { return m_ultim->getValor();}

private:
	NodoFigura* m_primer;
	NodoFigura* m_ultim;
	int m_nMoviments;
};

