#include "Swiat.h"
#include "Wilk.h"


Wilk::Wilk(std::pair<int, int> pozycjaStartowa) : Zwierze("Wi", 9, 5, pozycjaStartowa) {}

Organizm* Wilk::Dziecko() {
	return new Wilk(*this);
}