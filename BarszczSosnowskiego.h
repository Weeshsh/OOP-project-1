#pragma once
#include "Roslina.h"
class BarszczSosnowskiego : public Roslina {
public:
	BarszczSosnowskiego(std::pair<int, int> pozycjaStartowa);
	void Akcja();
	void Kolizja(Organizm* drugi);
	Organizm* Dziecko();
};