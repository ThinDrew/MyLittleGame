#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <ctime>

#include "map.h";

int main() {
    srand(time(0));

    int scale = 5; //во сколько раз увеличиваются пиксели

    Map map(scale);
    map.print();

    sf::RenderWindow window(sf::VideoMode(300, 600), "CURS");
    
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            
            if (event.type == sf::Event::KeyPressed and map.hero.isAlive()) {
                if (event.key.code == sf::Keyboard::Left) {
                    map.update(DIR_LEFT);
                    map.print();
                    map.show(window);
                }
                if (event.key.code == sf::Keyboard::Up) {
                    map.update(DIR_UP);
                    map.print();
                    map.show(window);
                }
                if (event.key.code == sf::Keyboard::Right) {
                    map.update(DIR_RIGHT);
                    map.print();
                    map.show(window);
                }
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

     
        window.clear();

        map.show(window);
        window.display();
    }

    return 0;
}