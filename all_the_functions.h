#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include "sintax.h"


typedef struct
{
    char *content;
    char *type;

    char *expresion;
    char *variable;

    int *value_int;
    float *value_float;
    bool *value_bool;

    int *capacity;

}The_box;

typedef struct
{
    The_box *number;
}Token;


///
Token *create_token_set(){

      Token *token = malloc(sizeof(Token));
      if (token == NULL) return NULL;

      //The_box *proprieties = malloc(sizeof(The_box));
      //if (proprieties == NULL) return NULL;

return token;
}


///
size_t read_cod_in(char *cod, Syntax *syntax)
{
    size_t base_size = 100;
    char *text = (char *)malloc(base_size * sizeof(char));

    if (text == NULL) {
        printf("Memory allocation failed.\n");
        return 1;
    }

    size_t tsize = 0;

    char ch;
    int ended = 0;
    int started = 0;
    size_t len = strlen(syntax->d_end_of_program);

    while (1) {
        ch = getchar();

        if ((ended == len) & (ch == syntax->d_end_of_end)) break;

        if (ch == syntax->d_end_of_program[ended]){
            ended++;
        }else{
            ended = 0;
        }

        text[tsize] = ch;
        tsize++;

        if (tsize == base_size - 1) {
            base_size = base_size * 2;
            char *new_buffer = (char *)realloc(text, base_size * sizeof(char));

            if (new_buffer == NULL) {
                printf("Memory reallocation failed.\n");
                free(text);
                return 1;
            }

            text = new_buffer;
        }
    }

    cod = text;
    return tsize;
}




/*//
Token *create_(int capacity)
{
  if (capacity <= 0) return NULL;

  Token *token = malloc(sizeof(Token));
  if (token == NULL) return NULL;

    token->expresion = malloc(sizeof(char) * capacity);

                if (token->expresion == NULL)
                {
                    free(token);
                    return NULL;
                }
    token->content = malloc(sizeof(char) * capacity);

                if (token->content == NULL)
                {
                    free(token);
                    return NULL;
                }

    token->type = malloc(sizeof(char) * 40);

                if (token->type == NULL)
                {
                    free(token);
                    return NULL;
                }

    token->variable = malloc(sizeof(char) * capacity);

                if (token->variable == NULL)
                {
                    free(token);
                    return NULL;
                }

    token->value_int = malloc(sizeof(int) * capacity);

                if (token->value_int == NULL)
                {
                    free(token);
                    return NULL;
                }

    token->value_float = malloc(sizeof(float) * capacity);

                if (token->value_float == NULL)
                {
                    free(token);
                    return NULL;
                }

    token->value_bool = malloc(sizeof(bool) * capacity);

                if (token->value_bool == NULL)
                {
                    free(token);
                    return NULL;
                }

  token->capacity = capacity;
  token->size = 0;

  return token;
}

///
void destroy_token(Token *token, int nr)
{
    for(int i = 0; i < nr; i++){
      free(token->content[i]);
      free(token->type[i]);

      free(token->value_variable[i]);
      free(token->value_int[i]);
      free(token->value_bool[i]);

      free(token->value_float[i]);
      free(token[i]);
    }
}



///
int give_tokens(char text, int start, details *partial)
{
    int verify = 0;
    int len = strlen(text);
    for(int i = start; i < len; i++){
            if(text[i] == ' '){
                if(verify == 0){
                    partial->content = ' ';
                    partial->type = 'space';
                    return i++;
                }else{
                    return i;
                }
            }





    }
}


*/













