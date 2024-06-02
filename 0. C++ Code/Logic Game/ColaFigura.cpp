#include "ColaFigura.h"

NodoFigura::NodoFigura(Figura valor)
	:m_next(nullptr)
{
	m_valor = valor;
}

ColaFigura::ColaFigura()
{
	m_primer = nullptr;
	m_ultim = nullptr;
	m_nMoviments = 0;
}

ColaFigura::~ColaFigura()
{
	NodoFigura* seguent = nullptr;
	NodoFigura* actual = m_primer;

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
void ColaFigura::afegeix(Figura tipus) 
{
	NodoFigura* nuevo = new NodoFigura(tipus);

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

void ColaFigura::treu()
{
	if (m_primer == nullptr)
	{
	}
	else if (m_primer == m_ultim)
	{
		delete m_primer;
		m_primer = nullptr;
		delete m_ultim;
		m_ultim = nullptr;
	}
	else
	{
		NodoFigura* temp = m_primer;
		m_primer = m_primer->getNext();
		delete temp;
		m_nMoviments--;
	}

}
