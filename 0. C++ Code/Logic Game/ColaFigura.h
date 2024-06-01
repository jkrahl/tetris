#pragma once
#include "Figura.h"

class NodeTipusFigura
{
public:
	Figura m_valor;
	NodeTipusFigura* m_next;
};

class CuaTipusFigura
{
public:
	CuaTipusFigura() : m_primer(nullptr), m_ultim(nullptr) {}

	void afegeix(Figura& valor);
	void treu();
	Figura& getPrimer() const { return m_primer->m_valor; }
	Figura& getUltim() const { return m_ultim->m_valor; }
	bool esBuida() const { return (m_primer == nullptr && m_ultim == nullptr); }
private:
	NodeTipusFigura* m_primer;
	NodeTipusFigura* m_ultim;
};