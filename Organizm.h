#pragma once
#include <iostream>

class Swiat;
class Organizm {
	int sila;
	int inicjatywa;
	int wiek;
	std::pair<int, int> pozycja;
	std::pair<int, int> pozycjaPoprzednia;
	std::string ikona;
protected:
	Swiat* swiat;
	const int ruchy[4][2] = {
		{0,1},
		{1,0},
		{0,-1},
		{-1,0}
	};
public:
	Organizm(std::string ikona, int sila, int inicjatywa, std::pair<int, int> pozycjaStartowa);
	Organizm(const Organizm& organizm);

	virtual void Akcja() = 0;
	virtual void Kolizja(Organizm* drugi) = 0;
	virtual bool Ucieczka();
	virtual Organizm* Dziecko() = 0;

	int GetSila();
	int GetInicjatywa();
	int GetWiek();
	std::string GetIkona();
	std::pair<int,int> GetPozycja();
	std::pair<int, int> GetPoprzedniaPozycja();


	void Postarz();
	void Usun();
	void Narysuj();
	void Wzmocnij(int dodaj);
	void Cofnij();

	bool SetPozycja(std::pair<int, int> pozycja, bool naPuste);
	void SetPoprzedniaPozycja(std::pair<int, int> pozycja);
	void SetWiek(int wiek);
	void SetSila(int sila);

	static int KtoPierwszy(Organizm* pierwszy, Organizm* drugi);
};