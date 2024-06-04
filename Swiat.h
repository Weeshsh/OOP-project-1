#pragma once
#include "Organizm.h"
#include <vector>
#include <string>
#include <algorithm>
#include <fstream>

class Swiat {
private:
	std::vector<Organizm*> organizmy;
	std::vector<std::string> logi;
	std::pair<int, int> rozmiar;
	Organizm* czlowiek;
	int tura;

	Swiat(std::pair<int, int> rozmiar);

	static Swiat* aktywnySwiat;

public:
	void Tura();
	void Narysuj();
	void DodajOrganizm(Organizm* organizm);
	void Inicjalizuj();
	void WypiszLogi();

	void ZapiszLog(Organizm* organizm, std::string log);

	static Swiat* GetSwiat(std::pair<int, int> rozmiar);
	static Swiat* GetSwiat();
	static Swiat* WczytajSwiat();

	std::pair<int, int> GetRozmiar();

	Organizm* GetOrganizm(std::pair<int, int> pozycja);
	Organizm* GetCzlowiek();
	
	void ZapiszDoPliku();
};
