EXE = test
CPP = g++
SDL_INC = `sdl2-config --cflags`
SDL_LIB = `sdl2-config --libs` -L/mingw64/lib -lSDL2_image -lSDL2_ttf
CFLAGS = -O3 -Wall $(SDL_INC)

ALL = $(EXE)

obj/%.o: src/%.cpp src/%.hpp
	$(CPP) $(CFLAGS) -c $< -o $@

$(EXE): obj/window.o obj/world.o obj/game.o obj/snake.o obj/view.o src/main.cpp
	$(CPP) $(CFLAGS) $^ -o $@ $(SDL_LIB)

clean:
	-$(RM) obj/*.o $(EXE)
