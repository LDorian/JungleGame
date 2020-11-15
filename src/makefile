PROJECT_EXE = Project

DIR_HEADERS = ../include
DIR_SOURCES = ../src
DIR_OBJECTS = ../obj

CC = g++ -std=c++11
CFLAGS = -I$(DIR_HEADERS) -ftest-coverage -fprofile-arcs
LIBS = -lm -lSDL2 -lSDL2_image

_HEADERS = Piece.hpp Rat.hpp Chat.hpp Chien.hpp Loup.hpp Panthere.hpp Tigre.hpp States.hpp Texture.hpp Button.hpp Graphics.hpp GameState.hpp GUIBoard.hpp Lion.hpp Elephant.hpp
HEADERS = $(patsubst %,$(DIR_HEADERS)/%,$(_HEADERS))

_OBJECTS = main.o Piece.o Rat.o Chat.o Chien.o Loup.o Panthere.o Tigre.o States.o Texture.o Button.o Graphics.o GameState.o GUIBoard.o Lion.o Elephant.o
OBJECTS = $(patsubst %,$(DIR_OBJECTS)/%,$(_OBJECTS))

$(DIR_OBJECTS)/%.o: %.cpp $(HEADERS)
	$(CC) -c -o $@ $< $(CFLAGS) $(LIBS)

$(PROJECT_EXE): $(OBJECTS)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

project:
	clear
	./$(PROJECT_EXE)
	
all: $(PROJECT_EXE) project

clean:
	rm -f $(DIR_OBJECTS)/*.o *~ core $(INCDIR)/*~ *.gcno *.o ../obj/*.gcda $(PROJECT_EXE) $(DIR_OBJECTS)/*. 
