#include "TribePCH.h"
#include "PrinterComponent.h"

void PrinterComponent::Print() const
{
	std::cout << m_Action << '\n';
}
