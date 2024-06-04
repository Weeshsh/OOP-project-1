#pragma once
#include "Zwierze.h"
class Zolw : public Zwierze {
public:
	Organizm* Dziecko();
	Zolw(std::pair<int, int> pozycjaStartowa);
	void Akcja();
	void Kolizja(Organizm* drugi);
};