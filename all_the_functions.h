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
    int *line;

}Token;

//typedef struct
//{
//    The_box *number;
//}Token;


///
Token *create_token_set(){

      Token *token = malloc(sizeof(Token));
      if (token == NULL) return NULL;

      //  token->number = malloc(sizeof(The_box));
      //if (token->number == NULL) return NULL;

return token;
}


///
size_t read_cod_in(char *cod, Syntax *syntax){
    size_t base_size = 100;
    char *text = (char *)malloc(base_size * sizeof(char));

    if (text == NULL) {
        printf("Memory allocation failed.\n");
        return 0;
    }

    size_t tsize = 0;

    char ch;
    int ended = 0;
    int ended_ended = 0;
    int before_ended = 0;
    int begining = 0;
    int after_begining = 0;
    size_t len = strlen(syntax->d_end_of_program);
    size_t lended = strlen(syntax->d_end_of_end);
    size_t lenbefore = strlen(syntax->d_end_of_something);
    size_t lenstart = strlen(syntax->d_begin_of_program);
    size_t lenstart_after = strlen(syntax->d_end_of_something);
    int i = 0;

    while (1) {
        ch = getchar();

        //
            if (i < lenstart){
                if (ch == syntax->d_begin_of_program[begining]){
                        begining++;
                }else{
                        printf("\nline 1 error: expected '%s'(new line)\n", syntax->d_begin_of_program);
                        return -1;
                }
            }
            if ((i >= lenstart) & (i < lenstart + lenstart_after)){
                if(ch == syntax->d_end_of_something[after_begining]){
                        after_begining++;
                    }else{
                        printf("\nline 1 error: expected '%s'(new line)\n", syntax->d_begin_of_program);
                        return -1;
                    }
            }

            i++;

        //
        if (ended == len){
            if(ch == syntax->d_end_of_end[ended_ended]){
                ended_ended++;
            }else{
                ended_ended = 0;
                ended = 0;
            }
        }

        if (before_ended == lenbefore){
            if (ch == syntax->d_end_of_program[ended]){
                ended++;
            }else{
                before_ended = 0;
            }
        }

        if (syntax->d_end_of_something[before_ended] == ch){
            before_ended++;
        }


        //
        text[tsize] = ch;
        tsize++;

        if (tsize == base_size - 1) {
            base_size = base_size * 2;
            char *new_buffer = (char *)realloc(text, base_size * sizeof(char));

            if (new_buffer == NULL) {
                printf("Memory reallocation failed.\n");
                free(text);
                return 0;
            }

            text = new_buffer;
        }

        if(ended_ended == lended) break;
    }

    cod = text;
    return tsize;
}


///
size_t read_cod_from_file_in(char *cod, Syntax *syntax){

    size_t base_size = 100;
    char *text = (char *)malloc(base_size * sizeof(char));

    if (text == NULL) {
        printf("Memory allocation failed.\n");
        return 0;
    }

    size_t tsize = 0;

    char ch;
    int ended = 0;
    int ended_ended = 0;
    int before_ended = 0;
    int begining = 0;
    int after_begining = 0;
    size_t len = strlen(syntax->d_end_of_program);
    size_t lended = strlen(syntax->d_end_of_end);
    size_t lenbefore = strlen(syntax->d_end_of_something);
    size_t lenstart = strlen(syntax->d_begin_of_program);
    size_t lenstart_after = strlen(syntax->d_end_of_something);
    int i = 0;
    FILE *fptr;
    fptr = fopen("codu.txt", "r");

    while (1) {
        ch = fgetc(fptr);

        //
            if (i < lenstart){
                if (ch == syntax->d_begin_of_program[begining]){
                        begining++;
                }else{
                        printf("\nline 1 error: expected '%s'(new line)\n", syntax->d_begin_of_program);
                        return -1;
                }
            }
            if ((i >= lenstart) & (i < lenstart + lenstart_after)){
                if(ch == syntax->d_end_of_something[after_begining]){
                        after_begining++;
                    }else{
                        printf("\nline 1 error: expected '%s'(new line)\n", syntax->d_begin_of_program);
                        return -1;
                    }
            }

            i++;

        //
        if (ended == len){
            if(ch == syntax->d_end_of_end[ended_ended]){
                ended_ended++;
            }else{
                ended_ended = 0;
                ended = 0;
            }
        }

        if (before_ended == lenbefore){
            if (ch == syntax->d_end_of_program[ended]){
                ended++;
            }else{
                before_ended = 0;
            }
        }

        if (syntax->d_end_of_something[before_ended] == ch){
            before_ended++;
        }


        //
        text[tsize] = ch;
        tsize++;

        if (tsize == base_size - 1) {
            base_size = base_size * 2;
            char *new_buffer = (char *)realloc(text, base_size * sizeof(char));

            if (new_buffer == NULL) {
                printf("Memory reallocation failed.\n");
                free(text);
                return 0;
            }

            text = new_buffer;
        }

        if(ended_ended == lended) break;
    }

    cod = text;
    fclose(fptr);
    return tsize;

}


///
void destroy_everything(Token *token, Syntax *syntax){

      free(token->content);
      free(token->type);
      free(token->capacity);
      free(token->expresion);
      free(token->line);
      free(token->value_bool);
      free(token->value_float);
      free(token->value_int);
      free(token->variable);

      free(syntax->d_integer);
      free(syntax->d_float);
      free(syntax->d_bool);
      free(syntax->d_char);
      free(syntax->d_string);
      free(syntax->d_end_of_something);
      free(syntax->d_must_have_too);
      free(syntax->d_ignore);
      free(syntax->d_atribution);
      free(syntax->d_begin_of_program);
      free(syntax->d_end_of_program);
      free(syntax->d_end_of_end);
      free(syntax->d_while_begin);
      free(syntax->d_while_start);
      free(syntax->d_if);
      free(syntax->d_else);
      free(syntax->d_print);

      free(syntax);
      free(token);

}


//The_box *create_the_box(){
//}
///
char *insert_content_token(Token *token, const char *text){
    size_t len = strlen(text);

      if (len <= 0) return NULL;

      char *content = malloc(len * sizeof(char));
      if (content == NULL)
        {
                        free(token);
                        return NULL;
                    }
    content = strdup(text);

  return content;
}


///
char *insert_character_provisory(const char *text, char ch){
    size_t len = strlen(text);

    len++;

            char *new_buffer = (char *)realloc((char*)text, len * sizeof(char));

            if (new_buffer == NULL) {
                printf("Memory reallocation failed.\n");
                free(new_buffer);
                return NULL;
            }
        new_buffer[len] = ch;


          char *content = new_buffer;

  return content;
}


///
int tokenization(Token *token, const char *cod, Syntax syntax){

        size_t len = strlen(cod);

        if (len <= 0) return -1;

        int i = 0;






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













