#pragma once
#include "Roslina.h"
class WilczeJagody :public Roslina {
public:
	Organizm* Dziecko();
	WilczeJagody(std::pair<int, int> pozycjaStartowa);
	void Kolizja(Organizm* drugi);
};