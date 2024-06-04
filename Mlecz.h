#pragma once
#include "Roslina.h"
class Mlecz : public Roslina {
public:
	Organizm* Dziecko();
	Mlecz(std::pair<int, int> pozycjaStartowa);
	void Akcja();
};