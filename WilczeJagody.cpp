#include "WilczeJagody.h"
#include "Swiat.h"
#include "Czlowiek.h"

WilczeJagody::WilczeJagody(std::pair<int, int> pozycjaStartowa) : Roslina("Wi", 99, pozycjaStartowa) {}

void WilczeJagody::Kolizja(Organizm* drugi) {
	Czlowiek* temp = dynamic_cast<Czlowiek*>(drugi);
	if (temp && temp->GetLicznikUmiejetnosci() == 10) {
		swiat->ZapiszLog(this, " nie zatruly czlowieka");
		return;
	}
	std::string nazwa = typeid(*drugi).name();
	nazwa = nazwa.substr(6);
	this->swiat->ZapiszLog(this, " zatruly i zabily " + nazwa);
	this->Usun();
	drugi->Usun();
}

Organizm* WilczeJagody::Dziecko() {
	return new WilczeJagody(*this);
}