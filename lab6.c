#include "all_the_functions.h"


int main(){


    Syntax *syntax = create_syntax();

        syntax->d_integer = assign_syntax(syntax, "int");
        syntax->d_float = assign_syntax(syntax, "float");
        syntax->d_bool = assign_syntax(syntax, "bool");
        syntax->d_char = assign_syntax(syntax, "char");
        syntax->d_string = assign_syntax(syntax, "string");

        syntax->d_end_of_something = assign_syntax(syntax, "\n");
        syntax->d_must_have_too = assign_syntax(syntax, " ");
        syntax->d_atribution = assign_syntax(syntax, "=");

        syntax->d_begin_of_program = assign_syntax(syntax, "begin");
        syntax->d_end_of_program = assign_syntax(syntax, "end");
        syntax->d_end_of_end = assign_syntax(syntax, ".");

        syntax->d_while_begin = assign_syntax(syntax, "while");
        syntax->d_while_start = assign_syntax(syntax, "do");
        syntax->d_repeat_begin = assign_syntax(syntax, "repeat");
        syntax->d_repeat_end = assign_syntax(syntax, "until");

        syntax->d_print = assign_syntax(syntax, "print");


    char *cod = (char *)malloc(sizeof(char));
    size_t cod_size = read_cod_in(cod, syntax);














return 0;
}


