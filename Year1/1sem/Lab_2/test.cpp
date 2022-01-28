/*
#include <iostream>

using namespace std;

struct point{

    double x;
    double y;
};

bool rotate(point a, point b, point c)
{
    return ((b.x - a.x) * (c.y - b.y) - (b.y - a.y)*(c.x - b.x)) > 0 ? true: false  ;

}
*/

#include <SFML/Graphics.hpp>

int main()
{
    sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        window.draw(shape);
        window.display();
    }

    return 0;
}