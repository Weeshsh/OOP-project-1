#include "Mlecz.h"
#include "Swiat.h"

Mlecz::Mlecz(std::pair<int, int> pozycjaStartowa) : Roslina("Ml", 0, pozycjaStartowa){}

void Mlecz::Akcja() {
	for (int i = 0; i < 3; i++) {
		Roslina::Akcja();
	}
}

Organizm* Mlecz::Dziecko() {
	return new Mlecz(*this);
}