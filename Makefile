DIRSRC := Source/
DIROBJ := Build/
DIREXE := Programs/
DIRCFG := Config/
DIRDOC := Docs/
DIRRES := Resources/
DIRIMG := $(DIRRES)Images/
DIRMDL := $(DIRRES)Models/

CXXFLG := -Wall -std=c++11 -I../ARToolKit/include -c
CXXLDL := -L../ARToolKit/lib -lARgsub -lARvideo -lAR -lGL -lGLU -lglut -lm 

CXXC := clang++

all: Game

dirs:
	mkdir -p $(DIRSRC) $(DIROBJ) $(DIREXE) $(DIRCFG) $(DIRDOC) $(DIRRES) $(DIRMDL)

Game: $(DIROBJ)Main.cpp.o $(DIROBJ)App.cpp.o $(DIROBJ)ConfigFile.cpp.o
	$(CXXC) -o $(DIREXE)$@ $^ $(CXXLDL)

Docs:
	doxygen Doxyfile

$(DIROBJ)%.o: $(DIRSRC)%
	$(CXXC) $(CXXFLG) $^ -o $@

clean:
	rm -rf Build/* Programs/*
