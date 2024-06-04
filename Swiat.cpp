#include "Swiat.h"
#include "Antylopa.h"
#include "BarszczSosnowskiego.h"
#include "Czlowiek.h"
#include "Guarana.h"
#include "Lis.h"
#include "Mlecz.h"
#include "Organizm.h"
#include "Owca.h"
#include "Trawa.h"
#include "WilczeJagody.h"
#include "Wilk.h"
#include "Zolw.h"
#include <fstream>

Swiat::Swiat(std::pair<int, int> rozmiar) {
    this->rozmiar = rozmiar;
    this->czlowiek = nullptr;
    this->tura = 0;
}


void Swiat::Inicjalizuj() {
    int szer = this->rozmiar.second;
    int wys = this->rozmiar.first;

    this->czlowiek = new Czlowiek({ rand() % wys, rand() % szer });
   
    new Antylopa({ rand() % wys, rand() % szer });
    new Antylopa({ rand() % wys, rand() % szer });
    new BarszczSosnowskiego({ rand() % wys, rand() % szer });
    new Lis({ rand() % wys, rand() % szer });
    new Guarana({ rand() % wys, rand() % szer });
    new Mlecz({ rand() % wys, rand() % szer });
    new Owca({ rand() % wys, rand() % szer });
    new Owca({ rand() % wys, rand() % szer });
    new Trawa({ rand() % wys, rand() % szer });
    new WilczeJagody({ rand() % wys, rand() % szer });
    new Wilk({ rand() % wys, rand() % szer });
    new Zolw({ rand() % wys, rand() % szer });
}

void Swiat::DodajOrganizm(Organizm* organizm) {
    this->organizmy.push_back(organizm);
}

void Swiat::ZapiszLog(Organizm* organizm, std::string log) {
    std::string nazwa = typeid(*organizm).name();
    nazwa = nazwa.substr(6, nazwa.length());
    nazwa += log;
    this->logi.push_back(nazwa);
}

void Swiat::WypiszLogi() {
    for (int i = 0; i < this->logi.size(); i++) {
        std::cout << "\033[" << i + 1 << ";" << this->rozmiar.second * 2 + 10 << "H";
        if (i >= this->rozmiar.first + 2) {
            std::cout << "\033[" << i - this->rozmiar.first - 2 + 1<< ";" << this->rozmiar.second * 2 + 55 << "H";
        }
        std::cout << i + 1 << ". " << logi[i] << std::endl;
    }
    this->logi.clear();
}

std::pair<int, int> Swiat::GetRozmiar() {
    return this->rozmiar;
}

Organizm* Swiat::GetOrganizm(std::pair<int, int> pozycja) {
    if (pozycja.first < 0 || pozycja.first >= this->rozmiar.first || pozycja.second < 0 || pozycja.second >= this->rozmiar.second)
        return nullptr;

    for (Organizm* org : this->organizmy) {
        if (org->GetPozycja() == pozycja)
            return org;
    }

    return nullptr;
}

Organizm* Swiat::GetCzlowiek() {
    return this->czlowiek;
}


Swiat* Swiat::aktywnySwiat = nullptr;

Swiat* Swiat::GetSwiat() {
    return aktywnySwiat;
}

Swiat* Swiat::GetSwiat(std::pair<int, int> rozmiary) {
    if (aktywnySwiat != nullptr)
        delete aktywnySwiat;

    aktywnySwiat = new Swiat(rozmiary);
    return aktywnySwiat;
}

void Swiat::Tura() {
    this->tura++;

    std::sort(this->organizmy.begin(), this->organizmy.end(), Organizm::KtoPierwszy);

    int rozmiar = this->organizmy.size();

    for (int i = 0; i < rozmiar; i++) {
        Organizm* org = this->organizmy[i];
        if (org->GetInicjatywa() != -1)
            org->Akcja();
        else
            break;
    }
}

void Swiat::Narysuj() {
    std::cout << "\x1B[2J\x1B[H";
    int szer = this->rozmiar.second;
    int wys = this->rozmiar.first;

    for (int i = 0; i < szer*2+3; i++) {
        std::cout << "#";
    }
    std::cout << std::endl;
    
    for (int i = 0; i < wys; i++) {
        std::cout << "# ";
        for (int j = 0; j < szer; j++) {
            std::cout << ". ";
        }
        std::cout << "#" << std::endl;
    }
    
    for (int i = 0; i < szer*2+3; i++) {
        std::cout << "#";
    }
    std::cout << std::endl;

    for (Organizm* org : this->organizmy) {
        if (org->GetInicjatywa() != -1)
            org->Narysuj();
    }
    std::cout << "\033[0;0H" << "TURA " << tura;
    this->WypiszLogi();
}

Swiat* Swiat::WczytajSwiat() {
    std::ifstream pliki;
    pliki.open("./zapisy/pliki.txt");
    std::string linijka;
    std::string nazwa;
    std::cout << "\x1B[2J\x1B[H";
    std::cout << "Wpisz nazwe pliku, ktory chcesz otworzyc: \n";
    while (pliki >> linijka) {
        std::cout << linijka << "\n";
    }
    std::cin >> nazwa;
    pliki.close();

    std::ifstream wejscie;
    wejscie.open("./zapisy/" + nazwa + ".txt");
    delete aktywnySwiat;

    if (wejscie.is_open()) {

        std::getline(wejscie, linijka, ' ');
        int wysokosc = std::stoi(linijka);
        std::getline(wejscie, linijka, ' ');
        int szerokosc = std::stoi(linijka);

        aktywnySwiat = new Swiat({ wysokosc, szerokosc });
        std::getline(wejscie, linijka, '\n');
        aktywnySwiat->tura = std::stoi(linijka);

        while (getline(wejscie, linijka, ' ')) {
            int x, y, xPop, yPop, sila, wiek;
            Organizm* org = nullptr;
            nazwa = linijka;

            std::getline(wejscie, linijka, ' ');
            x = std::stoi(linijka);

            std::getline(wejscie, linijka, ' ');
            y = std::stoi(linijka);

            std::getline(wejscie, linijka, ' ');
            xPop = std::stoi(linijka);

            std::getline(wejscie, linijka, ' ');
            yPop = std::stoi(linijka);


            std::getline(wejscie, linijka, ' ');
            sila = std::stoi(linijka);

            if (nazwa == "Czlowiek") {
                std::getline(wejscie, linijka, ' ');
                wiek = std::stoi(linijka);
                org = new Czlowiek({ x,y });
                std::getline(wejscie, linijka, '\n');
                aktywnySwiat->czlowiek = org;
                ((Czlowiek*)org)->SetLicznikUmiejetnosci(std::stoi(linijka));
            }
            else {
                std::getline(wejscie, linijka, '\n');
                wiek = std::stoi(linijka);
            }
            if (nazwa == "Antylopa") 
                org = new Antylopa({ x, y });
            
            else  if (nazwa == "BarszczSosnowskiego") 
                org = new BarszczSosnowskiego({ x, y });
            
            else  if (nazwa == "Guarana") 
                org = new Guarana({ x, y });
            
            else  if (nazwa == "Lis") 
                org = new Lis({ x, y });
            
            else  if (nazwa == "Mlecz") 
                org = new Mlecz({ x, y });
            
            else  if (nazwa == "Owca") 
                org = new Owca({ x, y });
            
            else  if (nazwa == "Trawa") 
                org = new Trawa({ x, y });
            
            else  if (nazwa == "WilczeJagody") 
                org = new WilczeJagody({ x, y });
            
            else  if (nazwa == "Wilk") 
                org = new Wilk({ x, y });
            
            else  if (nazwa == "Zolw") 
                org = new Zolw({ x, y });
            
            org->SetPoprzedniaPozycja({ xPop, yPop });
            org->SetSila(sila);
            org->SetWiek(wiek);
        }
    }
    else {
        std::cout << "Bledna nazwa pliku";
        return nullptr;
    }
    return aktywnySwiat;
}

void Swiat::ZapiszDoPliku() {
    std::ofstream wyjscie;
    std::string plik;
    std::cout << "\x1B[2J\x1B[H";
    std::cout << "Podaj nazwe pliku do ktorego chcesz zapisac stan gry: ";
    std::cin >> plik;
    wyjscie.open("./zapisy/" + plik + ".txt");
    if (wyjscie.is_open()) {
        std::string out = std::to_string(this->rozmiar.first) + " " + std::to_string(this->rozmiar.second) + " ";
        out += std::to_string(this->tura) + "\n";
        wyjscie << out;

        for (Organizm* org : this->organizmy) {
            if (org->GetSila() != -1) {
                Czlowiek* check = dynamic_cast<Czlowiek*>(org);
                std::string temp = typeid(*org).name();
                temp = temp.substr(6) + " ";

                temp += std::to_string(org->GetPozycja().first) + " " + std::to_string(org->GetPozycja().second) + " ";
                temp += std::to_string(org->GetPoprzedniaPozycja().first) + " " + std::to_string(org->GetPoprzedniaPozycja().second) + " ";
                temp += std::to_string(org->GetSila()) + " ";
                temp += std::to_string(org->GetWiek());
                if (check) temp += " " + std::to_string(check->GetLicznikUmiejetnosci()) + "\n";
                else temp += "\n";
                wyjscie << temp;
            }
        }
        wyjscie.close();
    }
    else {
        std::cout << "Bledna nazwa pliku";
    }
    std::ofstream pliki;
    pliki.open("./zapisy/pliki.txt", std::ios_base::app);
    if (pliki.is_open()) {
        pliki << plik + ".txt\n";
        pliki.close();

        std::cout << "\nPomyslnie zapisano swiat do pliku!";
    }
    else {
        std::cout << "Bledna nazwa pliku";
    }

    }