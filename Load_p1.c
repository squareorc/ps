#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 40
#define MEMORY_ROWS 100
#define MEMORY_COLS 4

char buffer[BUFFER_SIZE];
char Memory[MEMORY_ROWS][MEMORY_COLS];
FILE *infile;

void init()
{
    memset(buffer, '\0', sizeof(buffer));
    memset(Memory, '\0', sizeof(Memory));
}

void resetBuffer()
{
    memset(buffer, '\0', sizeof(buffer));
}

void LOAD()
{
    infile = fopen("input.txt", "r");
    if (infile == NULL)
    {
        printf("Error opening input file\n");
        return;
    }

    char s[BUFFER_SIZE];
    int IC = 0;

    while (fgets(s, sizeof(s), infile))
    {
        if (strncmp(s, "$AMJ", 4) == 0)
        {
            init();
            printf("\nNew Job started\n");
        }
        else if (strncmp(s, "$DTA", 4) == 0)
        {
            printf("Data card loading\n");
            resetBuffer();
        }
        else if (strncmp(s, "$END", 4) == 0)
        {
            printf("END of Job\n");
        }
        else
        {
            printf("Program Card loading\n");
            resetBuffer();
            strncpy(buffer, s, BUFFER_SIZE);

            int buff = 0;
            while (buff < BUFFER_SIZE && buffer[buff] != '\0')
            {
                for (int j = 0; j < MEMORY_COLS; j++)
                {
                    if (buffer[buff] == 'H')
                    {
                        Memory[IC][j] = 'H';
                        buff++;
                        break;
                    }
                    Memory[IC][j] = buffer[buff];
                    buff++;
                }
                IC++;
            }
        }
    }

    fclose(infile);
}

int main()
{
    LOAD();
    return 0;
}
