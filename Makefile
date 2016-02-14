all: sample2D

sample2D: glad.c Main.cpp Controls.cpp Untouchable.cpp Objects.cpp 
	g++ glad.c Main.cpp Controls.cpp Objects.cpp Untouchable.cpp -lGL -lglfw -lSOIL -ldl -I/usr/local/include -L/usr/local/include -L/usr/local/lib ./libIrrKlang.so ./ikpMP3.so

