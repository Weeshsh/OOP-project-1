#include "Organizm.h"
#include "Swiat.h"
#include "Zwierze.h"

Organizm::Organizm(std::string ikona, int sila, int inicjatywa, std::pair<int, int> pozycjaStartowa) {
	this->swiat = Swiat::GetSwiat();
	this->ikona = ikona;
	this->sila = sila;
	this->inicjatywa = inicjatywa;
	this->pozycja = pozycjaStartowa;
	this->wiek = 0;
	this->pozycjaPoprzednia = pozycjaStartowa;
	swiat->DodajOrganizm(this);
}

Organizm::Organizm(const Organizm& organizm) {
	this->swiat = organizm.swiat;
	this->ikona = organizm.ikona;
	this->sila = organizm.sila;
	this->inicjatywa = organizm.inicjatywa;
	this->pozycja = organizm.pozycja;
	this->wiek = 0;
	this->pozycjaPoprzednia = organizm.pozycjaPoprzednia;
	swiat->DodajOrganizm(this);
}

std::string Organizm::GetIkona() {
	return this->ikona;
}

bool Organizm::Ucieczka() {
	return false;
}

int Organizm::GetInicjatywa() {
	return this->inicjatywa;
}

int Organizm::GetSila() {
	return this->sila;
}

int Organizm::GetWiek() {
	return this->wiek;
}

void Organizm::Wzmocnij(int dodaj) {
	this->sila += dodaj;
}

std::pair<int,int> Organizm::GetPozycja() {
	return this->pozycja;
}

void Organizm::Postarz() {
	this->wiek++;
}

void Organizm::Usun() {
	this->pozycja = { -1, -1 };
	this->sila = -1;
	this->inicjatywa = -1;
}

bool Organizm::SetPozycja(std::pair<int, int> pozycja, bool naPuste) {
	if (pozycja.first < 0 || pozycja.first >= swiat->GetRozmiar().first || pozycja.second < 0 || pozycja.second >= swiat->GetRozmiar().second)
		return false;

	if (naPuste && swiat->GetOrganizm(pozycja) != nullptr)
		return false;

	Organizm* org = swiat->GetOrganizm(pozycja);
	this->pozycjaPoprzednia = this->pozycja;
	this->pozycja = pozycja;
	swiat->ZapiszLog(this, " ruch na " + std::to_string(pozycja.second) + ", " + std::to_string(pozycja.first) + ".");
	if(org != nullptr)
		org->Kolizja(this);

	return true;
}

void Organizm::Cofnij() {
	this->SetPozycja(pozycjaPoprzednia, false);
}

int Organizm::KtoPierwszy(Organizm* pierwszy, Organizm* drugi) {
	int in1 = pierwszy->inicjatywa;
	int in2 = drugi->inicjatywa;
	
	if (in1 > in2)
		return 1;
	
	if (in1 < in2)
		return 0;
	
	if (pierwszy->wiek > drugi->wiek)
		return 1;
	
	return 0;
}

void Organizm::Narysuj() {
	std::cout << "\x1B[" << this->GetPozycja().first + 2 << ";" << this->GetPozycja().second *2 + 2<< "H";
	
	std::cout << "\033[32m";
	if (dynamic_cast<Zwierze*>(this)) {
		std::cout << "\033[31m";
	}
	std::cout << this->ikona;
	std::cout << "\033[0m";
}

std::pair<int, int> Organizm::GetPoprzedniaPozycja() {
	return this->pozycjaPoprzednia;
}

void Organizm::SetWiek(int wiek) {
	this->wiek = wiek;
}

void Organizm::SetSila(int sila) {
	this->sila = sila;
}

void Organizm::SetPoprzedniaPozycja(std::pair<int, int> pozycja) {
	this->pozycjaPoprzednia = pozycja;
}