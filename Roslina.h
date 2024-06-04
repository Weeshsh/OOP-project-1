#pragma once
#include "Organizm.h"
class Roslina : public Organizm {
public:
	Roslina(std::string ikona, int sila, std::pair<int, int> pozycjaStartowa);
	virtual void Akcja();
	virtual void Kolizja(Organizm* drugi);
};