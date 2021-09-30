# *****************************************************************************************
# Project        : //TODO : 
# Filename       : //TODO : 
# Purpose        : //TODO : 
# Author         : Hanumantappa Budihal 
# Date           : 27-09-2021 
# 
# Bugs Log       :
# 
# Change Log     : Initial Creation : 27-09-2021
# *****************************************************************************************

SRCDIR = ./src
OBJDIR = ./obj
BINDIR = ./bin
INCDIR = ./include#Need to make dynamic way
CFLAGS = -g -c -I$(INCDIR)
CC = g++

all: $(BINDIR)/tsp 

$(BINDIR)/tsp: $(OBJDIR)/Main.o  $(OBJDIR)/GeneticAlgorithm.o $(OBJDIR)/Graph.o
	$(CC) -g -o $(BINDIR)/tsp  $(OBJDIR)/Main.o $(OBJDIR)/GeneticAlgorithm.o  $(OBJDIR)/Graph.o -I$(INCDIR)

$(OBJDIR)/Main.o: $(SRCDIR)/Main.cpp 
	$(CC) $(CFLAGS) -o $(OBJDIR)/Main.o $(SRCDIR)/Main.cpp -I$(INCDIR)

$(OBJDIR)/GeneticAlgorithm.o:	$(SRCDIR)/GeneticAlgorithm.cpp
	$(CC) $(CFLAGS) -o $(OBJDIR)/GeneticAlgorithm.o $(SRCDIR)/GeneticAlgorithm.cpp -I$(INCDIR)

$(OBJDIR)/Graph.o:	$(SRCDIR)/Graph.cpp
	$(CC) $(CFLAGS) -o $(OBJDIR)/Graph.o $(SRCDIR)/Graph.cpp -I$(INCDIR)

clean: 
	rm -fr $(BINDIR)/* $(OBJDIR)/* 

build: 
	make clean
	make

run: 
	./bin/tsp




