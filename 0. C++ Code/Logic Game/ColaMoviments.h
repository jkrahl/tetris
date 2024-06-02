#pragma once
#include "InfoJoc.h"

class NodoTipusMoviment
{
public:
	NodoTipusMoviment():m_next(nullptr), m_valor(MOVIMENT_BAIXA){}

	NodoTipusMoviment(TipusMoviment valor);

	NodoTipusMoviment* getNext() { return m_next; }
	TipusMoviment& getValor() { return m_valor; }
	void setNext(NodoTipusMoviment* next) { m_next = next; }
	void setValor(TipusMoviment valor) { m_valor= valor; }
private:
	NodoTipusMoviment* m_next;
	TipusMoviment m_valor;
};

class ColaMoviments
{
public:
	ColaMoviments();
	~ColaMoviments();
	void afegeix(TipusMoviment tipus);
	bool esBuida() const
	{
		return m_primer == nullptr;
	}
	
	void treu();

	TipusMoviment& getPrimer() const
	{
		return m_primer->getValor();
	}
	TipusMoviment& getUltim() const
	{
		return m_ultim->getValor();
	}

private:
	NodoTipusMoviment* m_primer;
	NodoTipusMoviment* m_ultim;
	int m_nMoviments;
};

