/*
Name: Samuel Markus
Project: Assignment 2 - Bank Algorithm
Date: 4/25/24
File: main.c
Banker algorithm borrowed and modified from GeeksForGeeks website
*/


#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "filereader.h"

//// CONSTANTS ////
#define NUM_OF_RESOURCES 3
#define LINE_SIZE 256
#define NUM_OF_PROCESSES 5

#define AVAIL_RESOURCE_A 3
#define AVAIL_RESOURCE_B 3
#define AVAIL_RESOURCE_C 2

//// STRUCTURES ////
/// Customer structure ///
typedef struct customer
{
    int alloc[NUM_OF_RESOURCES];
    int max[NUM_OF_RESOURCES];
    int need[NUM_OF_RESOURCES];
}customer;

//// MAIN PROGRAM ////
int main() {
    /// Varialbles ///
    customer list[NUM_OF_PROCESSES]; // initial customer list
    int avail[3] = {AVAIL_RESOURCE_A, 
                    AVAIL_RESOURCE_B, 
                    AVAIL_RESOURCE_C}; // available resources

    bool checkForUnsafe[NUM_OF_PROCESSES];
    int orderedList[NUM_OF_PROCESSES]; // final order of customers

    /// Read from input.txt file and output data to customer's ///
    /// alloc and max array. ///
    FILE* fptr; 
    fptr = fopen("input.txt", "r"); 

    // loop through each line using the getDataFromLine function
    for(int i = 0; i < NUM_OF_PROCESSES; i++) 
        getDataFromLine(fptr, list[i].alloc, list[i].max); 
    fclose(fptr);
    
    /// Calculate need arrays for each customer /// 
    for (int i = 0; i < NUM_OF_PROCESSES; i++)
        for (int j = 0; j < NUM_OF_RESOURCES; j++)
            list[i].need[j] = list[i].max[j] - list[i].alloc[j];

    /// Banker algorithm ///
    int orderIndex = 0;
    for (int i = 0; i < NUM_OF_PROCESSES; i++)
    {
        for (int j = 0; j < NUM_OF_PROCESSES; j++)
        {
            if (checkForUnsafe[j] == false)
            {
                bool flag = false;
                for (int k = 0; k < NUM_OF_RESOURCES; k++)
                {
                    if (list[j].need[k] > avail[k])
                    {
                        flag = true;
                        break;
                    }
                }

                if (flag == false)
                {
                    orderedList[orderIndex++] = j; 
                    for (int k = 0; k < NUM_OF_RESOURCES; k++)
                        avail[k] += list[j].alloc[k];
                    checkForUnsafe[j] = true;
                }
            }
        }
    }

    /// Print sequence ///
    bool flag = true;
    for (int i = 0; i < NUM_OF_PROCESSES; i++) // check if the system is safe
    {
        if (checkForUnsafe[i] == false)
        {
            flag = false; 
            printf("The following system is not safe.\n");
            break;
        }
    }

    if (flag == true) // Print sequence if the system is safe 
    {
        printf("Following is the SAFE sequence\n");
        for (int i = 0; i < NUM_OF_PROCESSES - 1; i++)
        {
            printf("P%d ->", orderedList[i]);
        }
        printf("P%d\n", orderedList[NUM_OF_PROCESSES - 1]);
    }

    return 0;
}
