#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include <unistd.h>


typedef enum
{
    META_COMMAND_SUCCESS,
    META_COMMAND_UNRECOGNIZED
}
MetaCommandResult;


typedef enum
{
    PREPARE_SUCCESS,
    PREPARE_UNRECOGNIZED
}
PrepareResult;


typedef enum
{
    STATEMENT_INSERT,
    STATEMENT_SELECT
}
StatementType;


typedef struct
{
    char* buffer;
    size_t buffer_length;
    ssize_t input_length;
}
InputBuffer;


typedef struct
{
    StatementType type;
}
Statement;


InputBuffer* new_input_buffer()
{
    InputBuffer* ib = malloc(sizeof(InputBuffer));

    ib->buffer = NULL;
    ib->buffer_length = 0;
    ib->input_length = 0;

    return ib;
}


MetaCommandResult do_meta_command(InputBuffer* ib)
{
    if(strcmp(ib->buffer, ".exit") == 0)
    {
        exit(EXIT_SUCCESS);
    }
    else
    {
        return META_COMMAND_UNRECOGNIZED;
    }
}


PrepareResult prepare_statement(InputBuffer* ib, Statement* st)
{
    if(strncmp(ib->buffer, "insert", 6) == 0)
    {
        st->type = STATEMENT_INSERT;
        return PREPARE_SUCCESS;
    }

    if(strcmp(ib->buffer, "select") == 0)
    {
        st->type = STATEMENT_SELECT;
        return PREPARE_SUCCESS;
    }

    return PREPARE_UNRECOGNIZED;
}


void execute_statement(Statement* st)
{
    switch(st->type)
    {
        case(STATEMENT_INSERT):
            printf("Insert.\n");
            break;

        case(STATEMENT_SELECT):
            printf("Select.\n");
            break;
    }
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

        if(ib->buffer[0] == '.')
        {
            switch(do_meta_command(ib))
            {
                case(META_COMMAND_SUCCESS):
                    continue;

                case(META_COMMAND_UNRECOGNIZED):
                    printf("Unrecognized keyword at start of '%s'.\n", ib->buffer);
                    continue;
            }
        }

        Statement st;
        switch(prepare_statement(ib, &st))
        {
            case(PREPARE_SUCCESS):
                break;

            case(PREPARE_UNRECOGNIZED):
                printf("Unrecognized keyword at start of '%s'.\n", ib->buffer);
                continue;
        }

        execute_statement(&st);
        printf("Executed.\n");
    }
}
