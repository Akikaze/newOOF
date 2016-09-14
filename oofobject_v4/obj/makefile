# DEFINITION DES ACRONYMES 
CXXFLAGS = -std=c++11
LDFLAGS =  -g
LDLIBS  =  -ldl
 
SRC     =   std.cpp \
			config.cpp \
			ioof_object.cpp \
			instance_manager.cpp \
			log_device.cpp \
			command_parser.cpp \
			project_storage.cpp \
			core.cpp \
			main.cpp \
			test.cpp \
  
OBJ     =   $(SRC:.cpp=.o)
EXEC    =   ../newOOF
  
# EXECUTION
all: $(EXEC)
  
# FABRICATION DES OBJETS (.o)
$(EXEC): $(OBJ)
	$(LINK.cc)  $(LOADLIBES) $(LDLIBS) -o $@ $^
  
# FABRICATION DES (.o) A PARTIR DES (.cpp)
%.o: ../src/%.cpp
	$(COMPILE.cc) $<

%.o: ../src/*/%.cpp
	$(COMPILE.cc) $<

# CLEAN
clean :
	rm *.o

# RESTART
restart :
	rm -r ../.logs ;
	rm -r ../projects ;

# RESET
reset : $(EXEC)
	reset
