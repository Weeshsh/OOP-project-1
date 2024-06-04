#include <iostream>
#include <fstream>
#include <windows.h>
#include <time.h>
#include <conio.h>
#include "Swiat.h"
#include "Czlowiek.h"
#include <fstream>

using namespace std;

enum kontrolki {
	strzalka_gora = 72,
	strzalka_dol = 80,
	strzalka_lewo = 75,
	strzalka_prawo = 77,
    
    umiejetnosc = ' ',

    escape = 27,
    
    zapisz = 's',
    wczytaj = 'w',
};

int main() {
    pair<int, int> rozmiary;
    char wejscie;

    cout << "\x1B[2J\x1B[H";

    srand(time(NULL));
    SetConsoleTitle(L"Mikolaj Wiszniewski 197925");
    ios::sync_with_stdio(false);

    cout << "Podaj wysokosc swiata: " << endl;
    cin >> rozmiary.first;
    cout << "Podaj szerokosc swiata: " << endl;
    cin >> rozmiary.second;

    std::cout << "\033[?25l";

    Swiat* swiat = Swiat::GetSwiat(rozmiary);

    swiat->Inicjalizuj();
    swiat->Narysuj();

    wejscie = ' ';

    while (wejscie != escape) {
        Czlowiek* czlowiek = dynamic_cast<Czlowiek*>(swiat->GetCzlowiek());
        wejscie = _getch();
        if (wejscie == -32 || wejscie == 0 || wejscie == 224) {
            wejscie = _getch();
        }
        if (czlowiek != nullptr && czlowiek->GetPozycja().first != -1) {
            switch (wejscie) {
            case strzalka_gora:
                if (!czlowiek->SetRuch({ -1, 0 }))
                    continue;
                break;
            case strzalka_dol:
                if (!czlowiek->SetRuch({ 1, 0 }))
                    continue;
                break;
            case strzalka_lewo:
                if (!czlowiek->SetRuch({ 0, -1 }))
                    continue;
                break;
            case strzalka_prawo:
                if (!czlowiek->SetRuch({ 0, 1 }))
                    continue;
                break;

            case umiejetnosc:
                czlowiek->UzyjUmiejetnosci();
                continue;
            }
        }
        switch (wejscie) {
        case zapisz:
            swiat->ZapiszDoPliku();
            continue;
        case wczytaj:
            swiat = Swiat::WczytajSwiat();
            swiat->Narysuj();
            continue;
        }
        swiat->Tura();
        swiat->Narysuj();
    }

    return 0;
}