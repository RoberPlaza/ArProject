ARTOOLKITPATH := ../ARToolKit/

DIRSRC := Source/
DIROBJ := Build/
DIREXE := Programs/
DIRCFG := Config/
DIRDOC := Docs/
DIRRES := Resources/
DIRIMG := $(DIRRES)Images/
DIRMDL := $(DIRRES)Models/

CXXFLG := -Wall -std=c++11 -I$(ARTOOLKITPATH)include -c #-fPIC #uncomment in case of incompatibility
CXXLDL := -L$(ARTOOLKITPATH)lib -lARvideo -lARgsub -lAR -lGL -lGLU -lglut -lm 

all: debug

debug: CXXC := clang++
debug: CXXFLG += -O2 -DDEBUG -g
debug: Game

release: CXXC := g++
release: clean
release: Game

.PHONY: Docs

dirs:
	mkdir -p $(DIRSRC) $(DIROBJ) $(DIREXE) $(DIRCFG) $(DIRDOC) $(DIRRES) $(DIRMDL)

Game: $(DIROBJ)Main.cpp.o $(DIROBJ)App.cpp.o $(DIROBJ)ConfigFile.cpp.o $(DIROBJ)Marker.cpp.o $(DIROBJ)Renderer.cpp.o $(DIROBJ)GameMode.cpp.o $(DIROBJ)MarkerMath.cpp.o
	$(CXXC) -o $(DIREXE)$@ $^ $(CXXLDL)

run:
	./$(DIREXE)Game

Docs:
	doxygen Doxyfile
	firefox $(DIRDOC)html/index.html

$(DIROBJ)%.o: $(DIRSRC)%
	$(CXXC) $(CXXFLG) $^ -o $@

clean:
	rm -rf $(DIROBJ)* $(DIREXE)* $(DIRDOC)*
