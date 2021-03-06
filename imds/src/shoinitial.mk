BIN:= shoinitial
INC = 
LIBS = -lpthread 
VPATH = $(shell find ../../src -type d)

SRCLIST = $(shell find ../../src/sho/initial -name *.cpp)
SRCLIST += $(shell find ../../src/public/program -name *.cpp)
SRCLIST += $(shell find ../../src/public/initial -name *.cpp)
SRCLIST += $(shell find ../../src/public/option -name *.cpp)
SRCLIST += $(shell find ../../src/public/market -name *.cpp)
SRCLIST += $(shell find ../../src/util/atof -name *.cpp)
SRCLIST += $(shell find ../../src/util/shm -name *.cpp)
SRCLIST += $(shell find ../../src/util/convert -name *.cpp)

OBJS = $(patsubst %.cpp, %.o, $(notdir $(SRCLIST)))

all:$(BIN)

$(OBJS):%.o:%.cpp
	$(CXX) -c $(CXXFLAGS) $< -o $@ $(INC)

$(BIN):$(OBJS)
	$(CXX) -o $(BIN) $(OBJS) $(LIBS)
	mv $(BIN) ../../bin/$(BIN)