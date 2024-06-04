#include "Zwierze.h"
#include "Swiat.h"
#include "Czlowiek.h"

Zwierze::Zwierze(std::string ikona, int sila, int inicjatywa, std::pair<int, int> pozycjaStartowa) : Organizm(ikona, sila, inicjatywa, pozycjaStartowa){}

void Zwierze::Akcja() {
	Postarz();
	int ruch = rand() % 4;
	while (!SetPozycja({ GetPozycja().first + ruchy[ruch][0], GetPozycja().second + ruchy[ruch][1] }, false)) {
		ruch++;
		ruch %= 4;
	}
}

void Zwierze::Kolizja(Organizm* drugi) {
	if (this == drugi)
		return;

	if (typeid(*this) == typeid(*drugi)) {
		if (this->GetWiek() < 2 || drugi->GetWiek() < 2)
			return;
		Zwierze* dziecko = dynamic_cast<Zwierze*>(this->Dziecko());
		int ruch = rand() % 4;
		while (!dziecko->SetPozycja({ this->GetPozycja().first + ruchy[ruch % 4][0], this->GetPozycja().second + ruchy[ruch % 4][1] }, true)) {
			ruch++;
			if (ruch == 9) {
				this->swiat->ZapiszLog(this, " Nie ma miejsca na rozmnozenie");
				dziecko->Usun();
				return;
			}
		}
		this->swiat->ZapiszLog(this, " rozmnozyly sie");
		return;
	}
	
	
	if (this->Ucieczka() || drugi->Ucieczka())
		return;

	std::string nazwa = typeid(*drugi).name();
	nazwa = nazwa.substr(6);

	Czlowiek* temp = dynamic_cast<Czlowiek*>(drugi);
	Czlowiek* temp2 = dynamic_cast<Czlowiek*>(this);

	if (this->GetSila() > drugi->GetSila()) {
		if (temp && temp->CzyUmiejetnoscAktywna())
			return;
		
		swiat->ZapiszLog(this, " zabil " + nazwa);
		drugi->Usun();
	}
	else if (this->GetSila() < drugi->GetSila()){
		if (temp2 && temp2->CzyUmiejetnoscAktywna())
			return;
		swiat->ZapiszLog(this, " zostal zabity przez " + nazwa);
		this->Usun();
	}
	else {
		Czlowiek* temp = dynamic_cast<Czlowiek*>(drugi);
		if (temp && temp->CzyUmiejetnoscAktywna()) {
			return;
		}
		swiat->ZapiszLog(this, " zabil " + nazwa + " , rowne sily");
		drugi->Usun();
	}
}


