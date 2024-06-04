#pragma once
#include "Zwierze.h"
class CyberOwca : public Zwierze {
	CyberOwca* dziecko;
public:
	CyberOwca(std::pair<int, int> pozycjaStartowa);
	void Akcja();
	void Kolizja(Organizm* drugi);
};