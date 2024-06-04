#pragma once
#include "Zwierze.h"
class Antylopa : public Zwierze {
private:
	const int ruchy[8][2] = {
		{1,1},
		{1,-1},
		{1,-1},
		{-1,1},
		{0,2},
		{2,0},
		{0,-2},
		{-2,0}
	};
public:
	Antylopa(std::pair<int, int> pozycjaStartowa);

	void Akcja();
	bool Ucieczka();

	Antylopa* Dziecko();
};