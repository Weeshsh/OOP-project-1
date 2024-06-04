#pragma once
#include "Zwierze.h"
class Wilk : public Zwierze {
public:
	Organizm* Dziecko();
	Wilk(std::pair<int, int> pozycjaStartowa);
};