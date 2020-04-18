//Jorge Avila 1001543128
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "edit_distance.h"

#define WHITESPACE " \t\n"
#define MAX 999
/*  Suggestions
- When you work with 2D arrays, be careful. Either manage the memory yourself, or
work with local 2D arrays. Note C99 allows parameters as array sizes as long as
they are declared before the array in the parameter list. See:
https://www.geeksforgeeks.org/pass-2d-array-parameter-c/

Worst case time complexity to compute the edit distance from T test words
 to D dictionary words where all words have length MaxLen:
Student answer:  Theta(............)

*/

int minimum(int v1, int v2, int v3)
{
    int first_min = (v1 < v2) ? v1 : v2;
    int ret = (first_min < v3) ? first_min : v3;
    return ret;
}

int edit_distance(char *first_string, char *second_string, int print_table)
{
    //variable declarations - (i.e. iterations)
    int i, j;
    int upperMatrix, leftMatrix, lateral;
    //we need our column and row length
    int string1_size = strlen(first_string);
    int string2_size = strlen(second_string);

    //we need to make a 2D array
    // we add one for the extra space at the start
    int matrix[string1_size + 1][string2_size + 1];

    //begin with creating populating the matrix
    for (i = 0; i < string1_size + 1; i++)
    {
        //nested for loop is required in doing a matrix
        for (j = 0; j < string2_size + 1; j++)
        {
            if (i == 0)
                matrix[i][j] = j;
            else if (j == 0)
                matrix[i][j] = i;
            else
            {
                //constantly populating the top & left side
                upperMatrix = matrix[i - 1][j] + 1;
                leftMatrix = matrix[i][j - 1] + 1;

                if (second_string[j - 1] == first_string[i - 1])
                    lateral = matrix[i - 1][j - 1];
                else
                    lateral = matrix[i - 1][j - 1] + 1;

                matrix[i][j] = minimum(upperMatrix, leftMatrix, lateral);
            }
        }
    }
    //processes for printing the matrix out
    if (print_table == 1)
    {
        for (i = 0; i < ((string1_size + 2) * 2); i++)
        {
            if ((i % 2) != 0)
            {
                for (j = 0; j < string2_size + 2; j++)
                {
                    if (j == 0)
                        printf("---");
                    else
                        printf("----");
                }
                printf("\n");
            }
            else if (i == 0)
            {
                for (j = 0; j < string2_size + 2; j++)
                {
                    if (j == 0)
                        printf("%2s|", " ");
                    else if (j == 1)
                        printf("%3s|", " ");
                    else
                        printf("%3c|", second_string[j - 2]);
                }
                printf("\n");
            }
            else if (i == 2)
            {
                for (j = 0; j < string2_size + 2; j++)
                {
                    if (j == 0)
                        printf("%2s|", " ");
                    else
                        printf("%3d|", matrix[(i - 2) / 2][j - 1]);
                }
                printf("\n");
            }
            else
            {
                for (j = 0; j < string2_size + 2; j++)
                {
                    if (j == 0)
                        printf("%2c|", first_string[(i - 4) / 2]);
                    else
                        printf("%3d|", matrix[(i - 2) / 2][j - 1]);
                }
                printf("\n");
            }
        }
    }
    //returns the distance
    return matrix[string1_size][string2_size];
}

void spellcheck(char *dictname, char *testname)
{
    FILE * dictionary_file;
    FILE * test_file;
    char buffer[258];
    dictionary_file = fopen(dictname,"r");
    test_file = fopen(testname, "r");
    int DictWords, word_size;
    //make sure we can open it
    if(dictionary_file == NULL)
    {
        fprintf(stderr, "%s could not be opened\n",dictname );
        exit (EXIT_FAILURE);
    }
    else if(test_file == NULL)
    {
        fprintf(stderr, "%s could not be opened\n", testname );
        exit (EXIT_FAILURE);
    }
    else
    {
        fscanf(dictionary_file, "%d\n", &DictWords);
        fscanf(test_file, "%d\n",&word_size );

        char dictionary[DictWords][258];
        char test_array[word_size][258];

        int distance[DictWords];
        int i;

        for(i = 0; i < DictWords; i++)
        {
            if(i == (DictWords -1))
                fscanf(dictionary_file, "%s", dictionary[i]);
            fscanf(dictionary_file, "%s\n", dictionary[i]);
        }
        fclose(dictionary_file);
        for(i =0; i <word_size; ++i)
        {
            if(i == (word_size - 1))
                fscanf(test_file, "%s", test_array[i]);
            fscanf(test_file, "%s\n", test_array[i]);
        }
        fclose(test_file);
        int k;
        for(i =0; i < word_size; i++)
        {
            int min = MAX;
            for(k =0; k < DictWords; k++)
            {
                distance[k] = edit_distance(test_array[i], dictionary[k], 0);
                if(min > distance[k])
                    min = distance[k];
            }
            printf("\n------ Current Test Word: %s\n",test_array[i]);
            printf("Minimun distance = %d\n", min);
            printf("Words that give minimun distance\n");
            for(k = 0; k <DictWords; k++)
            {
                if(distance[k + 0] == min)
                    printf("%s\n",dictionary[k]);
            }
        }
    }
//end of the function
}
