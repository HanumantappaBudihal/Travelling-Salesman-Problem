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
INCDIR = ./include
CFLAGS = -g -c -I$(INCDIR)
CC = g++

all: $(BINDIR)/tsp 

$(BINDIR)/tsp: $(OBJDIR)/TSPMain.o  $(OBJDIR)/Data.o $(OBJDIR)/Ant.o  $(OBJDIR)/ACO.o    
	$(CC) -g -o $(BINDIR)/tsp  $(OBJDIR)/Data.o $(OBJDIR)/Ant.o  $(OBJDIR)/ACO.o $(OBJDIR)/TSPMain.o   -I$(INCDIR)

$(OBJDIR)/TSPMain.o: $(SRCDIR)/TSPMain.cpp 
	$(CC) $(CFLAGS) -o $(OBJDIR)/TSPMain.o $(SRCDIR)/TSPMain.cpp -I$(INCDIR)

$(OBJDIR)/ACO.o:	$(SRCDIR)/ACO.cpp
	$(CC) $(CFLAGS) -o $(OBJDIR)/ACO.o $(SRCDIR)/ACO.cpp -I$(INCDIR)

$(OBJDIR)/Ant.o:	$(SRCDIR)/Ant.cpp
	$(CC) $(CFLAGS) -o $(OBJDIR)/Ant.o $(SRCDIR)/Ant.cpp -I$(INCDIR)

$(OBJDIR)/Data.o:	$(SRCDIR)/Data.cpp
	$(CC) $(CFLAGS) -o $(OBJDIR)/Data.o $(SRCDIR)/Data.cpp -I$(INCDIR)

clean: 
	rm -fr $(BINDIR)/* $(OBJDIR)/* 




