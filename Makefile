# Variables
CXX = g++
CXXFLAGS = -std=c++17 -Werror -g
SFML_FLAGS = -lsfml-graphics -lsfml-window -lsfml-system
VALGRIND_FLAGS = -v --leak-check=full --show-leak-kinds=all --error-exitcode=99\


# Source and Object files
SOURCES = node.cpp tree.cpp Demo.cpp
OBJECTS = $(SOURCES:.cpp=.o)

# Targets
all: demo

# Build the demo executable
demo: Demo.o $(OBJECTS)
	$(CXX) $(CXXFLAGS) $^ -o demo $(SFML_FLAGS)

# Pattern rule for compiling .cpp files to .o files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Run the demo
run: demo
	./demo

# Test target (commented out since it's not used in the provided Makefile)
# test: TestCounter.o Test.o $(OBJECTS)
# 	$(CXX) $(CXXFLAGS) $^ -o test

# Tidy target
tidy:
	clang-tidy $(SOURCES) -checks=bugprone-*,clang-analyzer-*,cppcoreguidelines-*,performance-*,portability-*,readability-*,-cppcoreguidelines-pro-bounds-pointer-arithmetic,-cppcoreguidelines-owning-memory --warnings-as-errors=-* --

# Valgrind target (commented out since it's not used in the provided Makefile)
# valgrind: demo test
# 	valgrind --tool=memcheck $(VALGRIND_FLAGS) ./demo 2>&1 | { egrep "lost| at " || true; }
# 	valgrind --tool=memcheck $(VALGRIND_FLAGS) ./test 2>&1 | { egrep "lost| at " || true; }

# Clean target
clean:
	rm -f *.o demo
