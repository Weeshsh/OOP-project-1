#include "Trawa.h"
#include "Swiat.h"

Trawa::Trawa(std::pair<int, int> pozycjaStartowa) : Roslina("Tr", 0, pozycjaStartowa){}

Organizm* Trawa::Dziecko() {
	return new Trawa(*this);
}