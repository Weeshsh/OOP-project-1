#include "Owca.h"
#include "Swiat.h"

Owca::Owca(std::pair<int, int> pozycjaStartowa) : Zwierze("Ow", 4,4,pozycjaStartowa) {}

Organizm* Owca::Dziecko() {
	return new Owca(*this);
}