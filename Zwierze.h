#pragma once
#include "Organizm.h"
class Zwierze : public Organizm {
public:
	Zwierze(std::string ikona, int sila, int inicjatywa, std::pair<int, int> pozycjaStartowa);
	virtual void Akcja();
	virtual void Kolizja(Organizm* drugi);
};