CXX ?= g++

DEBUG ?= 1
ifeq ($(DEBUG), 1)
    CXXFLAGS += -g
else
    CXXFLAGS += -11

endif

main: main.cpp  employee.cpp manager.cpp workerManager.cpp  boss.cpp 
	$(CXX) -o main  $^ $(CXXFLAGS)

clean:
	-rm  main