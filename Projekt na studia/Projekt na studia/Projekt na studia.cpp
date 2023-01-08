#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>


int main()
{
    sf::RenderWindow window(sf::VideoMode(1900, 1000), "Qest List");
    sf::RectangleShape shape(sf::Vector2f(300, 300));
    shape.setFillColor(sf::Color::Green);
    sf::Font font;
    font.loadFromFile("Jack.TTF");
    sf::Text tekst;
    tekst.setFont(font);
    tekst.setCharacterSize(20);
    tekst.setFillColor(sf::Color::Red);
    tekst.setString("ABCDEFGH");
    sf::String playerInput, przenoszenie;

    //vectory ze zmieniajaca sie iloscia zasobow
    std::vector<sf::RectangleShape> przyciski; //vector ze wszystkimi przyciskami
    std::vector<int> Xprzyciski; //po dwie kolejne zmienne na kazdy przycisk (poczatek i koniec)
    std::vector<int> Yprzyciski; //po dwie kolejne zmienne na kazdy przycisk (gora i dol)
    std::vector<sf::Text> teksty; //vector z tekstami do wyswietlenia

    sf::Vector2i pozycja;
    int szerokosc = 300;
    int state = -1;
    bool change_state = true;
    while (window.isOpen())
    {
        if (change_state) //wczytywanie i usuwanie
        {
            if (state == -1) //menu glowne
            {
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
                for (int i = 0; i < 48; i++)
                    przyciski.push_back(sf::RectangleShape()); //tworzenie wszystkich przyciskow
                int ey = 180;
                for (int i = 0; i < 42; i++)
                {
                    przyciski[i].setSize(sf::Vector2f(115, 68));
                    przyciski[i].setFillColor(sf::Color::Green); //przyciski kalendarza na zielono i wymiary
                }
                for (int i = 0; i < 6; i++)
                {
                    przyciski[7 * i + 0].setPosition(sf::Vector2f(200, ey));
                    przyciski[7 * i + 1].setPosition(sf::Vector2f(430, ey));
                    przyciski[7 * i + 2].setPosition(sf::Vector2f(660, ey)); //kolejne dni tygodnia
                    przyciski[7 * i + 3].setPosition(sf::Vector2f(891, ey));
                    przyciski[7 * i + 4].setPosition(sf::Vector2f(1125, ey));
                    przyciski[7 * i + 5].setPosition(sf::Vector2f(1355, ey));
                    przyciski[7 * i + 6].setPosition(sf::Vector2f(1585, ey));
                    ey += 136;
                }
                przyciski[42].setSize(sf::Vector2f(50, 600)); //przycisk w lewo
                przyciski[42].setPosition(sf::Vector2f(30, 200));
                przyciski[43].setSize(sf::Vector2f(50, 600)); //przycisk w prawo
                przyciski[43].setPosition(sf::Vector2f(1820, 200));
                przyciski[43].setFillColor(sf::Color::Blue);
                przyciski[42].setFillColor(sf::Color::Blue);
                for (int i = 0; i < 4; i++)
                {
                    przyciski[i + 44].setSize(sf::Vector2f(255, 50)); //ustawienia dla paska funkcji
                    przyciski[i + 44].setFillColor(sf::Color::Cyan);
                }
                przyciski[44].setPosition(sf::Vector2f(250, 30));
                przyciski[45].setPosition(sf::Vector2f(631, 30));
                przyciski[46].setPosition(sf::Vector2f(1014, 30)); //pozycje dla paska funkcji
                przyciski[47].setPosition(sf::Vector2f(1395, 30));
                for (int i = 0; i < 46; i++)
                    teksty.push_back(sf::Text()); //tworzenie wszystkich tekst
                for (int i = 0; i < 46; i++)
                {
                    teksty[i].setFont(font);
                    teksty[i].setCharacterSize(20);
                    teksty[i].setFillColor(sf::Color::Black);
                    teksty[i].setString(std::to_string(i));
                }
                ey = 180;
                for (int i = 0; i < 6; i++)
                {
                    teksty[7 * i + 0].setPosition(sf::Vector2f(200, ey));
                    teksty[7 * i + 1].setPosition(sf::Vector2f(430, ey));
                    teksty[7 * i + 2].setPosition(sf::Vector2f(660, ey)); //kolejne dni tygodnia
                    teksty[7 * i + 3].setPosition(sf::Vector2f(891, ey));
                    teksty[7 * i + 4].setPosition(sf::Vector2f(1125, ey));
                    teksty[7 * i + 5].setPosition(sf::Vector2f(1355, ey));
                    teksty[7 * i + 6].setPosition(sf::Vector2f(1585, ey));
                    ey += 136;
                }
                teksty[42].setString("MENU");
                teksty[43].setString("BOARD");
                teksty[44].setString("QUEST LIST"); //teksty dla przyciskow gornych
                teksty[45].setString("QUEST LOG");

                teksty[42].setPosition(sf::Vector2f(250, 30));
                teksty[43].setPosition(sf::Vector2f(631, 30)); //umiejcowienie przyciskow gornych
                teksty[44].setPosition(sf::Vector2f(1014, 30));
                teksty[45].setPosition(sf::Vector2f(1395, 30));
            }
            if (state == 1) //board
            {
                przyciski.clear();
                teksty.clear();
                Xprzyciski.clear();
                Yprzyciski.clear();

                for (int i = 0; i < 26; i++)
                {
                    przyciski.push_back(sf::RectangleShape()); //wszystkie elementy
                }
                for (int i = 0; i < 9; i++)
                {
                    przyciski[i].setSize(sf::Vector2f(250, 250));
                    przyciski[i].setFillColor(sf::Color::Green);
                }

                przyciski[0].setPosition(sf::Vector2f(110, 200));
                przyciski[1].setPosition(sf::Vector2f(410, 200));
                przyciski[2].setPosition(sf::Vector2f(110, 485));
                przyciski[3].setPosition(sf::Vector2f(410, 485)); //pozycje kolejnych kartek
                przyciski[4].setPosition(sf::Vector2f(110, 770));
                przyciski[5].setPosition(sf::Vector2f(410, 770));
                przyciski[6].setPosition(sf::Vector2f(1600, 200));
                przyciski[7].setPosition(sf::Vector2f(1600, 485));
                przyciski[8].setPosition(sf::Vector2f(1600, 770));

                for (int i = 9; i < 18; i++)
                {
                    przyciski[i].setSize(sf::Vector2f(220, 50)); //rozmiary zdjec
                    przyciski[i].setFillColor(sf::Color::Yellow); //color
                }

                przyciski[9].setPosition(sf::Vector2f(125, 215));
                przyciski[10].setPosition(sf::Vector2f(425, 215));
                przyciski[11].setPosition(sf::Vector2f(125, 500));
                przyciski[12].setPosition(sf::Vector2f(425, 500));
                przyciski[13].setPosition(sf::Vector2f(125, 785));
                przyciski[14].setPosition(sf::Vector2f(425, 785)); //pozycje zdjec
                przyciski[15].setPosition(sf::Vector2f(1615, 215));
                przyciski[16].setPosition(sf::Vector2f(1615, 500));
                przyciski[17].setPosition(sf::Vector2f(1615, 785));

                for (int i = 18; i < 22; i++)
                {
                    przyciski[i].setSize(sf::Vector2f(255, 50)); //przyciski gorne
                    przyciski[i].setFillColor(sf::Color::Blue);
                }

                przyciski[18].setPosition(sf::Vector2f(250, 30));
                przyciski[19].setPosition(sf::Vector2f(631, 30)); //pozycje przyciskow gornych
                przyciski[20].setPosition(sf::Vector2f(1014, 30));
                przyciski[21].setPosition(sf::Vector2f(1395, 30));

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

                for (int i = 0; i < 4; i++)
                    teksty.push_back(sf::Text()); //tworzenie wszystkich tekst
                for (int i = 0; i < 4; i++)
                {
                    teksty[i].setFont(font);
                    teksty[i].setCharacterSize(20);
                    teksty[i].setFillColor(sf::Color::Black);
                }
                teksty[0].setString("CALENDAR");
                teksty[1].setString("MENU");
                teksty[2].setString("QUEST LIST"); //teksty dla przyciskow gornych
                teksty[3].setString("QUEST LOG");

                teksty[0].setPosition(sf::Vector2f(250, 30));
                teksty[1].setPosition(sf::Vector2f(631, 30)); //umiejcowienie przyciskow gornych
                teksty[2].setPosition(sf::Vector2f(1014, 30));
                teksty[3].setPosition(sf::Vector2f(1395, 30));
            }
            if (state == 2) //quest list
            {
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
                przyciski.clear();
                teksty.clear();
                Xprzyciski.clear();
                Yprzyciski.clear();

                przyciski.push_back(sf::RectangleShape(sf::Vector2f(634, 66)));
                teksty.push_back(sf::Text());

                teksty[0].setFont(font);
                teksty[0].setCharacterSize(20);
                teksty[0].setFillColor(sf::Color::White);
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
            przyciski[44].setFillColor(sf::Color::Cyan);
            if (pozycja.x >= 255 && pozycja.x <= 505 && pozycja.y >= 30 && pozycja.y <= 80) //board
                przyciski[44].setFillColor(sf::Color::Magenta);

            przyciski[45].setFillColor(sf::Color::Cyan);
            if (pozycja.x >= 631 && pozycja.x <= 886 && pozycja.y >= 30 && pozycja.y <= 80) //board
                przyciski[45].setFillColor(sf::Color::Magenta);

            przyciski[46].setFillColor(sf::Color::Cyan);
            if (pozycja.x >= 1014 && pozycja.x <= 1269 && pozycja.y >= 30 && pozycja.y <= 80) //board
                przyciski[46].setFillColor(sf::Color::Magenta);

            przyciski[47].setFillColor(sf::Color::Cyan);
            if (pozycja.x >= 1395 && pozycja.x <= 1650 && pozycja.y >= 30 && pozycja.y <= 80) //board
                przyciski[47].setFillColor(sf::Color::Magenta);
        }
        else if (state == 1) //board
        {
            przyciski[18].setFillColor(sf::Color::Blue);
            if (pozycja.x >= 255 && pozycja.x <= 505 && pozycja.y >= 30 && pozycja.y <= 80) //board
                przyciski[18].setFillColor(sf::Color::Magenta);

            przyciski[19].setFillColor(sf::Color::Blue);
            if (pozycja.x >= 631 && pozycja.x <= 886 && pozycja.y >= 30 && pozycja.y <= 80) //board
                przyciski[19].setFillColor(sf::Color::Magenta);

            przyciski[20].setFillColor(sf::Color::Blue);
            if (pozycja.x >= 1014 && pozycja.x <= 1269 && pozycja.y >= 30 && pozycja.y <= 80) //board
                przyciski[20].setFillColor(sf::Color::Magenta);

            przyciski[21].setFillColor(sf::Color::Blue);
            if (pozycja.x >= 1395 && pozycja.x <= 1650 && pozycja.y >= 30 && pozycja.y <= 80) //board
                przyciski[21].setFillColor(sf::Color::Magenta);
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
                }
                else if (state == 1) //board
                {
                    if (pozycja.x >= 255 && pozycja.x <= 505 && pozycja.y >= 30 && pozycja.y <= 80) //calendar
                    {
                        std::cout << "przycisk calendar \n";
                        state = 0;
                        change_state = true;
                    }
                    if (pozycja.x >= 631 && pozycja.x <= 886 && pozycja.y >= 30 && pozycja.y <= 80) //board
                    {
                        std::cout << "przycisk menu \n";
                        state = -1;
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

            //pisanie tekstu
            if (event.type == sf::Event::TextEntered)
            {
                if (event.text.unicode == '\b')
                {
                    if(playerInput.getSize() != 0)
                        playerInput.erase(playerInput.getSize() - 1, 1);
                    tekst.setString(playerInput);
                }
                else if (event.text.unicode == '\r')
                {
                    playerInput += "\n";
                }
                else if (event.text.unicode < 128)
                {
                    playerInput += event.text.unicode;
                    tekst.setString(playerInput); //postawienie znaku
                    if (tekst.findCharacterPos(playerInput.getSize() + 1).x >= szerokosc) //test czy nie wychodzi poza limit
                    {
                        przenoszenie = playerInput[playerInput.getSize() - 1]; //usuniecie znaku, dodanie \n i przywrocenie znaku na koncu
                        playerInput.erase(playerInput.getSize() - 1, 1);
                        playerInput += "\n";
                        playerInput += przenoszenie;
                    }
                }
            }//koniec pisania tekstu

        }

        window.clear();
        for (int i = 0; i < przyciski.size(); i++)
            window.draw(przyciski[i]);
        for (int i = 0; i < teksty.size(); i++)
            window.draw(teksty[i]);
        //window.draw(shape);
        //window.draw(tekst);
        window.display();
    }

    return 0;
}