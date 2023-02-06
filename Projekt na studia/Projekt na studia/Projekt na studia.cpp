#define _CRT_SECURE_NO_WARNINGS
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <time.h>
#include <direct.h>
#include <cstdio>


int main()
{
    sf::RenderWindow window(sf::VideoMode(1900, 1000), "Quest List");
    sf::RectangleShape shape(sf::Vector2f(300, 300));
    sf::Texture calendarblue, calendargreen, calendarred, calendarfree, calendarright, calendarleft;
    sf::Texture buttonback, free;
    sf::Texture boardback, boardbook, boardhealth, boardmeat, boardweight, boardup, boarddown, boardadd;

    //wczytywanie tekstur
    calendarblue.loadFromFile("resources/calendarblue.png");
    calendarred.loadFromFile("resources/calendarred.png");
    calendargreen.loadFromFile("resources/calendargreen.png");
    calendarfree.loadFromFile("resources/calendarfree.png");
    calendarright.loadFromFile("resources/calendarright.png");
    calendarleft.loadFromFile("resources/calendarleft.png");
    buttonback.loadFromFile("resources/buttonback.png");
    boardback.loadFromFile("resources/boardback.png");
    boardbook.loadFromFile("resources/boardbook.png");
    boardhealth.loadFromFile("resources/boardhealth.png");
    boardmeat.loadFromFile("resources/boardmeat.png");
    boardweight.loadFromFile("resources/boardweight.png");
    boardup.loadFromFile("resources/boardup.png");
    boarddown.loadFromFile("resources/boarddown.png");
    boardadd.loadFromFile("resources/boardadd.png");
    free.loadFromFile("resources/free.png");




    time_t czas;
    struct tm* data;
    int month, day, year;
    std::string name, line, calendarmonth, note, helper;
    std::fstream plik;
    time(&czas);
    data = localtime(&czas);
    int dzien = 0, rok = 0, miesiac = 0;
    bool zkal = false;

    shape.setFillColor(sf::Color::Green);
    sf::Font font;
    font.loadFromFile("Jack.TTF");
    sf::Text tekst;
    tekst.setFont(font);
    tekst.setCharacterSize(20);
    tekst.setFillColor(sf::Color::Black);
    tekst.setString("...");
    sf::String playerInput, przenoszenie;

    //vectory ze zmieniajaca sie iloscia zasobow
    std::vector<sf::RectangleShape> przyciski; //vector ze wszystkimi przyciskami
    std::vector<sf::Sprite> objects; //vector ze wszystkimi obiektami
    std::vector<int> Xprzyciski; //po dwie kolejne zmienne na kazdy przycisk (poczatek i koniec)
    std::vector<int> Yprzyciski; //po dwie kolejne zmienne na kazdy przycisk (gora i dol)
    std::vector<sf::Text> teksty; //vector z tekstami do wyswietlenia
    
    sf::Sprite addoner[5];
    addoner[0].setTexture(boardmeat);
    addoner[1].setTexture(boardhealth);
    addoner[2].setTexture(boardweight);
    addoner[3].setTexture(boardbook);
    addoner[4].setTexture(boardback);
    addoner[0].setPosition(sf::Vector2f(2000, 1100));
    addoner[1].setPosition(sf::Vector2f(2000, 1100));
    addoner[2].setPosition(sf::Vector2f(2000, 1100));
    addoner[3].setPosition(sf::Vector2f(2000, 1100));
    addoner[4].setPosition(sf::Vector2f(2000, 1100));
    tekst.setPosition(sf::Vector2f(2000, 1100));

    sf::Vector2i pozycja;
    int szerokosc = 300, licznik_umieszczanie = 0, licznik_wysokosc = 1;
    int state = -1, dni = 0, przesownik = 0;
    bool change_state = true, completed = true, adding = false, texting = false;
    window.setFramerateLimit(15);
    while (window.isOpen())
    {
        if (change_state) //wczytywanie i usuwanie
        {
            if (state == -1) //menu glowne
            {
                objects.clear();
                przyciski.clear();
                teksty.clear();
                Xprzyciski.clear();
                Yprzyciski.clear();
                for(int i = 0; i < 5; i++)
                    przyciski.push_back(sf::RectangleShape(sf::Vector2f(634, 66)));
                for (int i = 0; i < 5; i++)
                {
                    teksty.push_back(sf::Text());
                    teksty[i].setFont(font);
                    teksty[i].setCharacterSize(20);
                    teksty[i].setFillColor(sf::Color::White);
                    
                }
                teksty[0].setPosition(sf::Vector2f(633, 500));
                teksty[1].setPosition(sf::Vector2f(633, 600));
                teksty[2].setPosition(sf::Vector2f(633, 700));
                teksty[3].setPosition(sf::Vector2f(633, 800));
                teksty[4].setPosition(sf::Vector2f(633, 900));
                teksty[0].setString("CALENDAR");
                teksty[1].setString("BOARD");
                teksty[2].setString("QUEST LIST");
                teksty[3].setString("QUEST LOG");
                teksty[4].setString("CREATOR");
                

                //xy
                /*przyciski[0].setFillColor(sf::Color::Red);
                Xprzyciski.push_back(633); //przycisk 0
                Xprzyciski.push_back(1267);
                Xprzyciski.push_back(633); //przycisk 1
                Xprzyciski.push_back(1267);
                Xprzyciski.push_back(633); //przycisk 2
                Xprzyciski.push_back(1267);
                Xprzyciski.push_back(633); //przycisk 3
                Xprzyciski.push_back(1267);
                Xprzyciski.push_back(633); //przycisk 4
                Xprzyciski.push_back(1267);

                //ygreki
                Yprzyciski.push_back(500);//przycisk 0
                Yprzyciski.push_back(566);
                Yprzyciski.push_back(600);//przycisk 1
                Yprzyciski.push_back(666);
                Yprzyciski.push_back(700);//przycisk 2
                Yprzyciski.push_back(766);
                Yprzyciski.push_back(800);//przycisk 3
                Yprzyciski.push_back(866);
                Yprzyciski.push_back(900);//przycisk 4
                Yprzyciski.push_back(966);*/
                przyciski[0].setPosition(sf::Vector2f(633, 500));
                przyciski[1].setPosition(sf::Vector2f(633, 600));
                przyciski[2].setPosition(sf::Vector2f(633, 700));
                przyciski[3].setPosition(sf::Vector2f(633, 800));
                przyciski[4].setPosition(sf::Vector2f(633, 900));
            }
            if (state == 0) //calendar
            {
                przyciski.clear();
                teksty.clear();
                Xprzyciski.clear();
                Yprzyciski.clear();
                objects.clear();
                for (int i = 0; i < 48; i++)
                    objects.push_back(sf::Sprite()); //tworzenie wszystkich przyciskow beda one od 0 do 47 (48 rzeczy)
                int ey = 44;
                data->tm_mday = 1;
                mktime(data);

                //dni dla miesiaca
                if (data->tm_mon == 0) //styczen
                {
                    dni = 31;
                    calendarmonth = "Styczen ";
                }
                if (data->tm_mon == 1) //luty
                {
                    dni = 28;
                    if ((data->tm_year % 4) == 0)
                        dni = 29;
                    calendarmonth = "Luty ";
                }
                if (data->tm_mon == 2) //marzec
                {
                    dni = 31;
                    calendarmonth = "Marzec ";
                }
                if (data->tm_mon == 3) //kwiecien
                {
                    dni = 30;
                    calendarmonth = "Kwiecen ";
                }
                if (data->tm_mon == 4) //maj
                {
                    dni = 31;
                    calendarmonth = "Maj ";
                }
                if (data->tm_mon == 5) //czerwiec
                {
                    dni = 30;
                    calendarmonth = "Czerwiec ";
                }
                if (data->tm_mon == 6) //lipiec
                {
                    dni = 31;
                    calendarmonth = "Lipiec ";
                }
                if (data->tm_mon == 7) //sierpien
                {
                    dni = 31;
                    calendarmonth = "Sierpien ";
                }
                if (data->tm_mon == 8) //wrzesien
                {
                    dni = 30;
                    calendarmonth = "Wrzesien ";
                }
                if (data->tm_mon == 9) //pazdziernik
                {
                    dni = 31;
                    calendarmonth = "Pazdziernik ";
                }
                if (data->tm_mon == 10) //listopad
                {
                    dni = 30;
                    calendarmonth = "Listopad ";
                }
                if (data->tm_mon == 11) //grudzien
                {
                    dni = 31;
                    calendarmonth = "Grudzien ";
                }
                calendarmonth += std::to_string(data->tm_year + 1900);

                if (data->tm_wday != 0)
                {
                    for (int i = 1; i <= dni; i++)
                    {
                        name = "calendar/";
                        name = name + std::to_string(i) + "v" + std::to_string(data->tm_mon + 1) + "v" + std::to_string(data->tm_year + 1900) + ".txt";
                        plik.open(name.c_str(), std::ios::in);
                        std::cout << name << "\n";
                        if (!(plik.good()))
                            objects[i + data->tm_wday - 2].setTexture(calendarblue);
                        if (plik.good())
                        {
                            std::getline(plik, line);
                            if (line == "red")
                                objects[i + data->tm_wday - 2].setTexture(calendarred);
                            if (line == "green")
                                objects[i + data->tm_wday - 2].setTexture(calendargreen);
                        }
                        plik.close();
                    }
                }
                else
                {
                    for (int i = 1; i <= dni; i++)
                    {
                        name = "calendar/";
                        name = name + std::to_string(i) + "v" + std::to_string(data->tm_mon + 1) + "v" + std::to_string(data->tm_year + 1900) + ".txt";
                        plik.open(name.c_str(), std::ios::in);
                        std::cout << name << "\n";
                        if (!(plik.good()))
                            objects[i + data->tm_wday + 5].setTexture(calendarblue);
                        if (plik.good())
                        {
                            std::getline(plik, line);
                            if (line == "red")
                                objects[i + data->tm_wday + 5].setTexture(calendarred);
                            if (line == "green")
                                objects[i + data->tm_wday + 5].setTexture(calendargreen);
                        }
                        plik.close();
                    }
                    for (int i = 1; i <= dni; i++)
                        teksty[i + data->tm_wday + 5].setString(std::to_string(i));
                }
                for (int i = 0; i < 42; i++)
                {
                    if (i % 7 == 0)
                        ey += 136;
                    objects[i].setPosition(sf::Vector2f(143 + ((i%7) * 230), ey));
                    
                    //ey += 136;
                }
                objects[42].setTexture(calendarleft); //przycisk w lewo
                objects[42].setPosition(sf::Vector2f(30, 200));
                objects[43].setTexture(calendarright); //przycisk w prawo
                objects[43].setPosition(sf::Vector2f(1820, 200));
                
                for (int i = 0; i < 4; i++)
                {
                    objects[i + 44].setTexture(buttonback); //ustawienia dla paska funkcji
                }
                objects[44].setPosition(sf::Vector2f(250, 30));
                objects[45].setPosition(sf::Vector2f(631, 30));
                objects[46].setPosition(sf::Vector2f(1014, 30)); //pozycje dla paska funkcji
                objects[47].setPosition(sf::Vector2f(1395, 30));


                //teksty
                for (int i = 0; i < 47; i++)
                    teksty.push_back(sf::Text()); //tworzenie wszystkich tekst
                for (int i = 0; i <47; i++)
                {
                    teksty[i].setFont(font);
                    teksty[i].setCharacterSize(20);
                    teksty[i].setFillColor(sf::Color::Black);
                    //teksty[i].setString(std::to_string(i));
                }
                ey = 45;
                for (int i = 0; i < 42; i++)
                {
                    if (i % 7 == 0)
                        ey += 136;
                    teksty[i].setPosition(sf::Vector2f(145 + ((i % 7) * 230), ey));

                    //ey += 136;
                }
                for (int i = 1; i <= dni; i++)
                    teksty[i + data->tm_wday - 2].setString(std::to_string(i));

                teksty[42].setString("MENU");
                teksty[43].setString("BOARD");
                teksty[44].setString("QUEST LIST"); //teksty dla przyciskow gornych
                teksty[45].setString("QUEST LOG");

                teksty[42].setPosition(sf::Vector2f(255, 30));
                teksty[43].setPosition(sf::Vector2f(636, 30)); //umiejcowienie przyciskow gornych
                teksty[44].setPosition(sf::Vector2f(1019, 30));
                teksty[45].setPosition(sf::Vector2f(1400, 30));
                teksty[46].setCharacterSize(30);
                teksty[46].setPosition(sf::Vector2f(250, 100));
                teksty[46].setString(calendarmonth);
            }
            if (state == 1) //board
            {
                przesownik = 0;
                objects.clear();
                przyciski.clear();
                teksty.clear();
                Xprzyciski.clear();
                Yprzyciski.clear();

                for (int i = 0; i < 32; i++)
                {
                    objects.push_back(sf::Sprite()); //wszystkie elementy
                }

                for (int i = 0; i < 16; i++)
                    teksty.push_back(sf::Text()); //tworzenie wszystkich tekst
                for (int i = 0; i < 16; i++)
                {
                    teksty[i].setFont(font);
                    teksty[i].setCharacterSize(20);
                    teksty[i].setFillColor(sf::Color::Black);
                }

                for (int i = 0; i < 12; i++)
                {
                    objects[i].setTexture(boardback);
                }
                szerokosc = 220;
                objects[0].setPosition(sf::Vector2f(110, 200));
                objects[1].setPosition(sf::Vector2f(410, 200));
                objects[2].setPosition(sf::Vector2f(710, 200));
                objects[3].setPosition(sf::Vector2f(110, 485)); //pozycje kolejnych kartek
                objects[4].setPosition(sf::Vector2f(410, 485));
                objects[5].setPosition(sf::Vector2f(710, 485));
                objects[6].setPosition(sf::Vector2f(110, 770));
                objects[7].setPosition(sf::Vector2f(410, 770));
                objects[8].setPosition(sf::Vector2f(710, 770));
                objects[9].setPosition(sf::Vector2f(1600, 200));
                objects[10].setPosition(sf::Vector2f(1600, 485));
                objects[11].setPosition(sf::Vector2f(1600, 770));

                teksty[0].setPosition(sf::Vector2f(125, 275));
                teksty[1].setPosition(sf::Vector2f(425, 275));
                teksty[2].setPosition(sf::Vector2f(725, 275));
                teksty[3].setPosition(sf::Vector2f(125, 560)); //pozycje kolejnych kartek
                teksty[4].setPosition(sf::Vector2f(425, 560));
                teksty[5].setPosition(sf::Vector2f(725, 560));
                teksty[6].setPosition(sf::Vector2f(125, 845));
                teksty[7].setPosition(sf::Vector2f(425, 845));
                teksty[8].setPosition(sf::Vector2f(725, 845));
                teksty[9].setPosition(sf::Vector2f(1615, 275));
                teksty[10].setPosition(sf::Vector2f(1615, 560));
                teksty[11].setPosition(sf::Vector2f(1615, 845));
                teksty[9].setString("przejdz 10 km");
                teksty[10].setString("naucz sie czegos \nnowego");
                teksty[11].setString("przypomnienie o \nlekach");

                data = localtime(&czas);
                if (zkal)
                {
                    data->tm_year = rok;
                    data->tm_mon = miesiac;
                    data->tm_mday = dzien;
                }
                mktime(data);

                name = "board/";
                name = name + std::to_string(data->tm_mday) + "a" + std::to_string(data->tm_mon + 1) + "a" + std::to_string(data->tm_year + 1900);
                std::cout << name << "\n";
                if (_mkdir(name.c_str()))
                {
                    for (int i = 12; i < 21; i++)
                    {
                        note = name + "/" + std::to_string(i - 11) + ".txt";
                        plik.open(note.c_str(), std::ios::in);
                        std::cout << note << "\n";
                        if (plik.good())
                        {
                            helper = "";
                            std::getline(plik, line);
                            std::cout << line << "\n";
                            if(line == "weight")
                                objects[i].setTexture(boardweight);
                            if(line == "book")
                                objects[i].setTexture(boardbook);
                            if(line == "health")
                                objects[i].setTexture(boardhealth);
                            if(line == "meat")
                                objects[i].setTexture(boardmeat);
                            while (getline(plik, line))
                            {
                                
                                std::cout << helper << "\n";
                                helper = helper + line + "\n";
                                teksty[i-12].setString(helper);
                            }
                        }
                        plik.close();
                         //tekstury obrazkow
                    }
                    //teksty[0].setString("aadada");
                }
                else
                {
                    _rmdir(name.c_str());
                }
                objects[12].setPosition(sf::Vector2f(125, 215));
                objects[13].setPosition(sf::Vector2f(425, 215));
                objects[14].setPosition(sf::Vector2f(725, 215));
                objects[15].setPosition(sf::Vector2f(125, 500)); //pozycje zdjec
                objects[16].setPosition(sf::Vector2f(425, 500));
                objects[17].setPosition(sf::Vector2f(725, 500));
                objects[18].setPosition(sf::Vector2f(125, 785));
                objects[19].setPosition(sf::Vector2f(425, 785));
                objects[20].setPosition(sf::Vector2f(725, 785));
                objects[21].setPosition(sf::Vector2f(1615, 215));
                objects[22].setPosition(sf::Vector2f(1615, 500));
                objects[23].setPosition(sf::Vector2f(1615, 785));
                objects[21].setTexture(boardweight);
                objects[22].setTexture(boardbook);
                objects[23].setTexture(boardhealth);

                objects[24].setTexture(boardup); //przyciski gorne
                objects[25].setTexture(boardadd);
                objects[26].setTexture(boarddown);

                objects[24].setPosition(sf::Vector2f(30, 180));
                objects[25].setPosition(sf::Vector2f(30, 540)); //pozycje przyciskow gornych
                objects[26].setPosition(sf::Vector2f(30, 930));
                for (int i = 0; i < 4; i++)
                {
                    objects[i + 27].setTexture(buttonback); //ustawienia dla paska funkcji
                }
                objects[27].setPosition(sf::Vector2f(250, 30));
                objects[28].setPosition(sf::Vector2f(631, 30));
                objects[29].setPosition(sf::Vector2f(1014, 30)); //pozycje dla paska funkcji
                objects[30].setPosition(sf::Vector2f(1395, 30));
                //objects[21].setPosition(sf::Vector2f(1395, 30));
                teksty[12].setString("CALENDAR");
                teksty[13].setString("MENU");
                teksty[14].setString("QUEST LIST"); //teksty dla przyciskow gornych
                teksty[15].setString("QUEST LOG");

                teksty[12].setPosition(sf::Vector2f(255, 30));
                teksty[13].setPosition(sf::Vector2f(636, 30)); //umiejcowienie przyciskow gornych
                teksty[14].setPosition(sf::Vector2f(1019, 30));
                teksty[15].setPosition(sf::Vector2f(1400, 30));
                /*
                for (int i = 22; i < 25; i++)
                {
                    przyciski[i].setSize(sf::Vector2f(50, 50));
                    przyciski[i].setFillColor(sf::Color::Cyan); //przyciski wysokosci i dodawania
                }

                przyciski[22].setPosition(sf::Vector2f(30, 180));
                przyciski[23].setPosition(sf::Vector2f(30, 665)); //pozycje^^
                przyciski[24].setPosition(sf::Vector2f(30, 920));

                przyciski[25].setFillColor(sf::Color::White);
                przyciski[25].setSize(sf::Vector2f(5, 820)); //podzialka miedzy sugerowanymi i zwyklymi
                przyciski[25].setPosition(sf::Vector2f(1128, 200));
                */
                
            }
            if (state == 2) //quest list
            {
                objects.clear();
                przyciski.clear();
                teksty.clear();
                Xprzyciski.clear();
                Yprzyciski.clear();

                for (int i = 0; i < 34; i++)
                    przyciski.push_back(sf::RectangleShape()); //tworzenie wszystkich elementow

                for (int i = 0; i < 14; i++)
                {
                    przyciski[i].setSize(sf::Vector2f(450, 50));
                    przyciski[i].setFillColor(sf::Color::Blue); //dla przewijanej czesci z lewej
                    przyciski[i].setOutlineThickness(1);
                    przyciski[i].setOutlineColor(sf::Color::Cyan);
                    przyciski[i].setPosition(sf::Vector2f(50, 205 + (i * 50)));
                }
                
                przyciski[14].setSize(sf::Vector2f(450, 25)); //wielkosc przyciskow do przewijania
                przyciski[15].setSize(sf::Vector2f(450, 25));

                przyciski[14].setPosition(sf::Vector2f(50, 180));
                przyciski[15].setPosition(sf::Vector2f(50, 905)); //pozycje prz. do przesowania

                przyciski[14].setFillColor(sf::Color::Red);
                przyciski[15].setFillColor(sf::Color::Red); //na czerwono

                przyciski[16].setFillColor(sf::Color::Yellow);
                przyciski[17].setFillColor(sf::Color::Yellow);
                przyciski[16].setSize(sf::Vector2f(50, 50)); //przyciski dodawania i usuwania
                przyciski[16].setPosition(sf::Vector2f(570, 190));
                przyciski[17].setSize(sf::Vector2f(50, 50));
                przyciski[17].setPosition(sf::Vector2f(1750, 190));

                przyciski[18].setSize(sf::Vector2f(450, 200));
                przyciski[19].setSize(sf::Vector2f(1200, 200));
                przyciski[18].setPosition(sf::Vector2f(960, 130)); //pole tekstowe i zdjecie
                przyciski[19].setPosition(sf::Vector2f(590, 350));
                przyciski[18].setFillColor(sf::Color::White);
                przyciski[19].setFillColor(sf::Color::White);

                for (int i = 20; i < 24; i++)
                {
                    przyciski[i].setSize(sf::Vector2f(255, 50));
                    przyciski[i].setFillColor(sf::Color::Green);
                }

                przyciski[20].setPosition(sf::Vector2f(250, 30));
                przyciski[21].setPosition(sf::Vector2f(631, 30)); //pozycje przyciskow gornych
                przyciski[22].setPosition(sf::Vector2f(1014, 30));
                przyciski[23].setPosition(sf::Vector2f(1395, 30));

                for (int i = 0; i < 10; i++)
                {
                    przyciski[24 + i].setSize(sf::Vector2f(900, 40));
                    przyciski[24 + i].setPosition(sf::Vector2f(740, 570 + (i * 40)));
                    przyciski[24 + i].setFillColor(sf::Color::Cyan);
                    przyciski[24 + i].setOutlineThickness(1);
                    przyciski[24 + i].setOutlineColor(sf::Color::White);
                }

                for (int i = 0; i < 4; i++)
                    teksty.push_back(sf::Text()); //tworzenie wszystkich tekst
                for (int i = 0; i < 4; i++)
                {
                    teksty[i].setFont(font);
                    teksty[i].setCharacterSize(20);
                    teksty[i].setFillColor(sf::Color::Black);
                }
                teksty[0].setString("CALENDAR");
                teksty[1].setString("BOARD");
                teksty[2].setString("MENU"); //teksty dla przyciskow gornych
                teksty[3].setString("QUEST LOG");

                teksty[0].setPosition(sf::Vector2f(250, 30));
                teksty[1].setPosition(sf::Vector2f(631, 30)); //umiejcowienie przyciskow gornych
                teksty[2].setPosition(sf::Vector2f(1014, 30));
                teksty[3].setPosition(sf::Vector2f(1395, 30));

            }
            if (state == 3) //quest log
            {
                objects.clear();
                przyciski.clear();
                teksty.clear();
                Xprzyciski.clear();
                Yprzyciski.clear();

                for (int i = 0; i < 19; i++)
                {
                    przyciski.push_back(sf::RectangleShape()); //wszystkie elementy
                }

                for (int i = 0; i < 13; i++)
                {
                    przyciski[i].setSize(sf::Vector2f(1700, 50));
                    przyciski[i].setPosition(sf::Vector2f(100, 225 + (i * 50)));
                    przyciski[i].setOutlineThickness(1); //kolejne rzedy tabeli
                    przyciski[i].setOutlineColor(sf::Color::White);
                    przyciski[i].setFillColor(sf::Color::Green);
                }

                przyciski[13].setSize(sf::Vector2f(570, 25));
                przyciski[13].setPosition(sf::Vector2f(665, 200));
                przyciski[13].setFillColor(sf::Color::Cyan); //przyciski przewijania
                przyciski[14].setSize(sf::Vector2f(570, 25));
                przyciski[14].setPosition(sf::Vector2f(665, 875));
                przyciski[14].setFillColor(sf::Color::Cyan);

                for (int i = 15; i < 19; i++)
                {
                    przyciski[i].setSize(sf::Vector2f(255, 50));
                    przyciski[i].setFillColor(sf::Color::Red);
                }

                przyciski[15].setPosition(sf::Vector2f(250, 30));
                przyciski[16].setPosition(sf::Vector2f(631, 30)); //pozycje przyciskow gornych
                przyciski[17].setPosition(sf::Vector2f(1014, 30));
                przyciski[18].setPosition(sf::Vector2f(1395, 30));

                for (int i = 0; i < 4; i++)
                    teksty.push_back(sf::Text()); //tworzenie wszystkich tekst
                for (int i = 0; i < 4; i++)
                {
                    teksty[i].setFont(font);
                    teksty[i].setCharacterSize(20);
                    teksty[i].setFillColor(sf::Color::Black);
                }
                teksty[0].setString("CALENDAR");
                teksty[1].setString("BOARD");
                teksty[2].setString("QUEST LIST"); //teksty dla przyciskow gornych
                teksty[3].setString("MENU");

                teksty[0].setPosition(sf::Vector2f(250, 30));
                teksty[1].setPosition(sf::Vector2f(631, 30)); //umiejcowienie przyciskow gornych
                teksty[2].setPosition(sf::Vector2f(1014, 30));
                teksty[3].setPosition(sf::Vector2f(1395, 30));

            }
            if (state == 4) //creator
            {
                objects.clear();
                przyciski.clear();
                teksty.clear();
                Xprzyciski.clear();
                Yprzyciski.clear();

                przyciski.push_back(sf::RectangleShape(sf::Vector2f(634, 66)));
                teksty.push_back(sf::Text());

                teksty[0].setFont(font);
                teksty[0].setCharacterSize(20);
                teksty[0].setFillColor(sf::Color::Black);
                teksty[0].setPosition(sf::Vector2f(633, 500));
                teksty[0].setString("Jakub Szklarz");

                teksty.push_back(sf::Text());
                teksty[1].setFont(font);
                teksty[1].setCharacterSize(20);
                teksty[1].setFillColor(sf::Color::White);
                teksty[1].setPosition(sf::Vector2f(633, 900));
                teksty[1].setString("BACK");

                przyciski[0].setPosition(sf::Vector2f(633, 900));
                przyciski[0].setFillColor(sf::Color::Red);
            }

            change_state = false;
        }
        //ruchy mysza
        pozycja = sf::Mouse::getPosition(window);
        if (state == -1) //menu
        {
            przyciski[0].setFillColor(sf::Color::Red);
            if (pozycja.x >= 633 && pozycja.x <= 1267 && pozycja.y >= 500 && pozycja.y <= 566) //calendar
                przyciski[0].setFillColor(sf::Color::Magenta);

            przyciski[1].setFillColor(sf::Color::Red);
            if (pozycja.x >= 633 && pozycja.x <= 1267 && pozycja.y >= 600 && pozycja.y <= 666) //board
                przyciski[1].setFillColor(sf::Color::Magenta);

            przyciski[2].setFillColor(sf::Color::Red);
            if (pozycja.x >= 633 && pozycja.x <= 1267 && pozycja.y >= 700 && pozycja.y <= 766) //quest list
                przyciski[2].setFillColor(sf::Color::Magenta);

            przyciski[3].setFillColor(sf::Color::Red);
            if (pozycja.x >= 633 && pozycja.x <= 1267 && pozycja.y >= 800 && pozycja.y <= 866) //quest log
                przyciski[3].setFillColor(sf::Color::Magenta);

            przyciski[4].setFillColor(sf::Color::Red);
            if (pozycja.x >= 633 && pozycja.x <= 1267 && pozycja.y >= 900 && pozycja.y <= 966) //creator
                przyciski[4].setFillColor(sf::Color::Magenta);
        }
        else if (state == 0) //calendar
        {
            objects[44].setColor(sf::Color::White);
            if (pozycja.x >= 255 && pozycja.x <= 505 && pozycja.y >= 30 && pozycja.y <= 80) //board
                objects[44].setColor(sf::Color(125,125,125,255));

            objects[45].setColor(sf::Color::White);
            if (pozycja.x >= 631 && pozycja.x <= 886 && pozycja.y >= 30 && pozycja.y <= 80) //board
                objects[45].setColor(sf::Color(125, 125, 125, 255));

            objects[46].setColor(sf::Color::White);
            if (pozycja.x >= 1014 && pozycja.x <= 1269 && pozycja.y >= 30 && pozycja.y <= 80) //board
                objects[46].setColor(sf::Color(125, 125, 125, 255));

            objects[47].setColor(sf::Color::White);
            if (pozycja.x >= 1395 && pozycja.x <= 1650 && pozycja.y >= 30 && pozycja.y <= 80) //board
                objects[47].setColor(sf::Color(125, 125, 125, 255));

            objects[42].setColor(sf::Color::White);
            if (pozycja.x >= 30 && pozycja.x <= 80 && pozycja.y >= 200 && pozycja.y <= 800) //calendar left
                objects[42].setColor(sf::Color(125, 125, 125, 255));

            objects[43].setColor(sf::Color::White);
            if (pozycja.x >= 1820 && pozycja.x <= 1870 && pozycja.y >= 200 && pozycja.y <= 800) //calendar right
                objects[43].setColor(sf::Color(125, 125, 125, 255));

        }
        else if (state == 1) //board
        {
            objects[27].setColor(sf::Color::White);
            if (pozycja.x >= 255 && pozycja.x <= 505 && pozycja.y >= 30 && pozycja.y <= 80) //board
                objects[27].setColor(sf::Color(125, 125, 125, 255));

            objects[28].setColor(sf::Color::White);
            if (pozycja.x >= 631 && pozycja.x <= 886 && pozycja.y >= 30 && pozycja.y <= 80) //board
                objects[28].setColor(sf::Color(125, 125, 125, 255));

            objects[29].setColor(sf::Color::White);
            if (pozycja.x >= 1014 && pozycja.x <= 1269 && pozycja.y >= 30 && pozycja.y <= 80) //board
                objects[29].setColor(sf::Color(125, 125, 125, 255));

            objects[30].setColor(sf::Color::White);
            if (pozycja.x >= 1395 && pozycja.x <= 1650 && pozycja.y >= 30 && pozycja.y <= 80) //board
                objects[30].setColor(sf::Color(125, 125, 125, 255));

            objects[24].setColor(sf::Color::White);
            if (pozycja.x >= 30 && pozycja.x <= 80 && pozycja.y >= 180 && pozycja.y <= 230) //board
                objects[24].setColor(sf::Color::Yellow);

            objects[25].setColor(sf::Color::White);
            if (pozycja.x >= 30 && pozycja.x <= 80 && pozycja.y >= 540 && pozycja.y <= 590) //board
                objects[25].setColor(sf::Color::Green);

            objects[26].setColor(sf::Color::White);
            if (pozycja.x >= 30 && pozycja.x <= 80 && pozycja.y >= 930 && pozycja.y <= 980) //board
                objects[26].setColor(sf::Color::Yellow);

        }
        else if (state == 2) //quest list
        {
            przyciski[20].setFillColor(sf::Color::Green);
            if (pozycja.x >= 255 && pozycja.x <= 505 && pozycja.y >= 30 && pozycja.y <= 80) //board
                przyciski[20].setFillColor(sf::Color::Magenta);

            przyciski[21].setFillColor(sf::Color::Green);
            if (pozycja.x >= 631 && pozycja.x <= 886 && pozycja.y >= 30 && pozycja.y <= 80) //board
                przyciski[21].setFillColor(sf::Color::Magenta);

            przyciski[22].setFillColor(sf::Color::Green);
            if (pozycja.x >= 1014 && pozycja.x <= 1269 && pozycja.y >= 30 && pozycja.y <= 80) //board
                przyciski[22].setFillColor(sf::Color::Magenta);

            przyciski[23].setFillColor(sf::Color::Green);
            if (pozycja.x >= 1395 && pozycja.x <= 1650 && pozycja.y >= 30 && pozycja.y <= 80) //board
                przyciski[23].setFillColor(sf::Color::Magenta);
        }
        else if (state == 3) //quest log
        {
            przyciski[15].setFillColor(sf::Color::Red);
            if (pozycja.x >= 255 && pozycja.x <= 505 && pozycja.y >= 30 && pozycja.y <= 80) //board
                przyciski[15].setFillColor(sf::Color::Magenta);

            przyciski[16].setFillColor(sf::Color::Red);
            if (pozycja.x >= 631 && pozycja.x <= 886 && pozycja.y >= 30 && pozycja.y <= 80) //board
                przyciski[16].setFillColor(sf::Color::Magenta);

            przyciski[17].setFillColor(sf::Color::Red);
            if (pozycja.x >= 1014 && pozycja.x <= 1269 && pozycja.y >= 30 && pozycja.y <= 80) //board
                przyciski[17].setFillColor(sf::Color::Magenta);

            przyciski[18].setFillColor(sf::Color::Red);
            if (pozycja.x >= 1395 && pozycja.x <= 1650 && pozycja.y >= 30 && pozycja.y <= 80) //board
                przyciski[18].setFillColor(sf::Color::Magenta);
        }
        else if (state == 4) //creator
        {
            przyciski[0].setFillColor(sf::Color::Red);
            if (pozycja.x >= 633 && pozycja.x <= 1267 && pozycja.y >= 900 && pozycja.y <= 966) //creator
                przyciski[0].setFillColor(sf::Color::Magenta);
        }
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::MouseButtonPressed) //jesli przycisk myszy klikniety
            {
                if (state == -1) //menu
                {
                    if (pozycja.x >= 633 && pozycja.x <= 1267 && pozycja.y >= 500 && pozycja.y <= 566) //calendar
                    {
                        std::cout << "przycisk calendar \n";
                        state = 0;
                        change_state = true;
                    }
                    if (pozycja.x >= 633 && pozycja.x <= 1267 && pozycja.y >= 600 && pozycja.y <= 666) //board
                    {
                        std::cout << "przycisk board \n";
                        state = 1;
                        change_state = true;
                    }
                    if (pozycja.x >= 633 && pozycja.x <= 1267 && pozycja.y >= 700 && pozycja.y <= 766) //quest list
                    {
                        std::cout << "przycisk quest list \n";
                        state = 2;
                        change_state = true;
                    }
                    if (pozycja.x >= 633 && pozycja.x <= 1267 && pozycja.y >= 800 && pozycja.y <= 866) //quest log
                    {
                        std::cout << "przycisk quest log \n";
                        state = 3;
                        change_state = true;
                    }
                    if (pozycja.x >= 633 && pozycja.x <= 1267 && pozycja.y >= 900 && pozycja.y <= 966) //creator
                    {
                        std::cout << "przycisk creator \n";
                        state = 4;
                        change_state = true;
                    }
                }
                else if (state == 0) //calendar
                {
                    if (pozycja.x >= 255 && pozycja.x <= 505 && pozycja.y >= 30 && pozycja.y <= 80) //calendar
                    {
                        std::cout << "przycisk menu \n";
                        state = -1;
                        change_state = true;
                    }
                    if (pozycja.x >= 631 && pozycja.x <= 886 && pozycja.y >= 30 && pozycja.y <= 80) //board
                    {
                        std::cout << "przycisk board \n";
                        state = 1;
                        change_state = true;
                    }
                    if (pozycja.x >= 1014 && pozycja.x <= 1269 && pozycja.y >= 30 && pozycja.y <= 80) //quest list
                    {
                        std::cout << "przycisk quest list \n";
                        state = 2;
                        change_state = true;
                    }
                    if (pozycja.x >= 1395 && pozycja.x <= 1650 && pozycja.y >= 30 && pozycja.y <= 80) //quest log
                    {
                        std::cout << "przycisk quest log \n";
                        state = 3;
                        change_state = true;
                    }
                    if (pozycja.x >= 30 && pozycja.x <= 80 && pozycja.y >= 200 && pozycja.y <= 800) //calendar left
                    {
                        for (int i = 0; i < 42; i++)
                        {
                            objects[i].setTexture(calendarfree);
                            teksty[i].setString("");
                        }
                        std::cout << "przycisk calendar left \n";
                        if (data->tm_mon == 0)
                        {
                            data->tm_mon = 11;
                            data->tm_year -= 1;
                        }
                        else
                        {
                            data->tm_mon -= 1;
                        }
                        mktime(data);

                        if (data->tm_mon == 0) //styczen
                        {
                            dni = 31;
                            calendarmonth = "Styczen ";
                        }
                        if (data->tm_mon == 1) //luty
                        {
                            dni = 28;
                            if ((data->tm_year % 4) == 0)
                                dni = 29;
                            calendarmonth = "Luty ";
                        }
                        if (data->tm_mon == 2) //marzec
                        {
                            dni = 31;
                            calendarmonth = "Marzec ";
                        }
                        if (data->tm_mon == 3) //kwiecien
                        {
                            dni = 30;
                            calendarmonth = "Kwiecen ";
                        }
                        if (data->tm_mon == 4) //maj
                        {
                            dni = 31;
                            calendarmonth = "Maj ";
                        }
                        if (data->tm_mon == 5) //czerwiec
                        {
                            dni = 30;
                            calendarmonth = "Czerwiec ";
                        }
                        if (data->tm_mon == 6) //lipiec
                        {
                            dni = 31;
                            calendarmonth = "Lipiec ";
                        }
                        if (data->tm_mon == 7) //sierpien
                        {
                            dni = 31;
                            calendarmonth = "Sierpien ";
                        }
                        if (data->tm_mon == 8) //wrzesien
                        {
                            dni = 30;
                            calendarmonth = "Wrzesien ";
                        }
                        if (data->tm_mon == 9) //pazdziernik
                        {
                            dni = 31;
                            calendarmonth = "Pazdziernik ";
                        }
                        if (data->tm_mon == 10) //listopad
                        {
                            dni = 30;
                            calendarmonth = "Listopad ";
                        }
                        if (data->tm_mon == 11) //grudzien
                        {
                            dni = 31;
                            calendarmonth = "Grudzien ";
                        }
                        calendarmonth += std::to_string(data->tm_year + 1900);
                        if (data->tm_wday != 0)
                        {
                            for (int i = 1; i <= dni; i++)
                            {
                                name = "calendar/";
                                name = name + std::to_string(i) + "v" + std::to_string(data->tm_mon + 1) + "v" + std::to_string(data->tm_year + 1900) + ".txt";
                                plik.open(name.c_str(), std::ios::in);
                                std::cout << name << "\n";
                                if (!(plik.good()))
                                    objects[i + data->tm_wday - 2].setTexture(calendarblue);
                                if (plik.good())
                                {
                                    std::getline(plik, line);
                                    if (line == "red")
                                        objects[i + data->tm_wday - 2].setTexture(calendarred);
                                    if (line == "green")
                                        objects[i + data->tm_wday - 2].setTexture(calendargreen);
                                }
                                plik.close();
                            }
                            for (int i = 1; i <= dni; i++)
                                teksty[i + data->tm_wday - 2].setString(std::to_string(i));
                        }
                        else
                        {
                            for (int i = 1; i <= dni; i++)
                            {
                                name = "calendar/";
                                name = name + std::to_string(i) + "v" + std::to_string(data->tm_mon + 1) + "v" + std::to_string(data->tm_year + 1900) + ".txt";
                                plik.open(name.c_str(), std::ios::in);
                                std::cout << name << "\n";
                                if (!(plik.good()))
                                    objects[i + data->tm_wday + 5].setTexture(calendarblue);
                                if (plik.good())
                                {
                                    std::getline(plik, line);
                                    if (line == "red")
                                        objects[i + data->tm_wday + 5].setTexture(calendarred);
                                    if (line == "green")
                                        objects[i + data->tm_wday + 5].setTexture(calendargreen);
                                }
                                plik.close();
                            }
                            for (int i = 1; i <= dni; i++)
                                teksty[i + data->tm_wday + 5].setString(std::to_string(i));
                        }
                        teksty[46].setString(calendarmonth);
                        

                    }
                    if (pozycja.x >= 1820 && pozycja.x <= 1870 && pozycja.y >= 200 && pozycja.y <= 800) //calendar right
                    {
                        std::cout << "przycisk calendar right \n";
                        for (int i = 0; i < 42; i++)
                        {
                            objects[i].setTexture(calendarfree);
                            teksty[i].setString("");
                        }
                        if (data->tm_mon == 11)
                        {
                            data->tm_mon = 0;
                            data->tm_year += 1;
                        }
                        else
                        {
                            data->tm_mon += 1;
                        }
                        mktime(data);

                        if (data->tm_mon == 0) //styczen
                        {
                            dni = 31;
                            calendarmonth = "Styczen ";
                        }
                        if (data->tm_mon == 1) //luty
                        {
                            dni = 28;
                            if ((data->tm_year % 4) == 0)
                                dni = 29;
                            calendarmonth = "Luty ";
                        }
                        if (data->tm_mon == 2) //marzec
                        {
                            dni = 31;
                            calendarmonth = "Marzec ";
                        }
                        if (data->tm_mon == 3) //kwiecien
                        {
                            dni = 30;
                            calendarmonth = "Kwiecen ";
                        }
                        if (data->tm_mon == 4) //maj
                        {
                            dni = 31;
                            calendarmonth = "Maj ";
                        }
                        if (data->tm_mon == 5) //czerwiec
                        {
                            dni = 30;
                            calendarmonth = "Czerwiec ";
                        }
                        if (data->tm_mon == 6) //lipiec
                        {
                            dni = 31;
                            calendarmonth = "Lipiec ";
                        }
                        if (data->tm_mon == 7) //sierpien
                        {
                            dni = 31;
                            calendarmonth = "Sierpien ";
                        }
                        if (data->tm_mon == 8) //wrzesien
                        {
                            dni = 30;
                            calendarmonth = "Wrzesien ";
                        }
                        if (data->tm_mon == 9) //pazdziernik
                        {
                            dni = 31;
                            calendarmonth = "Pazdziernik ";
                        }
                        if (data->tm_mon == 10) //listopad
                        {
                            dni = 30;
                            calendarmonth = "Listopad ";
                        }
                        if (data->tm_mon == 11) //grudzien
                        {
                            dni = 31;
                            calendarmonth = "Grudzien ";
                        }
                        calendarmonth += std::to_string(data->tm_year + 1900);
                        if (data->tm_wday != 0)
                        {
                            for (int i = 1; i <= dni; i++)
                            {
                                name = "calendar/";
                                name = name + std::to_string(i) + "v" + std::to_string(data->tm_mon + 1) + "v" + std::to_string(data->tm_year + 1900) + ".txt";
                                plik.open(name.c_str(), std::ios::in);
                                std::cout << name << "\n";
                                if (!(plik.good()))
                                    objects[i + data->tm_wday - 2].setTexture(calendarblue);
                                if (plik.good())
                                {
                                    std::getline(plik, line);
                                    if (line == "red")
                                        objects[i + data->tm_wday - 2].setTexture(calendarred);
                                    if (line == "green")
                                        objects[i + data->tm_wday - 2].setTexture(calendargreen);
                                }
                                plik.close();
                            }
                            for (int i = 1; i <= dni; i++)
                                teksty[i + data->tm_wday - 2].setString(std::to_string(i));
                        }
                        else
                        {
                            for (int i = 1; i <= dni; i++)
                            {
                                name = "calendar/";
                                name = name + std::to_string(i) + "v" + std::to_string(data->tm_mon + 1) + "v" + std::to_string(data->tm_year + 1900) + ".txt";
                                plik.open(name.c_str(), std::ios::in);
                                std::cout << name << "\n";
                                if (!(plik.good()))
                                    objects[i + data->tm_wday + 5].setTexture(calendarblue);
                                if (plik.good())
                                {
                                    std::getline(plik, line);
                                    if (line == "red")
                                        objects[i + data->tm_wday + 5].setTexture(calendarred);
                                    if (line == "green")
                                        objects[i + data->tm_wday + 5].setTexture(calendargreen);
                                }
                                plik.close();
                            }
                            for (int i = 1; i <= dni; i++)
                                teksty[i + data->tm_wday + 5].setString(std::to_string(i));
                        }
                        teksty[46].setString(calendarmonth);
                    }
                    if (pozycja.x >= 143 && pozycja.x <= 373 && pozycja.y >= 180 && pozycja.y <= 316) //pon1
                    {
                        if (objects[0].getTexture() == &calendarblue || objects[0].getTexture() == &calendargreen || objects[0].getTexture() == &calendarred)
                        {
                            if (data->tm_wday != 0)
                            {
                                dzien = 2 - data->tm_wday;
                                miesiac = data->tm_mon;
                                rok = data->tm_year;
                                change_state = true;
                                state = 1;
                                zkal = true;
                            }
                            else
                            {
                                dzien = 2 - 7;
                                miesiac = data->tm_mon;
                                rok = data->tm_year;
                                change_state = true;
                                state = 1;
                                zkal = true;
                            }
                        }
                    }
                    if (pozycja.x >= 373 && pozycja.x <= 603 && pozycja.y >= 180 && pozycja.y <= 316) //wt1
                    {
                        if (objects[1].getTexture() == &calendarblue || objects[1].getTexture() == &calendargreen || objects[1].getTexture() == &calendarred)
                        {
                            if (data->tm_wday != 0)
                            {
                                dzien = 3 - data->tm_wday;
                                miesiac = data->tm_mon;
                                rok = data->tm_year;
                                change_state = true;
                                state = 1;
                                zkal = true;
                            }
                            else
                            {
                                dzien = 3 - 7;
                                miesiac = data->tm_mon;
                                rok = data->tm_year;
                                change_state = true;
                                state = 1;
                                zkal = true;
                            }
                        }
                    }
                    if (pozycja.x >= 603 && pozycja.x <= 833 && pozycja.y >= 180 && pozycja.y <= 316) //sr1
                    {
                        if (objects[2].getTexture() == &calendarblue || objects[2].getTexture() == &calendargreen || objects[2].getTexture() == &calendarred)
                        {
                            if (data->tm_wday != 0)
                            {
                                dzien = 4 - data->tm_wday;
                                miesiac = data->tm_mon;
                                rok = data->tm_year;
                                change_state = true;
                                state = 1;
                                zkal = true;
                            }
                            else
                            {
                                dzien = 4 - 7;
                                miesiac = data->tm_mon;
                                rok = data->tm_year;
                                change_state = true;
                                state = 1;
                                zkal = true;
                            }
                        }
                    }
                    if (pozycja.x >= 833 && pozycja.x <= 1063 && pozycja.y >= 180 && pozycja.y <= 316) //czw1
                    {
                        if (objects[3].getTexture() == &calendarblue || objects[3].getTexture() == &calendargreen || objects[3].getTexture() == &calendarred)
                        {
                            if (data->tm_wday != 0)
                            {
                                dzien = 5 - data->tm_wday;
                                miesiac = data->tm_mon;
                                rok = data->tm_year;
                                change_state = true;
                                state = 1;
                                zkal = true;
                            }
                            else
                            {
                                dzien = 5 - 7;
                                miesiac = data->tm_mon;
                                rok = data->tm_year;
                                change_state = true;
                                state = 1;
                                zkal = true;
                            }
                        }
                    }
                    if (pozycja.x >= 1063 && pozycja.x <= 1293 && pozycja.y >= 180 && pozycja.y <= 316) //pt1
                    {
                        if (objects[4].getTexture() == &calendarblue || objects[4].getTexture() == &calendargreen || objects[4].getTexture() == &calendarred)
                        {
                            if (data->tm_wday != 0)
                            {
                                dzien = 6 - data->tm_wday;
                                miesiac = data->tm_mon;
                                rok = data->tm_year;
                                change_state = true;
                                state = 1;
                                zkal = true;
                            }
                            else
                            {
                                dzien = 6 - 7;
                                miesiac = data->tm_mon;
                                rok = data->tm_year;
                                change_state = true;
                                state = 1;
                                zkal = true;
                            }
                        }
                    }
                    if (pozycja.x >= 1293 && pozycja.x <= 1523 && pozycja.y >= 180 && pozycja.y <= 316) //sob1
                    {
                        if (objects[5].getTexture() == &calendarblue || objects[5].getTexture() == &calendargreen || objects[5].getTexture() == &calendarred)
                        {
                            if (data->tm_wday != 0)
                            {
                                dzien = 7 - data->tm_wday;
                                miesiac = data->tm_mon;
                                rok = data->tm_year;
                                change_state = true;
                                state = 1;
                                zkal = true;
                            }
                            else
                            {
                                dzien = 7 - 7;
                                miesiac = data->tm_mon;
                                rok = data->tm_year;
                                change_state = true;
                                state = 1;
                                zkal = true;
                            }
                        }
                    }
                    if (pozycja.x >= 1523 && pozycja.x <= 1753 && pozycja.y >= 180 && pozycja.y <= 316) //nd1
                    {
                        if (objects[6].getTexture() == &calendarblue || objects[6].getTexture() == &calendargreen || objects[6].getTexture() == &calendarred)
                        {
                            if (data->tm_wday != 0)
                            {
                                dzien = 8 - data->tm_wday;
                                miesiac = data->tm_mon;
                                rok = data->tm_year;
                                change_state = true;
                                state = 1;
                                zkal = true;
                            }
                            else
                            {
                                dzien = 8 - 7;
                                miesiac = data->tm_mon;
                                rok = data->tm_year;
                                change_state = true;
                                state = 1;
                                zkal = true;
                            }
                        }
                    }
                    if (pozycja.x >= 143 && pozycja.x <= 373 && pozycja.y >= 316 && pozycja.y <= 452) //pon2
                    {
                        if (objects[7].getTexture() == &calendarblue || objects[7].getTexture() == &calendargreen || objects[7].getTexture() == &calendarred)
                        {
                            if (data->tm_wday != 0)
                            {
                                dzien = 9 - data->tm_wday;
                                miesiac = data->tm_mon;
                                rok = data->tm_year;
                                change_state = true;
                                state = 1;
                                zkal = true;
                            }
                            else
                            {
                                dzien = 9 - 7;
                                miesiac = data->tm_mon;
                                rok = data->tm_year;
                                change_state = true;
                                state = 1;
                                zkal = true;
                            }
                        }
                    }
                    if (pozycja.x >= 373 && pozycja.x <= 603 && pozycja.y >= 316 && pozycja.y <= 452) //wt2
                    {
                        if (objects[8].getTexture() == &calendarblue || objects[8].getTexture() == &calendargreen || objects[8].getTexture() == &calendarred)
                        {
                            if (data->tm_wday != 0)
                            {
                                dzien = 10 - data->tm_wday;
                                miesiac = data->tm_mon;
                                rok = data->tm_year;
                                change_state = true;
                                state = 1;
                                zkal = true;
                            }
                            else
                            {
                                dzien = 10 - 7;
                                miesiac = data->tm_mon;
                                rok = data->tm_year;
                                change_state = true;
                                state = 1;
                                zkal = true;
                            }
                        }
                    }
                    if (pozycja.x >= 603 && pozycja.x <= 833 && pozycja.y >= 316 && pozycja.y <= 452) //sr2
                    {
                        if (objects[9].getTexture() == &calendarblue || objects[9].getTexture() == &calendargreen || objects[9].getTexture() == &calendarred)
                        {
                            if (data->tm_wday != 0)
                            {
                                dzien = 11 - data->tm_wday;
                                miesiac = data->tm_mon;
                                rok = data->tm_year;
                                change_state = true;
                                state = 1;
                                zkal = true;
                            }
                            else
                            {
                                dzien = 11 - 7;
                                miesiac = data->tm_mon;
                                rok = data->tm_year;
                                change_state = true;
                                state = 1;
                                zkal = true;
                            }
                        }
                    }
                    if (pozycja.x >= 833 && pozycja.x <= 1063 && pozycja.y >= 316 && pozycja.y <= 452) //czw2
                    {
                        if (objects[10].getTexture() == &calendarblue || objects[10].getTexture() == &calendargreen || objects[10].getTexture() == &calendarred)
                        {
                            if (data->tm_wday != 0)
                            {
                                dzien = 12 - data->tm_wday;
                                miesiac = data->tm_mon;
                                rok = data->tm_year;
                                change_state = true;
                                state = 1;
                                zkal = true;
                            }
                            else
                            {
                                dzien = 12 - 7;
                                miesiac = data->tm_mon;
                                rok = data->tm_year;
                                change_state = true;
                                state = 1;
                                zkal = true;
                            }
                        }
                    }
                    if (pozycja.x >= 1063 && pozycja.x <= 1293 && pozycja.y >= 316 && pozycja.y <= 452) //pt2
                    {
                        if (objects[11].getTexture() == &calendarblue || objects[11].getTexture() == &calendargreen || objects[11].getTexture() == &calendarred)
                        {
                            if (data->tm_wday != 0)
                            {
                                dzien = 13 - data->tm_wday;
                                miesiac = data->tm_mon;
                                rok = data->tm_year;
                                change_state = true;
                                state = 1;
                                zkal = true;
                            }
                            else
                            {
                                dzien = 13 - 7;
                                miesiac = data->tm_mon;
                                rok = data->tm_year;
                                change_state = true;
                                state = 1;
                                zkal = true;
                            }
                        }
                    }
                    if (pozycja.x >= 1293 && pozycja.x <= 1523 && pozycja.y >= 316 && pozycja.y <= 452) //sob2
                    {
                        if (objects[12].getTexture() == &calendarblue || objects[12].getTexture() == &calendargreen || objects[12].getTexture() == &calendarred)
                        {
                            if (data->tm_wday != 0)
                            {
                                dzien = 14 - data->tm_wday;
                                miesiac = data->tm_mon;
                                rok = data->tm_year;
                                change_state = true;
                                state = 1;
                                zkal = true;
                            }
                            else
                            {
                                dzien = 14 - 7;
                                miesiac = data->tm_mon;
                                rok = data->tm_year;
                                change_state = true;
                                state = 1;
                                zkal = true;
                            }
                        }
                    }
                    if (pozycja.x >= 1523 && pozycja.x <= 1753 && pozycja.y >= 316 && pozycja.y <= 452) //nd2
                    {
                        if (objects[13].getTexture() == &calendarblue || objects[13].getTexture() == &calendargreen || objects[13].getTexture() == &calendarred)
                        {
                            if (data->tm_wday != 0)
                            {
                                dzien = 15 - data->tm_wday;
                                miesiac = data->tm_mon;
                                rok = data->tm_year;
                                change_state = true;
                                state = 1;
                                zkal = true;
                            }
                            else
                            {
                                dzien = 15 - 7;
                                miesiac = data->tm_mon;
                                rok = data->tm_year;
                                change_state = true;
                                state = 1;
                                zkal = true;
                            }
                        }
                    }
                    if (pozycja.x >= 143 && pozycja.x <= 373 && pozycja.y >= 452 && pozycja.y <= 588) //pon3
                    {
                        if (objects[14].getTexture() == &calendarblue || objects[14].getTexture() == &calendargreen || objects[14].getTexture() == &calendarred)
                        {
                            if (data->tm_wday != 0)
                            {
                                dzien = 16 - data->tm_wday;
                                miesiac = data->tm_mon;
                                rok = data->tm_year;
                                change_state = true;
                                state = 1;
                                zkal = true;
                            }
                            else
                            {
                                dzien = 16 - 7;
                                miesiac = data->tm_mon;
                                rok = data->tm_year;
                                change_state = true;
                                state = 1;
                                zkal = true;
                            }
                        }
                    }
                    if (pozycja.x >= 373 && pozycja.x <= 603 && pozycja.y >= 452 && pozycja.y <= 588) //wt3
                    {
                        if (objects[15].getTexture() == &calendarblue || objects[15].getTexture() == &calendargreen || objects[15].getTexture() == &calendarred)
                        {
                            if (data->tm_wday != 0)
                            {
                                dzien = 17 - data->tm_wday;
                                miesiac = data->tm_mon;
                                rok = data->tm_year;
                                change_state = true;
                                state = 1;
                                zkal = true;
                            }
                            else
                            {
                                dzien = 17 - 7;
                                miesiac = data->tm_mon;
                                rok = data->tm_year;
                                change_state = true;
                                state = 1;
                                zkal = true;
                            }
                        }
                    }
                    if (pozycja.x >= 603 && pozycja.x <= 833 && pozycja.y >= 452 && pozycja.y <= 588) //sr3
                    {
                        if (objects[16].getTexture() == &calendarblue || objects[16].getTexture() == &calendargreen || objects[16].getTexture() == &calendarred)
                        {
                            if (data->tm_wday != 0)
                            {
                                dzien = 18 - data->tm_wday;
                                miesiac = data->tm_mon;
                                rok = data->tm_year;
                                change_state = true;
                                state = 1;
                                zkal = true;
                            }
                            else
                            {
                                dzien = 18 - 7;
                                miesiac = data->tm_mon;
                                rok = data->tm_year;
                                change_state = true;
                                state = 1;
                                zkal = true;
                            }
                        }
                    }
                    if (pozycja.x >= 833 && pozycja.x <= 1063 && pozycja.y >= 452 && pozycja.y <= 588) //czw3
                    {
                        if (objects[17].getTexture() == &calendarblue || objects[17].getTexture() == &calendargreen || objects[17].getTexture() == &calendarred)
                        {
                            if (data->tm_wday != 0)
                            {
                                dzien = 19 - data->tm_wday;
                                miesiac = data->tm_mon;
                                rok = data->tm_year;
                                change_state = true;
                                state = 1;
                                zkal = true;
                            }
                            else
                            {
                                dzien = 19 - 7;
                                miesiac = data->tm_mon;
                                rok = data->tm_year;
                                change_state = true;
                                state = 1;
                                zkal = true;
                            }
                        }
                    }
                    if (pozycja.x >= 1063 && pozycja.x <= 1293 && pozycja.y >= 452 && pozycja.y <= 588) //pt3
                    {
                        if (objects[18].getTexture() == &calendarblue || objects[18].getTexture() == &calendargreen || objects[18].getTexture() == &calendarred)
                        {
                            if (data->tm_wday != 0)
                            {
                                dzien = 20 - data->tm_wday;
                                miesiac = data->tm_mon;
                                rok = data->tm_year;
                                change_state = true;
                                state = 1;
                                zkal = true;
                            }
                            else
                            {
                                dzien = 20 - 7;
                                miesiac = data->tm_mon;
                                rok = data->tm_year;
                                change_state = true;
                                state = 1;
                                zkal = true;
                            }
                        }
                    }
                    if (pozycja.x >= 1293 && pozycja.x <= 1523 && pozycja.y >= 452 && pozycja.y <= 588) //sob3
                    {
                        if (objects[19].getTexture() == &calendarblue || objects[19].getTexture() == &calendargreen || objects[19].getTexture() == &calendarred)
                        {
                            if (data->tm_wday != 0)
                            {
                                dzien = 21 - data->tm_wday;
                                miesiac = data->tm_mon;
                                rok = data->tm_year;
                                change_state = true;
                                state = 1;
                                zkal = true;
                            }
                            else
                            {
                                dzien = 21 - 7;
                                miesiac = data->tm_mon;
                                rok = data->tm_year;
                                change_state = true;
                                state = 1;
                                zkal = true;
                            }
                        }
                    }
                    if (pozycja.x >= 1523 && pozycja.x <= 1753 && pozycja.y >= 452 && pozycja.y <= 588) //nd3
                    {
                        if (objects[20].getTexture() == &calendarblue || objects[20].getTexture() == &calendargreen || objects[20].getTexture() == &calendarred)
                        {
                            if (data->tm_wday != 0)
                            {
                                dzien = 22 - data->tm_wday;
                                miesiac = data->tm_mon;
                                rok = data->tm_year;
                                change_state = true;
                                state = 1;
                                zkal = true;
                            }
                            else
                            {
                                dzien = 22 - 7;
                                miesiac = data->tm_mon;
                                rok = data->tm_year;
                                change_state = true;
                                state = 1;
                                zkal = true;
                            }
                        }
                    }
                    if (pozycja.x >= 143 && pozycja.x <= 373 && pozycja.y >= 588 && pozycja.y <= 724) //pon4
                    {
                        if (objects[21].getTexture() == &calendarblue || objects[21].getTexture() == &calendargreen || objects[21].getTexture() == &calendarred)
                        {
                            if (data->tm_wday != 0)
                            {
                                dzien = 23 - data->tm_wday;
                                miesiac = data->tm_mon;
                                rok = data->tm_year;
                                change_state = true;
                                state = 1;
                                zkal = true;
                            }
                            else
                            {
                                dzien = 23 - 7;
                                miesiac = data->tm_mon;
                                rok = data->tm_year;
                                change_state = true;
                                state = 1;
                                zkal = true;
                            }
                        }
                    }
                    if (pozycja.x >= 373 && pozycja.x <= 603 && pozycja.y >= 588 && pozycja.y <= 724) //wt4
                    {
                        if (objects[22].getTexture() == &calendarblue || objects[22].getTexture() == &calendargreen || objects[22].getTexture() == &calendarred)
                        {
                            if (data->tm_wday != 0)
                            {
                                dzien = 24 - data->tm_wday;
                                miesiac = data->tm_mon;
                                rok = data->tm_year;
                                change_state = true;
                                state = 1;
                                zkal = true;
                            }
                            else
                            {
                                dzien = 24 - 7;
                                miesiac = data->tm_mon;
                                rok = data->tm_year;
                                change_state = true;
                                state = 1;
                                zkal = true;
                            }
                        }
                    }
                    if (pozycja.x >= 603 && pozycja.x <= 833 && pozycja.y >= 588 && pozycja.y <= 724) //sr4
                    {
                        if (objects[23].getTexture() == &calendarblue || objects[23].getTexture() == &calendargreen || objects[23].getTexture() == &calendarred)
                        {
                            if (data->tm_wday != 0)
                            {
                                dzien = 25 - data->tm_wday;
                                miesiac = data->tm_mon;
                                rok = data->tm_year;
                                change_state = true;
                                state = 1;
                                zkal = true;
                            }
                            else
                            {
                                dzien = 25 - 7;
                                miesiac = data->tm_mon;
                                rok = data->tm_year;
                                change_state = true;
                                state = 1;
                                zkal = true;
                            }
                        }
                    }
                    if (pozycja.x >= 833 && pozycja.x <= 1063 && pozycja.y >= 588 && pozycja.y <= 724) //czw4
                    {
                        if (objects[24].getTexture() == &calendarblue || objects[24].getTexture() == &calendargreen || objects[24].getTexture() == &calendarred)
                        {
                            if (data->tm_wday != 0)
                            {
                                dzien = 26 - data->tm_wday;
                                miesiac = data->tm_mon;
                                rok = data->tm_year;
                                change_state = true;
                                state = 1;
                                zkal = true;
                            }
                            else
                            {
                                dzien = 26 - 7;
                                miesiac = data->tm_mon;
                                rok = data->tm_year;
                                change_state = true;
                                state = 1;
                                zkal = true;
                            }
                        }
                    }
                    if (pozycja.x >= 1063 && pozycja.x <= 1293 && pozycja.y >= 588 && pozycja.y <= 724) //pt4
                    {
                        if (objects[25].getTexture() == &calendarblue || objects[25].getTexture() == &calendargreen || objects[25].getTexture() == &calendarred)
                        {
                            if (data->tm_wday != 0)
                            {
                                dzien = 27 - data->tm_wday;
                                miesiac = data->tm_mon;
                                rok = data->tm_year;
                                change_state = true;
                                state = 1;
                                zkal = true;
                            }
                            else
                            {
                                dzien = 27 - 7;
                                miesiac = data->tm_mon;
                                rok = data->tm_year;
                                change_state = true;
                                state = 1;
                                zkal = true;
                            }
                        }
                    }
                    if (pozycja.x >= 1293 && pozycja.x <= 1523 && pozycja.y >= 588 && pozycja.y <= 724) //sob4
                    {
                        if (objects[26].getTexture() == &calendarblue || objects[26].getTexture() == &calendargreen || objects[26].getTexture() == &calendarred)
                        {
                            if (data->tm_wday != 0)
                            {
                                dzien = 28 - data->tm_wday;
                                miesiac = data->tm_mon;
                                rok = data->tm_year;
                                change_state = true;
                                state = 1;
                                zkal = true;
                            }
                            else
                            {
                                dzien = 28 - 7;
                                miesiac = data->tm_mon;
                                rok = data->tm_year;
                                change_state = true;
                                state = 1;
                                zkal = true;
                            }
                        }
                    }
                    if (pozycja.x >= 1523 && pozycja.x <= 1753 && pozycja.y >= 588 && pozycja.y <= 724) //nd4
                    {
                        if (objects[27].getTexture() == &calendarblue || objects[27].getTexture() == &calendargreen || objects[27].getTexture() == &calendarred)
                        {
                            if (data->tm_wday != 0)
                            {
                                dzien = 29 - data->tm_wday;
                                miesiac = data->tm_mon;
                                rok = data->tm_year;
                                change_state = true;
                                state = 1;
                                zkal = true;
                            }
                            else
                            {
                                dzien = 29 - 7;
                                miesiac = data->tm_mon;
                                rok = data->tm_year;
                                change_state = true;
                                state = 1;
                                zkal = true;
                            }
                        }
                    }
                    if (pozycja.x >= 143 && pozycja.x <= 373 && pozycja.y >= 724 && pozycja.y <= 860) //pon5
                    {
                        if (objects[28].getTexture() == &calendarblue || objects[28].getTexture() == &calendargreen || objects[28].getTexture() == &calendarred)
                        {
                            if (data->tm_wday != 0)
                            {
                                dzien = 30 - data->tm_wday;
                                miesiac = data->tm_mon;
                                rok = data->tm_year;
                                change_state = true;
                                state = 1;
                                zkal = true;
                            }
                            else
                            {
                                dzien = 30 - 7;
                                miesiac = data->tm_mon;
                                rok = data->tm_year;
                                change_state = true;
                                state = 1;
                                zkal = true;
                            }
                        }
                    }
                    if (pozycja.x >= 373 && pozycja.x <= 603 && pozycja.y >= 724 && pozycja.y <= 860) //wt5
                    {
                        if (objects[29].getTexture() == &calendarblue || objects[29].getTexture() == &calendargreen || objects[29].getTexture() == &calendarred)
                        {
                            if (data->tm_wday != 0)
                            {
                                dzien = 31 - data->tm_wday;
                                miesiac = data->tm_mon;
                                rok = data->tm_year;
                                change_state = true;
                                state = 1;
                                zkal = true;
                            }
                            else
                            {
                                dzien = 31 - 7;
                                miesiac = data->tm_mon;
                                rok = data->tm_year;
                                change_state = true;
                                state = 1;
                                zkal = true;
                            }
                        }
                    }
                    if (pozycja.x >= 603 && pozycja.x <= 833 && pozycja.y >= 724 && pozycja.y <= 860) //sr5
                    {
                        if (objects[30].getTexture() == &calendarblue || objects[30].getTexture() == &calendargreen || objects[30].getTexture() == &calendarred)
                        {
                            if (data->tm_wday != 0)
                            {
                                dzien = 32 - data->tm_wday;
                                miesiac = data->tm_mon;
                                rok = data->tm_year;
                                change_state = true;
                                state = 1;
                                zkal = true;
                            }
                            else
                            {
                                dzien = 32 - 7;
                                miesiac = data->tm_mon;
                                rok = data->tm_year;
                                change_state = true;
                                state = 1;
                                zkal = true;
                            }
                        }
                    }
                    if (pozycja.x >= 833 && pozycja.x <= 1063 && pozycja.y >= 724 && pozycja.y <= 860) //czw5
                    {
                        if (objects[31].getTexture() == &calendarblue || objects[31].getTexture() == &calendargreen || objects[31].getTexture() == &calendarred)
                        {
                            if (data->tm_wday != 0)
                            {
                                dzien = 33 - data->tm_wday;
                                miesiac = data->tm_mon;
                                rok = data->tm_year;
                                change_state = true;
                                state = 1;
                                zkal = true;
                            }
                            else
                            {
                                dzien = 33 - 7;
                                miesiac = data->tm_mon;
                                rok = data->tm_year;
                                change_state = true;
                                state = 1;
                                zkal = true;
                            }
                        }
                    }
                    if (pozycja.x >= 1063 && pozycja.x <= 1293 && pozycja.y >= 724 && pozycja.y <= 860) //pt5
                    {
                        if (objects[32].getTexture() == &calendarblue || objects[32].getTexture() == &calendargreen || objects[32].getTexture() == &calendarred)
                        {
                            if (data->tm_wday != 0)
                            {
                                dzien = 34 - data->tm_wday;
                                miesiac = data->tm_mon;
                                rok = data->tm_year;
                                change_state = true;
                                state = 1;
                                zkal = true;
                            }
                            else
                            {
                                dzien = 34 - 7;
                                miesiac = data->tm_mon;
                                rok = data->tm_year;
                                change_state = true;
                                state = 1;
                                zkal = true;
                            }
                        }
                    }
                    if (pozycja.x >= 1293 && pozycja.x <= 1523 && pozycja.y >= 724 && pozycja.y <= 860) //sob5
                    {
                        if (objects[33].getTexture() == &calendarblue || objects[33].getTexture() == &calendargreen || objects[33].getTexture() == &calendarred)
                        {
                            if (data->tm_wday != 0)
                            {
                                dzien = 35 - data->tm_wday;
                                miesiac = data->tm_mon;
                                rok = data->tm_year;
                                change_state = true;
                                state = 1;
                                zkal = true;
                            }
                            else
                            {
                                dzien = 35 - 7;
                                miesiac = data->tm_mon;
                                rok = data->tm_year;
                                change_state = true;
                                state = 1;
                                zkal = true;
                            }
                        }
                    }
                    if (pozycja.x >= 1523 && pozycja.x <= 1753 && pozycja.y >= 724 && pozycja.y <= 860) //nd5
                    {
                        if (objects[34].getTexture() == &calendarblue || objects[34].getTexture() == &calendargreen || objects[34].getTexture() == &calendarred)
                        {
                            if (data->tm_wday != 0)
                            {
                                dzien = 36 - data->tm_wday;
                                miesiac = data->tm_mon;
                                rok = data->tm_year;
                                change_state = true;
                                state = 1;
                                zkal = true;
                            }
                            else
                            {
                                dzien = 36 - 7;
                                miesiac = data->tm_mon;
                                rok = data->tm_year;
                                change_state = true;
                                state = 1;
                                zkal = true;
                            }
                        }
                    }
                    if (pozycja.x >= 143 && pozycja.x <= 373 && pozycja.y >= 724 && pozycja.y <= 860) //pon6
                    {
                        if (objects[35].getTexture() == &calendarblue || objects[35].getTexture() == &calendargreen || objects[35].getTexture() == &calendarred)
                        {
                            if (data->tm_wday != 0)
                            {
                                dzien = 37 - data->tm_wday;
                                miesiac = data->tm_mon;
                                rok = data->tm_year;
                                change_state = true;
                                state = 1;
                                zkal = true;
                            }
                            else
                            {
                                dzien = 37 - 7;
                                miesiac = data->tm_mon;
                                rok = data->tm_year;
                                change_state = true;
                                state = 1;
                                zkal = true;
                            }
                        }
                    }
                    if (pozycja.x >= 373 && pozycja.x <= 603 && pozycja.y >= 724 && pozycja.y <= 860) //wt6
                    {
                        if (objects[36].getTexture() == &calendarblue || objects[36].getTexture() == &calendargreen || objects[36].getTexture() == &calendarred)
                        {
                            if (data->tm_wday != 0)
                            {
                                dzien = 38 - data->tm_wday;
                                miesiac = data->tm_mon;
                                rok = data->tm_year;
                                change_state = true;
                                state = 1;
                                zkal = true;
                            }
                            else
                            {
                                dzien = 38 - 7;
                                miesiac = data->tm_mon;
                                rok = data->tm_year;
                                change_state = true;
                                state = 1;
                                zkal = true;
                            }
                        }
                    }
                    if (pozycja.x >= 603 && pozycja.x <= 833 && pozycja.y >= 724 && pozycja.y <= 860) //sr6
                    {
                        if (objects[37].getTexture() == &calendarblue || objects[37].getTexture() == &calendargreen || objects[37].getTexture() == &calendarred)
                        {
                            if (data->tm_wday != 0)
                            {
                                dzien = 39 - data->tm_wday;
                                miesiac = data->tm_mon;
                                rok = data->tm_year;
                                change_state = true;
                                state = 1;
                                zkal = true;
                            }
                            else
                            {
                                dzien = 39 - 7;
                                miesiac = data->tm_mon;
                                rok = data->tm_year;
                                change_state = true;
                                state = 1;
                                zkal = true;
                            }
                        }
                    }
                    if (pozycja.x >= 833 && pozycja.x <= 1063 && pozycja.y >= 724 && pozycja.y <= 860) //czw6
                    {
                        if (objects[38].getTexture() == &calendarblue || objects[38].getTexture() == &calendargreen || objects[38].getTexture() == &calendarred)
                        {
                            if (data->tm_wday != 0)
                            {
                                dzien = 40 - data->tm_wday;
                                miesiac = data->tm_mon;
                                rok = data->tm_year;
                                change_state = true;
                                state = 1;
                                zkal = true;
                            }
                            else
                            {
                                dzien = 40 - 7;
                                miesiac = data->tm_mon;
                                rok = data->tm_year;
                                change_state = true;
                                state = 1;
                                zkal = true;
                            }
                        }
                    }
                    if (pozycja.x >= 1063 && pozycja.x <= 1293 && pozycja.y >= 724 && pozycja.y <= 860) //pt6
                    {
                        if (objects[39].getTexture() == &calendarblue || objects[39].getTexture() == &calendargreen || objects[39].getTexture() == &calendarred)
                        {
                            if (data->tm_wday != 0)
                            {
                                dzien = 41 - data->tm_wday;
                                miesiac = data->tm_mon;
                                rok = data->tm_year;
                                change_state = true;
                                state = 1;
                                zkal = true;
                            }
                            else
                            {
                                dzien = 41 - 7;
                                miesiac = data->tm_mon;
                                rok = data->tm_year;
                                change_state = true;
                                state = 1;
                                zkal = true;
                            }
                        }
                    }
                    if (pozycja.x >= 1293 && pozycja.x <= 1523 && pozycja.y >= 724 && pozycja.y <= 860) //sob6
                    {
                        if (objects[40].getTexture() == &calendarblue || objects[40].getTexture() == &calendargreen || objects[40].getTexture() == &calendarred)
                        {
                            if (data->tm_wday != 0)
                            {
                                dzien = 42 - data->tm_wday;
                                miesiac = data->tm_mon;
                                rok = data->tm_year;
                                change_state = true;
                                state = 1;
                                zkal = true;
                            }
                            else
                            {
                                dzien = 42 - 7;
                                miesiac = data->tm_mon;
                                rok = data->tm_year;
                                change_state = true;
                                state = 1;
                                zkal = true;
                            }
                        }
                    }
                    if (pozycja.x >= 1523 && pozycja.x <= 1753 && pozycja.y >= 724 && pozycja.y <= 860) //nd6
                    {
                        if (objects[41].getTexture() == &calendarblue || objects[41].getTexture() == &calendargreen || objects[41].getTexture() == &calendarred)
                        {
                            if (data->tm_wday != 0)
                            {
                                dzien = 43 - data->tm_wday;
                                miesiac = data->tm_mon;
                                rok = data->tm_year;
                                change_state = true;
                                state = 1;
                                zkal = true;
                            }
                            else
                            {
                                dzien = 43 - 7;
                                miesiac = data->tm_mon;
                                rok = data->tm_year;
                                change_state = true;
                                state = 1;
                                zkal = true;
                            }
                        }
                    }
                }
                else if (state == 1) //board
                {
                    if (pozycja.x >= 255 && pozycja.x <= 505 && pozycja.y >= 30 && pozycja.y <= 80 && !(adding)) //calendar
                    {
                        std::cout << "przycisk calendar \n";
                        state = 0;
                        change_state = true;
                    }
                    if (pozycja.x >= 631 && pozycja.x <= 886 && pozycja.y >= 30 && pozycja.y <= 80 && !(adding)) //board
                    {
                        std::cout << "przycisk menu \n";
                        state = -1;
                        change_state = true;
                    }
                    if (pozycja.x >= 1014 && pozycja.x <= 1269 && pozycja.y >= 30 && pozycja.y <= 80 && !(adding)) //quest list
                    {
                        std::cout << "przycisk quest list \n";
                        state = 2;
                        change_state = true;
                    }
                    if (pozycja.x >= 1395 && pozycja.x <= 1650 && pozycja.y >= 30 && pozycja.y <= 80 && !(adding)) //quest log
                    {
                        std::cout << "przycisk quest log \n";
                        state = 3;
                        change_state = true;
                    }
                    if (pozycja.x >= 30 && pozycja.x <= 80 && pozycja.y >= 180 && pozycja.y <= 230 && !(adding)) //przesowanie w gore
                    {
                        if (przesownik >= 3)
                        {
                            /*for (int i = 12; i < 21; i++)
                            {
                                objects[i].setTexture(free);
                                teksty[i - 12].setString("");
                            }*/

                            przesownik -= 3;

                            name = "board/";
                            name = name + std::to_string(data->tm_mday) + "a" + std::to_string(data->tm_mon + 1) + "a" + std::to_string(data->tm_year + 1900);
                            std::cout << name << "\n";
                            if (_mkdir(name.c_str()))
                            {
                                for (int i = 12; i < 21; i++)
                                {
                                    line = "";
                                    note = name + "/" + std::to_string(i - 11 + przesownik) + ".txt";
                                    plik.open(note.c_str(), std::ios::in);
                                    std::cout << note << "\n";
                                    if (plik.good())
                                    {
                                        helper = "";
                                        std::getline(plik, line);
                                        std::cout << line ;
                                        if (line == "weight")
                                            objects[i].setTexture(boardweight);
                                        if (line == "book")
                                            objects[i].setTexture(boardbook);
                                        if (line == "health")
                                            objects[i].setTexture(boardhealth);
                                        if (line == "meat")
                                            objects[i].setTexture(boardmeat);
                                        while (getline(plik, line))
                                        {

                                            std::cout << helper << "\n";
                                            helper = helper + line + "\n";
                                            teksty[i - 12].setString(helper);
                                        }
                                    }
                                    else
                                    {
                                        objects[i].setTexture(free);
                                        teksty[i - 12].setString("");
                                    }
                                    plik.close();
                                    //tekstury obrazkow
                                }
                                //teksty[0].setString("aadada");
                            }
                            else
                            {
                                _rmdir(name.c_str());
                                
                            }
                        }
                    }
                    if (pozycja.x >= 30 && pozycja.x <= 80 && pozycja.y >= 930 && pozycja.y <= 980 && !(adding)) //przesowanie w dol
                    {
                        /*for (int i = 12; i < 21; i++)
                        {
                            objects[i].setTexture(free);
                            teksty[i - 12].setString("");
                        }*/

                        przesownik += 3;

                        name = "board/";
                        name = name + std::to_string(data->tm_mday) + "a" + std::to_string(data->tm_mon + 1) + "a" + std::to_string(data->tm_year + 1900);
                        std::cout << name << "\n";
                        if (_mkdir(name.c_str()))
                        {
                            for (int i = 12; i < 21; i++)
                            {
                                line = "";
                                note = name + "/" + std::to_string(i - 11 + przesownik) + ".txt";
                                plik.open(note.c_str(), std::ios::in);
                                std::cout << note << "\n";
                                if (plik.good())
                                {
                                    helper = "";
                                    std::getline(plik, line);
                                    std::cout << line;
                                    if (line == "weight")
                                        objects[i].setTexture(boardweight);
                                    if (line == "book")
                                        objects[i].setTexture(boardbook);
                                    if (line == "health")
                                        objects[i].setTexture(boardhealth);
                                    if (line == "meat")
                                        objects[i].setTexture(boardmeat);
                                    while (getline(plik, line))
                                    {

                                        std::cout << helper << "\n";
                                        helper = helper + line + "\n";
                                        teksty[i - 12].setString(helper);
                                    }
                                }
                                else
                                {
                                    objects[i].setTexture(free);
                                    teksty[i - 12].setString("");
                                }
                                plik.close();
                                //tekstury obrazkow
                            }
                            //teksty[0].setString("aadada");
                        }
                        else
                        {
                            _rmdir(name.c_str());
                        }
                    }
                    if (pozycja.x >= 1600 && pozycja.x <= 1850 && pozycja.y >= 200 && pozycja.y <= 450 && !(adding)) //dodawanie z prawa 1
                    {
                        completed = false;
                        licznik_umieszczanie = 1;
                        if (_mkdir(name.c_str()))
                        {
                            while (!(completed))
                            {
                                note = name + "/" + std::to_string(licznik_umieszczanie) + ".txt";
                                plik.open(note.c_str(), std::ios::in);
                                if (plik.good())
                                {
                                    plik.close();
                                }
                                else
                                {
                                    plik.close();
                                    plik.open(note.c_str(), std::ios::out);
                                    plik << "weight\nprzejdz 10 km";
                                    completed = true;
                                    plik.close();
                                }
                                licznik_umieszczanie += 1;
                            }
                        }
                        else
                        {
                            note = name + "/1.txt";
                            plik.open(note.c_str(), std::ios::out);
                            plik << "weight\nprzejdz 10 km";
                            completed = true;
                            plik.close();
                        }
                       
                        for (int i = 12; i < 21; i++)
                        {
                            line = "";
                            note = name + "/" + std::to_string(i - 11 + przesownik) + ".txt";
                            plik.open(note.c_str(), std::ios::in);
                            std::cout << note << "\n";
                            if (plik.good())
                            {
                                helper = "";
                                std::getline(plik, line);
                                std::cout << line;
                                if (line == "weight")
                                    objects[i].setTexture(boardweight);
                                if (line == "book")
                                    objects[i].setTexture(boardbook);
                                if (line == "health")
                                    objects[i].setTexture(boardhealth);
                                if (line == "meat")
                                    objects[i].setTexture(boardmeat);
                                while (getline(plik, line))
                                {

                                    std::cout << helper << "\n";
                                    helper = helper + line + "\n";
                                    teksty[i - 12].setString(helper);
                                }
                            }
                            else
                            {
                                objects[i].setTexture(free);
                                teksty[i - 12].setString("");
                            }
                            plik.close();
                            //tekstury obrazkow
                        }
                    }
                    if (pozycja.x >= 1600 && pozycja.x <= 1850 && pozycja.y >= 485 && pozycja.y <= 735 && !(adding)) //dodawanie z prawa 2
                    {
                        completed = false;
                        licznik_umieszczanie = 1;
                        if (_mkdir(name.c_str()))
                        {
                            while (!(completed))
                            {
                                note = name + "/" + std::to_string(licznik_umieszczanie) + ".txt";
                                plik.open(note.c_str(), std::ios::in);
                                if (plik.good())
                                {
                                    plik.close();
                                }
                                else
                                {
                                    plik.close();
                                    plik.open(note.c_str(), std::ios::out);
                                    plik << "book\nnaucz sie czegos\nnowego";
                                    completed = true;
                                    plik.close();
                                }
                                licznik_umieszczanie += 1;
                            }
                        }
                        else
                        {
                            note = name + "/1.txt";
                            plik.open(note.c_str(), std::ios::out);
                            plik << "book\nnaucz sie czegos\nnowego";
                            completed = true;
                            plik.close();
                        }

                        for (int i = 12; i < 21; i++)
                        {
                            line = "";
                            note = name + "/" + std::to_string(i - 11 + przesownik) + ".txt";
                            plik.open(note.c_str(), std::ios::in);
                            std::cout << note << "\n";
                            if (plik.good())
                            {
                                helper = "";
                                std::getline(plik, line);
                                std::cout << line;
                                if (line == "weight")
                                    objects[i].setTexture(boardweight);
                                if (line == "book")
                                    objects[i].setTexture(boardbook);
                                if (line == "health")
                                    objects[i].setTexture(boardhealth);
                                if (line == "meat")
                                    objects[i].setTexture(boardmeat);
                                while (getline(plik, line))
                                {

                                    std::cout << helper << "\n";
                                    helper = helper + line + "\n";
                                    teksty[i - 12].setString(helper);
                                }
                            }
                            else
                            {
                                objects[i].setTexture(free);
                                teksty[i - 12].setString("");
                            }
                            plik.close();
                            //tekstury obrazkow
                        }
                    }
                    if (pozycja.x >= 1600 && pozycja.x <= 1850 && pozycja.y >= 770 && pozycja.y <= 1020 && !(adding)) //dodawanie z prawa 3
                    {
                        completed = false;
                        licznik_umieszczanie = 1;
                        if (_mkdir(name.c_str()))
                        {
                            while (!(completed))
                            {
                                note = name + "/" + std::to_string(licznik_umieszczanie) + ".txt";
                                plik.open(note.c_str(), std::ios::in);
                                if (plik.good())
                                {
                                    plik.close();
                                }
                                else
                                {
                                    plik.close();
                                    plik.open(note.c_str(), std::ios::out);
                                    plik << "health\nprzypomnienie o\nlekach";
                                    completed = true;
                                    plik.close();
                                }
                                licznik_umieszczanie += 1;
                            }
                        }
                        else
                        {
                            note = name + "/1.txt";
                            plik.open(note.c_str(), std::ios::out);
                            plik << "health\nprzypomnienie o\nlekach";
                            completed = true;
                            plik.close();
                        }

                        for (int i = 12; i < 21; i++)
                        {
                            line = "";
                            note = name + "/" + std::to_string(i - 11 + przesownik) + ".txt";
                            plik.open(note.c_str(), std::ios::in);
                            std::cout << note << "\n";
                            if (plik.good())
                            {
                                helper = "";
                                std::getline(plik, line);
                                std::cout << line;
                                if (line == "weight")
                                    objects[i].setTexture(boardweight);
                                if (line == "book")
                                    objects[i].setTexture(boardbook);
                                if (line == "health")
                                    objects[i].setTexture(boardhealth);
                                if (line == "meat")
                                    objects[i].setTexture(boardmeat);
                                while (getline(plik, line))
                                {

                                    std::cout << helper << "\n";
                                    helper = helper + line + "\n";
                                    teksty[i - 12].setString(helper);
                                }
                            }
                            else
                            {
                                objects[i].setTexture(free);
                                teksty[i - 12].setString("");
                            }
                            plik.close();
                            //tekstury obrazkow
                        }
                    }
                    if (pozycja.x >= 30 && pozycja.x <= 80 && pozycja.y >= 540 && pozycja.y <= 590 && !(adding)) //wysuniecie okna
                    {
                        adding = true;
                        addoner[4].setPosition(sf::Vector2f(825, 375));
                        addoner[0].setPosition(sf::Vector2f(840, 390));
                        addoner[1].setPosition(sf::Vector2f(840, 446));
                        addoner[2].setPosition(sf::Vector2f(840, 502));
                        addoner[3].setPosition(sf::Vector2f(840, 558));
                        licznik_wysokosc = 1;
                        playerInput = "";

                    }
                    if (pozycja.x >= 30 && pozycja.x <= 80 && pozycja.y >= 540 && pozycja.y <= 590 && texting) //zapis i chowanie okna
                    {
                        std::cout << note;
                        plik.open(note.c_str(), std::ios::out | std::ios::app);
                        helper = tekst.getString();
                        plik << helper;
                        plik.close();
                        addoner[0].setPosition(sf::Vector2f(2000, 1100));
                        addoner[1].setPosition(sf::Vector2f(2000, 1100));
                        addoner[2].setPosition(sf::Vector2f(2000, 1100));
                        addoner[3].setPosition(sf::Vector2f(2000, 1100));
                        addoner[4].setPosition(sf::Vector2f(2000, 1100));
                        tekst.setPosition(sf::Vector2f(2000, 1100));
                        
                        
                        std::cout << "przycisk menu \n";
                        state = 1;
                        change_state = true;
                        texting = false;
                        adding = false;

                    }
                    if (pozycja.x >= 840 && pozycja.x <= 1060 && pozycja.y >= 390 && pozycja.y <= 440 && adding && !(texting)) //wybor obrazek 1
                    {
                        //std::cout << "powiodlo sie";
                        addoner[0].setPosition(sf::Vector2f(840, 390));
                        addoner[1].setPosition(sf::Vector2f(2000, 1100));
                        addoner[2].setPosition(sf::Vector2f(2000, 1100));
                        addoner[3].setPosition(sf::Vector2f(2000, 1100));
                        texting = true;
                        tekst.setPosition(sf::Vector2f(840, 450));

                        completed = false;
                        licznik_umieszczanie = 1;
                        if (_mkdir(name.c_str()))
                        {
                            while (!(completed))
                            {
                                note = name + "/" + std::to_string(licznik_umieszczanie) + ".txt";
                                plik.open(note.c_str(), std::ios::in);
                                if (plik.good())
                                {
                                    plik.close();
                                }
                                else
                                {
                                    plik.close();
                                    plik.open(note.c_str(), std::ios::out);
                                    plik << "meat\n";
                                    completed = true;
                                    plik.close();
                                }
                                licznik_umieszczanie += 1;
                            }
                        }
                        else
                        {
                            note = name + "/1.txt";
                            plik.open(note.c_str(), std::ios::out);
                            plik << "meat\n";
                            completed = true;
                            plik.close();
                        }

                    }
                    if (pozycja.x >= 840 && pozycja.x <= 1060 && pozycja.y >= 446 && pozycja.y <= 496 && adding && !(texting)) //wybor obrazek 2
                    {
                        //std::cout << "powiodlo sie";
                        addoner[1].setPosition(sf::Vector2f(840, 390));
                        addoner[0].setPosition(sf::Vector2f(2000, 1100));
                        addoner[2].setPosition(sf::Vector2f(2000, 1100));
                        addoner[3].setPosition(sf::Vector2f(2000, 1100));
                        texting = true;
                        tekst.setPosition(sf::Vector2f(840, 450));

                        completed = false;
                        licznik_umieszczanie = 1;
                        if (_mkdir(name.c_str()))
                        {
                            while (!(completed))
                            {
                                note = name + "/" + std::to_string(licznik_umieszczanie) + ".txt";
                                plik.open(note.c_str(), std::ios::in);
                                if (plik.good())
                                {
                                    plik.close();
                                }
                                else
                                {
                                    plik.close();
                                    plik.open(note.c_str(), std::ios::out);
                                    plik << "health\n";
                                    completed = true;
                                    plik.close();
                                }
                                licznik_umieszczanie += 1;
                            }
                        }
                        else
                        {
                            note = name + "/1.txt";
                            plik.open(note.c_str(), std::ios::out);
                            plik << "health\n";
                            completed = true;
                            plik.close();
                        }
                    }
                    if (pozycja.x >= 840 && pozycja.x <= 1060 && pozycja.y >= 502 && pozycja.y <= 552 && adding && !(texting)) //wybor obrazek 3
                    {
                        //std::cout << "powiodlo sie";
                        addoner[2].setPosition(sf::Vector2f(840, 390));
                        addoner[1].setPosition(sf::Vector2f(2000, 1100));
                        addoner[0].setPosition(sf::Vector2f(2000, 1100));
                        addoner[3].setPosition(sf::Vector2f(2000, 1100));
                        texting = true;
                        tekst.setPosition(sf::Vector2f(840, 450));

                        completed = false;
                        licznik_umieszczanie = 1;
                        if (_mkdir(name.c_str()))
                        {
                            while (!(completed))
                            {
                                note = name + "/" + std::to_string(licznik_umieszczanie) + ".txt";
                                plik.open(note.c_str(), std::ios::in);
                                if (plik.good())
                                {
                                    plik.close();
                                }
                                else
                                {
                                    plik.close();
                                    plik.open(note.c_str(), std::ios::out);
                                    plik << "weight\n";
                                    completed = true;
                                    plik.close();
                                }
                                licznik_umieszczanie += 1;
                            }
                        }
                        else
                        {
                            note = name + "/1.txt";
                            plik.open(note.c_str(), std::ios::out);
                            plik << "weight\n";
                            completed = true;
                            plik.close();
                        }
                    }
                    if (pozycja.x >= 840 && pozycja.x <= 1060 && pozycja.y >= 558 && pozycja.y <= 608 && adding && !(texting)) //wybor obrazek 4
                    {
                        //std::cout << "powiodlo sie";
                        addoner[3].setPosition(sf::Vector2f(840, 390));
                        addoner[1].setPosition(sf::Vector2f(2000, 1100));
                        addoner[2].setPosition(sf::Vector2f(2000, 1100));
                        addoner[0].setPosition(sf::Vector2f(2000, 1100));
                        texting = true;
                        tekst.setPosition(sf::Vector2f(840, 450));

                        completed = false;
                        licznik_umieszczanie = 1;
                        if (_mkdir(name.c_str()))
                        {
                            while (!(completed))
                            {
                                note = name + "/" + std::to_string(licznik_umieszczanie) + ".txt";
                                plik.open(note.c_str(), std::ios::in);
                                if (plik.good())
                                {
                                    plik.close();
                                }
                                else
                                {
                                    plik.close();
                                    plik.open(note.c_str(), std::ios::out);
                                    plik << "book\n";
                                    completed = true;
                                    plik.close();
                                }
                                licznik_umieszczanie += 1;
                            }
                        }
                        else
                        {
                            note = name + "/1.txt";
                            plik.open(note.c_str(), std::ios::out);
                            plik << "book\n";
                            completed = true;
                            plik.close();
                        }
                    }
                    if (pozycja.x >= 110 && pozycja.x <= 360 && pozycja.y >= 200 && pozycja.y <= 450 && !(adding)) //zalicz zad 1
                    {
                        note = name + "/" + std::to_string(1 + przesownik) + ".txt";
                        remove(note.c_str());
                        state = 1;
                        change_state = true;
                    }
                    if (pozycja.x >= 410 && pozycja.x <= 660 && pozycja.y >= 200 && pozycja.y <= 450 && !(adding)) //zalicz zad 2
                    {
                        note = name + "/" + std::to_string(2 + przesownik) + ".txt";
                        remove(note.c_str());
                        state = 1;
                        change_state = true;
                    }
                    if (pozycja.x >= 710 && pozycja.x <= 960 && pozycja.y >= 200 && pozycja.y <= 450 && !(adding)) //zalicz zad 3
                    {
                        note = name + "/" + std::to_string(3 + przesownik) + ".txt";
                        remove(note.c_str());
                        state = 1;
                        change_state = true;
                    }
                    if (pozycja.x >= 110 && pozycja.x <= 360 && pozycja.y >= 485 && pozycja.y <= 735 && !(adding)) //zalicz zad 4
                    {
                        note = name + "/" + std::to_string(4 + przesownik) + ".txt";
                        remove(note.c_str());
                        state = 1;
                        change_state = true;
                    }
                    if (pozycja.x >= 410 && pozycja.x <= 660 && pozycja.y >= 485 && pozycja.y <= 735 && !(adding)) //zalicz zad 5
                    {
                        note = name + "/" + std::to_string(5 + przesownik) + ".txt";
                        remove(note.c_str());
                        state = 1;
                        change_state = true;
                    }
                    if (pozycja.x >= 710 && pozycja.x <= 960 && pozycja.y >= 485 && pozycja.y <= 735 && !(adding)) //zalicz zad 6
                    {
                        note = name + "/" + std::to_string(6 + przesownik) + ".txt";
                        remove(note.c_str());
                        state = 1;
                        change_state = true;
                    }
                    if (pozycja.x >= 110 && pozycja.x <= 360 && pozycja.y >= 770 && pozycja.y <= 1020 && !(adding)) //zalicz zad 7
                    {
                        note = name + "/" + std::to_string(7 + przesownik) + ".txt";
                        remove(note.c_str());
                        state = 1;
                        change_state = true;
                    }
                    if (pozycja.x >= 410 && pozycja.x <= 660 && pozycja.y >= 770 && pozycja.y <= 1020 && !(adding)) //zalicz zad 8
                    {
                        note = name + "/" + std::to_string(8 + przesownik) + ".txt";
                        remove(note.c_str());
                        state = 1;
                        change_state = true;
                    }
                    if (pozycja.x >= 710 && pozycja.x <= 960 && pozycja.y >= 770 && pozycja.y <= 1020 && !(adding)) //zalicz zad 9
                    {
                        note = name + "/" + std::to_string(9 + przesownik) + ".txt";
                        remove(note.c_str());
                        state = 1;
                        change_state = true;
                    }
                }
                else if (state == 2) //quest list
                {
                    if (pozycja.x >= 255 && pozycja.x <= 505 && pozycja.y >= 30 && pozycja.y <= 80) //calendar
                    {
                        std::cout << "przycisk calendar \n";
                        state = 0;
                        change_state = true;
                    }
                    if (pozycja.x >= 631 && pozycja.x <= 886 && pozycja.y >= 30 && pozycja.y <= 80) //board
                    {
                        std::cout << "przycisk board \n";
                        state = 1;
                        change_state = true;
                    }
                    if (pozycja.x >= 1014 && pozycja.x <= 1269 && pozycja.y >= 30 && pozycja.y <= 80) //quest list
                    {
                        std::cout << "przycisk menu \n";
                        state = -1;
                        change_state = true;
                    }
                    if (pozycja.x >= 1395 && pozycja.x <= 1650 && pozycja.y >= 30 && pozycja.y <= 80) //quest log
                    {
                        std::cout << "przycisk quest log \n";
                        state = 3;
                        change_state = true;
                    }
                }
                else if (state == 3) //quest log
                {
                    if (pozycja.x >= 255 && pozycja.x <= 505 && pozycja.y >= 30 && pozycja.y <= 80) //calendar
                    {
                        std::cout << "przycisk calendar \n";
                        state = 0;
                        change_state = true;
                    }
                    if (pozycja.x >= 631 && pozycja.x <= 886 && pozycja.y >= 30 && pozycja.y <= 80) //board
                    {
                        std::cout << "przycisk board \n";
                        state = 1;
                        change_state = true;
                    }
                    if (pozycja.x >= 1014 && pozycja.x <= 1269 && pozycja.y >= 30 && pozycja.y <= 80) //quest list
                    {
                        std::cout << "przycisk quest list \n";
                        state = 2;
                        change_state = true;
                    }
                    if (pozycja.x >= 1395 && pozycja.x <= 1650 && pozycja.y >= 30 && pozycja.y <= 80) //quest log
                    {
                        std::cout << "przycisk menu \n";
                        state = -1;
                        change_state = true;
                    }
                }
                else if (state == 4) //creator
                {
                    if (pozycja.x >= 633 && pozycja.x <= 1267 && pozycja.y >= 900 && pozycja.y <= 966) //creator
                    {
                        std::cout << "przycisk back \n";
                        state = -1;
                        change_state = true;
                    }
                }
            }


            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::KeyPressed)
            {
                if (state == 0)
                {
                    if (event.key.code == sf::Keyboard::G)
                    {
                        if (pozycja.x >= 143 && pozycja.x <= 373 && pozycja.y >= 180 && pozycja.y <= 316) //pon1
                        {
                            if (objects[0].getTexture() == &calendarblue || objects[0].getTexture() == &calendargreen || objects[0].getTexture() == &calendarred)
                            {
                                if (data->tm_wday != 0)
                                {
                                    dzien = 2 - data->tm_wday;
                                    miesiac = data->tm_mon;
                                    rok = data->tm_year;
                                }
                                else
                                {
                                    dzien = 2 - 7;
                                    miesiac = data->tm_mon;
                                    rok = data->tm_year;
                                }
                                name = "calendar/";
                                name = name + std::to_string(dzien) + "v" + std::to_string(miesiac + 1) + "v" + std::to_string(rok + 1900) + ".txt";
                                plik.open(name.c_str(), std::ios::out);
                                plik << "green";
                                plik.close();
                            }
                        }
                        if (pozycja.x >= 373 && pozycja.x <= 603 && pozycja.y >= 180 && pozycja.y <= 316) //wt1
                        {
                            if (objects[1].getTexture() == &calendarblue || objects[1].getTexture() == &calendargreen || objects[1].getTexture() == &calendarred)
                            {
                                if (data->tm_wday != 0)
                                {
                                    dzien = 3 - data->tm_wday;
                                    miesiac = data->tm_mon;
                                    rok = data->tm_year;
                                }
                                else
                                {
                                    dzien = 3 - 7;
                                    miesiac = data->tm_mon;
                                    rok = data->tm_year;
                                }
                                name = "calendar/";
                                name = name + std::to_string(dzien) + "v" + std::to_string(miesiac + 1) + "v" + std::to_string(rok + 1900) + ".txt";
                                plik.open(name.c_str(), std::ios::out);
                                plik << "green";
                                plik.close();
                            }
                        }
                        if (pozycja.x >= 603 && pozycja.x <= 833 && pozycja.y >= 180 && pozycja.y <= 316) //sr1
                        {
                            if (objects[2].getTexture() == &calendarblue || objects[2].getTexture() == &calendargreen || objects[2].getTexture() == &calendarred)
                            {
                                if (data->tm_wday != 0)
                                {
                                    dzien = 4 - data->tm_wday;
                                    miesiac = data->tm_mon;
                                    rok = data->tm_year;
                                }
                                else
                                {
                                    dzien = 4 - 7;
                                    miesiac = data->tm_mon;
                                    rok = data->tm_year;
                                }
                                name = "calendar/";
                                name = name + std::to_string(dzien) + "v" + std::to_string(miesiac + 1) + "v" + std::to_string(rok + 1900) + ".txt";
                                plik.open(name.c_str(), std::ios::out);
                                plik << "green";
                                plik.close();
                            }
                        }
                        if (pozycja.x >= 833 && pozycja.x <= 1063 && pozycja.y >= 180 && pozycja.y <= 316) //czw1
                        {
                            if (objects[3].getTexture() == &calendarblue || objects[3].getTexture() == &calendargreen || objects[3].getTexture() == &calendarred)
                            {
                                if (data->tm_wday != 0)
                                {
                                    dzien = 5 - data->tm_wday;
                                    miesiac = data->tm_mon;
                                    rok = data->tm_year;
                                }
                                else
                                {
                                    dzien = 5 - 7;
                                    miesiac = data->tm_mon;
                                    rok = data->tm_year;
                                }
                                name = "calendar/";
                                name = name + std::to_string(dzien) + "v" + std::to_string(miesiac + 1) + "v" + std::to_string(rok + 1900) + ".txt";
                                plik.open(name.c_str(), std::ios::out);
                                plik << "green";
                                plik.close();
                            }
                        }
                        if (pozycja.x >= 1063 && pozycja.x <= 1293 && pozycja.y >= 180 && pozycja.y <= 316) //pt1
                        {
                            if (objects[4].getTexture() == &calendarblue || objects[4].getTexture() == &calendargreen || objects[4].getTexture() == &calendarred)
                            {
                                if (data->tm_wday != 0)
                                {
                                    dzien = 6 - data->tm_wday;
                                    miesiac = data->tm_mon;
                                    rok = data->tm_year;
                                }
                                else
                                {
                                    dzien = 6 - 7;
                                    miesiac = data->tm_mon;
                                    rok = data->tm_year;
                                }
                                name = "calendar/";
                                name = name + std::to_string(dzien) + "v" + std::to_string(miesiac + 1) + "v" + std::to_string(rok + 1900) + ".txt";
                                plik.open(name.c_str(), std::ios::out);
                                plik << "green";
                                plik.close();
                            }
                        }
                        if (pozycja.x >= 1293 && pozycja.x <= 1523 && pozycja.y >= 180 && pozycja.y <= 316) //sob1
                        {
                            if (objects[5].getTexture() == &calendarblue || objects[5].getTexture() == &calendargreen || objects[5].getTexture() == &calendarred)
                            {
                                if (data->tm_wday != 0)
                                {
                                    dzien = 7 - data->tm_wday;
                                    miesiac = data->tm_mon;
                                    rok = data->tm_year;
                                }
                                else
                                {
                                    dzien = 7 - 7;
                                    miesiac = data->tm_mon;
                                    rok = data->tm_year;
                                }
                                name = "calendar/";
                                name = name + std::to_string(dzien) + "v" + std::to_string(miesiac + 1) + "v" + std::to_string(rok + 1900) + ".txt";
                                plik.open(name.c_str(), std::ios::out);
                                plik << "green";
                                plik.close();
                            }
                        }
                        if (pozycja.x >= 1523 && pozycja.x <= 1753 && pozycja.y >= 180 && pozycja.y <= 316) //nd1
                        {
                            if (objects[6].getTexture() == &calendarblue || objects[6].getTexture() == &calendargreen || objects[6].getTexture() == &calendarred)
                            {
                                if (data->tm_wday != 0)
                                {
                                    dzien = 8 - data->tm_wday;
                                    miesiac = data->tm_mon;
                                    rok = data->tm_year;
                                }
                                else
                                {
                                    dzien = 8 - 7;
                                    miesiac = data->tm_mon;
                                    rok = data->tm_year;
                                }
                                name = "calendar/";
                                name = name + std::to_string(dzien) + "v" + std::to_string(miesiac + 1) + "v" + std::to_string(rok + 1900) + ".txt";
                                plik.open(name.c_str(), std::ios::out);
                                plik << "green";
                                plik.close();
                            }
                        }
                        if (pozycja.x >= 143 && pozycja.x <= 373 && pozycja.y >= 316 && pozycja.y <= 452) //pon2
                        {
                            if (objects[7].getTexture() == &calendarblue || objects[7].getTexture() == &calendargreen || objects[7].getTexture() == &calendarred)
                            {
                                if (data->tm_wday != 0)
                                {
                                    dzien = 9 - data->tm_wday;
                                    miesiac = data->tm_mon;
                                    rok = data->tm_year;
                                }
                                else
                                {
                                    dzien = 9 - 7;
                                    miesiac = data->tm_mon;
                                    rok = data->tm_year;
                                }
                                name = "calendar/";
                                name = name + std::to_string(dzien) + "v" + std::to_string(miesiac + 1) + "v" + std::to_string(rok + 1900) + ".txt";
                                plik.open(name.c_str(), std::ios::out);
                                plik << "green";
                                plik.close();
                            }
                        }
                        if (pozycja.x >= 373 && pozycja.x <= 603 && pozycja.y >= 316 && pozycja.y <= 452) //wt2
                        {
                            if (objects[8].getTexture() == &calendarblue || objects[8].getTexture() == &calendargreen || objects[8].getTexture() == &calendarred)
                            {
                                if (data->tm_wday != 0)
                                {
                                    dzien = 10 - data->tm_wday;
                                    miesiac = data->tm_mon;
                                    rok = data->tm_year;
                                }
                                else
                                {
                                    dzien = 10 - 7;
                                    miesiac = data->tm_mon;
                                    rok = data->tm_year;
                                }
                                name = "calendar/";
                                name = name + std::to_string(dzien) + "v" + std::to_string(miesiac + 1) + "v" + std::to_string(rok + 1900) + ".txt";
                                plik.open(name.c_str(), std::ios::out);
                                plik << "green";
                                plik.close();
                            }
                        }
                        if (pozycja.x >= 603 && pozycja.x <= 833 && pozycja.y >= 316 && pozycja.y <= 452) //sr2
                        {
                            if (objects[9].getTexture() == &calendarblue || objects[9].getTexture() == &calendargreen || objects[9].getTexture() == &calendarred)
                            {
                                if (data->tm_wday != 0)
                                {
                                    dzien = 11 - data->tm_wday;
                                    miesiac = data->tm_mon;
                                    rok = data->tm_year;
                                }
                                else
                                {
                                    dzien = 11 - 7;
                                    miesiac = data->tm_mon;
                                    rok = data->tm_year;
                                }
                                name = "calendar/";
                                name = name + std::to_string(dzien) + "v" + std::to_string(miesiac + 1) + "v" + std::to_string(rok + 1900) + ".txt";
                                plik.open(name.c_str(), std::ios::out);
                                plik << "green";
                                plik.close();
                            }
                        }
                        if (pozycja.x >= 833 && pozycja.x <= 1063 && pozycja.y >= 316 && pozycja.y <= 452) //czw2
                        {
                            if (objects[10].getTexture() == &calendarblue || objects[10].getTexture() == &calendargreen || objects[10].getTexture() == &calendarred)
                            {
                                if (data->tm_wday != 0)
                                {
                                    dzien = 12 - data->tm_wday;
                                    miesiac = data->tm_mon;
                                    rok = data->tm_year;
                                }
                                else
                                {
                                    dzien = 12 - 7;
                                    miesiac = data->tm_mon;
                                    rok = data->tm_year;
                                }
                                name = "calendar/";
                                name = name + std::to_string(dzien) + "v" + std::to_string(miesiac + 1) + "v" + std::to_string(rok + 1900) + ".txt";
                                plik.open(name.c_str(), std::ios::out);
                                plik << "green";
                                plik.close();
                            }
                        }
                        if (pozycja.x >= 1063 && pozycja.x <= 1293 && pozycja.y >= 316 && pozycja.y <= 452) //pt2
                        {
                            if (objects[11].getTexture() == &calendarblue || objects[11].getTexture() == &calendargreen || objects[11].getTexture() == &calendarred)
                            {
                                if (data->tm_wday != 0)
                                {
                                    dzien = 13 - data->tm_wday;
                                    miesiac = data->tm_mon;
                                    rok = data->tm_year;
                                }
                                else
                                {
                                    dzien = 13 - 7;
                                    miesiac = data->tm_mon;
                                    rok = data->tm_year;
                                }
                                name = "calendar/";
                                name = name + std::to_string(dzien) + "v" + std::to_string(miesiac + 1) + "v" + std::to_string(rok + 1900) + ".txt";
                                plik.open(name.c_str(), std::ios::out);
                                plik << "green";
                                plik.close();
                            }
                        }
                        if (pozycja.x >= 1293 && pozycja.x <= 1523 && pozycja.y >= 316 && pozycja.y <= 452) //sob2
                        {
                            if (objects[12].getTexture() == &calendarblue || objects[12].getTexture() == &calendargreen || objects[12].getTexture() == &calendarred)
                            {
                                if (data->tm_wday != 0)
                                {
                                    dzien = 14 - data->tm_wday;
                                    miesiac = data->tm_mon;
                                    rok = data->tm_year;

                                }
                                else
                                {
                                    dzien = 14 - 7;
                                    miesiac = data->tm_mon;
                                    rok = data->tm_year;
                                }
                                name = "calendar/";
                                name = name + std::to_string(dzien) + "v" + std::to_string(miesiac + 1) + "v" + std::to_string(rok + 1900) + ".txt";
                                plik.open(name.c_str(), std::ios::out);
                                plik << "green";
                                plik.close();
                            }
                        }
                        if (pozycja.x >= 1523 && pozycja.x <= 1753 && pozycja.y >= 316 && pozycja.y <= 452) //nd2
                        {
                            if (objects[13].getTexture() == &calendarblue || objects[13].getTexture() == &calendargreen || objects[13].getTexture() == &calendarred)
                            {
                                if (data->tm_wday != 0)
                                {
                                    dzien = 15 - data->tm_wday;
                                    miesiac = data->tm_mon;
                                    rok = data->tm_year;
                                }
                                else
                                {
                                    dzien = 15 - 7;
                                    miesiac = data->tm_mon;
                                    rok = data->tm_year;
                                }
                                name = "calendar/";
                                name = name + std::to_string(dzien) + "v" + std::to_string(miesiac + 1) + "v" + std::to_string(rok + 1900) + ".txt";
                                plik.open(name.c_str(), std::ios::out);
                                plik << "green";
                                plik.close();
                            }
                        }
                        if (pozycja.x >= 143 && pozycja.x <= 373 && pozycja.y >= 452 && pozycja.y <= 588) //pon3
                        {
                            if (objects[14].getTexture() == &calendarblue || objects[14].getTexture() == &calendargreen || objects[14].getTexture() == &calendarred)
                            {
                                if (data->tm_wday != 0)
                                {
                                    dzien = 16 - data->tm_wday;
                                    miesiac = data->tm_mon;
                                    rok = data->tm_year;
                                }
                                else
                                {
                                    dzien = 16 - 7;
                                    miesiac = data->tm_mon;
                                    rok = data->tm_year;
                                }
                                name = "calendar/";
                                name = name + std::to_string(dzien) + "v" + std::to_string(miesiac + 1) + "v" + std::to_string(rok + 1900) + ".txt";
                                plik.open(name.c_str(), std::ios::out);
                                plik << "green";
                                plik.close();
                            }
                        }
                        if (pozycja.x >= 373 && pozycja.x <= 603 && pozycja.y >= 452 && pozycja.y <= 588) //wt3
                        {
                            if (objects[15].getTexture() == &calendarblue || objects[15].getTexture() == &calendargreen || objects[15].getTexture() == &calendarred)
                            {
                                if (data->tm_wday != 0)
                                {
                                    dzien = 17 - data->tm_wday;
                                    miesiac = data->tm_mon;
                                    rok = data->tm_year;
                                }
                                else
                                {
                                    dzien = 17 - 7;
                                    miesiac = data->tm_mon;
                                    rok = data->tm_year;
                                }
                                name = "calendar/";
                                name = name + std::to_string(dzien) + "v" + std::to_string(miesiac + 1) + "v" + std::to_string(rok + 1900) + ".txt";
                                plik.open(name.c_str(), std::ios::out);
                                plik << "green";
                                plik.close();
                            }
                        }
                        if (pozycja.x >= 603 && pozycja.x <= 833 && pozycja.y >= 452 && pozycja.y <= 588) //sr3
                        {
                            if (objects[16].getTexture() == &calendarblue || objects[16].getTexture() == &calendargreen || objects[16].getTexture() == &calendarred)
                            {
                                if (data->tm_wday != 0)
                                {
                                    dzien = 18 - data->tm_wday;
                                    miesiac = data->tm_mon;
                                    rok = data->tm_year;
                                }
                                else
                                {
                                    dzien = 18 - 7;
                                    miesiac = data->tm_mon;
                                    rok = data->tm_year;
                                }
                                name = "calendar/";
                                name = name + std::to_string(dzien) + "v" + std::to_string(miesiac + 1) + "v" + std::to_string(rok + 1900) + ".txt";
                                plik.open(name.c_str(), std::ios::out);
                                plik << "green";
                                plik.close();
                            }
                        }
                        if (pozycja.x >= 833 && pozycja.x <= 1063 && pozycja.y >= 452 && pozycja.y <= 588) //czw3
                        {
                            if (objects[17].getTexture() == &calendarblue || objects[17].getTexture() == &calendargreen || objects[17].getTexture() == &calendarred)
                            {
                                if (data->tm_wday != 0)
                                {
                                    dzien = 19 - data->tm_wday;
                                    miesiac = data->tm_mon;
                                    rok = data->tm_year;
                                }
                                else
                                {
                                    dzien = 19 - 7;
                                    miesiac = data->tm_mon;
                                    rok = data->tm_year;
                                }
                                name = "calendar/";
                                name = name + std::to_string(dzien) + "v" + std::to_string(miesiac + 1) + "v" + std::to_string(rok + 1900) + ".txt";
                                plik.open(name.c_str(), std::ios::out);
                                plik << "green";
                                plik.close();
                            }
                        }
                        if (pozycja.x >= 1063 && pozycja.x <= 1293 && pozycja.y >= 452 && pozycja.y <= 588) //pt3
                        {
                            if (objects[18].getTexture() == &calendarblue || objects[18].getTexture() == &calendargreen || objects[18].getTexture() == &calendarred)
                            {
                                if (data->tm_wday != 0)
                                {
                                    dzien = 20 - data->tm_wday;
                                    miesiac = data->tm_mon;
                                    rok = data->tm_year;
                                }
                                else
                                {
                                    dzien = 20 - 7;
                                    miesiac = data->tm_mon;
                                    rok = data->tm_year;
                                }
                                name = "calendar/";
                                name = name + std::to_string(dzien) + "v" + std::to_string(miesiac + 1) + "v" + std::to_string(rok + 1900) + ".txt";
                                plik.open(name.c_str(), std::ios::out);
                                plik << "green";
                                plik.close();
                            }
                        }
                        if (pozycja.x >= 1293 && pozycja.x <= 1523 && pozycja.y >= 452 && pozycja.y <= 588) //sob3
                        {
                            if (objects[19].getTexture() == &calendarblue || objects[19].getTexture() == &calendargreen || objects[19].getTexture() == &calendarred)
                            {
                                if (data->tm_wday != 0)
                                {
                                    dzien = 21 - data->tm_wday;
                                    miesiac = data->tm_mon;
                                    rok = data->tm_year;
                                }
                                else
                                {
                                    dzien = 21 - 7;
                                    miesiac = data->tm_mon;
                                    rok = data->tm_year;
                                }
                                name = "calendar/";
                                name = name + std::to_string(dzien) + "v" + std::to_string(miesiac + 1) + "v" + std::to_string(rok + 1900) + ".txt";
                                plik.open(name.c_str(), std::ios::out);
                                plik << "green";
                                plik.close();
                            }
                        }
                        if (pozycja.x >= 1523 && pozycja.x <= 1753 && pozycja.y >= 452 && pozycja.y <= 588) //nd3
                        {
                            if (objects[20].getTexture() == &calendarblue || objects[20].getTexture() == &calendargreen || objects[20].getTexture() == &calendarred)
                            {
                                if (data->tm_wday != 0)
                                {
                                    dzien = 22 - data->tm_wday;
                                    miesiac = data->tm_mon;
                                    rok = data->tm_year;
                                }
                                else
                                {
                                    dzien = 22 - 7;
                                    miesiac = data->tm_mon;
                                    rok = data->tm_year;
                                }
                                name = "calendar/";
                                name = name + std::to_string(dzien) + "v" + std::to_string(miesiac + 1) + "v" + std::to_string(rok + 1900) + ".txt";
                                plik.open(name.c_str(), std::ios::out);
                                plik << "green";
                                plik.close();
                            }
                        }
                        if (pozycja.x >= 143 && pozycja.x <= 373 && pozycja.y >= 588 && pozycja.y <= 724) //pon4
                        {
                            if (objects[21].getTexture() == &calendarblue || objects[21].getTexture() == &calendargreen || objects[21].getTexture() == &calendarred)
                            {
                                if (data->tm_wday != 0)
                                {
                                    dzien = 23 - data->tm_wday;
                                    miesiac = data->tm_mon;
                                    rok = data->tm_year;
                                }
                                else
                                {
                                    dzien = 23 - 7;
                                    miesiac = data->tm_mon;
                                    rok = data->tm_year;
                                }
                                name = "calendar/";
                                name = name + std::to_string(dzien) + "v" + std::to_string(miesiac + 1) + "v" + std::to_string(rok + 1900) + ".txt";
                                plik.open(name.c_str(), std::ios::out);
                                plik << "green";
                                plik.close();
                            }
                        }
                        if (pozycja.x >= 373 && pozycja.x <= 603 && pozycja.y >= 588 && pozycja.y <= 724) //wt4
                        {
                            if (objects[22].getTexture() == &calendarblue || objects[22].getTexture() == &calendargreen || objects[22].getTexture() == &calendarred)
                            {
                                if (data->tm_wday != 0)
                                {
                                    dzien = 24 - data->tm_wday;
                                    miesiac = data->tm_mon;
                                    rok = data->tm_year;
                                }
                                else
                                {
                                    dzien = 24 - 7;
                                    miesiac = data->tm_mon;
                                    rok = data->tm_year;
                                }
                                name = "calendar/";
                                name = name + std::to_string(dzien) + "v" + std::to_string(miesiac + 1) + "v" + std::to_string(rok + 1900) + ".txt";
                                plik.open(name.c_str(), std::ios::out);
                                plik << "green";
                                plik.close();
                            }
                        }
                        if (pozycja.x >= 603 && pozycja.x <= 833 && pozycja.y >= 588 && pozycja.y <= 724) //sr4
                        {
                            if (objects[23].getTexture() == &calendarblue || objects[23].getTexture() == &calendargreen || objects[23].getTexture() == &calendarred)
                            {
                                if (data->tm_wday != 0)
                                {
                                    dzien = 25 - data->tm_wday;
                                    miesiac = data->tm_mon;
                                    rok = data->tm_year;
                                }
                                else
                                {
                                    dzien = 25 - 7;
                                    miesiac = data->tm_mon;
                                    rok = data->tm_year;
                                }
                                name = "calendar/";
                                name = name + std::to_string(dzien) + "v" + std::to_string(miesiac + 1) + "v" + std::to_string(rok + 1900) + ".txt";
                                plik.open(name.c_str(), std::ios::out);
                                plik << "green";
                                plik.close();
                            }
                        }
                        if (pozycja.x >= 833 && pozycja.x <= 1063 && pozycja.y >= 588 && pozycja.y <= 724) //czw4
                        {
                            if (objects[24].getTexture() == &calendarblue || objects[24].getTexture() == &calendargreen || objects[24].getTexture() == &calendarred)
                            {
                                if (data->tm_wday != 0)
                                {
                                    dzien = 26 - data->tm_wday;
                                    miesiac = data->tm_mon;
                                    rok = data->tm_year;
                                }
                                else
                                {
                                    dzien = 26 - 7;
                                    miesiac = data->tm_mon;
                                    rok = data->tm_year;
                                }
                                name = "calendar/";
                                name = name + std::to_string(dzien) + "v" + std::to_string(miesiac + 1) + "v" + std::to_string(rok + 1900) + ".txt";
                                plik.open(name.c_str(), std::ios::out);
                                plik << "green";
                                plik.close();
                            }
                        }
                        if (pozycja.x >= 1063 && pozycja.x <= 1293 && pozycja.y >= 588 && pozycja.y <= 724) //pt4
                        {
                            if (objects[25].getTexture() == &calendarblue || objects[25].getTexture() == &calendargreen || objects[25].getTexture() == &calendarred)
                            {
                                if (data->tm_wday != 0)
                                {
                                    dzien = 27 - data->tm_wday;
                                    miesiac = data->tm_mon;
                                    rok = data->tm_year;
                                }
                                else
                                {
                                    dzien = 27 - 7;
                                    miesiac = data->tm_mon;
                                    rok = data->tm_year;
                                }
                                name = "calendar/";
                                name = name + std::to_string(dzien) + "v" + std::to_string(miesiac + 1) + "v" + std::to_string(rok + 1900) + ".txt";
                                plik.open(name.c_str(), std::ios::out);
                                plik << "green";
                                plik.close();
                            }
                        }
                        if (pozycja.x >= 1293 && pozycja.x <= 1523 && pozycja.y >= 588 && pozycja.y <= 724) //sob4
                        {
                            if (objects[26].getTexture() == &calendarblue || objects[26].getTexture() == &calendargreen || objects[26].getTexture() == &calendarred)
                            {
                                if (data->tm_wday != 0)
                                {
                                    dzien = 28 - data->tm_wday;
                                    miesiac = data->tm_mon;
                                    rok = data->tm_year;
                                }
                                else
                                {
                                    dzien = 28 - 7;
                                    miesiac = data->tm_mon;
                                    rok = data->tm_year;
                                }
                                name = "calendar/";
                                name = name + std::to_string(dzien) + "v" + std::to_string(miesiac + 1) + "v" + std::to_string(rok + 1900) + ".txt";
                                plik.open(name.c_str(), std::ios::out);
                                plik << "green";
                                plik.close();
                            }
                        }
                        if (pozycja.x >= 1523 && pozycja.x <= 1753 && pozycja.y >= 588 && pozycja.y <= 724) //nd4
                        {
                            if (objects[27].getTexture() == &calendarblue || objects[27].getTexture() == &calendargreen || objects[27].getTexture() == &calendarred)
                            {
                                if (data->tm_wday != 0)
                                {
                                    dzien = 29 - data->tm_wday;
                                    miesiac = data->tm_mon;
                                    rok = data->tm_year;
                                }
                                else
                                {
                                    dzien = 29 - 7;
                                    miesiac = data->tm_mon;
                                    rok = data->tm_year;
                                }
                                name = "calendar/";
                                name = name + std::to_string(dzien) + "v" + std::to_string(miesiac + 1) + "v" + std::to_string(rok + 1900) + ".txt";
                                plik.open(name.c_str(), std::ios::out);
                                plik << "green";
                                plik.close();
                            }
                        }
                        if (pozycja.x >= 143 && pozycja.x <= 373 && pozycja.y >= 724 && pozycja.y <= 860) //pon5
                        {
                            if (objects[28].getTexture() == &calendarblue || objects[28].getTexture() == &calendargreen || objects[28].getTexture() == &calendarred)
                            {
                                if (data->tm_wday != 0)
                                {
                                    dzien = 30 - data->tm_wday;
                                    miesiac = data->tm_mon;
                                    rok = data->tm_year;
                                }
                                else
                                {
                                    dzien = 30 - 7;
                                    miesiac = data->tm_mon;
                                    rok = data->tm_year;
                                }
                                name = "calendar/";
                                name = name + std::to_string(dzien) + "v" + std::to_string(miesiac + 1) + "v" + std::to_string(rok + 1900) + ".txt";
                                plik.open(name.c_str(), std::ios::out);
                                plik << "green";
                                plik.close();
                            }
                        }
                        if (pozycja.x >= 373 && pozycja.x <= 603 && pozycja.y >= 724 && pozycja.y <= 860) //wt5
                        {
                            if (objects[29].getTexture() == &calendarblue || objects[29].getTexture() == &calendargreen || objects[29].getTexture() == &calendarred)
                            {
                                if (data->tm_wday != 0)
                                {
                                    dzien = 31 - data->tm_wday;
                                    miesiac = data->tm_mon;
                                    rok = data->tm_year;
                                }
                                else
                                {
                                    dzien = 31 - 7;
                                    miesiac = data->tm_mon;
                                    rok = data->tm_year;
                                }
                                name = "calendar/";
                                name = name + std::to_string(dzien) + "v" + std::to_string(miesiac + 1) + "v" + std::to_string(rok + 1900) + ".txt";
                                plik.open(name.c_str(), std::ios::out);
                                plik << "green";
                                plik.close();
                            }
                        }
                        if (pozycja.x >= 603 && pozycja.x <= 833 && pozycja.y >= 724 && pozycja.y <= 860) //sr5
                        {
                            if (objects[30].getTexture() == &calendarblue || objects[30].getTexture() == &calendargreen || objects[30].getTexture() == &calendarred)
                            {
                                if (data->tm_wday != 0)
                                {
                                    dzien = 32 - data->tm_wday;
                                    miesiac = data->tm_mon;
                                    rok = data->tm_year;
                                }
                                else
                                {
                                    dzien = 32 - 7;
                                    miesiac = data->tm_mon;
                                    rok = data->tm_year;
                                }
                                name = "calendar/";
                                name = name + std::to_string(dzien) + "v" + std::to_string(miesiac + 1) + "v" + std::to_string(rok + 1900) + ".txt";
                                plik.open(name.c_str(), std::ios::out);
                                plik << "green";
                                plik.close();
                            }
                        }
                        if (pozycja.x >= 833 && pozycja.x <= 1063 && pozycja.y >= 724 && pozycja.y <= 860) //czw5
                        {
                            if (objects[31].getTexture() == &calendarblue || objects[31].getTexture() == &calendargreen || objects[31].getTexture() == &calendarred)
                            {
                                if (data->tm_wday != 0)
                                {
                                    dzien = 33 - data->tm_wday;
                                    miesiac = data->tm_mon;
                                    rok = data->tm_year;
                                }
                                else
                                {
                                    dzien = 33 - 7;
                                    miesiac = data->tm_mon;
                                    rok = data->tm_year;
                                }
                                name = "calendar/";
                                name = name + std::to_string(dzien) + "v" + std::to_string(miesiac + 1) + "v" + std::to_string(rok + 1900) + ".txt";
                                plik.open(name.c_str(), std::ios::out);
                                plik << "green";
                                plik.close();
                            }
                        }
                        if (pozycja.x >= 1063 && pozycja.x <= 1293 && pozycja.y >= 724 && pozycja.y <= 860) //pt5
                        {
                            if (objects[32].getTexture() == &calendarblue || objects[32].getTexture() == &calendargreen || objects[32].getTexture() == &calendarred)
                            {
                                if (data->tm_wday != 0)
                                {
                                    dzien = 34 - data->tm_wday;
                                    miesiac = data->tm_mon;
                                    rok = data->tm_year;
                                }
                                else
                                {
                                    dzien = 34 - 7;
                                    miesiac = data->tm_mon;
                                    rok = data->tm_year;
                                }
                                name = "calendar/";
                                name = name + std::to_string(dzien) + "v" + std::to_string(miesiac + 1) + "v" + std::to_string(rok + 1900) + ".txt";
                                plik.open(name.c_str(), std::ios::out);
                                plik << "green";
                                plik.close();
                            }
                        }
                        if (pozycja.x >= 1293 && pozycja.x <= 1523 && pozycja.y >= 724 && pozycja.y <= 860) //sob5
                        {
                            if (objects[33].getTexture() == &calendarblue || objects[33].getTexture() == &calendargreen || objects[33].getTexture() == &calendarred)
                            {
                                if (data->tm_wday != 0)
                                {
                                    dzien = 35 - data->tm_wday;
                                    miesiac = data->tm_mon;
                                    rok = data->tm_year;
                                }
                                else
                                {
                                    dzien = 35 - 7;
                                    miesiac = data->tm_mon;
                                    rok = data->tm_year;
                                }
                                name = "calendar/";
                                name = name + std::to_string(dzien) + "v" + std::to_string(miesiac + 1) + "v" + std::to_string(rok + 1900) + ".txt";
                                plik.open(name.c_str(), std::ios::out);
                                plik << "green";
                                plik.close();
                            }
                        }
                        if (pozycja.x >= 1523 && pozycja.x <= 1753 && pozycja.y >= 724 && pozycja.y <= 860) //nd5
                        {
                            if (objects[34].getTexture() == &calendarblue || objects[34].getTexture() == &calendargreen || objects[34].getTexture() == &calendarred)
                            {
                                if (data->tm_wday != 0)
                                {
                                    dzien = 36 - data->tm_wday;
                                    miesiac = data->tm_mon;
                                    rok = data->tm_year;
                                }
                                else
                                {
                                    dzien = 36 - 7;
                                    miesiac = data->tm_mon;
                                    rok = data->tm_year;
                                }
                                name = "calendar/";
                                name = name + std::to_string(dzien) + "v" + std::to_string(miesiac + 1) + "v" + std::to_string(rok + 1900) + ".txt";
                                plik.open(name.c_str(), std::ios::out);
                                plik << "green";
                                plik.close();
                            }
                        }
                        if (pozycja.x >= 143 && pozycja.x <= 373 && pozycja.y >= 724 && pozycja.y <= 860) //pon6
                        {
                            if (objects[35].getTexture() == &calendarblue || objects[35].getTexture() == &calendargreen || objects[35].getTexture() == &calendarred)
                            {
                                if (data->tm_wday != 0)
                                {
                                    dzien = 37 - data->tm_wday;
                                    miesiac = data->tm_mon;
                                    rok = data->tm_year;
                                }
                                else
                                {
                                    dzien = 37 - 7;
                                    miesiac = data->tm_mon;
                                    rok = data->tm_year;
                                }
                                name = "calendar/";
                                name = name + std::to_string(dzien) + "v" + std::to_string(miesiac + 1) + "v" + std::to_string(rok + 1900) + ".txt";
                                plik.open(name.c_str(), std::ios::out);
                                plik << "green";
                                plik.close();
                            }
                        }
                        if (pozycja.x >= 373 && pozycja.x <= 603 && pozycja.y >= 724 && pozycja.y <= 860) //wt6
                        {
                            if (objects[36].getTexture() == &calendarblue || objects[36].getTexture() == &calendargreen || objects[36].getTexture() == &calendarred)
                            {
                                if (data->tm_wday != 0)
                                {
                                    dzien = 38 - data->tm_wday;
                                    miesiac = data->tm_mon;
                                    rok = data->tm_year;
                                }
                                else
                                {
                                    dzien = 38 - 7;
                                    miesiac = data->tm_mon;
                                    rok = data->tm_year;
                                }
                                name = "calendar/";
                                name = name + std::to_string(dzien) + "v" + std::to_string(miesiac + 1) + "v" + std::to_string(rok + 1900) + ".txt";
                                plik.open(name.c_str(), std::ios::out);
                                plik << "green";
                                plik.close();
                            }
                        }
                        if (pozycja.x >= 603 && pozycja.x <= 833 && pozycja.y >= 724 && pozycja.y <= 860) //sr6
                        {
                            if (objects[37].getTexture() == &calendarblue || objects[37].getTexture() == &calendargreen || objects[37].getTexture() == &calendarred)
                            {
                                if (data->tm_wday != 0)
                                {
                                    dzien = 39 - data->tm_wday;
                                    miesiac = data->tm_mon;
                                    rok = data->tm_year;
                                }
                                else
                                {
                                    dzien = 39 - 7;
                                    miesiac = data->tm_mon;
                                    rok = data->tm_year;
                                }
                                name = "calendar/";
                                name = name + std::to_string(dzien) + "v" + std::to_string(miesiac + 1) + "v" + std::to_string(rok + 1900) + ".txt";
                                plik.open(name.c_str(), std::ios::out);
                                plik << "green";
                                plik.close();
                            }
                        }
                        if (pozycja.x >= 833 && pozycja.x <= 1063 && pozycja.y >= 724 && pozycja.y <= 860) //czw6
                        {
                            if (objects[38].getTexture() == &calendarblue || objects[38].getTexture() == &calendargreen || objects[38].getTexture() == &calendarred)
                            {
                                if (data->tm_wday != 0)
                                {
                                    dzien = 40 - data->tm_wday;
                                    miesiac = data->tm_mon;
                                    rok = data->tm_year;
                                }
                                else
                                {
                                    dzien = 40 - 7;
                                    miesiac = data->tm_mon;
                                    rok = data->tm_year;
                                }
                                name = "calendar/";
                                name = name + std::to_string(dzien) + "v" + std::to_string(miesiac + 1) + "v" + std::to_string(rok + 1900) + ".txt";
                                plik.open(name.c_str(), std::ios::out);
                                plik << "green";
                                plik.close();
                            }
                        }
                        if (pozycja.x >= 1063 && pozycja.x <= 1293 && pozycja.y >= 724 && pozycja.y <= 860) //pt6
                        {
                            if (objects[39].getTexture() == &calendarblue || objects[39].getTexture() == &calendargreen || objects[39].getTexture() == &calendarred)
                            {
                                if (data->tm_wday != 0)
                                {
                                    dzien = 41 - data->tm_wday;
                                    miesiac = data->tm_mon;
                                    rok = data->tm_year;
                                }
                                else
                                {
                                    dzien = 41 - 7;
                                    miesiac = data->tm_mon;
                                    rok = data->tm_year;
                                }
                                name = "calendar/";
                                name = name + std::to_string(dzien) + "v" + std::to_string(miesiac + 1) + "v" + std::to_string(rok + 1900) + ".txt";
                                plik.open(name.c_str(), std::ios::out);
                                plik << "green";
                                plik.close();
                            }
                        }
                        if (pozycja.x >= 1293 && pozycja.x <= 1523 && pozycja.y >= 724 && pozycja.y <= 860) //sob6
                        {
                            if (objects[40].getTexture() == &calendarblue || objects[40].getTexture() == &calendargreen || objects[40].getTexture() == &calendarred)
                            {
                                if (data->tm_wday != 0)
                                {
                                    dzien = 42 - data->tm_wday;
                                    miesiac = data->tm_mon;
                                    rok = data->tm_year;
                                }
                                else
                                {
                                    dzien = 42 - 7;
                                    miesiac = data->tm_mon;
                                    rok = data->tm_year;
                                }
                                name = "calendar/";
                                name = name + std::to_string(dzien) + "v" + std::to_string(miesiac + 1) + "v" + std::to_string(rok + 1900) + ".txt";
                                plik.open(name.c_str(), std::ios::out);
                                plik << "green";
                                plik.close();
                            }
                        }
                        if (pozycja.x >= 1523 && pozycja.x <= 1753 && pozycja.y >= 724 && pozycja.y <= 860) //nd6
                        {
                            if (objects[41].getTexture() == &calendarblue || objects[41].getTexture() == &calendargreen || objects[41].getTexture() == &calendarred)
                            {
                                if (data->tm_wday != 0)
                                {
                                    dzien = 43 - data->tm_wday;
                                    miesiac = data->tm_mon;
                                    rok = data->tm_year;
                                }
                                else
                                {
                                    dzien = 43 - 7;
                                    miesiac = data->tm_mon;
                                    rok = data->tm_year;
                                }
                                name = "calendar/";
                                name = name + std::to_string(dzien) + "v" + std::to_string(miesiac + 1) + "v" + std::to_string(rok + 1900) + ".txt";
                                plik.open(name.c_str(), std::ios::out);
                                plik << "green";
                                plik.close();
                            }
                        }
                        change_state = true;
                        state = 0;
                    }
                    if (event.key.code == sf::Keyboard::R)
                    {
                        if (pozycja.x >= 143 && pozycja.x <= 373 && pozycja.y >= 180 && pozycja.y <= 316) //pon1
                        {
                            if (objects[0].getTexture() == &calendarblue || objects[0].getTexture() == &calendarred || objects[0].getTexture() == &calendarred)
                            {
                                if (data->tm_wday != 0)
                                {
                                    dzien = 2 - data->tm_wday;
                                    miesiac = data->tm_mon;
                                    rok = data->tm_year;
                                }
                                else
                                {
                                    dzien = 2 - 7;
                                    miesiac = data->tm_mon;
                                    rok = data->tm_year;
                                }
                                name = "calendar/";
                                name = name + std::to_string(dzien) + "v" + std::to_string(miesiac + 1) + "v" + std::to_string(rok + 1900) + ".txt";
                                plik.open(name.c_str(), std::ios::out);
                                plik << "red";
                                plik.close();
                            }
                        }
                        if (pozycja.x >= 373 && pozycja.x <= 603 && pozycja.y >= 180 && pozycja.y <= 316) //wt1
                        {
                            if (objects[1].getTexture() == &calendarblue || objects[1].getTexture() == &calendarred || objects[1].getTexture() == &calendarred)
                            {
                                if (data->tm_wday != 0)
                                {
                                    dzien = 3 - data->tm_wday;
                                    miesiac = data->tm_mon;
                                    rok = data->tm_year;
                                }
                                else
                                {
                                    dzien = 3 - 7;
                                    miesiac = data->tm_mon;
                                    rok = data->tm_year;
                                }
                                name = "calendar/";
                                name = name + std::to_string(dzien) + "v" + std::to_string(miesiac + 1) + "v" + std::to_string(rok + 1900) + ".txt";
                                plik.open(name.c_str(), std::ios::out);
                                plik << "red";
                                plik.close();
                            }
                        }
                        if (pozycja.x >= 603 && pozycja.x <= 833 && pozycja.y >= 180 && pozycja.y <= 316) //sr1
                        {
                            if (objects[2].getTexture() == &calendarblue || objects[2].getTexture() == &calendarred || objects[2].getTexture() == &calendarred)
                            {
                                if (data->tm_wday != 0)
                                {
                                    dzien = 4 - data->tm_wday;
                                    miesiac = data->tm_mon;
                                    rok = data->tm_year;
                                }
                                else
                                {
                                    dzien = 4 - 7;
                                    miesiac = data->tm_mon;
                                    rok = data->tm_year;
                                }
                                name = "calendar/";
                                name = name + std::to_string(dzien) + "v" + std::to_string(miesiac + 1) + "v" + std::to_string(rok + 1900) + ".txt";
                                plik.open(name.c_str(), std::ios::out);
                                plik << "red";
                                plik.close();
                            }
                        }
                        if (pozycja.x >= 833 && pozycja.x <= 1063 && pozycja.y >= 180 && pozycja.y <= 316) //czw1
                        {
                            if (objects[3].getTexture() == &calendarblue || objects[3].getTexture() == &calendarred || objects[3].getTexture() == &calendarred)
                            {
                                if (data->tm_wday != 0)
                                {
                                    dzien = 5 - data->tm_wday;
                                    miesiac = data->tm_mon;
                                    rok = data->tm_year;
                                }
                                else
                                {
                                    dzien = 5 - 7;
                                    miesiac = data->tm_mon;
                                    rok = data->tm_year;
                                }
                                name = "calendar/";
                                name = name + std::to_string(dzien) + "v" + std::to_string(miesiac + 1) + "v" + std::to_string(rok + 1900) + ".txt";
                                plik.open(name.c_str(), std::ios::out);
                                plik << "red";
                                plik.close();
                            }
                        }
                        if (pozycja.x >= 1063 && pozycja.x <= 1293 && pozycja.y >= 180 && pozycja.y <= 316) //pt1
                        {
                            if (objects[4].getTexture() == &calendarblue || objects[4].getTexture() == &calendarred || objects[4].getTexture() == &calendarred)
                            {
                                if (data->tm_wday != 0)
                                {
                                    dzien = 6 - data->tm_wday;
                                    miesiac = data->tm_mon;
                                    rok = data->tm_year;
                                }
                                else
                                {
                                    dzien = 6 - 7;
                                    miesiac = data->tm_mon;
                                    rok = data->tm_year;
                                }
                                name = "calendar/";
                                name = name + std::to_string(dzien) + "v" + std::to_string(miesiac + 1) + "v" + std::to_string(rok + 1900) + ".txt";
                                plik.open(name.c_str(), std::ios::out);
                                plik << "red";
                                plik.close();
                            }
                        }
                        if (pozycja.x >= 1293 && pozycja.x <= 1523 && pozycja.y >= 180 && pozycja.y <= 316) //sob1
                        {
                            if (objects[5].getTexture() == &calendarblue || objects[5].getTexture() == &calendarred || objects[5].getTexture() == &calendarred)
                            {
                                if (data->tm_wday != 0)
                                {
                                    dzien = 7 - data->tm_wday;
                                    miesiac = data->tm_mon;
                                    rok = data->tm_year;
                                }
                                else
                                {
                                    dzien = 7 - 7;
                                    miesiac = data->tm_mon;
                                    rok = data->tm_year;
                                }
                                name = "calendar/";
                                name = name + std::to_string(dzien) + "v" + std::to_string(miesiac + 1) + "v" + std::to_string(rok + 1900) + ".txt";
                                plik.open(name.c_str(), std::ios::out);
                                plik << "red";
                                plik.close();
                            }
                        }
                        if (pozycja.x >= 1523 && pozycja.x <= 1753 && pozycja.y >= 180 && pozycja.y <= 316) //nd1
                        {
                            if (objects[6].getTexture() == &calendarblue || objects[6].getTexture() == &calendarred || objects[6].getTexture() == &calendarred)
                            {
                                if (data->tm_wday != 0)
                                {
                                    dzien = 8 - data->tm_wday;
                                    miesiac = data->tm_mon;
                                    rok = data->tm_year;
                                }
                                else
                                {
                                    dzien = 8 - 7;
                                    miesiac = data->tm_mon;
                                    rok = data->tm_year;
                                }
                                name = "calendar/";
                                name = name + std::to_string(dzien) + "v" + std::to_string(miesiac + 1) + "v" + std::to_string(rok + 1900) + ".txt";
                                plik.open(name.c_str(), std::ios::out);
                                plik << "red";
                                plik.close();
                            }
                        }
                        if (pozycja.x >= 143 && pozycja.x <= 373 && pozycja.y >= 316 && pozycja.y <= 452) //pon2
                        {
                            if (objects[7].getTexture() == &calendarblue || objects[7].getTexture() == &calendarred || objects[7].getTexture() == &calendarred)
                            {
                                if (data->tm_wday != 0)
                                {
                                    dzien = 9 - data->tm_wday;
                                    miesiac = data->tm_mon;
                                    rok = data->tm_year;
                                }
                                else
                                {
                                    dzien = 9 - 7;
                                    miesiac = data->tm_mon;
                                    rok = data->tm_year;
                                }
                                name = "calendar/";
                                name = name + std::to_string(dzien) + "v" + std::to_string(miesiac + 1) + "v" + std::to_string(rok + 1900) + ".txt";
                                plik.open(name.c_str(), std::ios::out);
                                plik << "red";
                                plik.close();
                            }
                        }
                        if (pozycja.x >= 373 && pozycja.x <= 603 && pozycja.y >= 316 && pozycja.y <= 452) //wt2
                        {
                            if (objects[8].getTexture() == &calendarblue || objects[8].getTexture() == &calendarred || objects[8].getTexture() == &calendarred)
                            {
                                if (data->tm_wday != 0)
                                {
                                    dzien = 10 - data->tm_wday;
                                    miesiac = data->tm_mon;
                                    rok = data->tm_year;
                                }
                                else
                                {
                                    dzien = 10 - 7;
                                    miesiac = data->tm_mon;
                                    rok = data->tm_year;
                                }
                                name = "calendar/";
                                name = name + std::to_string(dzien) + "v" + std::to_string(miesiac + 1) + "v" + std::to_string(rok + 1900) + ".txt";
                                plik.open(name.c_str(), std::ios::out);
                                plik << "red";
                                plik.close();
                            }
                        }
                        if (pozycja.x >= 603 && pozycja.x <= 833 && pozycja.y >= 316 && pozycja.y <= 452) //sr2
                        {
                            if (objects[9].getTexture() == &calendarblue || objects[9].getTexture() == &calendarred || objects[9].getTexture() == &calendarred)
                            {
                                if (data->tm_wday != 0)
                                {
                                    dzien = 11 - data->tm_wday;
                                    miesiac = data->tm_mon;
                                    rok = data->tm_year;
                                }
                                else
                                {
                                    dzien = 11 - 7;
                                    miesiac = data->tm_mon;
                                    rok = data->tm_year;
                                }
                                name = "calendar/";
                                name = name + std::to_string(dzien) + "v" + std::to_string(miesiac + 1) + "v" + std::to_string(rok + 1900) + ".txt";
                                plik.open(name.c_str(), std::ios::out);
                                plik << "red";
                                plik.close();
                            }
                        }
                        if (pozycja.x >= 833 && pozycja.x <= 1063 && pozycja.y >= 316 && pozycja.y <= 452) //czw2
                        {
                            if (objects[10].getTexture() == &calendarblue || objects[10].getTexture() == &calendarred || objects[10].getTexture() == &calendarred)
                            {
                                if (data->tm_wday != 0)
                                {
                                    dzien = 12 - data->tm_wday;
                                    miesiac = data->tm_mon;
                                    rok = data->tm_year;
                                }
                                else
                                {
                                    dzien = 12 - 7;
                                    miesiac = data->tm_mon;
                                    rok = data->tm_year;
                                }
                                name = "calendar/";
                                name = name + std::to_string(dzien) + "v" + std::to_string(miesiac + 1) + "v" + std::to_string(rok + 1900) + ".txt";
                                plik.open(name.c_str(), std::ios::out);
                                plik << "red";
                                plik.close();
                            }
                        }
                        if (pozycja.x >= 1063 && pozycja.x <= 1293 && pozycja.y >= 316 && pozycja.y <= 452) //pt2
                        {
                            if (objects[11].getTexture() == &calendarblue || objects[11].getTexture() == &calendarred || objects[11].getTexture() == &calendarred)
                            {
                                if (data->tm_wday != 0)
                                {
                                    dzien = 13 - data->tm_wday;
                                    miesiac = data->tm_mon;
                                    rok = data->tm_year;
                                }
                                else
                                {
                                    dzien = 13 - 7;
                                    miesiac = data->tm_mon;
                                    rok = data->tm_year;
                                }
                                name = "calendar/";
                                name = name + std::to_string(dzien) + "v" + std::to_string(miesiac + 1) + "v" + std::to_string(rok + 1900) + ".txt";
                                plik.open(name.c_str(), std::ios::out);
                                plik << "red";
                                plik.close();
                            }
                        }
                        if (pozycja.x >= 1293 && pozycja.x <= 1523 && pozycja.y >= 316 && pozycja.y <= 452) //sob2
                        {
                            if (objects[12].getTexture() == &calendarblue || objects[12].getTexture() == &calendarred || objects[12].getTexture() == &calendarred)
                            {
                                if (data->tm_wday != 0)
                                {
                                    dzien = 14 - data->tm_wday;
                                    miesiac = data->tm_mon;
                                    rok = data->tm_year;

                                }
                                else
                                {
                                    dzien = 14 - 7;
                                    miesiac = data->tm_mon;
                                    rok = data->tm_year;
                                }
                                name = "calendar/";
                                name = name + std::to_string(dzien) + "v" + std::to_string(miesiac + 1) + "v" + std::to_string(rok + 1900) + ".txt";
                                plik.open(name.c_str(), std::ios::out);
                                plik << "red";
                                plik.close();
                            }
                        }
                        if (pozycja.x >= 1523 && pozycja.x <= 1753 && pozycja.y >= 316 && pozycja.y <= 452) //nd2
                        {
                            if (objects[13].getTexture() == &calendarblue || objects[13].getTexture() == &calendarred || objects[13].getTexture() == &calendarred)
                            {
                                if (data->tm_wday != 0)
                                {
                                    dzien = 15 - data->tm_wday;
                                    miesiac = data->tm_mon;
                                    rok = data->tm_year;
                                }
                                else
                                {
                                    dzien = 15 - 7;
                                    miesiac = data->tm_mon;
                                    rok = data->tm_year;
                                }
                                name = "calendar/";
                                name = name + std::to_string(dzien) + "v" + std::to_string(miesiac + 1) + "v" + std::to_string(rok + 1900) + ".txt";
                                plik.open(name.c_str(), std::ios::out);
                                plik << "red";
                                plik.close();
                            }
                        }
                        if (pozycja.x >= 143 && pozycja.x <= 373 && pozycja.y >= 452 && pozycja.y <= 588) //pon3
                        {
                            if (objects[14].getTexture() == &calendarblue || objects[14].getTexture() == &calendarred || objects[14].getTexture() == &calendarred)
                            {
                                if (data->tm_wday != 0)
                                {
                                    dzien = 16 - data->tm_wday;
                                    miesiac = data->tm_mon;
                                    rok = data->tm_year;
                                }
                                else
                                {
                                    dzien = 16 - 7;
                                    miesiac = data->tm_mon;
                                    rok = data->tm_year;
                                }
                                name = "calendar/";
                                name = name + std::to_string(dzien) + "v" + std::to_string(miesiac + 1) + "v" + std::to_string(rok + 1900) + ".txt";
                                plik.open(name.c_str(), std::ios::out);
                                plik << "red";
                                plik.close();
                            }
                        }
                        if (pozycja.x >= 373 && pozycja.x <= 603 && pozycja.y >= 452 && pozycja.y <= 588) //wt3
                        {
                            if (objects[15].getTexture() == &calendarblue || objects[15].getTexture() == &calendarred || objects[15].getTexture() == &calendarred)
                            {
                                if (data->tm_wday != 0)
                                {
                                    dzien = 17 - data->tm_wday;
                                    miesiac = data->tm_mon;
                                    rok = data->tm_year;
                                }
                                else
                                {
                                    dzien = 17 - 7;
                                    miesiac = data->tm_mon;
                                    rok = data->tm_year;
                                }
                                name = "calendar/";
                                name = name + std::to_string(dzien) + "v" + std::to_string(miesiac + 1) + "v" + std::to_string(rok + 1900) + ".txt";
                                plik.open(name.c_str(), std::ios::out);
                                plik << "red";
                                plik.close();
                            }
                        }
                        if (pozycja.x >= 603 && pozycja.x <= 833 && pozycja.y >= 452 && pozycja.y <= 588) //sr3
                        {
                            if (objects[16].getTexture() == &calendarblue || objects[16].getTexture() == &calendarred || objects[16].getTexture() == &calendarred)
                            {
                                if (data->tm_wday != 0)
                                {
                                    dzien = 18 - data->tm_wday;
                                    miesiac = data->tm_mon;
                                    rok = data->tm_year;
                                }
                                else
                                {
                                    dzien = 18 - 7;
                                    miesiac = data->tm_mon;
                                    rok = data->tm_year;
                                }
                                name = "calendar/";
                                name = name + std::to_string(dzien) + "v" + std::to_string(miesiac + 1) + "v" + std::to_string(rok + 1900) + ".txt";
                                plik.open(name.c_str(), std::ios::out);
                                plik << "red";
                                plik.close();
                            }
                        }
                        if (pozycja.x >= 833 && pozycja.x <= 1063 && pozycja.y >= 452 && pozycja.y <= 588) //czw3
                        {
                            if (objects[17].getTexture() == &calendarblue || objects[17].getTexture() == &calendarred || objects[17].getTexture() == &calendarred)
                            {
                                if (data->tm_wday != 0)
                                {
                                    dzien = 19 - data->tm_wday;
                                    miesiac = data->tm_mon;
                                    rok = data->tm_year;
                                }
                                else
                                {
                                    dzien = 19 - 7;
                                    miesiac = data->tm_mon;
                                    rok = data->tm_year;
                                    //std::cout << "stalosiecoma";
                                }
                                name = "calendar/";
                                name = name + std::to_string(dzien) + "v" + std::to_string(miesiac + 1) + "v" + std::to_string(rok + 1900) + ".txt";
                                plik.open(name.c_str(), std::ios::out);
                                plik << "red";
                                plik.close();
                            }
                        }
                        if (pozycja.x >= 1063 && pozycja.x <= 1293 && pozycja.y >= 452 && pozycja.y <= 588) //pt3
                        {
                            if (objects[18].getTexture() == &calendarblue || objects[18].getTexture() == &calendarred || objects[18].getTexture() == &calendarred)
                            {
                                if (data->tm_wday != 0)
                                {
                                    dzien = 20 - data->tm_wday;
                                    miesiac = data->tm_mon;
                                    rok = data->tm_year;
                                }
                                else
                                {
                                    dzien = 20 - 7;
                                    miesiac = data->tm_mon;
                                    rok = data->tm_year;
                                }
                                name = "calendar/";
                                name = name + std::to_string(dzien) + "v" + std::to_string(miesiac + 1) + "v" + std::to_string(rok + 1900) + ".txt";
                                plik.open(name.c_str(), std::ios::out);
                                plik << "red";
                                plik.close();
                            }
                        }
                        if (pozycja.x >= 1293 && pozycja.x <= 1523 && pozycja.y >= 452 && pozycja.y <= 588) //sob3
                        {
                            if (objects[19].getTexture() == &calendarblue || objects[19].getTexture() == &calendarred || objects[19].getTexture() == &calendarred)
                            {
                                if (data->tm_wday != 0)
                                {
                                    dzien = 21 - data->tm_wday;
                                    miesiac = data->tm_mon;
                                    rok = data->tm_year;
                                }
                                else
                                {
                                    dzien = 21 - 7;
                                    miesiac = data->tm_mon;
                                    rok = data->tm_year;
                                }
                                name = "calendar/";
                                name = name + std::to_string(dzien) + "v" + std::to_string(miesiac + 1) + "v" + std::to_string(rok + 1900) + ".txt";
                                plik.open(name.c_str(), std::ios::out);
                                plik << "red";
                                plik.close();
                            }
                        }
                        if (pozycja.x >= 1523 && pozycja.x <= 1753 && pozycja.y >= 452 && pozycja.y <= 588) //nd3
                        {
                            if (objects[20].getTexture() == &calendarblue || objects[20].getTexture() == &calendarred || objects[20].getTexture() == &calendarred)
                            {
                                if (data->tm_wday != 0)
                                {
                                    dzien = 22 - data->tm_wday;
                                    miesiac = data->tm_mon;
                                    rok = data->tm_year;
                                }
                                else
                                {
                                    dzien = 22 - 7;
                                    miesiac = data->tm_mon;
                                    rok = data->tm_year;
                                }
                                name = "calendar/";
                                name = name + std::to_string(dzien) + "v" + std::to_string(miesiac + 1) + "v" + std::to_string(rok + 1900) + ".txt";
                                plik.open(name.c_str(), std::ios::out);
                                plik << "red";
                                plik.close();
                            }
                        }
                        if (pozycja.x >= 143 && pozycja.x <= 373 && pozycja.y >= 588 && pozycja.y <= 724) //pon4
                        {
                            if (objects[21].getTexture() == &calendarblue || objects[21].getTexture() == &calendarred || objects[21].getTexture() == &calendarred)
                            {
                                if (data->tm_wday != 0)
                                {
                                    dzien = 23 - data->tm_wday;
                                    miesiac = data->tm_mon;
                                    rok = data->tm_year;
                                }
                                else
                                {
                                    dzien = 23 - 7;
                                    miesiac = data->tm_mon;
                                    rok = data->tm_year;
                                }
                                name = "calendar/";
                                name = name + std::to_string(dzien) + "v" + std::to_string(miesiac + 1) + "v" + std::to_string(rok + 1900) + ".txt";
                                plik.open(name.c_str(), std::ios::out);
                                plik << "red";
                                plik.close();
                            }
                        }
                        if (pozycja.x >= 373 && pozycja.x <= 603 && pozycja.y >= 588 && pozycja.y <= 724) //wt4
                        {
                            if (objects[22].getTexture() == &calendarblue || objects[22].getTexture() == &calendarred || objects[22].getTexture() == &calendarred)
                            {
                                if (data->tm_wday != 0)
                                {
                                    dzien = 24 - data->tm_wday;
                                    miesiac = data->tm_mon;
                                    rok = data->tm_year;
                                }
                                else
                                {
                                    dzien = 24 - 7;
                                    miesiac = data->tm_mon;
                                    rok = data->tm_year;
                                }
                                name = "calendar/";
                                name = name + std::to_string(dzien) + "v" + std::to_string(miesiac + 1) + "v" + std::to_string(rok + 1900) + ".txt";
                                plik.open(name.c_str(), std::ios::out);
                                plik << "red";
                                plik.close();
                            }
                        }
                        if (pozycja.x >= 603 && pozycja.x <= 833 && pozycja.y >= 588 && pozycja.y <= 724) //sr4
                        {
                            if (objects[23].getTexture() == &calendarblue || objects[23].getTexture() == &calendarred || objects[23].getTexture() == &calendarred)
                            {
                                if (data->tm_wday != 0)
                                {
                                    dzien = 25 - data->tm_wday;
                                    miesiac = data->tm_mon;
                                    rok = data->tm_year;
                                }
                                else
                                {
                                    dzien = 25 - 7;
                                    miesiac = data->tm_mon;
                                    rok = data->tm_year;
                                }
                                name = "calendar/";
                                name = name + std::to_string(dzien) + "v" + std::to_string(miesiac + 1) + "v" + std::to_string(rok + 1900) + ".txt";
                                plik.open(name.c_str(), std::ios::out);
                                plik << "red";
                                plik.close();
                            }
                        }
                        if (pozycja.x >= 833 && pozycja.x <= 1063 && pozycja.y >= 588 && pozycja.y <= 724) //czw4
                        {
                            if (objects[24].getTexture() == &calendarblue || objects[24].getTexture() == &calendarred || objects[24].getTexture() == &calendarred)
                            {
                                if (data->tm_wday != 0)
                                {
                                    dzien = 26 - data->tm_wday;
                                    miesiac = data->tm_mon;
                                    rok = data->tm_year;
                                }
                                else
                                {
                                    dzien = 26 - 7;
                                    miesiac = data->tm_mon;
                                    rok = data->tm_year;
                                }
                                name = "calendar/";
                                name = name + std::to_string(dzien) + "v" + std::to_string(miesiac + 1) + "v" + std::to_string(rok + 1900) + ".txt";
                                plik.open(name.c_str(), std::ios::out);
                                plik << "red";
                                plik.close();
                            }
                        }
                        if (pozycja.x >= 1063 && pozycja.x <= 1293 && pozycja.y >= 588 && pozycja.y <= 724) //pt4
                        {
                            if (objects[25].getTexture() == &calendarblue || objects[25].getTexture() == &calendarred || objects[25].getTexture() == &calendarred)
                            {
                                if (data->tm_wday != 0)
                                {
                                    dzien = 27 - data->tm_wday;
                                    miesiac = data->tm_mon;
                                    rok = data->tm_year;
                                }
                                else
                                {
                                    dzien = 27 - 7;
                                    miesiac = data->tm_mon;
                                    rok = data->tm_year;
                                }
                                name = "calendar/";
                                name = name + std::to_string(dzien) + "v" + std::to_string(miesiac + 1) + "v" + std::to_string(rok + 1900) + ".txt";
                                plik.open(name.c_str(), std::ios::out);
                                plik << "red";
                                plik.close();
                            }
                        }
                        if (pozycja.x >= 1293 && pozycja.x <= 1523 && pozycja.y >= 588 && pozycja.y <= 724) //sob4
                        {
                            if (objects[26].getTexture() == &calendarblue || objects[26].getTexture() == &calendarred || objects[26].getTexture() == &calendarred)
                            {
                                if (data->tm_wday != 0)
                                {
                                    dzien = 28 - data->tm_wday;
                                    miesiac = data->tm_mon;
                                    rok = data->tm_year;
                                }
                                else
                                {
                                    dzien = 28 - 7;
                                    miesiac = data->tm_mon;
                                    rok = data->tm_year;
                                }
                                name = "calendar/";
                                name = name + std::to_string(dzien) + "v" + std::to_string(miesiac + 1) + "v" + std::to_string(rok + 1900) + ".txt";
                                plik.open(name.c_str(), std::ios::out);
                                plik << "red";
                                plik.close();
                            }
                        }
                        if (pozycja.x >= 1523 && pozycja.x <= 1753 && pozycja.y >= 588 && pozycja.y <= 724) //nd4
                        {
                            if (objects[27].getTexture() == &calendarblue || objects[27].getTexture() == &calendarred || objects[27].getTexture() == &calendarred)
                            {
                                if (data->tm_wday != 0)
                                {
                                    dzien = 29 - data->tm_wday;
                                    miesiac = data->tm_mon;
                                    rok = data->tm_year;
                                }
                                else
                                {
                                    dzien = 29 - 7;
                                    miesiac = data->tm_mon;
                                    rok = data->tm_year;
                                }
                                name = "calendar/";
                                name = name + std::to_string(dzien) + "v" + std::to_string(miesiac + 1) + "v" + std::to_string(rok + 1900) + ".txt";
                                plik.open(name.c_str(), std::ios::out);
                                plik << "red";
                                plik.close();
                            }
                        }
                        if (pozycja.x >= 143 && pozycja.x <= 373 && pozycja.y >= 724 && pozycja.y <= 860) //pon5
                        {
                            if (objects[28].getTexture() == &calendarblue || objects[28].getTexture() == &calendarred || objects[28].getTexture() == &calendarred)
                            {
                                if (data->tm_wday != 0)
                                {
                                    dzien = 30 - data->tm_wday;
                                    miesiac = data->tm_mon;
                                    rok = data->tm_year;
                                }
                                else
                                {
                                    dzien = 30 - 7;
                                    miesiac = data->tm_mon;
                                    rok = data->tm_year;
                                }
                                name = "calendar/";
                                name = name + std::to_string(dzien) + "v" + std::to_string(miesiac + 1) + "v" + std::to_string(rok + 1900) + ".txt";
                                plik.open(name.c_str(), std::ios::out);
                                plik << "red";
                                plik.close();
                            }
                        }
                        if (pozycja.x >= 373 && pozycja.x <= 603 && pozycja.y >= 724 && pozycja.y <= 860) //wt5
                        {
                            if (objects[29].getTexture() == &calendarblue || objects[29].getTexture() == &calendarred || objects[29].getTexture() == &calendarred)
                            {
                                if (data->tm_wday != 0)
                                {
                                    dzien = 31 - data->tm_wday;
                                    miesiac = data->tm_mon;
                                    rok = data->tm_year;
                                }
                                else
                                {
                                    dzien = 31 - 7;
                                    miesiac = data->tm_mon;
                                    rok = data->tm_year;
                                }
                                name = "calendar/";
                                name = name + std::to_string(dzien) + "v" + std::to_string(miesiac + 1) + "v" + std::to_string(rok + 1900) + ".txt";
                                plik.open(name.c_str(), std::ios::out);
                                plik << "red";
                                plik.close();
                            }
                        }
                        if (pozycja.x >= 603 && pozycja.x <= 833 && pozycja.y >= 724 && pozycja.y <= 860) //sr5
                        {
                            if (objects[30].getTexture() == &calendarblue || objects[30].getTexture() == &calendarred || objects[30].getTexture() == &calendarred)
                            {
                                if (data->tm_wday != 0)
                                {
                                    dzien = 32 - data->tm_wday;
                                    miesiac = data->tm_mon;
                                    rok = data->tm_year;
                                }
                                else
                                {
                                    dzien = 32 - 7;
                                    miesiac = data->tm_mon;
                                    rok = data->tm_year;
                                }
                                name = "calendar/";
                                name = name + std::to_string(dzien) + "v" + std::to_string(miesiac + 1) + "v" + std::to_string(rok + 1900) + ".txt";
                                plik.open(name.c_str(), std::ios::out);
                                plik << "red";
                                plik.close();
                            }
                        }
                        if (pozycja.x >= 833 && pozycja.x <= 1063 && pozycja.y >= 724 && pozycja.y <= 860) //czw5
                        {
                            if (objects[31].getTexture() == &calendarblue || objects[31].getTexture() == &calendarred || objects[31].getTexture() == &calendarred)
                            {
                                if (data->tm_wday != 0)
                                {
                                    dzien = 33 - data->tm_wday;
                                    miesiac = data->tm_mon;
                                    rok = data->tm_year;
                                }
                                else
                                {
                                    dzien = 33 - 7;
                                    miesiac = data->tm_mon;
                                    rok = data->tm_year;
                                }
                                name = "calendar/";
                                name = name + std::to_string(dzien) + "v" + std::to_string(miesiac + 1) + "v" + std::to_string(rok + 1900) + ".txt";
                                plik.open(name.c_str(), std::ios::out);
                                plik << "red";
                                plik.close();
                            }
                        }
                        if (pozycja.x >= 1063 && pozycja.x <= 1293 && pozycja.y >= 724 && pozycja.y <= 860) //pt5
                        {
                            if (objects[32].getTexture() == &calendarblue || objects[32].getTexture() == &calendarred || objects[32].getTexture() == &calendarred)
                            {
                                if (data->tm_wday != 0)
                                {
                                    dzien = 34 - data->tm_wday;
                                    miesiac = data->tm_mon;
                                    rok = data->tm_year;
                                }
                                else
                                {
                                    dzien = 34 - 7;
                                    miesiac = data->tm_mon;
                                    rok = data->tm_year;
                                }
                                name = "calendar/";
                                name = name + std::to_string(dzien) + "v" + std::to_string(miesiac + 1) + "v" + std::to_string(rok + 1900) + ".txt";
                                plik.open(name.c_str(), std::ios::out);
                                plik << "red";
                                plik.close();
                            }
                        }
                        if (pozycja.x >= 1293 && pozycja.x <= 1523 && pozycja.y >= 724 && pozycja.y <= 860) //sob5
                        {
                            if (objects[33].getTexture() == &calendarblue || objects[33].getTexture() == &calendarred || objects[33].getTexture() == &calendarred)
                            {
                                if (data->tm_wday != 0)
                                {
                                    dzien = 35 - data->tm_wday;
                                    miesiac = data->tm_mon;
                                    rok = data->tm_year;
                                }
                                else
                                {
                                    dzien = 35 - 7;
                                    miesiac = data->tm_mon;
                                    rok = data->tm_year;
                                }
                                name = "calendar/";
                                name = name + std::to_string(dzien) + "v" + std::to_string(miesiac + 1) + "v" + std::to_string(rok + 1900) + ".txt";
                                plik.open(name.c_str(), std::ios::out);
                                plik << "red";
                                plik.close();
                            }
                        }
                        if (pozycja.x >= 1523 && pozycja.x <= 1753 && pozycja.y >= 724 && pozycja.y <= 860) //nd5
                        {
                            if (objects[34].getTexture() == &calendarblue || objects[34].getTexture() == &calendarred || objects[34].getTexture() == &calendarred)
                            {
                                if (data->tm_wday != 0)
                                {
                                    dzien = 36 - data->tm_wday;
                                    miesiac = data->tm_mon;
                                    rok = data->tm_year;
                                }
                                else
                                {
                                    dzien = 36 - 7;
                                    miesiac = data->tm_mon;
                                    rok = data->tm_year;
                                }
                                name = "calendar/";
                                name = name + std::to_string(dzien) + "v" + std::to_string(miesiac + 1) + "v" + std::to_string(rok + 1900) + ".txt";
                                plik.open(name.c_str(), std::ios::out);
                                plik << "red";
                                plik.close();
                            }
                        }
                        if (pozycja.x >= 143 && pozycja.x <= 373 && pozycja.y >= 724 && pozycja.y <= 860) //pon6
                        {
                            if (objects[35].getTexture() == &calendarblue || objects[35].getTexture() == &calendarred || objects[35].getTexture() == &calendarred)
                            {
                                if (data->tm_wday != 0)
                                {
                                    dzien = 37 - data->tm_wday;
                                    miesiac = data->tm_mon;
                                    rok = data->tm_year;
                                }
                                else
                                {
                                    dzien = 37 - 7;
                                    miesiac = data->tm_mon;
                                    rok = data->tm_year;
                                }
                                name = "calendar/";
                                name = name + std::to_string(dzien) + "v" + std::to_string(miesiac + 1) + "v" + std::to_string(rok + 1900) + ".txt";
                                plik.open(name.c_str(), std::ios::out);
                                plik << "red";
                                plik.close();
                            }
                        }
                        if (pozycja.x >= 373 && pozycja.x <= 603 && pozycja.y >= 724 && pozycja.y <= 860) //wt6
                        {
                            if (objects[36].getTexture() == &calendarblue || objects[36].getTexture() == &calendarred || objects[36].getTexture() == &calendarred)
                            {
                                if (data->tm_wday != 0)
                                {
                                    dzien = 38 - data->tm_wday;
                                    miesiac = data->tm_mon;
                                    rok = data->tm_year;
                                }
                                else
                                {
                                    dzien = 38 - 7;
                                    miesiac = data->tm_mon;
                                    rok = data->tm_year;
                                }
                                name = "calendar/";
                                name = name + std::to_string(dzien) + "v" + std::to_string(miesiac + 1) + "v" + std::to_string(rok + 1900) + ".txt";
                                plik.open(name.c_str(), std::ios::out);
                                plik << "red";
                                plik.close();
                            }
                        }
                        if (pozycja.x >= 603 && pozycja.x <= 833 && pozycja.y >= 724 && pozycja.y <= 860) //sr6
                        {
                            if (objects[37].getTexture() == &calendarblue || objects[37].getTexture() == &calendarred || objects[37].getTexture() == &calendarred)
                            {
                                if (data->tm_wday != 0)
                                {
                                    dzien = 39 - data->tm_wday;
                                    miesiac = data->tm_mon;
                                    rok = data->tm_year;
                                }
                                else
                                {
                                    dzien = 39 - 7;
                                    miesiac = data->tm_mon;
                                    rok = data->tm_year;
                                }
                                name = "calendar/";
                                name = name + std::to_string(dzien) + "v" + std::to_string(miesiac + 1) + "v" + std::to_string(rok + 1900) + ".txt";
                                plik.open(name.c_str(), std::ios::out);
                                plik << "red";
                                plik.close();
                            }
                        }
                        if (pozycja.x >= 833 && pozycja.x <= 1063 && pozycja.y >= 724 && pozycja.y <= 860) //czw6
                        {
                            if (objects[38].getTexture() == &calendarblue || objects[38].getTexture() == &calendarred || objects[38].getTexture() == &calendarred)
                            {
                                if (data->tm_wday != 0)
                                {
                                    dzien = 40 - data->tm_wday;
                                    miesiac = data->tm_mon;
                                    rok = data->tm_year;
                                }
                                else
                                {
                                    dzien = 40 - 7;
                                    miesiac = data->tm_mon;
                                    rok = data->tm_year;
                                }
                                name = "calendar/";
                                name = name + std::to_string(dzien) + "v" + std::to_string(miesiac + 1) + "v" + std::to_string(rok + 1900) + ".txt";
                                plik.open(name.c_str(), std::ios::out);
                                plik << "red";
                                plik.close();
                            }
                        }
                        if (pozycja.x >= 1063 && pozycja.x <= 1293 && pozycja.y >= 724 && pozycja.y <= 860) //pt6
                        {
                            if (objects[39].getTexture() == &calendarblue || objects[39].getTexture() == &calendarred || objects[39].getTexture() == &calendarred)
                            {
                                if (data->tm_wday != 0)
                                {
                                    dzien = 41 - data->tm_wday;
                                    miesiac = data->tm_mon;
                                    rok = data->tm_year;
                                }
                                else
                                {
                                    dzien = 41 - 7;
                                    miesiac = data->tm_mon;
                                    rok = data->tm_year;
                                }
                                name = "calendar/";
                                name = name + std::to_string(dzien) + "v" + std::to_string(miesiac + 1) + "v" + std::to_string(rok + 1900) + ".txt";
                                plik.open(name.c_str(), std::ios::out);
                                plik << "red";
                                plik.close();
                            }
                        }
                        if (pozycja.x >= 1293 && pozycja.x <= 1523 && pozycja.y >= 724 && pozycja.y <= 860) //sob6
                        {
                            if (objects[40].getTexture() == &calendarblue || objects[40].getTexture() == &calendarred || objects[40].getTexture() == &calendarred)
                            {
                                if (data->tm_wday != 0)
                                {
                                    dzien = 42 - data->tm_wday;
                                    miesiac = data->tm_mon;
                                    rok = data->tm_year;
                                }
                                else
                                {
                                    dzien = 42 - 7;
                                    miesiac = data->tm_mon;
                                    rok = data->tm_year;
                                }
                                name = "calendar/";
                                name = name + std::to_string(dzien) + "v" + std::to_string(miesiac + 1) + "v" + std::to_string(rok + 1900) + ".txt";
                                plik.open(name.c_str(), std::ios::out);
                                plik << "red";
                                plik.close();
                            }
                        }
                        if (pozycja.x >= 1523 && pozycja.x <= 1753 && pozycja.y >= 724 && pozycja.y <= 860) //nd6
                        {
                            if (objects[41].getTexture() == &calendarblue || objects[41].getTexture() == &calendarred || objects[41].getTexture() == &calendarred)
                            {
                                if (data->tm_wday != 0)
                                {
                                    dzien = 43 - data->tm_wday;
                                    miesiac = data->tm_mon;
                                    rok = data->tm_year;
                                }
                                else
                                {
                                    dzien = 43 - 7;
                                    miesiac = data->tm_mon;
                                    rok = data->tm_year;
                                }
                                name = "calendar/";
                                name = name + std::to_string(dzien) + "v" + std::to_string(miesiac + 1) + "v" + std::to_string(rok + 1900) + ".txt";
                                plik.open(name.c_str(), std::ios::out);
                                plik << "red";
                                plik.close();
                            }
                        }
                        change_state = true;
                        state = 0;
                    }
                }
            }

            //pisanie tekstu
            if (event.type == sf::Event::TextEntered) //wysokosc max 8
            {
                if (texting)
                {
                    if (event.text.unicode == '\b')
                    {
                        if (playerInput.getSize() != 0)
                            playerInput.erase(playerInput.getSize() - 1, 1);
                        tekst.setString(playerInput);
                    }
                    else if (event.text.unicode == '\r')
                    {
                        if (licznik_wysokosc < 8)
                        {
                            playerInput += "\n";
                            licznik_wysokosc += 1;
                        }
                    }
                    else if (event.text.unicode < 128)
                    {
                        playerInput += event.text.unicode;
                        tekst.setString(playerInput); //postawienie znaku
                        if (tekst.findCharacterPos(playerInput.getSize() + 1).x >= 840 + szerokosc) //test czy nie wychodzi poza limit
                        {
                            if (licznik_wysokosc < 8)
                            {
                                przenoszenie = playerInput[playerInput.getSize() - 1]; //usuniecie znaku, dodanie \n i przywrocenie znaku na koncu
                                playerInput.erase(playerInput.getSize() - 1, 1);
                                playerInput += "\n";
                                playerInput += przenoszenie;
                                licznik_wysokosc += 1;
                            }
                            else
                            {
                                playerInput.erase(playerInput.getSize() - 1, 1);
                            }
                        }
                    }
                }
            }//koniec pisania tekstu

        }

        window.clear(sf::Color(211,211,211,255));
        for (int i = 0; i < przyciski.size(); i++)
            window.draw(przyciski[i]);
        
        for (int i = 0; i < objects.size(); i++)
            window.draw(objects[i]);
        //window.draw(shape);
        //window.draw(tekst);

        for (int i = 0; i < teksty.size(); i++)
            window.draw(teksty[i]);
        window.draw(addoner[4]);
        window.draw(addoner[0]);
        window.draw(addoner[1]);
        window.draw(addoner[2]);
        window.draw(addoner[3]);
        window.draw(tekst);
        window.display();
    }

    return 0;
}