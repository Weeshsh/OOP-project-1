#include "Roslina.h"
#include "Swiat.h"
Roslina::Roslina(std::string ikona, int sila, std::pair<int, int> pozycjaStartowa) : Organizm(ikona, sila, 0, pozycjaStartowa) {}

void Roslina::Akcja() {
	bool zasianie = !(rand() % 100);
	if (zasianie) {
		Roslina* dziecko = dynamic_cast<Roslina*>(this->Dziecko());
		int ruch = rand() % 4;
		while (!dziecko->SetPozycja({ this->GetPozycja().first + ruchy[ruch % 4][0], this->GetPozycja().second + ruchy[ruch % 4][1] }, true)) {
			ruch++;
			if (ruch == 9) {
				this->swiat->ZapiszLog(this, " nie ma miejsca na zasianie");
				dziecko->Usun();
				return;
			}
		}
		this->swiat->ZapiszLog(this, " rozsial sie");
	}
}

void Roslina::Kolizja(Organizm* drugi) {
	if (this == drugi)
		return;

	if (this->GetSila() > drugi->GetSila()) {
		this->swiat->ZapiszLog(this, " Zatruto napastnika");
		drugi->Usun();
	}
	else if(this->GetSila() < drugi->GetSila()){
		this->swiat->ZapiszLog(this, " Zostala zdeptana");
		this->Usun();
	}
	else {
		this->swiat->ZapiszLog(this, " Sily byly rowne");
		this->Usun();
		drugi->Usun();
	}
}