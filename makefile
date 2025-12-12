CXX := g++
SFML_INC ?= C:/SFML/include
SFML_LIB ?= C:/SFML/lib
CXXFLAGS := -std=c++17 -Iinclude -I"$(SFML_INC)"
LDFLAGS := -L"$(SFML_LIB)"
LDLIBS := -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio

APP := ring.exe
SRC := src/ring.cpp

.PHONY: all build run clean

all: build

build: $(APP)

$(APP): $(SRC)
	$(CXX) $(CXXFLAGS) $< $(LDFLAGS) $(LDLIBS) -o $@

run: build
	./$(APP)

clean:
	$(RM) $(APP)
