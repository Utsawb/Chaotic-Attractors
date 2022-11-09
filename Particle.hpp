#include <SFML/Graphics.hpp>
#include <cmath>

#define WIDTH 1280
#define HEIGHT 720

class Particle {
    public:
        float scale;
        Particle() { }

        Particle(sf::Vector2f p, sf::Color c, float r) 
        {
            scale = WIDTH / HEIGHT * 120.0;
            position = p;
            shape.setRadius(r);
            shape.setFillColor(c);
            selector = 0;
            constraints = 4;
        }

        void change_selector(int n)
        {
            selector = n;
        }

        void change_scale(float s) 
        {
            scale += s;
        }

        void update() 
        {
            float x = position.x;
            float y = position.y;
            position.x = sinf(a[selector] * y) + c[selector] * cosf(a[selector] * x);
            position.y = sinf(b[selector] * x) + d[selector] * cosf(b[selector] * y);
        }

        void draw(sf::RenderTexture &texture) 
        {
            float x = position.x * scale + WIDTH/2;
            float y = position.y * scale + HEIGHT/2;
            shape.setPosition(x, y);
            texture.draw(shape);
        }
    private:
        sf::Vector2f position;
        sf::CircleShape shape;
        int selector;
        int constraints;
        float a[5] = {-1.7, -1.7, 1.5, -2.239, -1.7};
        float b[5] = {1.3, 1.8, -1.8, -2.956, 1.8};
        float c[5] = {-0.1, -0.9, 1.6, 1.272, -1.9};
        float d[5] = {-1.21, -0.4, 2.0, 1.419, -0.4};
};