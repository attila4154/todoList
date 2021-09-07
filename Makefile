# program=todoList
# CXX=g++
# CFLAGS=-Wall -pedantic 


# SRCDIR=src
# OBJDIR=tmp

# # _SRC = main.cpp CApplication.cpp CExpr.cpp CMatrix.cpp CDense.cpp CSparse.cpp  CToken.cpp MatrixFunctions.cpp CMatrixCommands.cpp
# # _OBJ = $(patsubst %.cpp,%.o,$(_SRC))
# # HDR = src/hdr/CApplication.h src/hdr/CExpr.h src/hdr/CMatrix.h src/hdr/CDense.h src/hdr/CSparse.h  src/hdr/CToken.h src/hdr/MatrixFunctions.h src/hdr/CMatrixCommands.h

# # SRC = $(patsubst %,$(SRCDIR)/%,$(_SRC))
# SRC = src/main.cpp src/App.cpp
# OBJ = lib/App.h

# all: compile run clean

# # doc: $(SRC) $(HDR) Doxyfile
# # 	doxygen

# compile: $(program)

# run:
# 	./$(program)

# $(program): $(OBJ)
# 	$(CXX) -g -fsanitize=address $^ -lncurses -o $@ 

# $(OBJDIR)/%.o : $(SRCDIR)/%.cpp $(HDR)
# 	@mkdir -p $(@D)
# 	$(CXX) $(CFLAGS) -c $< -o $@

# clean:
# 	rm -rf $(OBJDIR)
# 	rm -f $(program)


program=todoList
CC=g++
CFLAGS= -Wall -pedantic -g -fsanitize=address

all: compile run clear

compile: $(program)

run: 
	./$(program)

clear:
	-rm $(program)

$(program): src/main.cpp src/App.cpp lib/App.h
	$(CC) $(CFLAGS) $^ -lncurses -o $@