linux: 
	g++ -Dlinux -c src/main.cpp
	g++ main.o -o bin/Chaotic_Attractors -lsfml-graphics -lsfml-window -lsfml-system -lX11
	rm main.o
