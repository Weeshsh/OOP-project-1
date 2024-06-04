#include "Zolw.h"
#include"Swiat.h"

Zolw::Zolw(std::pair<int, int> pozycjaStartowa) : Zwierze("Zo", 2, 1, pozycjaStartowa) {}


void Zolw::Akcja() {
	bool czyRuch = rand() % 4 != 0;
	if (czyRuch) {
		Zwierze::Akcja();
	}
	else {
		this->Postarz();
	}
}


void Zolw::Kolizja(Organizm* drugi) {
	if (drugi->GetSila() <= 5 && typeid(*this) != typeid(*drugi)) {
		std::string nazwa = typeid(*drugi).name();
		nazwa = nazwa.substr(6);
		swiat->ZapiszLog(this, " odbil atak " + nazwa);
		drugi->Cofnij();
	}
	else {
		Zwierze::Kolizja(drugi);
	}
}

Organizm* Zolw::Dziecko() {
	return new Zolw(*this);
}