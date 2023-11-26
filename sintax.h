#include<string.h>

typedef struct
{
    char *d_integer;
    char *d_float;
    char *d_bool;
    char *d_char;
    char *d_string;

    char *d_end_of_something;
    char *d_must_have_too;
    char * d_ignore;
    char *d_atribution;

    char *d_begin_of_program;
    char *d_end_of_program;
    char *d_end_of_end;

    char *d_while_begin;
    char *d_while_start;
    char *d_break;
    //char *d_repeat_begin;
    //char *d_repeat_end;

    char *d_if;
    char *d_else;
    char *d_then;

    char *d_trunc;
    char *d_power;

    char *d_print;

}Syntax;



///
Syntax *create_syntax(){

      Syntax *syntax = malloc(sizeof(Syntax));
      if (syntax == NULL) return NULL;

return syntax;
}


///
char *assign_syntax(Syntax *syntax, const char *text){
    size_t len = strlen(text);

      if (len <= 0) return NULL;

      char *content = malloc(len * sizeof(char));
      if (content == NULL)
                    {
                        free(syntax);
                        return NULL;
                    }
    content = strdup(text);

  return content;
}















