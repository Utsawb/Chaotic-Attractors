#include <SFML/Graphics.hpp>

#define WIDTH 1280
#define HEIGHT 720
#define N 10000

#include <Particle.hpp>

int main()
{
    // create the window
    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Particle go weee");
    sf::View view;
    view.setCenter(0, 0);
    window.setView(view);
    window.setKeyRepeatEnabled(false);
    window.setFramerateLimit(60);
    // creating the particles
    Particle* p = new Particle[N];
    for(int i = 0; i < N; i++) 
    {
        p[i] = Particle(sf::Vector2f(i/10, 0), sf::Color(255, 255, 255, 255), 1.0);
    }

    // run the program as long as the window is open
    while (window.isOpen())
    {
        // check all the window's events that were triggered since the last iteration of the loop
        sf::Event event;
        while (window.pollEvent(event))
        {
            // "close requested" event: we close the window
            if (event.type == sf::Event::Closed) window.close();
            if (event.key.code == sf::Keyboard::Num1 || event.key.code == sf::Keyboard::Num2 || event.key.code == sf::Keyboard::Num3 || event.key.code == sf::Keyboard::Num4 || event.key.code == sf::Keyboard::Num5)
            {
                for(int i = 0; i < N; i++) 
                {
                    p[i].change_selector(event.key.code - 27);
                }
            window.clear(sf::Color::Black);
            }
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        {
            for(int i = 0; i < N; i++) 
            {
                p[i].change_scale(0.5);
            }
            window.clear(sf::Color::Black);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        {
            for(int i = 0; i < N; i++) 
            {
                p[i].change_scale(-0.5);
            }
            window.clear(sf::Color::Black);
        }

        //update
        for(int i = 0; i < N; i++) 
        {
            p[i].update();
        }

        // draw
        for(int i = 0; i < N; i++) 
        {
            p[i].draw(window);
        }

        // end the current frame
        window.display();
    }

    return 0;
}