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
    char *value_char;
    char *value_string;

    size_t *string_capacity;

    int capacity;
    int line;

}The_box;

typedef struct
{
    The_box *number;
    int nr;

}Token;


///
Token *create_token_set(){

      Token *token = malloc(sizeof(Token));
      if (token == NULL) return NULL;

      token->number = malloc(sizeof(The_box));
      if (token->number == NULL) return NULL;

return token;
}


///
void *create_a_box(Token *token, int number){
        if(number == 0){
            token->number = malloc(0 * sizeof(The_box));

            if (token->number == NULL) {
                printf("Memory reallocation failed.\n");
                free(token);
                return NULL;
            }
            token->nr = 0;
            token->number[number].capacity = 0;
        }else{
            The_box *new_buffer = realloc(token->number, number * sizeof(The_box));

            if (new_buffer == NULL) {
                printf("Memory reallocation failed.\n");
                free(token);
                return NULL;
            }
            token->number = new_buffer;
            token->nr = number;
            token->number[number].capacity = 0;
        }




    //return new_buffer;
}


///
char *read_cod_in(Syntax *syntax){

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
    int j = 0;

    while (1) {
        ch = getchar();

        //
            if (i < lenstart){
                if (ch == syntax->d_begin_of_program[begining]){
                        begining++;
                }else{
                        printf("\nline 1 error: expected '%s'(new line)\n", syntax->d_begin_of_program);
                        return NULL;
                }
            }
            if ((i >= lenstart) & (i < lenstart + lenstart_after)){
                if(ch == syntax->d_end_of_something[after_begining]){
                        after_begining++;
                    }else{
                        printf("\nline 1 error: expected '%s'(new line)\n", syntax->d_begin_of_program);
                        return NULL;
                    }
            }

            i++;

        //
            if(j <= lenbefore + len + lended){
                if(j < lenbefore){
                    if (syntax->d_end_of_something[before_ended] == ch){
                        before_ended++;
                    }else{
                            ended_ended = 0;
                            ended = 0;
                            before_ended = 0;
                            j = 0;
                    }
                }
                if((j >= lenbefore) & (j < len + lenbefore)){
                    if (ch == syntax->d_end_of_program[ended]){
                        ended++;
                    }else{
                            ended_ended = 0;
                            ended = 0;
                            before_ended = 0;
                            j = 0;
                    }
                }
                if((j >= len + lenbefore) & (j < lended + len + lenbefore)){
                    if(ch == syntax->d_end_of_end[ended_ended]){
                            ended_ended++;
                        }else{
                            ended_ended = 0;
                            ended = 0;
                            before_ended = 0;
                            j = 0;
                        }
                }
                j++;
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
        //printf("\n\nch = %s",text);
    }
    text[tsize] = '\0';
    //printf("\n\nch = %s",text);
    return text;
}


///
char *read_cod_in_from_file(Syntax *syntax){

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
    int j = 0;
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
                        return NULL;
                }
            }
            if ((i >= lenstart) & (i < lenstart + lenstart_after)){
                if(ch == syntax->d_end_of_something[after_begining]){
                        after_begining++;
                    }else{
                        printf("\nline 1 error: expected '%s'(new line)\n", syntax->d_begin_of_program);
                        return NULL;
                    }
            }

            i++;

        //
            if(j <= lenbefore + len + lended){
                if(j < lenbefore){
                    if (syntax->d_end_of_something[before_ended] == ch){
                        before_ended++;
                    }else{
                            ended_ended = 0;
                            ended = 0;
                            before_ended = 0;
                            j = 0;
                    }
                }
                if((j >= lenbefore) & (j < len + lenbefore)){
                    if (ch == syntax->d_end_of_program[ended]){
                        ended++;
                    }else{
                            ended_ended = 0;
                            ended = 0;
                            before_ended = 0;
                            j = 0;
                    }
                }
                if((j >= len + lenbefore) & (j < lended + len + lenbefore)){
                    if(ch == syntax->d_end_of_end[ended_ended]){
                            ended_ended++;
                        }else{
                            ended_ended = 0;
                            ended = 0;
                            before_ended = 0;
                            j = 0;
                        }
                }
                j++;
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
        //printf("\n\nch = %s",text);
    }
    text[tsize] = '\0';
    fclose(fptr);
    return text;

}


///
void destroy_everything(Token *token, Syntax *syntax, char *cod){

      free(token->number->content);
      free(token->number->type);
      //free(token->number->capacity);
      free(token->number->expresion);
      //free(token->number->line);
      free(token->number->value_bool);
      free(token->number->value_float);
      free(token->number->value_int);
      free(token->number->variable);

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
      free(cod);

}

///
void *create_a_capacitor(Token *token, int number){
        token->number[number].content = (char*) malloc(0 * sizeof(char));
        if (token->number[number].content == NULL)
        {
                printf("Memory reallocation failed.\n");
                free(token);
                return NULL;
        }
        token->number[number].capacity = 0;

//return new_buffer;
}


///
void *insert_character(Token *token, int number, char ch){

//printf("\ncapacity = %d , number = %d", token->number[number].capacity, number);

    if(token->number[number].capacity == 0){
        char *new_buffer = (char*)malloc(0 * sizeof(char));
        if (new_buffer == NULL)
        {
                printf("Memory reallocation failed.\n");
                free(new_buffer);
                return NULL;
        }
        token->number[number].capacity++;
        printf("\n%d",token->number[number].capacity);
        new_buffer[token->number[number].capacity] = ch;//ch;
        token->number[number].content = new_buffer;
    }else{
            char *new_buffer = (char *)realloc(token->number[number].content, (size_t)token->number[number].capacity * sizeof(char));

            if (new_buffer == NULL) {
                printf("Memory reallocation failed.\n");
                free(new_buffer);
                return NULL;
            }
        new_buffer[token->number[number].capacity] = ch;//ch;
        token->number[number].content = new_buffer;
        token->number[number].capacity++;
        //printf("\n\n%s",new_buffer);//token->number[number].content);

    }
     //token->number[number].content[3] = '/0';
}

///
int count_tokens(char *cod, size_t cod_size){
    int tokens;
    for(int i = 0; i < cod_size; i++){
        if((cod[i] == '\n') || (cod[i] == ',') || (cod[i] == '!') || (cod[i] == '|') || (cod[i] == '"') || (cod[i] == '[') || (cod[i] == ']') || (cod[i] == '>') || (cod[i] == '<') || (cod[i] == ' ') || (cod[i] == '%') || (cod[i] == '/') || (cod[i] == '*') || (cod[i] == '+') || (cod[i] == '(') || (cod[i] == ')') || (cod[i] == '-')|| (cod[i] == '=') || (cod[i] == '^')) tokens = tokens + 2;
    }
    return tokens;
}


///
Token *tokenization(char *cod, Syntax *syntax, size_t len, int tokens){
//create the token set
    Token *token = malloc(sizeof(Token));
    if (token == NULL) return NULL;
//create the first token
    tokens = tokens + 10;
    token->number = malloc(tokens * sizeof(The_box));

            if (token->number == NULL) {
                printf("Memory reallocation failed.\n");
                free(token);
                return NULL;
            }
            token->nr = 0;
            token->number[0].capacity = 0;
//allocate memory for the fist token contet
    size_t base_size = 100;
    token->number[0].content = (char *)malloc(base_size * sizeof(char));

    if (token->number[0].content == NULL) {
        printf("Memory allocation failed.\n");
        return NULL;
    }
//
    size_t tsize = 0;
    size_t bsize = base_size;

    char ch;
    int i = 0;
    int j = 0;
    int verify = 0;

    for(i = 0; i < len; i++){
        ch = cod[i];
        //printf("\ni = %d ; len = %zu", i, len);
        //printf("\n ch = %c",ch);

        if((ch == '\n') || (cod[i] == ',') || (cod[i] == '!') || (cod[i] == '|') || (ch == '"') || (ch == '[') || (ch == ']') || (ch == '>') || (ch == '<') || (ch == ' ') || (ch == '%') || (ch == '/') || (ch == '*') || (ch == '+') || (ch == '(') || (ch == ')') || (ch == '-')|| (ch == '=') || (ch == '^')){

            //end of the anterior token
            if(verify == 0){
                token->number[j].content[tsize] = '\0';
                token->number[j].capacity = tsize;
                tsize = 0;
                j++;
            }
            ///start a new token
                    if(j == tokens - 1){
                        tokens = tokens + 10;
                        The_box *box_buffer = realloc(token->number, tokens * sizeof(The_box));
                                //printf("\nbuffer[%d] = %s",0 ,box_buffer[0].content);
                        if (box_buffer == NULL) {
                            printf("Memory reallocation failed.\n");
                            free(token);
                            return NULL;}
                                //printf("\ntoken[%d] = %s",0 ,token->number[0].content);
                        token->number = box_buffer;
                    }
            ///allocate memory for the token with \n
            //create_a_box(token, 10);
            //
            char *content_buffer = (char *)malloc(base_size * sizeof(char));
                if (content_buffer == NULL) {
                    printf("Memory allocation failed.\n");
                    return NULL;
                }
            token->number[j].content = content_buffer;
            token->number[j].capacity = 0;
            //we introduce \n
            token->number[j].content[tsize] = ch;//printf("\nddddd");
            tsize++;
            token->number[j].content[tsize] = '\0';
            //printf("\n dddd = %s", token->number[j].content);
            token->number[j].capacity = tsize;
            j++;
            //start another token
                    if(j == tokens - 1){
                        tokens = tokens + 10;
                        The_box *box_buffer = realloc(token->number, tokens * sizeof(The_box));
                                //printf("\nbuffer[%d] = %s",0 ,box_buffer[0].content);
                        if (box_buffer == NULL) {
                            printf("Memory reallocation failed.\n");
                            free(token);
                            return NULL;}
                                //printf("\ntoken[%d] = %s",0 ,token->number[0].content);
                        token->number = box_buffer;
                    }
            token->number[j].capacity = 0;
            //allocate memory for another content token
            char *content_buffer2 = (char *)malloc(base_size * sizeof(char));
                if (content_buffer2 == NULL) {
                    printf("Memory allocation failed.\n");
                    return NULL;
                }
            token->number[j].content = content_buffer2;
            token->number[j].capacity = 0;

            tsize = 0;
            bsize = base_size;
            //i++;
            //ch = cod[i];
            verify++;

        }else{

            //insert one character in the content
            token->number[j].content[tsize] = ch;
            tsize++;


            if (tsize == base_size - 1) {
                bsize = bsize * 2;
                char *new_buffer = (char *)realloc(token->number[j].content, bsize * sizeof(char));
            //verify if there is enough space in the capacitor
                if (new_buffer == NULL) {
                    printf("Memory reallocation failed.\n");
                    free(token);
                    return NULL;
                }

                token->number[j].content = new_buffer;
            }
            verify = 0;
        }

        //printf("\n\nch = %s",token->number[j].content);
        //printf("\ntoken[%d] = %s",0 ,token->number[0].content);
    }

    token->number[j].content[tsize] = '\0';
    token->number[j].capacity = tsize;
    j++;
    token->nr = j;



    //print_all_tokens(token);
return token;
}

///
void print_all_tokens(Token *token){
    printf("\n nr = %d", token->nr);
    for(int i = 0; i < token->nr; i++){
     printf("\ntoken[%d] = %s",i ,token->number[i].content);
    }
}
///






///


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













