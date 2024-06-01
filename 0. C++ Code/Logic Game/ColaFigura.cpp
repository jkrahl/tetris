#include "ColaFigura.h"

void CuaTipusFigura::afegeix(Figura& valor)
{
	NodeTipusFigura* aux = new NodeTipusFigura;
	aux->m_valor = valor;
	aux->m_next = nullptr;

	if (esBuida()) {
		m_primer = aux;
		m_ultim = aux;
	}
	else {
		m_ultim->m_next = aux;
		m_ultim = aux;
	}
}

void CuaTipusFigura::treu()
{
	if (esBuida())
		return;

	if (m_primer == m_ultim)
		m_ultim = nullptr;

	NodeTipusFigura* aux = m_primer;
	m_primer = aux->m_next;
	delete aux;
}
