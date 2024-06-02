#include "ColaMoviments.h"

NodoTipusMoviment::NodoTipusMoviment(TipusMoviment valor)
	:m_next(nullptr)
{
	m_valor = valor;
}

ColaMoviments::ColaMoviments()
{
	m_primer = nullptr;
	m_ultim = nullptr;
	m_nMoviments = 0;
}
ColaMoviments::~ColaMoviments()
{
	NodoTipusMoviment* seguent = nullptr;
	NodoTipusMoviment* actual = m_primer;

	if (m_primer != nullptr)
	{
		while (actual)
		{
			seguent = actual->getNext();
			delete actual;
			actual = seguent;
		}

		m_primer = nullptr;
	}
}
void ColaMoviments::afegeix(TipusMoviment tipus)
{
	NodoTipusMoviment* nuevo = new NodoTipusMoviment(tipus);

	if (m_primer == nullptr)
	{
		m_primer = nuevo;
		m_ultim = nuevo;
	}
	else
	{
		m_ultim->setNext(nuevo);
		m_ultim = nuevo;
		m_nMoviments++;
	}
}

void ColaMoviments::treu()
{
	if (m_primer == nullptr)
	{
	}
	else if (m_primer == m_ultim)
	{
		delete m_primer;
		m_primer = nullptr;
		m_ultim = nullptr;
	}
	else
	{
		NodoTipusMoviment* temp = m_primer;
		m_primer = m_primer->getNext();
		delete temp;
		m_nMoviments--;
	}

}
