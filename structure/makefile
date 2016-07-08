# DEFINITION DES ACRONYMES
CC 	= 	g++
CFLAGS 	= 	-std=c++11
SRC 	= 	oofobject.cpp \
			command_parser.cpp \
			log_device.cpp \
			project_storage.cpp \
			core.cpp \
			test.cpp \
			main.cpp
			
OBJ 	= 	$(SRC:.cpp=.o)
EXEC	=	prog

# EXECUTION
all: $(EXEC)

# FABRICATION DES OBJETS (.o)
$(EXEC): $(OBJ)
	$(CC) -o $@ $^

# FABRICATION DES (.o) A PARTIR DES (.cpp)
%.o: %.cpp
	$(CC) -c $(CFLAGS) $<

# CLEAN
clean :
	rm -rf $(OBJ)

# CLEAN_
clean_ : clean
	rm -rf $(EXEC)

# CLEAR
clear : clean_
	reset

# REPEAT
repeat : clear
	make
