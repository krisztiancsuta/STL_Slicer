# TARGET: Az eredményprogram neve (nem kötelező beleírni a .exe-t, Windowson automatikus)
TARGET = szuperszoftver

# CXX: A C++ fordító. El is hagyhatjuk. Ha nem adjuk meg, akkor a rendszer default C++ fordítója
CXX = g++	
# CXXFLAGS: A fordító flagek
CXXFLAGS = -g -Wall -pedantic
# LDFLAGS: A linker flagek (most üres)
LDFLAGS =

# SRCDIR: Ebben a könyvtárban van a forráskód (.cpp és .h fájlok)
SRCDIR   = src
# OBJDIR: Ide teszi a fordító a .o és .d fájlokat
OBJDIR   = obj
# BINDIR: Ide teszi a futtathatót (.exe)
BINDIR   = bin

# Itt automatikusan kikeressük az összes .cpp fájlt a src könyvtárban. Mindből külön .o készül majd.
SOURCES = $(wildcard $(SRCDIR)/*.cpp)
# Itt kikeressük az összes .h fájlt a src könyvtárban. Erre nincs semmi szükségünk a fordításhoz :) 
HEADERS = $(wildcard $(SRCDIR)/*.h)
# Az object fájlok. A SOURCES lista minden eleméből csinálunk egy objectet úgy, hogy a .cpp-t lecseréljük .o-ra
OBJECTS = $(SOURCES:$(SRCDIR)/%.cpp=$(OBJDIR)/%.o)
# A dependency fájlok. A SOURCES lista minden eleméből csinálunk egy dependency fájlt úgy, hogy a .cpp-t lecseréljük .d-re
DEPS = $(SOURCES:$(SRCDIR)/%.cpp=$(OBJDIR)/%.d)

# A célprogram minden objecttől függ. A fordítási szabály egyszerű.
$(BINDIR)/$(TARGET): $(OBJECTS)
	$(CXX) -o $@ $(OBJECTS) $(LDFLAGS) 

# Minden .o fájl függ az azonos nevű .cpp-től. A fordítási szabály egyszerű.
# A -MMD kapcsoló magyarázata: A fordító ezzel minden .cpp fájlból készít egy .d fájlt is, mely a .cpp fájl összes include függőségét tartalmazza. Ha pl a csucsu.cpp include-olja a csucsu.h-t, a csucsu.h pedig include-olja a bubu.h-t, akkor a fordító készít egy csucsu.d-t, melynek tartalma:
# csucsu.o: csucsu.cpp csucsu.h bubu.h
# Ez azért fontos, mert ha módosítom a bubu.h-t, akkor a csucsu.o-t újra kell fordítani.
$(OBJECTS): $(OBJDIR)/%.o : $(SRCDIR)/%.cpp
	$(CXX) -c -o $@ $(CXXFLAGS) -MMD $< 

# Itt beillesztjük a Makefile-ba a fordító által legyártott összes (.d) header-függőségi szabályt is
include $(DEPS)

$(DEPS): ;

# Ez a szabály arra jó, hogy ha beírom a parancssorba, hogy make clean (windowson mingw32-make clean), akkor letöröl minden gépi kódot és függőségi fájlt. Linuxon rm -rf obj/* bin/*
.PHONY: clean
clean:
	del obj\*.* bin\*.*

# Ez a szabály arra jó, hogy ha beírom a parancssorba, hogy make doc (windowson mingw32-make doc), akkor futtatja a doxygent.
.PHONY: doc
doc: $(SOURCES) $(HEADERS)
	doxygen
