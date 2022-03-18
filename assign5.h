/*
assign5.h - header file for assign5.c
*/
#ifndef ASSIGN5_H
#define ASSIGN5_H
#define ERROR_PROCESSING 99
//all the includes that will be used in assign5.c
#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>
#include<sys/stat.h>
#include<string.h>
#include<errno.h>
#include <stdarg.h>

//COURSE struct variables
typedef struct {
    char course_name[80]; //name of the course (w/ spaces)
    char course_Sched[4]; //course schedule (MWF or TR)
    unsigned course_Hours; //course hours
    unsigned course_Size; //size of course
    unsigned padding; //all the garbage values are collected in this variable
} COURSE; //name of struct

//errExit method copied over from errExit.c
void errExit(const char szFmt[], ... ){
    va_list args;               // This is the standard C variable argument list type
    va_start(args, szFmt);      // This tells the compiler where the variable arguments
                                // begins.  They begin after szFmt.
    printf("ERROR: ");
    vprintf(szFmt, args);       // vprintf receives a printf format string and  a
                                // va_list argument
    va_end(args);               // let the C environment know we are finished with the
                                // va_list argument
    printf("\n");
    exit(ERROR_PROCESSING);
}
//functions for the options in th emenu
void optionCreate(FILE*, COURSE);
void optionUpdate(FILE*, COURSE);
void optionRead(FILE*, COURSE);
void optionDelete(FILE*, COURSE);
#endif
