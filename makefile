CXX = g++
CXXFLAGS = -std=c++11 -g
VALGRIND_FLAGS = -v --leak-check=full --show-leak-kinds=all --error-exitcode=99

SOURCES = main.cpp Resource.cpp PromotionCard.cpp \
      KnightCard.cpp VictoryPointCard.cpp Catan.cpp  Player.cpp Board.cpp PlotOfLand.cpp ResourceType.cpp LandType.cpp DevelopmentCardType.cpp \
	  Point2D.cpp Road.cpp 
OBJECTS = $(SOURCES:.cpp=.o)

run: catan
	./catan

catan: $(OBJECTS)
	$(CXX) $(CXXFLAGS) $^ -o $@ -lstdc++

test: TestCounter.o Test.o Player.o Board.o Catan.o LandType.o Resource.o PlotOfLand.o Point2D.o ResourceType.o PromotionCard.o VictoryPointCard.o \
KnightCard.o Road.o DevelopmentCardType.o
	$(CXX) $(CXXFLAGS) $^ -o $@ -lstdc++ -lm

tidy:
	clang-tidy $(SOURCES) -checks=bugprone-*,clang-analyzer-*,cppcoreguidelines-*,performance-*,portability-*,readability-*,-cppcoreguidelines-pro-bounds-pointer-arithmetic,-cppcoreguidelines-owning-memory --warnings-as-errors=-* --

valgrind: demo test
	valgrind --tool=memcheck $(VALGRIND_FLAGS) ./demo 2>&1 | { egrep "lost| at " || true; }
	valgrind --tool=memcheck $(VALGRIND_FLAGS) ./test 2>&1 | { egrep "lost| at " || true; }

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f *.o catan test
