# *****************************************************************************************
# Project        : //TODO : 
# Filename       : //TODO : 
# Purpose        : //TODO : 
# Author         : Hanumantappa Budihal 
# Date           : 
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

$(BINDIR)/tsp: $(OBJDIR)/Main.o  $(OBJDIR)/SimulatedAnnealing.o 
	$(CC) -g -o $(BINDIR)/tsp  $(OBJDIR)/Main.o $(OBJDIR)/SimulatedAnnealing.o

$(OBJDIR)/Main.o: $(SRCDIR)/Main.cpp 
	$(CC) $(CFLAGS) -o $(OBJDIR)/Main.o $(SRCDIR)/Main.cpp -I$(INCDIR)

$(OBJDIR)/SimulatedAnnealing.o:	$(SRCDIR)/SimulatedAnnealing.cpp
	$(CC) $(CFLAGS) -o $(OBJDIR)/SimulatedAnnealing.o $(SRCDIR)/SimulatedAnnealing.cpp -I$(INCDIR)

clean: 
	rm -fr $(BINDIR)/* $(OBJDIR)/* 

build: 
	make clean
	make
run: 
	./bin/tsp




