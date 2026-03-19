#include <SFML/Graphics.hpp>
#include <algorithm>
#include <cmath>
#include <iostream>

struct SState
{
    float theta; // угол
    float omega; // угловая скорость
};

static void Integrator(SState& s, float dt, float gL, float k)
{
    const float alpha = -gL * std::sin(s.theta) - k * s.omega;
    s.omega += alpha * dt;
    s.theta += s.omega * dt;
}

int main()
{
    sf::RenderWindow window(
        sf::VideoMode(sf::Vector2u(1000, 700)),
        "Mayatnik"
    );
    window.setFramerateLimit(120);

    const sf::Vector2f tochka(500.f, 120.f);
    const float Lpx = 260.f;
    const float R = 18.f;

    const float g = 9.81f;
    const float L = 1.0f;
    const float gL = g / L;

    const float Dt = 1.f / 240.f;
    float Speed = 1.0f;
    float k = 0.08f;
    bool paused = false;

    SState s{1.f, 0.f};
    const SState start = s;

    sf::CircleShape gruz(R);
    gruz.setFillColor(sf::Color(220, 90, 90));
    gruz.setOrigin(sf::Vector2f(R, R));

    std::cout << "SPACE: pause, R: reset, UP/DOWN: speed, LEFT/RIGHT: k, ESC: exit\n";

    while (window.isOpen())
    {
        while (auto event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();

            if (auto* key = event->getIf<sf::Event::KeyPressed>())
            {
                if (key->code == sf::Keyboard::Key::Escape)
                    window.close();
                if (key->code == sf::Keyboard::Key::Space)
                    paused = !paused;
                if (key->code == sf::Keyboard::Key::R)
                    s = start;
                if (key->code == sf::Keyboard::Key::Up)
                    Speed = std::min(4.0f, Speed + 0.2f);
                if (key->code == sf::Keyboard::Key::Down)
                    Speed = std::max(0.2f, Speed - 0.2f);
                if (key->code == sf::Keyboard::Key::Right)
                    k = std::min(1.0f, k + 0.01f);
                if (key->code == sf::Keyboard::Key::Left)
                    k = std::max(0.0f, k - 0.01f);
            }
        }

        if (!paused)
            Integrator(s, Dt * Speed, gL, k);

        const sf::Vector2f gruzxy(
            tochka.x + Lpx * std::sin(s.theta),
            tochka.y + Lpx * std::cos(s.theta)
        );
        gruz.setPosition(gruzxy);

        sf::Vertex sterzhen[2];
        sterzhen[0].position = tochka;
        sterzhen[0].color = sf::Color(200, 200, 220);
        sterzhen[1].position = gruzxy;
        sterzhen[1].color = sf::Color(200, 200, 220);


        window.clear(sf::Color(18, 24, 42));
        window.draw(sterzhen, 2, sf::PrimitiveType::Lines);
        window.draw(gruz);
        window.display();
    }

    return 0;
}
