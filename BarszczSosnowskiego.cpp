#include "BarszczSosnowskiego.h"
#include "Swiat.h"
#include "Zwierze.h"
#include "Czlowiek.h"

BarszczSosnowskiego::BarszczSosnowskiego(std::pair<int, int> pozycjaStartowa) : Roslina("Bs", 10, pozycjaStartowa) {}

void BarszczSosnowskiego::Akcja() {
	Roslina::Akcja();

	for (int ruch = 0; ruch < 4; ruch++) {
		auto sasiad = this->swiat->GetOrganizm({ this->GetPozycja().first + ruchy[ruch][0], this->GetPozycja().second + ruchy[ruch][1] });
		if (sasiad != nullptr && dynamic_cast<Zwierze*>(sasiad)) {
			Czlowiek* temp = dynamic_cast<Czlowiek*>(sasiad);
			if (temp && temp->CzyUmiejetnoscAktywna()) {
				swiat->ZapiszLog(this, " nie zatrul czlowieka");
				return;
			}
			std::string nazwa = typeid(*sasiad).name();
			nazwa = nazwa.substr(6);
			swiat->ZapiszLog(this, " zatrul sasiada " + nazwa);
			sasiad->Usun();
		}
	}
}

void BarszczSosnowskiego::Kolizja(Organizm* drugi) {
	Czlowiek* temp = dynamic_cast<Czlowiek*>(drugi);
	if (temp && temp->CzyUmiejetnoscAktywna()) {
		swiat->ZapiszLog(this, " nie zatrul czlowieka");
		return;
	}
	std::string nazwa = typeid(*drugi).name();
	nazwa = nazwa.substr(6);
	swiat->ZapiszLog(this, " zatrul " + nazwa);
	drugi->Usun();
	this->Usun();
}

Organizm* BarszczSosnowskiego::Dziecko() {
	return new BarszczSosnowskiego(*this);
}