#include "lis.h"
#include"Swiat.h"

Lis::Lis(std::pair<int, int> pozycjaStartowa) : Zwierze("Li", 3, 7, pozycjaStartowa) {}


void Lis::Akcja() {
	this->Postarz();
	int ruch = rand() % 4;
	std::pair<int, int> nowaPozycja;
	while (ruch != 9) {
		nowaPozycja = { this->GetPozycja().first + this->ruchy[ruch % 4][0], this->GetPozycja().second + this->ruchy[ruch % 4][1] };
		Organizm* organizm = this->swiat->GetOrganizm(nowaPozycja);
		if (organizm == nullptr) {
			if(this->SetPozycja(nowaPozycja, false))
				break;
		}
		else if (organizm->GetSila() > this->GetSila()) {
			std::string nazwa = typeid(*organizm).name();
			nazwa = nazwa.substr(6);
			swiat->ZapiszLog(this, " uciekl przed " + nazwa);
		}
		else {
			if(this->SetPozycja(nowaPozycja, false))
				break;
		}
		ruch++;
	}
}


Organizm* Lis::Dziecko() {
	return new Lis(*this);
}