#include <SFML/Graphics.hpp>
#include <iostream>

int main()
{
    sf::RenderWindow window(
        sf::VideoMode(sf::Vector2u(1000, 700)),
        "Mayatnik"
    );

    window.setFramerateLimit(60);

    while (window.isOpen())
    {
        while (auto event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();

            if (event->is<sf::Event::KeyPressed>())
            {
                if (auto* key = event->getIf<sf::Event::KeyPressed>())
                {
                    if (key->code == sf::Keyboard::Key::Escape)
                        window.close();
                }
            }
        }

        window.clear(sf::Color(18, 24, 42));
        window.display();
    }

    return 0;
}
