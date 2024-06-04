#include "Czlowiek.h"
#include "Swiat.h"

Czlowiek::Czlowiek(std::pair<int, int> pozycjaStartowa) : Zwierze("Cz", 5, 4, pozycjaStartowa) {
	licznikUmiejetnosci = 0;
	this->ruch = { 0,0 };
}

void Czlowiek::Akcja() {
	Postarz();

	std::pair<int, int> nowaPozycja = { this->GetPozycja().first + this->ruch.first, this->GetPozycja().second + this->ruch.second };
	Organizm* org = this->swiat->GetOrganizm(nowaPozycja);
	if (org != nullptr && this->licznikUmiejetnosci > 5) {
		if (org != nullptr && org->GetSila() > this->GetSila()) {
			int ruch = rand() % 4;
			while (!SetPozycja({ GetPozycja().first + ruchy[ruch % 4][0], GetPozycja().second + ruchy[ruch % 4][1] }, false)) {
				ruch++;
				if (ruch == 8) {
					swiat->ZapiszLog(this, " nie mial gdzie uciec");
					return;
				}
			}
			std::string nazwa = typeid(*org).name();
			nazwa = nazwa.substr(6);
			swiat->ZapiszLog(this, " przezyl atak " + nazwa);
		}
	}
	else {
		SetPozycja({ GetPozycja().first + ruch.first, GetPozycja().second + ruch.second }, false);
	}

	if (this->licznikUmiejetnosci > 0)
		this->licznikUmiejetnosci--;
	

	this->ruch = { 0,0 };
}

void Czlowiek::UzyjUmiejetnosci() {
	if (this->licznikUmiejetnosci == 0) {
		swiat->ZapiszLog(this, " staje sie niesmiertelny");
		this->SetLicznikUmiejetnosci(10);
	}
}

bool Czlowiek::SetRuch(std::pair<int, int> ruch) {
	int nowyY = GetPozycja().first + ruch.first;
	int nowyX = GetPozycja().second + ruch.second;
	
	if (nowyY < 0 || nowyY >= swiat->GetRozmiar().first || nowyX < 0 || nowyX >= swiat->GetRozmiar().second)
		return false;

	this->ruch = ruch;
	return true;
}

void Czlowiek::SetLicznikUmiejetnosci(int licznikUmiejetnosci) {
	this->licznikUmiejetnosci = licznikUmiejetnosci;
}

Czlowiek* Czlowiek::Dziecko() {
	return nullptr;
}

int Czlowiek::GetLicznikUmiejetnosci() {
	return this->licznikUmiejetnosci;
}

bool Czlowiek::CzyUmiejetnoscAktywna() {
	return this->licznikUmiejetnosci > 4;
}