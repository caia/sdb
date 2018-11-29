#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include <unistd.h>


typedef struct {
    char* buffer;
    size_t buffer_length;
    ssize_t input_length;
} InputBuffer;


InputBuffer* new_input_buffer()
{
    InputBuffer* ib = malloc(sizeof(InputBuffer));

    ib->buffer = NULL;
    ib->buffer_length = 0;
    ib->input_length = 0;

    return ib;
}


void read_input(InputBuffer* ib)
{
    ssize_t bytes_read =
        getline(&(ib->buffer), &(ib->buffer_length), stdin);

    if(bytes_read <= 0)
    {
        printf("Error reading input.\n");
        exit(EXIT_FAILURE);
    }

    ib->input_length = bytes_read - 1;
    ib->buffer[bytes_read - 1] = 0;
}


void prompt()
{
    printf("sdb > ");
}


int main()
{
    InputBuffer* ib = new_input_buffer();

    while(true)
    {
        prompt();
        read_input(ib);

        if(strcmp(ib->buffer, ".exit") == 0)
        {
            exit(EXIT_SUCCESS);
        }
        else
        {
            printf("Unrecognized command '%s'.\n", ib->buffer);
        }
    }
}
