EXE = chess
TEST = tests

MAIN_FILE = src/main.cpp

CPP_FILES += $(wildcard src/*.cpp)

OBJS += $(CPP_FILES:.cpp=.o)

TEST_FILES += $(filter-out $(MAIN_FILE), $(CPP_FILES))
TEST_FILES += $(wildcard test/*.cpp)

TEST_OBJS = $(TEST_FILES:.cpp=.o)

RM = rm -f

CXX = g++
CXXFLAGS = -std=c++11 -stdlib=libc++ -c -g -O0 -Wall -Wextra -Wc++11-extensions -pedantic
LD = g++
LDFLAGS = -I../lib/pgnlib-0.2.5/include/

all : $(EXE)

$(EXE) : $(OBJS)
	$(CXX) $(LDFLAGS) $(OBJS) -lpgn -g -o $(EXE)

$(TEST): $(TEST_OBJS)
	$(LD) $(LDFLAGS) -lpgn $(TEST_OBJS) -o $(TEST)

%.o: %.cpp %.h
	$(CXX) $(LDFLAGS) $(CXXFLAGS) $< -o $@

clean:
	$(RM) $(OBJS) $(EXE_OBJ) $(EXE) $(TEST_OBJS)
	rm -f test/*.o
	rm tests
