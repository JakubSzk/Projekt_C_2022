#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>


int main()
{
    sf::RenderWindow window(sf::VideoMode(1000, 500), "SFML works!");
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);
    sf::Font font;
    font.loadFromFile("Jack.TTF");
    sf::Text tekst;
    tekst.setFont(font);
    tekst.setCharacterSize(20);
    tekst.setFillColor(sf::Color::Red);
    tekst.setString("ABCDEFGH");
    sf::String playerInput;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::TextEntered)
            {
                playerInput += event.text.unicode;
                tekst.setString(playerInput);
            }
        }

        window.clear();
        window.draw(shape);
        window.draw(tekst);
        window.display();
    }

    return 0;
}