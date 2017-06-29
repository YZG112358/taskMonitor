EXENAME = taskmonitor
OBJS = main.o

CXX = clang++
CXXFLAGS = -std=c++1y -stdlib=libc++ -c -g -O0 -Wall -Wextra -pedantic -I/usr/include/libxml2
LD = clang++
LDFLAGS = -std=c++1y -stdlib=libc++ -lpng -lc++abi -lpthread -lxml2

all : $(EXENAME)

$(EXENAME) : $(OBJS)
	$(LD) $(OBJS) $(LDFLAGS) -o $(EXENAME)

main.o : main.cpp utils.hpp
	$(CXX) $(CXXFLAGS) main.cpp

utils.o : utils.hpp
	$(CXX) $(CXXFLAGS) utils.hpp


clean :
	-rm -f *.o $(EXENAME)


