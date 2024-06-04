#pragma once
#include "Zwierze.h"
class Lis : public Zwierze {
public:
	Organizm* Dziecko();
	Lis(std::pair<int, int> pozycjaStartowa);
	void Akcja();
};