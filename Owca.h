#pragma once
#include "Zwierze.h"
class Owca : public Zwierze {
public:
	Organizm* Dziecko();
	Owca(std::pair<int, int> pozycjaStartowa);
};