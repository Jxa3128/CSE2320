//Jorge Avila
//mavID: 1001543128

/*
    being able to sort in 3 different ways - using insertion sort algorithm
    - ascending 
    - descending 
    - length size of name
    - objectives: using functions as parameters, non memory leaks
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
//prototypes
void print_data(char *[], int);
int comp_length(const char *, const char *);
int compt_mix(const char *, const char *);
int comp_greater(const char *, const char *);
void insertion_sort(char *Array[], int N, int returnResult(const char *, const char *));
void free_array(char **, int);
//main begins
int main(int argc, char **argv)
{
    /* declare variables here */
    char filename[101];
    FILE *filePtr = NULL;
    char fileLine[101]; //used with fgets()
    char name[101];     //used with fscanf()
    int i;
    char buffer[101];
    int counter = 0;
    int size_of_bytes = 0;
    /* code code code code */
    printf("Enter the file name: ");
    scanf("%s", &filename);
    filePtr = fopen(filename, "r");
    if (filePtr == NULL)
    {
        printf("File was unable to open\n");
        exit(EXIT_FAILURE);
    }
    //i tried reading from the data twice
    //one using fscaf()
    //one using fgets()
    while (fscanf(filePtr, "%s", name) == 1)
    {
        counter++; //counter to see how many names in file
        size_of_bytes += strlen(name);
    }
    int tempchars = size_of_bytes;
    //reason why I initialized these variables here is
    //because we do not know how many things are in the
    //file we are reading from.
    char *peopleNames[counter];

    rewind(filePtr);

    int position = 0;

    //getting my size of bytes 
    
    size_of_bytes = size_of_bytes + (counter * sizeof(void *));

    while (fgets(fileLine, sizeof(fileLine) - 1, filePtr))
    {
        //remove the new line at the end and replace w/ null terminator
        if (fileLine[sizeof(fileLine) == '\n'])
        {
            fileLine[sizeof(fileLine)] = '\0';
        }
        //dynamically allocate memory for the size of each name
        //copy that line into that space into the var peopleNames
        peopleNames[position] = (char *)malloc(sizeof(fileLine));
        strcpy(peopleNames[position], fileLine);

        //trying to get an array that is dynamically allocated
        //so we can add all numbers of the sizeof() each line
        //so we can do the total number of bytes.

        //positon is a counter
        position++;
    }

    printf("\nData Loaded.\n");
    printf("\nPointer size: %lu Bytes\n", sizeof(void *));
    printf("\nAllocated space for storing the data: %7d B ( %d char and %d pointers)",size_of_bytes, tempchars, counter);

    printf("\nOriginal Data - List of Names before Sorting\n");
    print_data(peopleNames, counter);

    insertion_sort(peopleNames, counter, comp_length);
    printf("--------------------------Sorting by Length Only----------------------------\n");
    print_data(peopleNames, counter);

    insertion_sort(peopleNames, counter, strcmp);
    printf("-------------------Sorting A to Z  by strcmp function-----------------------\n");
    print_data(peopleNames, counter);

    insertion_sort(peopleNames, counter, comp_greater);
    printf("--------------------Sorting Z to A  by greater function--------------------\n");
    print_data(peopleNames, counter);

    insertion_sort(peopleNames, counter, compt_mix);
    printf("--------------------Sorting by Lenght then lexi.. by mixed function--------------------\n");
    print_data(peopleNames, counter);

    free_array(peopleNames,counter);
    
    
    close(filePtr);
    return 0;
}
//this prints out my data
void print_data(char *peopleArray[], int N)
{
    int iterator = 0;
    for (iterator = 0; iterator < N; iterator++)
    {
        printf("%s\n", peopleArray[iterator]);
    }
}
//compare the words by its length
int comp_length(const char *left, const char *right)
{
    //if left > right, return left as greater
    if (strlen(left) > strlen(right))
    {
        return 1;
    }
    //if left < right return left as shorter
    else if (strlen(left) < strlen(right))
    {
        return -1;
    }
    else
    {
        //the same size
        return 0;
    }
}
int compt_mix(const char *left, const char *right)
{
    //if left < right return left as shorter
    if (strlen(left) < strlen(right))
    {
        return -1;
    }
    //if left > right, return left as greater
    else if (strlen(left) > strlen(right))
    {
        return 1;
    }
    else
    {
        //if they equal then return strcmp() convention
        return strcmp(left, right);
    }
}
//stefans implemented function
int comp_greater(const char *left, const char *right)
{
    return -strcmp(left, right);
}
//being passed the function as the third parameter
void insertion_sort(char *Array[], int N, int returnResult(const char *, const char *))
{
    int i, k;
    //k = the integer to track the position in the
    //array for placing the tempKey value.
    char *tempKey;
    for (i = 1; i < (N - 1); i++)
    {
        tempKey = Array[i];
        k = i - 1;
        //while not looking at negative position
        // calling the function
        while ((k >= 0) && (returnResult(Array[k], tempKey) > 0))
        {
            Array[k + 1] = Array[k];
            k -= 1;
        }
        Array[k + 1] = tempKey;
    }
}
//this function is to free my data
void free_array(char **peopleNames , int N)
{
    int i;
    for (i = 0; i < N; i++)
    {
        free(peopleNames[i]);
    }
    
}
