#include <SFML/Graphics.hpp>


int main()
{
    sf::RenderWindow window(sf::VideoMode(1024, 1024), "Bezier curves");

    while(window.isOpen())
    {
        sf::Event event;
        while(window.pollEvent(event))
        {
            switch(event.type) {
                case sf::Event::Closed:
                    window.close();
                    break;
                default:
                    break;
            }
        }

        window.clear(sf::Color::White);
        window.display();
    }

    return 0;
}