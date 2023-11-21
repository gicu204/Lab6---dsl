#include "first_part.h"
#include <math.h>
#include <stdbool.h>

float calculate_float_expresion(Token *token, Syntax *syntax, int d_start, int d_end);
int calculate_int_expresion(Token *token, Syntax *syntax, int d_start, int d_end);

bool verify_if_float_expresion(Token *token, Syntax *syntax, int d_start, int d_end);
bool verify_if_int_expresion(Token *token, Syntax *syntax, int d_start, int d_end);
bool verify_if_bool_expresion(Token *token, Syntax *syntax, int d_start, int d_end);

bool calculate_bool_expresion(Token *token, Syntax *syntax, int d_start, int d_end);



int calculate_int_expresion(Token *token, Syntax *syntax, int d_start, int d_end){
    int value = 0;
    for(int i = d_start; i <= d_end; i++){
        if(token->number[i].content != syntax->d_ignore){
                char *type = token->number[i].type;

                if(type == "value_int"){
                    value = value + atoi(token->number[i].content);

                }else if(type == "+"){
                    i++;
                    value = value + calculate_int_expresion(token, syntax, i, d_end);
                    i = d_end + 1;

                }else if(type == "-"){
                    i++;
                    value = value - calculate_int_expresion(token, syntax, i, d_end);
                    i = d_end + 1;

                }else if(type == "*"){
                    i++;
                    int j;
                    int parentheses = 0;
                    for(j = i; j <= d_end; j++){
                        if(token->number[j].type == "(") parentheses++;
                        if(token->number[j].type == ")") parentheses--;
                        if((parentheses == 0) & ((token->number[j].type == "+") /*|| (token->number[j].type == "^")  || (token->number[j].type == "%")*/ || (token->number[j].type == "-") || (token->number[j].type == "*") || (token->number[j].type == "/"))) break;
                    }
                    if(parentheses != 0){
                        printf("\nline %d !!!error:  parentheses not matched", token->number[i].line);
                    }
                    if(j < d_end) j--;
                    value = value * calculate_int_expresion(token, syntax, i, j);
                    i = j;

                }else if(type == "^"){
                    i++;
                    int j;
                    int parentheses = 0;
                    for(j = i; j <= d_end; j++){
                        if(token->number[j].type == "(") parentheses++;
                        if(token->number[j].type == ")") parentheses--;
                        if((parentheses == 0) & ((token->number[j].type == "+") /*|| (token->number[j].type == "^")  || (token->number[j].type == "%")*/ || (token->number[j].type == "-") || (token->number[j].type == "*") || (token->number[j].type == "/"))) break;
                    }
                    if(parentheses != 0){
                        printf("\nline %d !!!error:  parentheses not matched", token->number[i].line);
                    }
                    if(j < d_end) j--;
                    value = value ^ calculate_int_expresion(token, syntax, i, j);
                    i = j;

                }else if(type == "%"){
                    i++;
                    int j;
                    int parentheses = 0;
                    for(j = i; j <= d_end; j++){
                        if(token->number[j].type == "(") parentheses++;
                        if(token->number[j].type == ")") parentheses--;
                        if((parentheses == 0) & ((token->number[j].type == "+") /*|| (token->number[j].type == "^")*/ || (token->number[j].type == "%") || (token->number[j].type == "-") || (token->number[j].type == "*") || (token->number[j].type == "/"))) break;
                    }
                    if(parentheses != 0){
                        printf("\nline %d !!!error:  parentheses not matched", token->number[i].line);
                    }
                    if(j < d_end) j--;
                    value = value % calculate_int_expresion(token, syntax, i, j);
                    i = j;

                }else if(type == "("){
                    int j;
                    int parentheses = 0;
                    for(j = i; j <= d_end; j++){
                        if(token->number[j].type == "(") parentheses++;
                        if(token->number[j].type == ")") parentheses--;
                        if((parentheses == 0) & ((token->number[j].type == "+") || (token->number[j].type == "^") || (token->number[j].type == "%") || (token->number[j].type == "-") || (token->number[j].type == "*") || (token->number[j].type == "/"))) break;
                    }
                    if(parentheses != 0){
                        printf("\nline %d !!!error:  parentheses not matched", token->number[i].line);
                    }
                    if(j >= d_end){
                            for(j; j > i; j--){
                                if(token->number[j].type == ")") break;
                            }
                    }
                    i++;
                    j--;
                    value = value + calculate_int_expresion(token, syntax, i, j);
                    i = j + 2;

                }else if(type == ")"){
                    printf("\nline %d !!!error:  parentheses not matched", token->number[i].line);

                }else if(type == "trunc"){
                    i++;
                    int j;
                    int parentheses = 0;
                    for(j = i; j <= d_end; j++){
                        if(token->number[j].type == "(") parentheses++;
                        if(token->number[j].type == ")") parentheses--;
                        if((parentheses == 0) & ((token->number[j].type == "+") || (token->number[j].type == "^") || (token->number[j].type == "%") || (token->number[j].type == "-") || (token->number[j].type == "*") || (token->number[j].type == "/"))) break;
                    }
                    if(parentheses != 0){
                        printf("\nline %d !!!error:  parentheses not matched", token->number[i].line);
                    }
                    if(j < d_end) j--;
                    value = value + trunc(calculate_float_expresion(token, syntax, i, j));
                    i = j;

                }else if(type == "var_int"){
                    value = value + *token->number[i].value_int;
                }
        }
    }
return value;
}

float calculate_float_expresion(Token *token, Syntax *syntax, int d_start, int d_end){
    float value = 0;
    for(int i = d_start; i <= d_end; i++){
        if(token->number[i].content != syntax->d_ignore){
                char *type = token->number[i].type;

                if(type == "value_float"){
                    value = value + atof(token->number[i].content);

                }else if(type == "+"){
                    i++;
                    value = value + calculate_int_expresion(token, syntax, i, d_end);
                    i = d_end + 1;

                }else if(type == "-"){
                    i++;
                    value = value - calculate_int_expresion(token, syntax, i, d_end);
                    i = d_end + 1;

                }else if(type == "*"){
                    i++;
                    int j;
                    int parentheses = 0;
                    for(j = i; j <= d_end; j++){
                        if(token->number[j].type == "(") parentheses++;
                        if(token->number[j].type == ")") parentheses--;
                        if((parentheses == 0) & ((token->number[j].type == "+") /*|| (token->number[j].type == "^")  || (token->number[j].type == "%")*/ || (token->number[j].type == "-") || (token->number[j].type == "*") || (token->number[j].type == "/"))) break;
                    }
                    if(parentheses != 0){
                        printf("\nline %d !!!error:  parentheses not matched", token->number[i].line);
                    }
                    if(j < d_end) j--;
                    value = value * calculate_int_expresion(token, syntax, i, j);
                    i = j;

                }else if(type == "^"){
                    i++;
                    int j;
                    int parentheses = 0;
                    for(j = i; j <= d_end; j++){
                        if(token->number[j].type == "(") parentheses++;
                        if(token->number[j].type == ")") parentheses--;
                        if((parentheses == 0) & ((token->number[j].type == "+") /*|| (token->number[j].type == "^")  || (token->number[j].type == "%")*/ || (token->number[j].type == "-") || (token->number[j].type == "*") || (token->number[j].type == "/"))) break;
                    }
                    if(parentheses != 0){
                        printf("\nline %d !!!error:  parentheses not matched", token->number[i].line);
                    }
                    if(j < d_end) j--;
                    value = value ^ calculate_int_expresion(token, syntax, i, j);
                    i = j;

                }else if(type == "/"){
                    i++;
                    int j;
                    int parentheses = 0;
                    for(j = i; j <= d_end; j++){
                        if(token->number[j].type == "(") parentheses++;
                        if(token->number[j].type == ")") parentheses--;
                        if((parentheses == 0) & ((token->number[j].type == "+") || (token->number[j].type == "^") || (token->number[j].type == "%") || (token->number[j].type == "-") || (token->number[j].type == "*") || (token->number[j].type == "/"))) break;
                    }
                    if(parentheses != 0){
                        printf("\nline %d !!!error:  parentheses not matched", token->number[i].line);
                    }
                    if(j < d_end) j--;
                    value = value / calculate_int_expresion(token, syntax, i, j);
                    i = j;

                }else if(type == "("){
                    int j;
                    int parentheses = 0;
                    for(j = i; j <= d_end; j++){
                        if(token->number[j].type == "(") parentheses++;
                        if(token->number[j].type == ")") parentheses--;
                        if((parentheses == 0) & ((token->number[j].type == "+") || (token->number[j].type == "^") || (token->number[j].type == "%") || (token->number[j].type == "-") || (token->number[j].type == "*") || (token->number[j].type == "/"))) break;
                    }
                    if(parentheses != 0){
                        printf("\nline %d !!!error:  parentheses not matched", token->number[i].line);
                    }
                    if(j >= d_end){
                            for(j; j > i; j--){
                                if(token->number[j].type == ")") break;
                            }
                    }
                    i++;
                    j--;
                    value = value + calculate_int_expresion(token, syntax, i, j);
                    i = j + 2;

                }else if(type == ")"){
                    printf("\nline %d !!!error:  parentheses not matched", token->number[i].line);

                }else if(type == "trunc"){
                    i++;
                    int j;
                    int parentheses = 0;
                    for(j = i; j <= d_end; j++){
                        if(token->number[j].type == "(") parentheses++;
                        if(token->number[j].type == ")") parentheses--;
                        if((parentheses == 0) & ((token->number[j].type == "+") || (token->number[j].type == "^") || (token->number[j].type == "%") || (token->number[j].type == "-") || (token->number[j].type == "*") || (token->number[j].type == "/"))) break;
                    }
                    if(parentheses != 0){
                        printf("\nline %d !!!error:  parentheses not matched", token->number[i].line);
                    }
                    if(j < d_end) j--;
                    value = value + trunc(calculate_float_expresion(token, syntax, i, j));
                    i = j;

                }else if(type == "var_float"){
                    value = value + *token->number[i].value_float;
                }
        }
    }
return value;
}

bool calculate_bool_expresion(Token *token, Syntax *syntax, int d_start, int d_end){
bool value = false;

return value;
}

































