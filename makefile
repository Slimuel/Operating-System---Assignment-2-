###
# Name: Samuel Markus
# Project: Assignment 2 - Bank Algorithm
# Date: 4/25/24
# File: makefile
# Template curdosy of Paul Programming
###

output: main.o filereader.o
	gcc main.o filereader.o -o output

main.o: main.c
	gcc -c main.c

filereader.o: filereader.c filereader.h
	gcc -c filereader.c

clean:
	rm *.o output 