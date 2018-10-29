#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/stat.h>
#include<assert.h>

//Function's prototypes//

char* ReadFile(FILE* file, int nSym);
int compbegin(const void* str1, const void* str2);
int compend(const void* str1, const void* str2);
int strcopy(const char* str, char* strn);
int strcopyrev(const char* str, char* strn);
int FilePut(FILE* file, char** text, int NoS);


//Defines//

#define EQUALE_POINTERS -5
#define NUMBER_OF_SPACES 100
#define INVALID_TEST -2
#define STAT_RETURN_INVALID -1
#define NO_SYMBOLS 0
#define SECOND_ELEMENT_IN_TEXT 1
#define NO_STRINGS 0
#define UNUSED_SYMBOL '$'
#define EMPTY_STR 0
#define STRCOPY_GOOD 1
#define NO_PRINT -100
#define FILEPUT_GOOD 1
#define SET '1'
#define CLEAR '0'
#define POINTER_IS_NULL -4
#define INVALID_VALUE -3
#define CHECK(suspect , op , charge , CoE)              \
        {                                               \
            int re = (int)CoE;                          \
            assert((suspect) op (charge));              \
            if ((suspect) == (charge))                  \
            {                                           \
                printf(#suspect " is " #charge "\n");   \
                return re;                              \
            }                                           \
        }
#define TRUE_CHECK(suspect, op, charge, CoE)            \
        {                                               \
            int re = (int)CoE;                          \
            assert((suspect) op (charge));              \
            if ((suspect) != (charge))                  \
            {                                           \
                printf(#suspect "isn't" #charge "\n");  \
                printf(#suspect " = %d\n", suspect);    \
                return re;                              \
            }                                           \
        }                       


// Main Function //

int main()
{
    char SortFile[40] = "";
    printf("Enter the name of sorted file:\n");
    scanf("%s", SortFile);


    FILE *Onegin = fopen(SortFile, "r");
    FILE *Output = fopen("output.txt", "w");
    CHECK(Onegin, !=, NULL, POINTER_IS_NULL);
    CHECK(Output, !=, NULL, POINTER_IS_NULL);

      
    char **text = NULL, *string = NULL, *Copystring = NULL, flag = SET;
    struct stat buff;
    int Test = INVALID_TEST;
    int StatTester = STAT_RETURN_INVALID, nstring = NO_SYMBOLS ;
 
 
    StatTester = stat("EugeniyOnegin.txt", &buff);
    CHECK(StatTester, !=, STAT_RETURN_INVALID, INVALID_VALUE);


    nstring = buff.st_size;
    CHECK(nstring, !=, NO_SYMBOLS, INVALID_VALUE );


    string = ReadFile(Onegin, nstring);
    
  
    fseek(Onegin, 0, SEEK_SET);
    Copystring = ReadFile(Onegin, nstring);
       

    int i = SECOND_ELEMENT_IN_TEXT, j = 0, NoS = NO_STRINGS;
   
   
    while(string[j] != '\0')
    {
        if (flag == SET)
        {
            if(string[j] == '\n')
            {
                NoS++;
                flag = CLEAR;
            }
        }
        else 
        {
            if(string[j] == '\n')
            {
                string[j] = UNUSED_SYMBOL;
            }
            else
            {
                flag = SET;
            }
        }
        j++;   
    }
    j = 0;
    CHECK(NoS, !=, NO_STRINGS, INVALID_VALUE);
    

    text = (char**)calloc(NoS+1, sizeof(char*)); 
    CHECK(text, !=, NULL, POINTER_IS_NULL);
   
    
    while(string[j] != '\0')
    {
        if(string[j] == '\n')
        {
            text[i] = &string[j+1];
            string[j] = '\0';
            i++;
        }
        j++;
    }
    text[0] = string;
    i = 0;
    j = 0;
    

    qsort(text, NoS + 1, sizeof(char*), compbegin);
     
    
    Test = FilePut(Output, text, NoS);
    TRUE_CHECK(Test, ==, FILEPUT_GOOD, INVALID_VALUE);
    
    qsort(text, NoS+1, sizeof(char*), compend);
    
    
    Test = FilePut(Output, text, NoS); 
    TRUE_CHECK(Test, ==, FILEPUT_GOOD, INVALID_VALUE);
   

    fprintf(Output, "%s", Copystring);


    free(text);
    free(Copystring);
    free(string);
    fclose(Onegin);
    fclose(Output);


    return 0;
}


//Functions//

char* ReadFile(FILE* file, int nSym)                     //Gets 2 arguments: pointer to file(FILE*), number of symbols in file (int)// 
{
    char* string = (char*)calloc(nSym+1, sizeof(char));  //Create string for text i file//
    CHECK(string, !=, NULL, POINTER_IS_NULL);
   
    
    int Test = INVALID_TEST;
    fread(string, sizeof(char), nSym, file);             //Reads file and write it in string//
    Test = feof(file);
    CHECK(Test, !=, INVALID_TEST, INVALID_VALUE);


    string[nSym + 1] = '\0';
   
    
    return string;                                       //Returns pointer to string with file's text//
}


//Comparator for qsort//
int compbegin(const void* str1, const void* str2)        //Gets 2 pointers to pointers to strings//
{
    CHECK(str1, !=, NULL, POINTER_IS_NULL);
    CHECK(str2, !=, NULL, POINTER_IS_NULL);
    CHECK(str1, !=, str2, EQUALE_POINTERS);
 

    int StrS1 = EMPTY_STR, StrS2 = EMPTY_STR;     

   
    StrS1 = strlen(*((char**)str1));                     //Gets number of symbols in string 1//
    StrS2 = strlen(*((char**)str2));                     //Gets number of symbols in string 2// 
    

    char* str1n = (char*)calloc(StrS1 + 1, sizeof(char)); //Create string for copying string 1//
    char* str2n = (char*)calloc(StrS2 + 1, sizeof(char)); //Create string for copying string 2//
    CHECK(str1n, !=, NULL, POINTER_IS_NULL);
    CHECK(str2n, !=, NULL, POINTER_IS_NULL);


    int Test = INVALID_TEST;
    Test = strcopy(*((char**)str1), str1n);               //Copy string 1(process of copying look in strcopy)//
    TRUE_CHECK(Test, ==, STRCOPY_GOOD, INVALID_VALUE);    

   
    Test = strcopy(*((char**)str2), str2n);               //Copy string 2(process of copuing look in strcopy)//   
    TRUE_CHECK(Test, ==, STRCOPY_GOOD, INVALID_VALUE); 

    
    int ref = strcmp(str1n, str2n);                       //Compares new strings and writes result in ref//


    free(str1n);
    free(str2n);


    return ref;                                           //Returns ref//
}


//Comparator for qsort//
int compend(const void* str1, const void* str2)                     //Gets 2 pointers to pointers to strings//

{
    CHECK(str1, !=, NULL, POINTER_IS_NULL);
    CHECK(str2, !=, NULL, POINTER_IS_NULL);
    CHECK(str1, !=, str2, EQUALE_POINTERS);
    


    int StrS1 = EMPTY_STR, StrS2 = EMPTY_STR;
 

    StrS1 = strlen(*((char**)str1));                                //Gets number of symbols in string 1//
    StrS2 = strlen(*((char**)str2));                                //Gets number of symbols in string 1//


    char* str1n = (char*)calloc(StrS1 + 1,sizeof(char));            //Create string for copying string 1//
    char* str2n = (char*)calloc(StrS2 + 1,sizeof(char));            //Create string for copying string 1//
    CHECK(str1n, !=, NULL, POINTER_IS_NULL);
    CHECK(str2n, !=, NULL, POINTER_IS_NULL);

    
    int Test = INVALID_TEST;
    Test = strcopyrev(*((char**)str1), str1n);                      //Copy string 1(process of copying look in strcopyrev)//
    TRUE_CHECK(Test, ==, STRCOPY_GOOD, INVALID_VALUE);              


    Test = strcopyrev(*((char**)str2), str2n);                      //Copy string 2(process of copying look in strcopyrev)// 
    TRUE_CHECK(Test, ==, STRCOPY_GOOD, INVALID_VALUE);


    int ref = strcmp(str1n, str2n);                                 //Compare strings 1, 2 and writes result in ref//


    free(str1n);
    free(str2n);

  
    return ref;                                                     //Return ref//
}


int strcopy(const char* str, char* strn)                                                        //Gets 2 pointers to strings//
{
    CHECK(str, !=, NULL, POINTER_IS_NULL);
    CHECK(strn, !=, NULL, POINTER_IS_NULL);
    CHECK(str, !=, strn, EQUALE_POINTERS);
    

    int i = 0, k = 0;                                                                           //Copying only letters from str to strn //
    while( str[i] != '\0')                                                                      //        from begin to end             //    
    {                                                                                           //                                      //
        if (((str[i] >= 'A') && (str[i] <= 'Z')) ||  ((str[i] >= 'a') && (str[i] <= 'z')))      //                                      //
        {                                                                                       //                                      //
            strn[k] = str[i];                                                                   //                                      //
            k++;                                                                                //                                      //
        }                                                                                       //                                      //
        i++;                                                                                    //                                      //
    }                                                                                           //                                      //
    strn[k] = '\0';                                                                             //                                      //    


    return STRCOPY_GOOD;                                                                        //Returns value for testing//
}


int strcopyrev(const char* str, char* strn)                                                     //Gets 2 pointers to strings//
{
    CHECK(str, !=, NULL, POINTER_IS_NULL);
    CHECK(strn, !=, NULL, POINTER_IS_NULL);
    CHECK(str, !=, strn, EQUALE_POINTERS);


    int i = strlen(str), k = 0;                                                                 
    while( i >= 0)                                                                              //Copying only letters from str to strn // 
    {                                                                                           //        from end to begin             //
        if (((str[i] >= 'A') && (str[i] <= 'Z')) ||  ((str[i] >= 'a') && (str[i] <= 'z')))      //                                      //
        {                                                                                       //                                      //
            strn[k] = str[i];                                                                   //                                      //
            k++;                                                                                //                                      //  
        }                                                                                       //                                      //
        i--;                                                                                    //                                      //
    }                                                                                           //                                      //
    strn[k] = '\0';                                                                             //                                      //
    
    
    return STRCOPY_GOOD;                                                                        //Returns value for testing//    
}


                                                //Another function for writing, but it works strange//
/*
int FilePut(FILE* file, char** text, int NoS)
{
    CHECK(file, !=, NULL, POINTER_IS_NULL);
    CHECK(text, !=, NULL, POINTER_IS_NULL);
  
     
    int i = 0;
    for(i = 0; i < (NoS + 1); i++)
    {
        int k = 0;
        while((*(text[i] + k) < 'A') || ((*(text[i] + k) > 'Z') && (*(text[i] + k) < 'a')) || (*(text[i] + k) > 'z'))
        {
            if ((*(text[i]) + k) == '\0')
            {
                k = NO_PRINT;
                break;
            }
            k++;
        }
        if (k != NO_PRINT)
        {
            fprintf(file, "\t%s\n", text[i] + k);
        }
    }


    i = 0;
    while(i++ < NUMBER_OF_SPACES)
        fprintf(file, "\n");


    fprintf(file, "NEXT VERSION\n\n\n");


    return FILEPUT_GOOD; 
}
*/

int FilePut(FILE* file, char** text, int NoS)       //Gets 3 arguments: pointer to file(FILE*), pointer to massive of pointers to strings(char**, number of pointers(int)//
{
    CHECK(file, !=, NULL, POINTER_IS_NULL);         
    CHECK(text, !=, NULL, POINTER_IS_NULL);

     
    int i = 0;                                      
    for(i = 0; i < (NoS + 1); i++)                  //Cycle for printing//
    {
        int k = 0;
        while(*(text[i] + k) == '$')                //Skips symbols '$'//
            k++;
        while(*(text[i] + k) == '\t')               //Skips tabs//
            k++;
        while(*(text[i] + k) == ' ')                //Skips spaces//
            k++;
        fprintf(file, "\t%s\n", text[i] + k);       //Prints strings after skipping symbols//
    }


    i = 0;
    while(i++ < NUMBER_OF_SPACES)                   //Prints 100 '\n' for space between writings in file//
        fprintf(file, "\n");


    fprintf(file, "NEXT VERSION\n\n\n");

   
    return FILEPUT_GOOD;                            //Returns value for testing//
}
