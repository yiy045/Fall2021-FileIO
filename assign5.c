/*
assign5.c - main c program
*/
#include "assign5.h"
#define COURSE_FILE "courses.dat"
/*main: returns int
Main menu
*/

int main(int argc, char* argv[]) {
    char userInput[1024]; //buffer array to be used in stdin
    char in; //the input the user will put in
    char buffer[1024]; //buffer array to be used for the methods and stuff (idk help lol)
    //creates the inFile pointer
    FILE *inFile;
    COURSE myCourse;
    
    //MENU CONTROLS
    while(1) { //1 makes the loop infinite
        printf("Enter one of the following actions or press CRTL-D to exit.\n");
        printf("C - create a new course record\n");
        printf("U - update an existing course record.\n");
        printf("R - read an exisitng course record.\n");
        printf("D - delete an exisiting course record.\n");
        //reads the userinput and checks to see if they typed CRTL-D
        if(fgets(userInput, 100, stdin) == NULL) {
            printf("\nExiting program...\n");
            break;
        }//end of if-statement
        sscanf(userInput, "%c", &in); //reads the user input and puts whatever it was into the memory address of in
        switch(in) { //switch case for determing what was entered
            case 'C':
            case 'c':
                optionCreate(inFile, myCourse);
                break;
            case 'U':
            case 'u':
                optionUpdate(inFile, myCourse);
                break;
            case 'R':
            case 'r':
                optionRead(inFile, myCourse);
                break;
            case 'D':
            case 'd':
                optionDelete(inFile, myCourse);
                break;
            default:
                printf("Inavlid input. Please try again or exit program.\n");
               printf("-----------------------------------------------\n");
        }//end of switch case
    }//end of while loop
    return 0; //ends main
}
//creates the space for the course information and whatnot
void optionCreate(FILE* inFile, COURSE myCourse){
    //opens file
    inFile = fopen(COURSE_FILE, "rb+");
    if(inFile==NULL)
        inFile = fopen(COURSE_FILE, "wb+");

    char buffer[1024];//buffer
    int courseNum; //course number

    printf("Course number: "); //prompts for course number
    if(fgets(buffer, 100, stdin) != NULL)//if fgets does not equal NULL
        sscanf(buffer, "%d", &courseNum);//scans for the course number
    //checks and makes sure the number entered is a valid course number
    if(courseNum < 1000 || courseNum > 9999){
        printf("error: invalid course number\n");
        return;//goes back to the menu
    }
    //then it checks to see if spot where the course number would be there is NOT there
    fseek(inFile, courseNum * sizeof(COURSE), SEEK_SET);
    fread(&myCourse, sizeof(COURSE), 1L, inFile);
    if(myCourse.course_Hours != 0) {
        fprintf(stderr, "ERROR: course already exists\n");
        return;
    }
    else {
        printf("Course name: ");
        if(fgets(buffer, 100, stdin)!=0)
            sscanf(buffer, "%[^'\n']", &myCourse.course_name);
        printf("Scheduled days: ");
        if(fgets(buffer, 100, stdin) != 0)
            sscanf(buffer, "%s", &myCourse.course_Sched);
        printf("Credit hours: ");
        if(fgets(buffer, 100, stdin) != 0)
            sscanf(buffer, "%u", &myCourse.course_Hours);
        printf("Enrolled Students: ");
        if(fgets(buffer, 100, stdin) != 0)
            sscanf(buffer, "%u", &myCourse.course_Size);
        //seeks the position and writes in the data
        fseek(inFile, courseNum * sizeof(COURSE), SEEK_SET);
        fwrite(&myCourse, sizeof(COURSE), 1L, inFile);
    }
    fclose(inFile);
}

//update method: will update the specific course info
//will keep original info if left blank
void optionUpdate(FILE* inFile, COURSE myCourse) {
    char buffer[1024]; //buffer array
    int courseNum; //number of the course
    //opens file yet again
    inFile = fopen(COURSE_FILE, "rb+");
    if(inFile==NULL)
        inFile = fopen(COURSE_FILE, "wb+");

    printf("Enter course number: ");
    if(fgets(buffer, 100, stdin) != NULL)
        sscanf(buffer, "%d", &courseNum);
    //checks to see if it's a valid input
    if(courseNum < 1000 || courseNum > 9999) {
        fprintf(stderr, "ERORR: input invalid\n");
        return;
    }
    COURSE tempCourse;
    //reads the file and checks to see if the class is there
    fseek(inFile, courseNum * sizeof(COURSE), SEEK_SET);
    fread(&myCourse, sizeof(COURSE), 1L, inFile);
    if(myCourse.course_Hours != 0) {
        printf("Course name: ");
        if (fgets(buffer, 100, stdin) != NULL) {
            if (buffer[0] != '\0') {
                sscanf(buffer, "%[^'\n']", tempCourse.course_name);
                strcpy(myCourse.course_name, tempCourse.course_name);
            }
        }
        printf("Scheduled days: ");
        if(fgets(buffer, 100, stdin) != NULL)
            sscanf(buffer, "%s", &myCourse.course_Sched);
        else
            myCourse.course_Sched == &tempCourse.course_Sched;
        printf("Credit hours: ");
        if(fgets(buffer, 100, stdin) != NULL)
            sscanf(buffer, "%u", &myCourse.course_Hours);
        else
            myCourse.course_Hours == tempCourse.course_Hours;
        printf("Enrolled students: ");
        if(fgets(buffer, 100, stdin) != NULL)
            sscanf(buffer, "%u", &myCourse.course_Size);
        else
            myCourse.course_Size == tempCourse.course_Size;

        fseek(inFile, courseNum * sizeof(COURSE), SEEK_SET);
        fwrite(&myCourse, sizeof(COURSE), 1L, inFile);
    }
    fclose(inFile);
}

//read function
void optionRead(FILE* inFile, COURSE myCourse) {
    //opens file
    inFile = fopen(COURSE_FILE, "rb+");
    if(inFile == NULL)
        inFile = fopen(COURSE_FILE, "wb+");
    char buffer[1024]; //buffer array
    int courseNum;
    
    printf("Enter course number: ");
    if(fgets(buffer, 100, stdin) != NULL)
        sscanf(buffer, "%d", &courseNum);
    //checks to make sure it's a valid input
    if(courseNum < 1000 || courseNum > 9999) {
        fprintf(stderr, "ERROR: input too large or too small\n");
        return;
    }
    //searches the file for the location based off the courseNum
    //fseek(inFile, courseNum * sizeof(COURSE), SEEK_SET);
    fseek(inFile, courseNum * sizeof(COURSE), SEEK_SET);
    fread(&myCourse, sizeof(COURSE), 1L, inFile);
    //if it finds it, prints out the information ;)
    if(myCourse.course_Hours != 0) {
        printf("Course number: %d\n", courseNum);
        printf("Course name: %s\n", &myCourse.course_name);
        printf("Scheduled days: %s\n", &myCourse.course_Sched);
        printf("Credit hours: %u\n", myCourse.course_Hours);
        printf("Enrolled students: %u\n", myCourse.course_Size);
    }
    else{
        fprintf(stderr, "ERORR: course not found\n");
        return;
    }
    fclose(inFile);
}

void optionDelete(FILE* inFile, COURSE myCourse) {
    //opens file
    inFile = fopen(COURSE_FILE, "rb+");
    if(inFile==NULL)
        inFile = fopen(COURSE_FILE, "wb+");

    char buffer[1024];//buffer
    int courseNum; //course number

    printf("Course number: "); //prompts for course number
    if(fgets(buffer, 100, stdin) != NULL)//if fgets does not equal NULL
        sscanf(buffer, "%d", &courseNum);//scans for the course number
    //checks and makes sure the number entered is a valid course number
    if(courseNum < 1000 || courseNum > 9999){
        printf("error: invalid course number\n");
        return;//goes back to the menu
    }
    //then it checks to see if spot where the course number would be there is NOT there
    fseek(inFile, courseNum * sizeof(COURSE), SEEK_SET);
    fread(&myCourse, sizeof(COURSE), 1L, inFile);
    if(myCourse.course_Hours != 0) {
        myCourse.course_Hours = 0;
        fseek(inFile, courseNum * sizeof(COURSE), SEEK_SET);
        fwrite(&myCourse, sizeof(COURSE), 1L, inFile);
    }
    else{
        fprintf(stderr, "ERROR: course not found\n");
    }
    fclose(inFile);
}
