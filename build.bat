g++ -c main.cpp -O4 -ffast-math -IF:/Code/C++/SFML-2.5.1/include -IF:/Code/C++/attractors/ -DSFML_STATIC

g++ main.o -o main -LF:/Code/C++/SFML-2.5.1/lib -lsfml-graphics-s -lsfml-window-s -lsfml-system-s -lopengl32 -lwinmm -lgdi32 -lsfml-main

del main.o

main