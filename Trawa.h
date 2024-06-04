#pragma once
#include "Roslina.h"
class Trawa :public Roslina {
public:
	Organizm* Dziecko();
	Trawa(std::pair<int, int> pozycjaStartowa);
};