#include <SFML/Graphics.hpp>
#include <iostream>

#define WIDTH 1280
#define HEIGHT 720
#define N 10000

#include <Particle.hpp>

int main()
{
    const std::string fragmentShader = \
    "uniform sampler2D texture;" \
    "void main()" \
    "{" \
    "   vec4 pixel = texture2D(texture, gl_TexCoord[0].xy);" \
    "   gl_FragColor = gl_Color * pixel * vec4(0.95, 0.95, 0.95, 1);" \
    "}";
    // loading the shader
    sf::Shader shader;
    if (!shader.loadFromMemory(fragmentShader, sf::Shader::Fragment))
    {
        std::cout << "Shader didnt load idiot!";
        return -1;
    }

    // create the window
    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Particle go weee");

    // window stuff
    window.setFramerateLimit(60);

    // render texture stuff
    sf::RenderTexture renderTexture;
    renderTexture.create(WIDTH, HEIGHT);
    renderTexture.clear(sf::Color::Black);

    // housekeeping for input
    window.setKeyRepeatEnabled(false);

    // creating the particles
    Particle* p = new Particle[N];
    for(int i = 0; i < N; i++) 
    {
        p[i] = Particle(sf::Vector2f(i/10, 0), sf::Color(255, 255, 255, 255), 0.5);
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

        //update
        for(int i = 0; i < N; i++) 
        {
            p[i].update();
        }
        // do shader stuff
        shader.setUniform("texture", sf::Shader::CurrentTexture);
        renderTexture.draw(sf::Sprite(renderTexture.getTexture()), &shader);
        // draw to texture
        for(int i = 0; i < N; i++) 
        {
            p[i].draw(renderTexture);
        }
        
        // end the current frame
        renderTexture.display();
        window.draw(sf::Sprite(renderTexture.getTexture()));
        window.display();
    }

    return 0;
}