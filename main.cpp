#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <ctime>

#include "map.h";

int main() {
    srand(static_cast<unsigned int> (time(0)));

    int scale = 5; //во сколько раз увеличиваются пиксели

    sf::Clock clock;
    Map map(scale);
    map.print();

    sf::RenderWindow window(sf::VideoMode(300, 600), "CURS");
    
    while (window.isOpen())
    {
        float time = clock.getElapsedTime().asMicroseconds();
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            
            if (event.type == sf::Event::KeyPressed and map.hero.isAlive() and map.count_f == 61) {
                if (event.key.code == sf::Keyboard::Left) {
                    map.update(DIR_LEFT);
                }
                if (event.key.code == sf::Keyboard::Up) {
                    map.update(DIR_UP);
                }
                if (event.key.code == sf::Keyboard::Right) {
                    map.update(DIR_RIGHT);
                }
                if (event.key.code == sf::Keyboard::Space) {
                    map.update(DIR_DASH);
                }
                map.print();
            }

            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Escape)
                    window.close();
                if (event.key.code == sf::Keyboard::R or (event.key.code == sf::Keyboard::Enter and !map.hero.isAlive())) {
                    map.restart();

                    color(l_green);   
                    std::cout << "\n\n--------------------\n";
                    std::cout << "YOU RESTATRED A GAME\n";
                    std::cout << "--------------------\n\n";
                    color(white);

                    map.print();
                }
            }
        }

        if (time > 900 and map.count_f <= 60) {
            

            window.clear();

            map.show(window);
            
            window.display();
            map.count_f++;
            clock.restart();
        }
        if (map.count_f == 61 and time > 500000 and map.hero.isAlive()) {
            map.update(DIR_UP);
            map.print();
            map.count_f = 1;
        }
    }

    return 0;
}