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

int main()
{
    const std::string fragmentShader = \
    "uniform sampler2D texture;" \
    "void main()" \
    "{" \
    "   vec4 pixel = texture2D(texture, gl_TexCoord[0].xy);" \
    "   gl_FragColor = gl_Color * pixel * vec4(5, 5, 5, 1);" \
    "}";
    // loading the shader
    sf::Shader shader;
    if (!shader.loadFromMemory(fragmentShader, sf::Shader::Fragment))
    {
        std::cout << "Shader didnt load idiot!";
        return -1;
    }

    // create the window
    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Particle go weee", sf::Style::Fullscreen);

    // window stuff
    window.setFramerateLimit(60);

    // render texture stuff
    sf::RenderTexture renderTexture;
    renderTexture.create(WIDTH, HEIGHT);
    renderTexture.clear(sf::Color::White);

    // housekeeping for input
    window.setKeyRepeatEnabled(false);

    // creating the particles
    Particle* p = new Particle[N];
    for(int i = 0; i < N; i++) 
    {
        p[i] = Particle(sf::Vector2f(i/10, 0), sf::Color(1, 1, 1, 255));
    }

    sf::Thread t1(std::bind(&particle_update, p, 0, N/2));
    sf::Thread t2(std::bind(&particle_update, p, N/2, N));
    t1.launch();
    t2.launch();

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
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        {
            for(int i = 0; i < N; i++) 
            {
                p[i].change_scale(0.5);
            }
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        {
            for(int i = 0; i < N; i++) 
            {
                p[i].change_scale(-0.5);
            }
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        {
            for(int i = 0; i < N; i++) 
            {
                p[i].change_offset(0.05);
            }
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        {
            for(int i = 0; i < N; i++) 
            {
                p[i].change_offset(-0.05);
            }
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
        {
            for(int i = 0; i < N; i++) 
            {
                p[i].randomize();
            }
        }

        // do shader stuff
        shader.setUniform("texture", sf::Shader::CurrentTexture);
        renderTexture.draw(sf::Sprite(renderTexture.getTexture()), &shader);
        // draw to texture
        sf::VertexArray objs(sf::Points, N);
        for(int i = 0; i < N; i++) 
        {
            // p[i].draw(renderTexture);
            objs[i].position = p[i].draw_for_vertex_array();
            objs[i].color = p[i].color;
        }
        renderTexture.draw(objs);
        
        // end the current frame
        renderTexture.display();
        window.draw(sf::Sprite(renderTexture.getTexture()));
        window.display();
    }
    t1.wait();
    t2.wait();
    delete p;

    return 0;
}