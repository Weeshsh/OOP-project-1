#pragma once
#include "Zwierze.h"
class Czlowiek : public Zwierze {
private:
	int licznikUmiejetnosci;
	std::pair<int, int> ruch;
public:
	Czlowiek(std::pair<int, int> pozycjaStartowa);
	void Akcja();
	void UzyjUmiejetnosci();
	
	bool SetRuch(std::pair<int,int> ruch);
	void SetLicznikUmiejetnosci(int licznikUmiejetnosci);
	
	int GetLicznikUmiejetnosci();
	bool CzyUmiejetnoscAktywna();

	Czlowiek* Dziecko();
};