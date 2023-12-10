#include "all_the_functions.h"


int main(){

    Syntax *syntax = create_syntax();

        syntax->d_integer = assign_syntax(syntax, "int");
        syntax->d_float = assign_syntax(syntax, "float");
        //syntax->d_bool = assign_syntax(syntax, "bool");
        syntax->d_char = assign_syntax(syntax, "char");
        syntax->d_string = assign_syntax(syntax, "string");

        syntax->d_end_of_something = assign_syntax(syntax, "\n");
        syntax->d_must_have_too = assign_syntax(syntax, " ");
        syntax->d_ignore = assign_syntax(syntax, " ");
        syntax->d_atribution = assign_syntax(syntax, "=");

        syntax->d_begin_of_program = assign_syntax(syntax, "begin");
        syntax->d_end_of_program = assign_syntax(syntax, "end");
        syntax->d_end_of_end = assign_syntax(syntax, ".");

        syntax->d_while_begin = assign_syntax(syntax, "while");
        syntax->d_while_start = assign_syntax(syntax, "do");
        //syntax->d_break = assign_syntax(syntax, "break");

        //syntax->d_repeat_begin = assign_syntax(syntax, "repeat");
        //syntax->d_repeat_end = assign_syntax(syntax, "until");

        syntax->d_if = assign_syntax(syntax, "if");
        syntax->d_then = assign_syntax(syntax, "then");
        syntax->d_else = assign_syntax(syntax, "else");

        syntax->d_trunc = assign_syntax(syntax, "trunc");
        syntax->d_power = assign_syntax(syntax, "pow");

        syntax->d_print = assign_syntax(syntax, "print");

    char *cod = read_cod_in(syntax);
    if (cod == NULL){free(cod);}

    size_t cod_size = strlen(cod);
    int tokens = count_tokens(cod, cod_size);


    //printf("\nresult = %s",cod);

    //printf("\nsize = %d\n",tokens);


    Token *token = tokenization(cod, syntax, cod_size, tokens);
    if (token == NULL){destroy_everything(token, syntax, cod); return 2;}

    //token = put_line_to_all_tokens(token);
    print_all_tokens(token);
    //printf("\nline %d !!!error:  invalid name operator", token->number[3].line);

    program(token, syntax, 0, token->nr, false);
print_all_tokens_details(token);










/*
     token->number[2].content = "4";
    token->number[2].type = "value_int";
     token->number[3].content = "+";
    token->number[3].type = "+";
     token->number[4].content = "8";
    token->number[4].type = "value_int";
     token->number[5].content = "*";
    token->number[5].type = "*";
     token->number[6].content = "5";
    token->number[6].type = "value_int";
     token->number[7].content = "%";
    token->number[7].type = "%";
     token->number[8].content = "2";
    token->number[8].type = "value_int";
     token->number[9].content = "-";
    token->number[9].type = "-";
     token->number[10].content = "5";
    token->number[10].type = "value_int";
     token->number[11].content = "*";
    token->number[11].type = "*";
     token->number[12].content = "(";
    token->number[12].type = "(";
     token->number[13].content = "7";
    token->number[13].type = "value_int";
     token->number[14].content = "+";
    token->number[14].type = "+";
     token->number[15].content = "1";
    token->number[15].type = "value_int";
     token->number[16].content = ")";
    token->number[16].type = ")";


    int dddd = 4+8*(5%2)-5*(7+1);
    printf("\nvalue = %d , and = %d", calculate_int_expresion(token, syntax, 2, 16), dddd);


//2-15
*/






    destroy_everything(token, syntax, cod);
    printf("\n\nProcess finished");
return 0;
}



















