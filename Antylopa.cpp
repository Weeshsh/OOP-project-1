#include "Antylopa.h"
#include "Swiat.h"

Antylopa::Antylopa(std::pair<int, int> pozycjaStartowa) : Zwierze("An", 4, 4, pozycjaStartowa) {}

void Antylopa::Akcja() {
	Postarz();
	int ruch = rand() % 8;

	while (!SetPozycja({ GetPozycja().first + ruchy[ruch][0], GetPozycja().second + ruchy[ruch][1] }, false)) {
		ruch++;
		ruch %= 8;
	}
}

bool Antylopa::Ucieczka() {
	if (rand() % 2) {
		int ruch = rand() % 8;
		while (!SetPozycja({ GetPozycja().first + ruchy[ruch%8][0], GetPozycja().second + ruchy[ruch%8][1] }, false)) {
			ruch++;
			if (ruch == 8) {
				this->swiat->ZapiszLog(this, " nie miala gdzie uciec");
				return false;
			}
		}
		this->swiat->ZapiszLog(this, " uciekla");
		return true;
	}
	return false;
}

Antylopa* Antylopa::Dziecko() {
	return new Antylopa(*this);
}