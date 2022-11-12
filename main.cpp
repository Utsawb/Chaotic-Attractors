#include <SFML/Graphics.hpp>
#include <iostream>
#include <functional>
#include <SFML/System.hpp>

#define WIDTH 1920
#define HEIGHT 1080
#define N 1000000

#include <Particle.hpp>

void particle_update(Particle* arr, int start, int end) 
{
    while(!(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)))
    {
        for(int i = start; i < end; i++)
        {
            arr[i].update();
        }
    }
}

void update_vertex_array(Particle* arr, int start, int end, sf::VertexArray &vert_array)
{
    for(int i = start; i < end; i++) 
    {
        vert_array[i].position = arr[i].position;
    }
}

int main()
{
    // create the window
    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Particle go weee", sf::Style::Fullscreen);

    // window stuff
    window.setFramerateLimit(60);
    sf::View view(sf::Vector2f(0, 0), sf::Vector2f(16, 9));

    // housekeeping for input
    window.setKeyRepeatEnabled(false);

    // creating the particles
    Particle* p = new Particle[N];
    for(int i = 0; i < N; i++) 
    {
        p[i] = Particle(sf::Vector2f(i/10, 0));
    }

    sf::Thread t1(std::bind(&particle_update, p, 0, N/4));
    sf::Thread t2(std::bind(&particle_update, p, N/4, N/2));
    sf::Thread t3(std::bind(&particle_update, p, N/2, N*3/4));
    sf::Thread t4(std::bind(&particle_update, p, N*3/4, N));
    t1.launch();
    t2.launch();
    t3.launch();
    t4.launch();

    sf::VertexArray vert_arr1(sf::Points, N/2);
    sf::VertexArray vert_arr2(sf::Points, N/2);
    for(int i = 0; i < N/2; i++)
    {
        vert_arr1[i].color = sf::Color(0, 0, 0, 255);
        vert_arr2[i].color = sf::Color(0, 0, 0, 255);
    }

    // run the program as long as the window is open
    while (window.isOpen())
    {
        // check all the window's events that were triggered since the last iteration of the loop
        sf::Event event;
        while (window.pollEvent(event))
        {
            // "close requested" event: we close the window
            if (event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) window.close();
            if (event.key.code == sf::Keyboard::Num1 || event.key.code == sf::Keyboard::Num2 || event.key.code == sf::Keyboard::Num3 || event.key.code == sf::Keyboard::Num4 || event.key.code == sf::Keyboard::Num5)
            {
                for(int i = 0; i < N; i++) 
                {
                    p[i].change_selector(event.key.code - 27);
                }
            }
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) view.zoom(0.95);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) view.zoom(1.05);

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        {
            for(int i = 0; i < N; i++) 
            {
                p[i].change_offset(0.025);
            }
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        {
            for(int i = 0; i < N; i++) 
            {
                p[i].change_offset(-0.025);
            }
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
        {
            for(int i = 0; i < N; i++) 
            {
                p[i].randomize();
            }
        }
        
        // draw to texture
        window.setView(view);
        window.clear(sf::Color::White);
        update_vertex_array(p, 0, N/2, vert_arr1);
        update_vertex_array(p, 0, N/2, vert_arr2);
        window.draw(vert_arr1);
        window.draw(vert_arr2);
        window.display();
    }
    t1.wait();
    t2.wait();
    t3.wait();
    t4.wait();
    delete p;

    return 0;
}