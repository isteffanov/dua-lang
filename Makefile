CXX=g++
CXXFLAGS=-std=c++17 -o

INCDIR = inc
OBJDIR = out
SRCDIR = src

OBJECTS = $(OBJDIR)/main.o
MAIN_INCLUDES =

.PHONY: all
all: $(OBJECTS)
	$(CXX) $(CXXFLAGS) main $(OBJECTS)

$(OBJDIR)/main.o: $(SRCDIR)/main.cpp $(MAIN_INCLUDES)
	$(CXX) -c $(CXXFLAGS) $@ -I $(INCDIR) $(SRCDIR)/$(*F).cpp

$(OBJDIR)/%.o : $(SRCDIR)/%.cpp $(INCDIR)/%.h      
	$(CXX) -c $(CXXFLAGS) $@ -I $(INCDIR) $(SRCDIR)/$(*F).cpp

$(OBJDIR):
	mkdir $(OBJDIR)

.cpp.h:

.PHONY: run
run:
	@./main

.PHONY: clean
clean:
	-rm -f $(OBJDIR)/* main