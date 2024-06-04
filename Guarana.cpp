#include "Swiat.h"
#include "Guarana.h"

Guarana::Guarana(std::pair<int, int> pozycjaStartowa) : Roslina("Gu", 0, pozycjaStartowa) {}

void Guarana::Kolizja(Organizm* drugi) {
	std::string nazwa = typeid(*drugi).name();
	nazwa = nazwa.substr(6);
	this->swiat->ZapiszLog(this, " Wzmocnila " + nazwa);
	drugi->Wzmocnij(3);
	this->Usun();
}

Organizm* Guarana::Dziecko() {
	return new Guarana(*this);
}