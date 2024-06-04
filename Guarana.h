#pragma once
#include "Roslina.h"

class Guarana :public Roslina {
public:
	Guarana(std::pair<int, int> pozycjaStartowa);
	void Kolizja(Organizm* drugi);
	Organizm* Dziecko();
};