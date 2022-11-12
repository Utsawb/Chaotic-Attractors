#include <SFML/Graphics.hpp>
#include <cmath>
#include <cstdlib>

class Particle {
    public:
        sf::Vector2f position;
        Particle() { }

        Particle(sf::Vector2f p) 
        {
            position = p;
            selector = 0;
        }

        void change_selector(int n)
        {
            selector = n;
        }

        void change_offset(float s)
        {
            offset += s;
        }

        void randomize()
        {
            position.x = rand() % WIDTH;
            position.y = rand() % HEIGHT;
        }

        void update() 
        {
            float x = position.x;
            float y = position.y;
            position.x = (sinf(a[selector] * y) + (c[selector] + offset) * cosf(a[selector] * x));
            position.y = (sinf(b[selector] * x) + (d[selector] + offset) * cosf(b[selector] * y));
        }
    private:
        int selector;
        float offset;
        float a[6] = {-1.7, -1.7, 1.5, -2.239, -1.7, 0};
        float b[6] = {1.3, 1.8, -1.8, -2.956, 1.8, 0};
        float c[6] = {-0.1, -0.9, 1.6, 1.272, -1.9, 0};
        float d[6] = {-1.21, -0.4, 2.0, 1.419, -0.4, 0};
};