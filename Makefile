CXX=g++
RM=rm -frd
CXXFLAGS=-Wall -Walloc-zero -Walloca -Wanalyzer-too-complex -Warith-conversion \
    -Warray-bounds=2 -Wcast-align=strict -Wcast-qual -Wconversion              \
    -Wdisabled-optimization -Wdouble-promotion -Wduplicated-branches           \
    -Wduplicated-cond -Weffc++ -Werror -Wextra -Wfatal-errors -Wfloat-equal    \
    -Wformat=2 -Wformat-overflow=2 -Wformat-signedness -Wformat-truncation=2   \
    -Wimplicit-fallthrough=5 -Winit-self -Winline -Wmain -Wmissing-braces      \
    -Wmissing-declarations -Wmissing-include-dirs -Wnon-virtual-dtor           \
    -Wnull-dereference -Wpedantic -Wredundant-decls -Wshadow=global            \
    -Wsign-conversion -Wswitch-default -Wswitch-enum -Wundef -Wuninitialized   \
    -Wunreachable-code -Wunsafe-loop-optimizations -Wunused-const-variable=2   \
    -Wunused-macros -Wzero-as-null-pointer-constant -pedantic-errors -std=c++23
LDFLAGS=
LDLIBS=-lm
SOURCES=main.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=main

all: $(SOURCES) $(EXECUTABLE)

debug: CXXFLAGS+=-Og -g
debug: all
release: CXXFLAGS+=-DNDEBUG -O3 -flto -s
release: LDFLAGS+=-O3 -flto -s
release: all

$(EXECUTABLE): $(OBJECTS)
	$(CXX) $(LDFLAGS) $(OBJECTS) $(LDLIBS) -o $@

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJECTS) $(EXECUTABLE)
