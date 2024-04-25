/*
Name: Samuel Markus
Project: Assignment 2 - Bank Algorithm
Date: 4/25/24
File: filereader.c
*/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>
#include <string.h>

//// CONSTANTS //// 
#define lineSize 256
#define NUM_OF_RESOURCES 3 

//// Reads line from text file and outputs data to an "allocation" and "max" array //// 
void getDataFromLine(FILE* fptr, int alloc[], int max[]) 
{
    /// Inputting line from text ///
    char string[lineSize];
    fgets(string, sizeof(string), fptr);

    /// Variables for strtok and outputting data ///
    char* token = strtok(string, " ,[]");
    int i = 0; 
    int num = 0;
    bool firstHalf = true;

    /// Loop through each token and output digits into the allocation and max arrays ///
    while (token != NULL) {
        num = atoi(token);
        (firstHalf) ? (alloc[i] = num) : (max[i] = num);
        i++;
        token = strtok(NULL, " ,[]");
        if (i == NUM_OF_RESOURCES) {
            if (!firstHalf) { break; };
            firstHalf = false;
            i = 0;
        }
    }
}