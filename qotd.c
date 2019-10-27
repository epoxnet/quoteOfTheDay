/*
 Sean Dehghani
 Secure Coding
 */
#include "qotd.h"
static qotd_t *qotd = NULL;
static size_t count = 0;
static char *buffer = NULL;

void freePointer(void *ptr)
{
    /*
     *
     * 1. Write a short routine to clear *ptr.
     * 2. Use freePointer() throughout the code
     *    to remove all memory leaks.
     *
     */
    if (ptr == NULL)
    {
        printf("Warning: Null Pointer\n");
    }
    else
    {
        free(ptr); // free the pointer if ptr is not NULL !
    }
}

buffersize_t getBufferSize(ssize_t new_size)
{
    
    /*
     *
     * Calculate a new buffer size, being
     * sure to prevent against integer overflow
     * and/or wrap.
     *
     */
    if (new_size < BUFFERSIZE)
    {
        return BUFFERSIZE;
    }
    else
    {
        return BUFFERSIZE;
    }
    return 0;
}

int addQuote(uint16_t pos, uint16_t len)
{
    qotd = (qotd_t*)realloc(qotd, sizeof(qotd_t) * (count + 1));
    
    if (qotd == NULL)
    {
        return ERROR_CONDITION;
    }
    
    qotd[count].pos = pos;
    qotd[count].len = len;
    
    count++;
    
    return SUCCESS;
}

void quoteOfTheDay()
{
    char *str = NULL;
    
    srand((unsigned)time(NULL));
    uint16_t index = ((rand() % count) + 1) - 1;
    
    str = malloc(qotd[index].len + 1);
    
    if (str == NULL)
    {
        fprintf(stderr, "quoteOfTheDay() %s", ERROR_MESSAGE);
    }
    else
    {
        strncpy(str, (char*)(buffer + qotd[index].pos), qotd[index].len);
        str[qotd[index].len] = '\0';
        
        printf("%s\n", str);
        freePointer(str);
    }
}

int load(char *file)
{
    FILE *stream;
    char *line = NULL;
    size_t length = 0;
    ssize_t lineSize;
    
    stream = fopen(file, "r");
    if (stream == NULL)
    {
        return ERROR_CONDITION;
    }
    
    while ((lineSize = getline(&line, &length, stream)) != -1)
    {
        char* pos;
        buffersize_t bufferSize;
        
        if ((pos = strchr(line, '\n')) != NULL)
        {
            *pos = '\0';
        }
        
        bufferSize = getBufferSize(lineSize);
        
        if (bufferSize == 0)
        {
            fclose(stream);
            fprintf(stderr, "getBufferSize() %s", ERROR_MESSAGE);
            return ERROR_CONDITION;
            freePointer(line);//free() the pointer if this condition is Ture
        }
        
        if ((buffer = realloc(buffer, bufferSize * sizeof(char))) == NULL)
        {
            fclose(stream);
            fprintf(stderr, "realloc() %s", ERROR_MESSAGE);
            return ERROR_CONDITION;
            freePointer(line);//free() the pointer if this condition is Ture
        }
        
        if (addQuote(strlen(buffer), lineSize - 1) == ERROR_CONDITION)
        {
            fclose(stream);
            fprintf(stderr, "addQuote() %s", ERROR_MESSAGE);
            return ERROR_CONDITION;
            freePointer(line);//free() the pointer if this condition is Ture
        }
        
        strncat(buffer, line, lineSize - 1);
    }
    freePointer(line);//free() the pointer if none of the if statement doesn't work
    fclose(stream);
    
    return strlen(buffer);
    
}

int main (int argc, char** argv)
{
    if (load(QOTD_FILE) == ERROR_CONDITION)
    {
        return ERROR_CONDITION;
    }
    
    quoteOfTheDay();
    
    freePointer(buffer);
    freePointer(qotd);
}

