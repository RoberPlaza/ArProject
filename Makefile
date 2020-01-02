ARTOOLKITPATH := ../ARToolKit/

DIRSRC := Source/
DIROBJ := Build/
DIREXE := Programs/
DIRCFG := Config/
DIRDOC := Docs/
DIRRES := Resources/
DIRIMG := $(DIRRES)Images/
DIRMDL := $(DIRRES)Models/

CXXFLG := -Wall -std=c++14 -I$(ARTOOLKITPATH)include -c -fPIC
CXXLDL := -L$(ARTOOLKITPATH)lib -lARvideo -lARgsub -lAR -lGL -lGLU -lglut -lm 

all: debug

debug: CXXC := clang++
debug: CXXFLG += -O2 -DDEBUG -g
debug: Game

release: CXXC := g++
release: Game

dirs:
	mkdir -p $(DIRSRC) $(DIROBJ) $(DIREXE) $(DIRCFG) $(DIRDOC) $(DIRRES) $(DIRMDL)

Game: $(DIROBJ)Main.cpp.o $(DIROBJ)App.cpp.o $(DIROBJ)ConfigFile.cpp.o $(DIROBJ)Pattern.cpp.o
	$(CXXC) -o $(DIREXE)$@ $^ $(CXXLDL)

Docs:
	doxygen Doxyfile

$(DIROBJ)%.o: $(DIRSRC)%
	$(CXXC) $(CXXFLG) $^ -o $@

clean:
	rm -rf Build/* Programs/*
