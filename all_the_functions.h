#include "first_part.h"
#include <math.h>
#include <stdbool.h>

void insert_int_in_var(Token *token, Syntax *syntax, int nr, int *value);
int extract_int_from_var(Token *token, Syntax *syntax,  int nr);

void insert_float_in_var(Token *token, Syntax *syntax, int nr, float *value);
float extract_float_from_var(Token *token, Syntax *syntax, int nr);

//void insert_bool_in_var(Token *token, int nr, bool value);
//bool extract_bool_from_var(Token *token, int nr);

void insert_char_in_var(Token *token, Syntax *syntax, int nr, char *value);
char extract_char_from_var(Token *token, Syntax *syntax, int nr);

void insert_string_in_var(Token *token, Syntax *syntax, int nr, char value[]);
char *extract_string_from_var(Token *token, Syntax *syntax, int nr);
void insert_one_char_string_in_var(Token *token, Syntax *syntax, int nr, char value, int where);
char *extract_one_char_string_from_var(Token *token, Syntax *syntax, int nr, int where);


float calculate_power_expresion(Token *token, Syntax *syntax, int d_start, int d_end);
float calculate_float_expresion(Token *token, Syntax *syntax, int d_start, int d_end);
int calculate_int_expresion(Token *token, Syntax *syntax, int d_start, int d_end);

bool verify_if_float_expresion(Token *token, Syntax *syntax, int d_start, int d_end);
bool verify_if_int_expresion(Token *token, Syntax *syntax, int d_start, int d_end);
bool calculate_next_bool_expresion(Token *token, Syntax *syntax, bool value, char operation_type[], int d_start, int d_end);
bool verify_if_bool_expresion(Token *token, Syntax *syntax, int d_start, int d_end);
bool verify_if_string(Token *token, Syntax *syntax, int d_start, int d_end);
bool verify_if_char(Token *token, Syntax *syntax, int d_start, int d_end);

bool calculate_bool_expresion(Token *token, Syntax *syntax, int d_start, int d_end);


///
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
                    int parentheses2 = 0;
                    for(j = i; j <= d_end; j++){
                        if(token->number[j].type == "(") parentheses++;
                        if(token->number[j].type == ")") parentheses--;
                        if(token->number[j].type == "[") parentheses2++;
                        if(token->number[j].type == "]") parentheses2--;
                        if((parentheses == 0) & (parentheses2 == 0) & ((token->number[j].type == "+") /*|| (token->number[j].type == "^")  || (token->number[j].type == "%")*/ || (token->number[j].type == "-") || (token->number[j].type == "*"))) break;
                    }
                    if((parentheses != 0) & (parentheses2 != 0)){
                        printf("\nline %d !!!error:  parentheses not matched", token->number[i].line);
                    }
                    if(j < d_end) j--;
                    value = value * calculate_int_expresion(token, syntax, i, j);
                    i = j;

                /*}else if(type == "^"){
                    i++;
                    int j;
                    int parentheses = 0;
                    int parentheses2 = 0;
                    for(j = i; j <= d_end; j++){
                        if(token->number[j].type == "(") parentheses++;
                        if(token->number[j].type == ")") parentheses--;
                        if(token->number[j].type == "[") parentheses2++;
                        if(token->number[j].type == "]") parentheses2--;
                        if((parentheses == 0) & (parentheses2 == 0) & ((token->number[j].type == "+") /*|| (token->number[j].type == "^")  || (token->number[j].type == "%") || (token->number[j].type == "-") || (token->number[j].type == "*") || (token->number[j].type == "/"))) break;
                    }
                    if((parentheses != 0) & (parentheses2 != 0)){
                        printf("\nline %d !!!error:  parentheses not matched", token->number[i].line);
                    }
                    if(j < d_end) j--;
                    value = pow(value, calculate_int_expresion(token, syntax, i, j));
                    i = j;
                    */
                }else if(type == "%"){
                    i++;
                    int j;
                    int parentheses = 0;
                    int parentheses2 = 0;
                    for(j = i; j <= d_end; j++){
                        if(token->number[j].type == "(") parentheses++;
                        if(token->number[j].type == ")") parentheses--;
                        if(token->number[j].type == "[") parentheses2++;
                        if(token->number[j].type == "]") parentheses2--;
                        if((parentheses == 0) & (parentheses2 == 0) & ((token->number[j].type == "+") /*|| (token->number[j].type == "^")*/ || (token->number[j].type == "%") || (token->number[j].type == "-") || (token->number[j].type == "*"))) break;
                    }
                    if((parentheses != 0) & (parentheses2 != 0)){
                        printf("\nline %d !!!error:  parentheses not matched", token->number[i].line);
                    }
                    if(j < d_end) j--;
                    value = value % calculate_int_expresion(token, syntax, i, j);
                    i = j;

                }else if(type == "("){
                    int j;
                    int parentheses = 0;
                    int parentheses2 = 0;
                    for(j = i; j <= d_end; j++){
                        if(token->number[j].type == "(") parentheses++;
                        if(token->number[j].type == ")") parentheses--;
                        if(token->number[j].type == "[") parentheses2++;
                        if(token->number[j].type == "]") parentheses2--;
                        if((parentheses == 0) & (parentheses2 == 0) & ((token->number[j].type == "+") /*|| (token->number[j].type == "^")*/ || (token->number[j].type == "%") || (token->number[j].type == "-") || (token->number[j].type == "*"))) break;
                    }
                    if((parentheses != 0) & (parentheses2 != 0)){
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

                }else if(type == "["){
                    int j;
                    int parentheses = 0;
                    int parentheses2 = 0;
                    for(j = i; j <= d_end; j++){
                        if(token->number[j].type == "(") parentheses++;
                        if(token->number[j].type == ")") parentheses--;
                        if(token->number[j].type == "[") parentheses2++;
                        if(token->number[j].type == "]") parentheses2--;
                        if((parentheses == 0) & (parentheses2 == 0) & ((token->number[j].type == "+") /*|| (token->number[j].type == "^")*/ || (token->number[j].type == "%") || (token->number[j].type == "-") || (token->number[j].type == "*"))) break;
                    }
                    if((parentheses != 0) & (parentheses2 != 0)){
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

                }else if(type == "]"){
                    printf("\nline %d !!!error:  parentheses not matched", token->number[i].line);

                }else if(type == "trunc"){
                    i++;
                    int j;
                    int parentheses = 0;
                    int parentheses2 = 0;
                    for(j = i; j <= d_end; j++){
                        if(token->number[j].type == "(") parentheses++;
                        if(token->number[j].type == ")") parentheses--;
                        if(token->number[j].type == "[") parentheses2++;
                        if(token->number[j].type == "]") parentheses2--;
                        if((parentheses == 0) & (parentheses2 == 0) & ((token->number[j].type == "+") /*|| (token->number[j].type == "^")*/ || (token->number[j].type == "%") || (token->number[j].type == "-") || (token->number[j].type == "*"))) break;
                    }
                    if(parentheses != 0){
                        printf("\nline %d !!!error:  parentheses not matched", token->number[i].line);
                    }
                    if(j < d_end) j--;
                    value = value + trunc(calculate_float_expresion(token, syntax, i, j));
                    i = j;

                }else if(type == "var_int"){
                    if(token->number[i].value_int == NULL){
                        printf("\nline %d !!!error: %s has no assigned value", token->number[i].line, token->number[i].content);
                    }else{
                    value = value + extract_int_from_var(token,syntax, i);
                    }
                }
        }
    }

return value;
}


///
float calculate_float_expresion(Token *token, Syntax *syntax, int d_start, int d_end){
    float value = 0;
    for(int i = d_start; i <= d_end; i++){
        if(token->number[i].content != syntax->d_ignore){
                char *type = token->number[i].type;

                if(type == "value_int"){
                    value = value + atoi(token->number[i].content);

                }else if(type == "value_flaot"){
                    value = value + atof(token->number[i].content);

                }else if(type == "+"){
                    i++;
                    value = value + calculate_float_expresion(token, syntax, i, d_end);
                    i = d_end + 1;

                }else if(type == "-"){
                    i++;
                    value = value - calculate_float_expresion(token, syntax, i, d_end);
                    i = d_end + 1;

                }else if(type == "*"){
                    i++;
                    int j;
                    int parentheses = 0;
                    int parentheses2 = 0;
                    for(j = i; j <= d_end; j++){
                        if(token->number[j].type == "(") parentheses++;
                        if(token->number[j].type == ")") parentheses--;
                        if(token->number[j].type == "[") parentheses2++;
                        if(token->number[j].type == "]") parentheses2--;
                        if((parentheses == 0) & (parentheses2 == 0) & ((token->number[j].type == "+") /* || (token->number[j].type == "pow") || (token->number[j].type == "%")*/ || (token->number[j].type == "-") || (token->number[j].type == "*"))) break;
                    }
                    if((parentheses != 0) & (parentheses2 != 0)){
                        printf("\nline %d !!!error:  parentheses not matched", token->number[i].line);
                    }
                    if(j < d_end) j--;
                    value = value * calculate_float_expresion(token, syntax, i, j);
                    i = j;

                }else if(type == "pow"){
                    i++;
                    int j;
                    int parentheses = 0;
                    int parentheses2 = 0;
                    for(j = i; j <= d_end; j++){
                        if(token->number[j].type == "(") parentheses++;
                        if(token->number[j].type == ")") parentheses--;
                        if(token->number[j].type == "[") parentheses2++;
                        if(token->number[j].type == "]") parentheses2--;
                        if((parentheses == 0) & (parentheses2 == 0) & ((token->number[j].type == "+")/* || (token->number[j].type == "pow")*/ || (token->number[j].type == "-") || (token->number[j].type == "*") || (token->number[j].type == "/"))) break;
                    }
                    if((parentheses != 0) & (parentheses2 != 0)){
                        printf("\nline %d !!!error:  parentheses not matched", token->number[i].line);
                    }
                    if(j < d_end) j--;

                    value = value + calculate_power_expresion(token, syntax, i++, j);
                    i = j++;

                }else if(type == "/"){
                    i++;
                    int j;
                    int parentheses = 0;
                    int parentheses2 = 0;
                    for(j = i; j <= d_end; j++){
                        if(token->number[j].type == "(") parentheses++;
                        if(token->number[j].type == ")") parentheses--;
                        if(token->number[j].type == "[") parentheses2++;
                        if(token->number[j].type == "]") parentheses2--;
                        if((parentheses == 0) & (parentheses2 == 0) & ((token->number[j].type == "+")/* || (token->number[j].type == "pow") || (token->number[j].type == "/")*/ || (token->number[j].type == "-") || (token->number[j].type == "*") || (token->number[j].type == "/"))) break;
                    }
                    if((parentheses != 0) & (parentheses2 != 0)){
                        printf("\nline %d !!!error:  parentheses not matched", token->number[i].line);
                    }
                    if(j < d_end) j--;
                    float sss = calculate_float_expresion(token, syntax, i, j);
                    if(sss == 0){
                        printf("\nline %d !!!error: do you want to divide by 0? :|", token->number[i].line);
                    }else{
                        value = value / sss;
                    }
                    i = j;

                }else if(type == "("){
                    int j;
                    int parentheses = 0;
                    int parentheses2 = 0;
                    for(j = i; j <= d_end; j++){
                        if(token->number[j].type == "(") parentheses++;
                        if(token->number[j].type == ")") parentheses--;
                        if(token->number[j].type == "[") parentheses2++;
                        if(token->number[j].type == "]") parentheses2--;
                        if((parentheses == 0) & (parentheses2 == 0) & ((token->number[j].type == "+")/* || (token->number[j].type == "^")*/ || (token->number[j].type == "-") || (token->number[j].type == "*") || (token->number[j].type == "/"))) break;
                    }
                    if((parentheses != 0) & (parentheses2 != 0)){
                        printf("\nline %d !!!error:  parentheses not matched", token->number[i].line);
                    }
                    if(j >= d_end){
                            for(j; j > i; j--){
                                if(token->number[j].type == ")") break;
                            }
                    }
                    i++;
                    j--;
                    value = value + calculate_float_expresion(token, syntax, i, j);
                    i = j + 2;

                }else if(type == "["){
                    int j;
                    int parentheses = 0;
                    int parentheses2 = 0;
                    for(j = i; j <= d_end; j++){
                        if(token->number[j].type == "(") parentheses++;
                        if(token->number[j].type == ")") parentheses--;
                        if(token->number[j].type == "[") parentheses2++;
                        if(token->number[j].type == "]") parentheses2--;
                        if((parentheses == 0) & (parentheses2 == 0) & ((token->number[j].type == "+")/* || (token->number[j].type == "^")*/ || (token->number[j].type == "-") || (token->number[j].type == "*") || (token->number[j].type == "/"))) break;
                    }
                    if((parentheses != 0) & (parentheses2 != 0)){
                        printf("\nline %d !!!error:  parentheses not matched", token->number[i].line);
                    }
                    if(j >= d_end){
                            for(j; j > i; j--){
                                if(token->number[j].type == ")") break;
                            }
                    }
                    i++;
                    j--;
                    value = value + calculate_float_expresion(token, syntax, i, j);
                    i = j + 2;


                }else if(type == ")"){
                    printf("\nline %d !!!error:  parentheses not matched", token->number[i].line);

                }else if(type == "]"){
                    printf("\nline %d !!!error:  parentheses not matched", token->number[i].line);

                }else if(type == "trunc"){
                    i++;
                    int j;
                    int parentheses = 0;
                    int parentheses2 = 0;
                    for(j = i; j <= d_end; j++){
                        if(token->number[j].type == "(") parentheses++;
                        if(token->number[j].type == ")") parentheses--;
                        if(token->number[j].type == "[") parentheses2++;
                        if(token->number[j].type == "]") parentheses2--;
                        if((parentheses == 0) & (parentheses2 == 0) & ((token->number[j].type == "+")/* || (token->number[j].type == "^")*/ || (token->number[j].type == "%") || (token->number[j].type == "-") || (token->number[j].type == "*") || (token->number[j].type == "/"))) break;
                    }
                    if(parentheses != 0){
                        printf("\nline %d !!!error:  parentheses not matched", token->number[i].line);
                    }
                    if(j < d_end) j--;
                    value = value + trunc(calculate_float_expresion(token, syntax, i, j));
                    i = j;

                }else if(type == "var_float"){
                    if(token->number[i].value_float == NULL){
                        printf("\nline %d !!!error: %s has no assigned value", token->number[i].line, token->number[i].content);
                    }else{
                    value = value + *token->number[i].value_float;
                    }
                }else if(type == "var_int"){
                    if(token->number[i].value_int == NULL){
                        printf("\nline %d !!!error: %s has no assigned value", token->number[i].line, token->number[i].content);
                    }else{
                    value = value + extract_float_from_var(token,syntax, i);
                    }
                }
        }
    }

return value;
}


///
bool calculate_bool_expresion(Token *token, Syntax *syntax, int d_start, int d_end){
int j, i;
int j1, i1;
int j2, i2;
int terms = 0;
bool value = false;
bool verify = false;
char type[5] = "NUll";
char type1[5] = "NUll";
char type2[5] = "NUll";
char operation_type[5] = "NULL";

    for( j = d_start; j <= d_end; i++){
        if(token->number[j].content != syntax->d_ignore){
            if(token->number[j].content != syntax->d_ignore){

            if((token->number[j].type == "[") || (token->number[j].type == "]") || (token->number[j].type == "(")  || (token->number[j].type == ")")){
               int parentheses = 0;
               int parentheses2 = 0;
               for(i = j; i <= d_end; i++){
                            if(token->number[i].type == "(") parentheses++;
                            if(token->number[i].type == ")") parentheses--;
                            if(token->number[i].type == "[") parentheses2++;
                            if(token->number[i].type == "]") parentheses2--;
                            if((parentheses != 0) & (parentheses2 != 0) % ((token->number[j].type == "&") || (token->number[j].type == "<") || (token->number[j].type == ">") || (token->number[j].type == "=") || (token->number[j].type == "|"))) break;
                        }
                        if((parentheses != 0) & (parentheses2 != 0)){
                            printf("\nline %d !!!error:  parentheses not matched", token->number[j].line);
                        }else{
                                for(i; i > j; i--){
                                    if(token->number[i].type == ")") break;
                                    if(token->number[i].type == "]") break;
                                }
                            if((type == "NULL") & ((type1 == "NULL") || (type2 == "NULL"))){
                                j++;
                                i--;
                                if(verify_if_bool_expresion(token, syntax, j, i)){
                                    strcpy(type, "bool");
                                    goto done;
                                }
                                if(verify_if_int_expresion(token, syntax, j, i)){
                                    strcpy(type, "int");
                                    goto done;
                                }
                                if(verify_if_float_expresion(token, syntax, j, i)){
                                    strcpy(type, "float");
                                    goto done;
                                }
                            }
                        }
                        done:
                        if(type1 == "NULL"){
                            strcpy(type1, type);
                            strcpy(type, "NUll");
                            i1 = i;
                            j1 = j;
                        }else if(type2 == "NULL"){
                            strcpy(type2, type);
                            strcpy(type, "NUll");
                            i2 = i;
                            j2 = j;
                        }
                        j = i + 2;
                        terms++;
            }

            if((type == "NULL") & ((type1 == "NULL") || (type2 == "NULL"))){
                if(token->number[j].type == "value_bool"){
                    strcpy(type, "bool"); terms++;
                }
                if((token->number[j].type == "var_int") || (token->number[j].type == "value_int")){
                    strcpy(type, "int"); terms++;
                }
                if((token->number[j].type == "var_float") || (token->number[j].type == "value_float")){
                    strcpy(type, "float"); terms++;
                }

                if(type1 == "NULL"){
                            strcpy(type1, type);
                            strcpy(type, "NUll");
                            i1 = i;
                            j1 = j;
                        }else if(type2 == "NULL"){
                            strcpy(type2, type);
                            strcpy(type, "NUll");
                            i2 = i;
                            j2 = j;
                }
            }
            if(operation_type == "NULL"){
                    if(token->number[j].type == "&"){
                        terms--;
                        strcpy(operation_type, "&");
                    }else if(token->number[j].type == "="){
                        j++;
                        if(token->number[j].type == "="){
                            terms--;
                            strcpy(operation_type, "==");
                        }else{
                             printf("\nline %d !!!error:  it should be '==' without space", token->number[j].line);
                             return false;
                        }
                    }else if(token->number[j].type == "!"){
                        j++;
                        if(token->number[j].type == "="){
                            terms--;
                            strcpy(operation_type, "!=");
                        }else{
                             printf("\nline %d !!!error:  it should be '!=' without space", token->number[j].line);
                             return false;
                        }
                    }else if(token->number[j].type == "|"){
                        j++;
                        if(token->number[j].type == "|"){
                            terms--;
                            strcpy(operation_type, "||");
                        }else{
                             printf("\nline %d !!!error:  it should be '||' without space", token->number[j].line);
                             return false;
                        }
                    }else if(token->number[j].type == "<"){
                        j++;
                        if(token->number[j].type == "="){
                            terms--;
                            strcpy(operation_type, "<=");
                        }else{
                            terms--;
                            strcpy(operation_type, "<");
                        }
                    }else if(token->number[j].type == ">"){
                        j++;
                        if(token->number[j].type == "="){
                            terms--;
                            strcpy(operation_type, ">=");
                        }else{
                            terms--;
                            strcpy(operation_type, ">");
                        }
                    }
            }


            if((operation_type != "NULL") & (type1 != "NULL") & (type2 != "NULL")){

                    if (operation_type == "&"){

                            if((type1 != "bool") & (type2 != "bool")){
                            value = calculate_bool_expresion(token, syntax, j1, i1) & calculate_bool_expresion(token, syntax, j2, i2);
                            strcpy(operation_type, "NULL");
                            strcpy(type1, "NULL");
                            strcpy(type2, "NULL");
                            verify = true;

                        }else if((type1 != "bool") & (type2 != "int")){
                            value = calculate_bool_expresion(token, syntax, j1, i1) & calculate_int_expresion(token, syntax, j2, i2);
                            strcpy(operation_type, "NULL");
                            strcpy(type1, "NULL");
                            strcpy(type2, "NULL");
                            verify = true;

                        }else if((type1 != "bool") & (type2 != "float")){
                            printf("\nline %d !!!error:  invalid operation bool to float", token->number[j].line);
                            //value = calculate_bool_expresion(token, syntax, j1, i1) & calculate_float_expresion(token, syntax, j2, i2);
                            return false;

                        }else if((type1 != "int") & (type2 != "int")){
                            value = calculate_int_expresion(token, syntax, j1, i1) & calculate_int_expresion(token, syntax, j2, i2);
                            strcpy(operation_type, "NULL");
                            strcpy(type1, "NULL");
                            strcpy(type2, "NULL");
                            verify = true;

                        }else if((type1 != "int") & (type2 != "bool")){
                            value = calculate_int_expresion(token, syntax, j1, i1) & calculate_bool_expresion(token, syntax, j2, i2);
                            strcpy(operation_type, "NULL");
                            strcpy(type1, "NULL");
                            strcpy(type2, "NULL");
                            verify = true;

                        }else if((type1 != "int") & (type2 != "float")){
                            printf("\nline %d !!!error:  invalid operation int to float", token->number[j].line);
                            //value = calculate_int_expresion(token, syntax, j1, i1) & calculate_float_expresion(token, syntax, j2, i2);
                            return false;

                        }else if((type1 != "float") & (type2 != "float")){
                            //value = calculate_float_expresion(token, syntax, j1, i1) & calculate_float_expresion(token, syntax, j2, i2);
                            //strcpy(operation_type, "NULL");
                            //strcpy(type1, "NULL");
                            //strcpy(type2, "NULL");
                            //verify = true;
                            printf("\nline %d !!!error:  invalid operation bool to float", token->number[j].line);
                            return false;

                        }else if((type1 != "float") & (type2 != "bool")){
                            //value = calculate_float_expresion(token, syntax, j1, i1) & calculate_bool_expresion(token, syntax, j2, i2);
                            //strcpy(operation_type, "NULL");
                            //strcpy(type1, "NULL");
                            //strcpy(type2, "NULL");
                            //verify = true;
                            printf("\nline %d !!!error:  invalid operation float to boolean", token->number[j].line);
                            return false;

                        }else if((type1 != "float") & (type2 != "int")){
                            //value = calculate_float_expresion(token, syntax, j1, i1) & calculate_int_expresion(token, syntax, j2, i2);
                            //strcpy(operation_type, "NULL");
                            //strcpy(type1, "NULL");
                            //strcpy(type2, "NULL");
                            //verify = true;
                            printf("\nline %d !!!error:  invalid operation float to int", token->number[j].line);
                            return false;

                        }

                    }else if(operation_type == "=="){

                        if((type1 != "bool") & (type2 != "bool")){
                            value = calculate_bool_expresion(token, syntax, j1, i1) == calculate_bool_expresion(token, syntax, j2, i2);
                            strcpy(operation_type, "NULL");
                            strcpy(type1, "NULL");
                            strcpy(type2, "NULL");
                            verify = true;

                        }else if((type1 != "bool") & (type2 != "int")){
                            value = calculate_bool_expresion(token, syntax, j1, i1) == calculate_int_expresion(token, syntax, j2, i2);
                            strcpy(operation_type, "NULL");
                            strcpy(type1, "NULL");
                            strcpy(type2, "NULL");
                            verify = true;

                        }else if((type1 != "bool") & (type2 != "float")){
                            value = calculate_bool_expresion(token, syntax, j1, i1) == calculate_float_expresion(token, syntax, j2, i2);
                            strcpy(operation_type, "NULL");
                            strcpy(type1, "NULL");
                            strcpy(type2, "NULL");
                            verify = true;

                        }else if((type1 != "int") & (type2 != "int")){
                            value = calculate_int_expresion(token, syntax, j1, i1) == calculate_int_expresion(token, syntax, j2, i2);
                            strcpy(operation_type, "NULL");
                            strcpy(type1, "NULL");
                            strcpy(type2, "NULL");
                            verify = true;

                        }else if((type1 != "int") & (type2 != "bool")){
                            value = calculate_int_expresion(token, syntax, j1, i1) == calculate_bool_expresion(token, syntax, j2, i2);
                            strcpy(operation_type, "NULL");
                            strcpy(type1, "NULL");
                            strcpy(type2, "NULL");
                            verify = true;

                        }else if((type1 != "int") & (type2 != "float")){
                            value = calculate_int_expresion(token, syntax, j1, i1) == calculate_float_expresion(token, syntax, j2, i2);
                            strcpy(operation_type, "NULL");
                            strcpy(type1, "NULL");
                            strcpy(type2, "NULL");
                            verify = true;

                        }else if((type1 != "float") & (type2 != "float")){
                            value = calculate_float_expresion(token, syntax, j1, i1) == calculate_float_expresion(token, syntax, j2, i2);
                            strcpy(operation_type, "NULL");
                            strcpy(type1, "NULL");
                            strcpy(type2, "NULL");
                            verify = true;

                        }else if((type1 != "float") & (type2 != "bool")){
                            value = calculate_float_expresion(token, syntax, j1, i1) == calculate_bool_expresion(token, syntax, j2, i2);
                            strcpy(operation_type, "NULL");
                            strcpy(type1, "NULL");
                            strcpy(type2, "NULL");
                            verify = true;

                        }else if((type1 != "float") & (type2 != "int")){
                            value = calculate_float_expresion(token, syntax, j1, i1) == calculate_int_expresion(token, syntax, j2, i2);
                            strcpy(operation_type, "NULL");
                            strcpy(type1, "NULL");
                            strcpy(type2, "NULL");
                            verify = true;

                        }
                    }else if(operation_type == "!="){


                        if((type1 != "bool") & (type2 != "bool")){
                            value = calculate_bool_expresion(token, syntax, j1, i1) != calculate_bool_expresion(token, syntax, j2, i2);
                            strcpy(operation_type, "NULL");
                            strcpy(type1, "NULL");
                            strcpy(type2, "NULL");
                            verify = true;

                        }else if((type1 != "bool") & (type2 != "int")){
                            value = calculate_bool_expresion(token, syntax, j1, i1) != calculate_int_expresion(token, syntax, j2, i2);
                            strcpy(operation_type, "NULL");
                            strcpy(type1, "NULL");
                            strcpy(type2, "NULL");
                            verify = true;

                        }else if((type1 != "bool") & (type2 != "float")){
                            value = calculate_bool_expresion(token, syntax, j1, i1) != calculate_float_expresion(token, syntax, j2, i2);
                            strcpy(operation_type, "NULL");
                            strcpy(type1, "NULL");
                            strcpy(type2, "NULL");
                            verify = true;

                        }else if((type1 != "int") & (type2 != "int")){
                            value = calculate_int_expresion(token, syntax, j1, i1) != calculate_int_expresion(token, syntax, j2, i2);
                            strcpy(operation_type, "NULL");
                            strcpy(type1, "NULL");
                            strcpy(type2, "NULL");
                            verify = true;

                        }else if((type1 != "int") & (type2 != "bool")){
                            value = calculate_int_expresion(token, syntax, j1, i1) != calculate_bool_expresion(token, syntax, j2, i2);
                            strcpy(operation_type, "NULL");
                            strcpy(type1, "NULL");
                            strcpy(type2, "NULL");
                            verify = true;

                        }else if((type1 != "int") & (type2 != "float")){
                            value = calculate_int_expresion(token, syntax, j1, i1) != calculate_float_expresion(token, syntax, j2, i2);
                            strcpy(operation_type, "NULL");
                            strcpy(type1, "NULL");
                            strcpy(type2, "NULL");
                            verify = true;

                        }else if((type1 != "float") & (type2 != "float")){
                            value = calculate_float_expresion(token, syntax, j1, i1) != calculate_float_expresion(token, syntax, j2, i2);
                            strcpy(operation_type, "NULL");
                            strcpy(type1, "NULL");
                            strcpy(type2, "NULL");
                            verify = true;

                        }else if((type1 != "float") & (type2 != "bool")){
                            value = calculate_float_expresion(token, syntax, j1, i1) != calculate_bool_expresion(token, syntax, j2, i2);
                            strcpy(operation_type, "NULL");
                            strcpy(type1, "NULL");
                            strcpy(type2, "NULL");
                            verify = true;

                        }else if((type1 != "float") & (type2 != "int")){
                            value = calculate_float_expresion(token, syntax, j1, i1) != calculate_int_expresion(token, syntax, j2, i2);
                            strcpy(operation_type, "NULL");
                            strcpy(type1, "NULL");
                            strcpy(type2, "NULL");
                            verify = true;

                        }

                    }else if(operation_type == "||"){

                        if((type1 != "bool") & (type2 != "bool")){
                            value = calculate_bool_expresion(token, syntax, j1, i1) || calculate_bool_expresion(token, syntax, j2, i2);
                            strcpy(operation_type, "NULL");
                            strcpy(type1, "NULL");
                            strcpy(type2, "NULL");
                            verify = true;

                        }else if((type1 != "bool") & (type2 != "int")){
                            value = calculate_bool_expresion(token, syntax, j1, i1) || calculate_int_expresion(token, syntax, j2, i2);
                            strcpy(operation_type, "NULL");
                            strcpy(type1, "NULL");
                            strcpy(type2, "NULL");
                            verify = true;

                        }else if((type1 != "bool") & (type2 != "float")){
                            value = calculate_bool_expresion(token, syntax, j1, i1) || calculate_float_expresion(token, syntax, j2, i2);
                            strcpy(operation_type, "NULL");
                            strcpy(type1, "NULL");
                            strcpy(type2, "NULL");
                            verify = true;

                        }else if((type1 != "int") & (type2 != "int")){
                            value = calculate_int_expresion(token, syntax, j1, i1) || calculate_int_expresion(token, syntax, j2, i2);
                            strcpy(operation_type, "NULL");
                            strcpy(type1, "NULL");
                            strcpy(type2, "NULL");
                            verify = true;

                        }else if((type1 != "int") & (type2 != "bool")){
                            value = calculate_int_expresion(token, syntax, j1, i1) || calculate_bool_expresion(token, syntax, j2, i2);
                            strcpy(operation_type, "NULL");
                            strcpy(type1, "NULL");
                            strcpy(type2, "NULL");
                            verify = true;

                        }else if((type1 != "int") & (type2 != "float")){
                            value = calculate_int_expresion(token, syntax, j1, i1) || calculate_float_expresion(token, syntax, j2, i2);
                            strcpy(operation_type, "NULL");
                            strcpy(type1, "NULL");
                            strcpy(type2, "NULL");
                            verify = true;

                        }else if((type1 != "float") & (type2 != "float")){
                            value = calculate_float_expresion(token, syntax, j1, i1) || calculate_float_expresion(token, syntax, j2, i2);
                            strcpy(operation_type, "NULL");
                            strcpy(type1, "NULL");
                            strcpy(type2, "NULL");
                            verify = true;

                        }else if((type1 != "float") & (type2 != "bool")){
                            value = calculate_float_expresion(token, syntax, j1, i1) || calculate_bool_expresion(token, syntax, j2, i2);
                            strcpy(operation_type, "NULL");
                            strcpy(type1, "NULL");
                            strcpy(type2, "NULL");
                            verify = true;

                        }else if((type1 != "float") & (type2 != "int")){
                            value = calculate_float_expresion(token, syntax, j1, i1) || calculate_int_expresion(token, syntax, j2, i2);
                            strcpy(operation_type, "NULL");
                            strcpy(type1, "NULL");
                            strcpy(type2, "NULL");
                            verify = true;

                        }

                    }else if(operation_type == "<="){

                            if((type1 != "bool") & (type2 != "bool")){
                            value = calculate_bool_expresion(token, syntax, j1, i1) <= calculate_bool_expresion(token, syntax, j2, i2);
                            strcpy(operation_type, "NULL");
                            strcpy(type1, "NULL");
                            strcpy(type2, "NULL");
                            verify = true;

                        }else if((type1 != "bool") & (type2 != "int")){
                            value = calculate_bool_expresion(token, syntax, j1, i1) <= calculate_int_expresion(token, syntax, j2, i2);
                            strcpy(operation_type, "NULL");
                            strcpy(type1, "NULL");
                            strcpy(type2, "NULL");
                            verify = true;

                        }else if((type1 != "bool") & (type2 != "float")){
                            value = calculate_bool_expresion(token, syntax, j1, i1) <= calculate_float_expresion(token, syntax, j2, i2);
                            strcpy(operation_type, "NULL");
                            strcpy(type1, "NULL");
                            strcpy(type2, "NULL");
                            verify = true;

                        }else if((type1 != "int") & (type2 != "int")){
                            value = calculate_int_expresion(token, syntax, j1, i1) <= calculate_int_expresion(token, syntax, j2, i2);
                            strcpy(operation_type, "NULL");
                            strcpy(type1, "NULL");
                            strcpy(type2, "NULL");
                            verify = true;

                        }else if((type1 != "int") & (type2 != "bool")){
                            value = calculate_int_expresion(token, syntax, j1, i1) <= calculate_bool_expresion(token, syntax, j2, i2);
                            strcpy(operation_type, "NULL");
                            strcpy(type1, "NULL");
                            strcpy(type2, "NULL");
                            verify = true;

                        }else if((type1 != "int") & (type2 != "float")){
                            value = calculate_int_expresion(token, syntax, j1, i1) <= calculate_float_expresion(token, syntax, j2, i2);
                            strcpy(operation_type, "NULL");
                            strcpy(type1, "NULL");
                            strcpy(type2, "NULL");
                            verify = true;

                        }else if((type1 != "float") & (type2 != "float")){
                            value = calculate_float_expresion(token, syntax, j1, i1) <= calculate_float_expresion(token, syntax, j2, i2);
                            strcpy(operation_type, "NULL");
                            strcpy(type1, "NULL");
                            strcpy(type2, "NULL");
                            verify = true;

                        }else if((type1 != "float") & (type2 != "bool")){
                            value = calculate_float_expresion(token, syntax, j1, i1) <= calculate_bool_expresion(token, syntax, j2, i2);
                            strcpy(operation_type, "NULL");
                            strcpy(type1, "NULL");
                            strcpy(type2, "NULL");
                            verify = true;

                        }else if((type1 != "float") & (type2 != "int")){
                            value = calculate_float_expresion(token, syntax, j1, i1) <= calculate_int_expresion(token, syntax, j2, i2);
                            strcpy(operation_type, "NULL");
                            strcpy(type1, "NULL");
                            strcpy(type2, "NULL");
                            verify = true;

                        }

                    }else if(operation_type == "<"){

                        if((type1 != "bool") & (type2 != "bool")){
                            value = calculate_bool_expresion(token, syntax, j1, i1) < calculate_bool_expresion(token, syntax, j2, i2);
                            strcpy(operation_type, "NULL");
                            strcpy(type1, "NULL");
                            strcpy(type2, "NULL");
                            verify = true;

                        }else if((type1 != "bool") & (type2 != "int")){
                            value = calculate_bool_expresion(token, syntax, j1, i1) < calculate_int_expresion(token, syntax, j2, i2);
                            strcpy(operation_type, "NULL");
                            strcpy(type1, "NULL");
                            strcpy(type2, "NULL");
                            verify = true;

                        }else if((type1 != "bool") & (type2 != "float")){
                            value = calculate_bool_expresion(token, syntax, j1, i1) < calculate_float_expresion(token, syntax, j2, i2);
                            strcpy(operation_type, "NULL");
                            strcpy(type1, "NULL");
                            strcpy(type2, "NULL");
                            verify = true;

                        }else if((type1 != "int") & (type2 != "int")){
                            value = calculate_int_expresion(token, syntax, j1, i1) < calculate_int_expresion(token, syntax, j2, i2);
                            strcpy(operation_type, "NULL");
                            strcpy(type1, "NULL");
                            strcpy(type2, "NULL");
                            verify = true;

                        }else if((type1 != "int") & (type2 != "bool")){
                            value = calculate_int_expresion(token, syntax, j1, i1) < calculate_bool_expresion(token, syntax, j2, i2);
                            strcpy(operation_type, "NULL");
                            strcpy(type1, "NULL");
                            strcpy(type2, "NULL");
                            verify = true;

                        }else if((type1 != "int") & (type2 != "float")){
                            value = calculate_int_expresion(token, syntax, j1, i1) < calculate_float_expresion(token, syntax, j2, i2);
                            strcpy(operation_type, "NULL");
                            strcpy(type1, "NULL");
                            strcpy(type2, "NULL");
                            verify = true;

                        }else if((type1 != "float") & (type2 != "float")){
                            value = calculate_float_expresion(token, syntax, j1, i1) < calculate_float_expresion(token, syntax, j2, i2);
                            strcpy(operation_type, "NULL");
                            strcpy(type1, "NULL");
                            strcpy(type2, "NULL");
                            verify = true;

                        }else if((type1 != "float") & (type2 != "bool")){
                            value = calculate_float_expresion(token, syntax, j1, i1) < calculate_bool_expresion(token, syntax, j2, i2);
                            strcpy(operation_type, "NULL");
                            strcpy(type1, "NULL");
                            strcpy(type2, "NULL");
                            verify = true;

                        }else if((type1 != "float") & (type2 != "int")){
                            value = calculate_float_expresion(token, syntax, j1, i1) < calculate_int_expresion(token, syntax, j2, i2);
                            strcpy(operation_type, "NULL");
                            strcpy(type1, "NULL");
                            strcpy(type2, "NULL");
                            verify = true;

                        }

                    }else if(operation_type == ">="){

                        if((type1 != "bool") & (type2 != "bool")){
                            value = calculate_bool_expresion(token, syntax, j1, i1) >= calculate_bool_expresion(token, syntax, j2, i2);
                            strcpy(operation_type, "NULL");
                            strcpy(type1, "NULL");
                            strcpy(type2, "NULL");
                            verify = true;

                        }else if((type1 != "bool") & (type2 != "int")){
                            value = calculate_bool_expresion(token, syntax, j1, i1) >= calculate_int_expresion(token, syntax, j2, i2);
                            strcpy(operation_type, "NULL");
                            strcpy(type1, "NULL");
                            strcpy(type2, "NULL");
                            verify = true;

                        }else if((type1 != "bool") & (type2 != "float")){
                            value = calculate_bool_expresion(token, syntax, j1, i1) >= calculate_float_expresion(token, syntax, j2, i2);
                            strcpy(operation_type, "NULL");
                            strcpy(type1, "NULL");
                            strcpy(type2, "NULL");
                            verify = true;

                        }else if((type1 != "int") & (type2 != "int")){
                            value = calculate_int_expresion(token, syntax, j1, i1) >= calculate_int_expresion(token, syntax, j2, i2);
                            strcpy(operation_type, "NULL");
                            strcpy(type1, "NULL");
                            strcpy(type2, "NULL");
                            verify = true;

                        }else if((type1 != "int") & (type2 != "bool")){
                            value = calculate_int_expresion(token, syntax, j1, i1) >= calculate_bool_expresion(token, syntax, j2, i2);
                            strcpy(operation_type, "NULL");
                            strcpy(type1, "NULL");
                            strcpy(type2, "NULL");
                            verify = true;

                        }else if((type1 != "int") & (type2 != "float")){
                            value = calculate_int_expresion(token, syntax, j1, i1) >= calculate_float_expresion(token, syntax, j2, i2);
                            strcpy(operation_type, "NULL");
                            strcpy(type1, "NULL");
                            strcpy(type2, "NULL");
                            verify = true;

                        }else if((type1 != "float") & (type2 != "float")){
                            value = calculate_float_expresion(token, syntax, j1, i1) >= calculate_float_expresion(token, syntax, j2, i2);
                            strcpy(operation_type, "NULL");
                            strcpy(type1, "NULL");
                            strcpy(type2, "NULL");
                            verify = true;

                        }else if((type1 != "float") & (type2 != "bool")){
                            value = calculate_float_expresion(token, syntax, j1, i1) >= calculate_bool_expresion(token, syntax, j2, i2);
                            strcpy(operation_type, "NULL");
                            strcpy(type1, "NULL");
                            strcpy(type2, "NULL");
                            verify = true;

                        }else if((type1 != "float") & (type2 != "int")){
                            value = calculate_float_expresion(token, syntax, j1, i1) >= calculate_int_expresion(token, syntax, j2, i2);
                            strcpy(operation_type, "NULL");
                            strcpy(type1, "NULL");
                            strcpy(type2, "NULL");
                            verify = true;

                        }

                    }else if(operation_type == ">"){

                        if((type1 != "bool") & (type2 != "bool")){
                            value = calculate_bool_expresion(token, syntax, j1, i1) > calculate_bool_expresion(token, syntax, j2, i2);
                            strcpy(operation_type, "NULL");
                            strcpy(type1, "NULL");
                            strcpy(type2, "NULL");
                            verify = true;

                        }else if((type1 != "bool") & (type2 != "int")){
                            value = calculate_bool_expresion(token, syntax, j1, i1) >= calculate_int_expresion(token, syntax, j2, i2);
                            strcpy(operation_type, "NULL");
                            strcpy(type1, "NULL");
                            strcpy(type2, "NULL");
                            verify = true;

                        }else if((type1 != "bool") & (type2 != "float")){
                            value = calculate_bool_expresion(token, syntax, j1, i1) >= calculate_float_expresion(token, syntax, j2, i2);
                            strcpy(operation_type, "NULL");
                            strcpy(type1, "NULL");
                            strcpy(type2, "NULL");
                            verify = true;

                        }else if((type1 != "int") & (type2 != "int")){
                            value = calculate_int_expresion(token, syntax, j1, i1) >= calculate_int_expresion(token, syntax, j2, i2);
                            strcpy(operation_type, "NULL");
                            strcpy(type1, "NULL");
                            strcpy(type2, "NULL");
                            verify = true;

                        }else if((type1 != "int") & (type2 != "bool")){
                            value = calculate_int_expresion(token, syntax, j1, i1) >= calculate_bool_expresion(token, syntax, j2, i2);
                            strcpy(operation_type, "NULL");
                            strcpy(type1, "NULL");
                            strcpy(type2, "NULL");
                            verify = true;

                        }else if((type1 != "int") & (type2 != "float")){
                            value = calculate_int_expresion(token, syntax, j1, i1) >= calculate_float_expresion(token, syntax, j2, i2);
                            strcpy(operation_type, "NULL");
                            strcpy(type1, "NULL");
                            strcpy(type2, "NULL");
                            verify = true;

                        }else if((type1 != "float") & (type2 != "float")){
                            value = calculate_float_expresion(token, syntax, j1, i1) >= calculate_float_expresion(token, syntax, j2, i2);
                            strcpy(operation_type, "NULL");
                            strcpy(type1, "NULL");
                            strcpy(type2, "NULL");
                            verify = true;

                        }else if((type1 != "float") & (type2 != "bool")){
                            value = calculate_float_expresion(token, syntax, j1, i1) >= calculate_bool_expresion(token, syntax, j2, i2);
                            strcpy(operation_type, "NULL");
                            strcpy(type1, "NULL");
                            strcpy(type2, "NULL");
                            verify = true;

                        }else if((type1 != "float") & (type2 != "int")){
                            value = calculate_float_expresion(token, syntax, j1, i1) >= calculate_int_expresion(token, syntax, j2, i2);
                            strcpy(operation_type, "NULL");
                            strcpy(type1, "NULL");
                            strcpy(type2, "NULL");
                            verify = true;

                        }

                    }

                }



            }else if((operation_type != "NULL") & verify){
                            j++;
                            value = calculate_next_bool_expresion(token, syntax, value, operation_type, j, d_end);
            }
        }
        }
return value;
}


///
bool calculate_next_bool_expresion(Token *token, Syntax *syntax, bool value, char operation_type[], int d_start, int d_end){

int j, i;
int j1, i1;
int terms = 0;
bool value1;
bool verify = false;
char type[5] = "NUll";
char type1[5] = "NUll";

    for( j = d_start; j <= d_end; i++){
        if(token->number[j].content != syntax->d_ignore){

            if((token->number[j].type == "[") || (token->number[j].type == "]") || (token->number[j].type == "(")  || (token->number[j].type == ")")){
               int parentheses = 0;
               int parentheses2 = 0;
               for(i = j; i <= d_end; i++){
                            if(token->number[i].type == "(") parentheses++;
                            if(token->number[i].type == ")") parentheses--;
                            if(token->number[i].type == "[") parentheses2++;
                            if(token->number[i].type == "]") parentheses2--;
                            if((parentheses != 0) & (parentheses2 != 0) % ((token->number[j].type == "&") || (token->number[j].type == "<") || (token->number[j].type == ">") || (token->number[j].type == "=") || (token->number[j].type == "|"))) break;
                        }
                        if((parentheses != 0) & (parentheses2 != 0)){
                            printf("\nline %d !!!error:  parentheses not matched", token->number[j].line);
                        }else{
                                for(i; i > j; i--){
                                    if(token->number[i].type == ")") break;
                                    if(token->number[i].type == "]") break;
                                }
                            if((type == "NULL") & (type1 == "NULL")){
                                j++;
                                i--;
                                if(verify_if_bool_expresion(token, syntax, j, i)){
                                    strcpy(type, "bool");
                                    goto done;
                                }
                                if(verify_if_int_expresion(token, syntax, j, i)){
                                    strcpy(type, "int");
                                    goto done;
                                }
                                if(verify_if_float_expresion(token, syntax, j, i)){
                                    strcpy(type, "float");
                                    goto done;
                                }
                            }
                        }
                        done:
                        if(type1 == "NULL"){
                            strcpy(type1, type);
                            strcpy(type, "NUll");
                            i1 = i;
                            j1 = j;
                        }
            }

            if((type == "NULL") & (type1 == "NULL")){
                if(token->number[j].type == "value_bool"){
                    strcpy(type, "bool"); terms++;
                }
                if((token->number[j].type == "var_int") || (token->number[j].type == "value_int")){
                    strcpy(type, "int"); terms++;
                }
                if((token->number[j].type == "var_float") || (token->number[j].type == "value_float")){
                    strcpy(type, "float"); terms++;
                }

                if(type1 == "NULL"){
                            strcpy(type1, type);
                            strcpy(type, "NUll");
                            i1 = i;
                            j1 = j;
                }
            }
            if(operation_type == "NULL"){
                    if(token->number[j].type == "&"){
                        terms--;
                        strcpy(operation_type, "&");
                    }else if(token->number[j].type == "="){
                        j++;
                        if(token->number[j].type == "="){
                            terms--;
                            strcpy(operation_type, "==");
                        }else{
                             printf("\nline %d !!!error:  it should be '==' without space", token->number[j].line);
                             return false;
                        }
                    }else if(token->number[j].type == "!"){
                        j++;
                        if(token->number[j].type == "="){
                            terms--;
                            strcpy(operation_type, "!=");
                        }else{
                             printf("\nline %d !!!error:  it should be '!=' without space", token->number[j].line);
                             return false;
                        }
                    }else if(token->number[j].type == "<"){
                        j++;
                        if(token->number[j].type == "="){
                            terms--;
                            strcpy(operation_type, "<=");
                        }else{
                            terms--;
                            strcpy(operation_type, "<");
                        }
                    }else if(token->number[j].type == ">"){
                        j++;
                        if(token->number[j].type == "="){
                            terms--;
                            strcpy(operation_type, ">=");
                        }else{
                            terms--;
                            strcpy(operation_type, ">");
                        }
                    }
            }


            if((operation_type != "NULL") & (type1 != "NULL")){
                if(operation_type == "&"){

                        if(type1 != "bool"){
                            value1 = value & calculate_bool_expresion(token, syntax, j1, i1);
                            strcpy(operation_type, "NULL");
                            strcpy(type1, "NULL");
                            verify = true;

                        }else if(type1 != "int"){
                            value1 = value & calculate_int_expresion(token, syntax, j1, i1);
                            strcpy(operation_type, "NULL");
                            strcpy(type1, "NULL");
                            verify = true;

                        }else if(type1 != "float"){
                            //value1 = value & calculate_float_expresion(token, syntax, j1, i1);
                            //strcpy(operation_type, "NULL");
                            //strcpy(type1, "NULL");
                            //verify = true;
                            printf("\nline %d !!!error:  invalid operation bool to float", token->number[j].line);
                            return false;

                        }

                }else if(operation_type == "=="){

                        if(type1 != "bool"){
                            value1 = value == calculate_bool_expresion(token, syntax, j1, i1);
                            strcpy(operation_type, "NULL");
                            strcpy(type1, "NULL");
                            verify = true;

                        }else if(type1 != "int"){
                            value1 = value == calculate_int_expresion(token, syntax, j1, i1);
                            strcpy(operation_type, "NULL");
                            strcpy(type1, "NULL");
                            verify = true;

                        }else if(type1 != "float"){
                            value1 = value == calculate_float_expresion(token, syntax, j1, i1);
                            strcpy(operation_type, "NULL");
                            strcpy(type1, "NULL");
                            verify = true;

                        }

                }else if(operation_type == "!="){

                        if(type1 != "bool"){
                            value1 = value == calculate_bool_expresion(token, syntax, j1, i1);
                            strcpy(operation_type, "NULL");
                            strcpy(type1, "NULL");
                            verify = true;

                        }else if(type1 != "int"){
                            value1 = value == calculate_int_expresion(token, syntax, j1, i1);
                            strcpy(operation_type, "NULL");
                            strcpy(type1, "NULL");
                            verify = true;

                        }else if(type1 != "float"){
                            value1 = value == calculate_float_expresion(token, syntax, j1, i1);
                            strcpy(operation_type, "NULL");
                            strcpy(type1, "NULL");
                            verify = true;

                        }

                }else if(operation_type == "<="){

                        if(type1 != "bool"){
                            value1 = value <= calculate_bool_expresion(token, syntax, j1, i1);
                            strcpy(operation_type, "NULL");
                            strcpy(type1, "NULL");
                            verify = true;

                        }else if(type1 != "int"){
                            value1 = value <= calculate_int_expresion(token, syntax, j1, i1);
                            strcpy(operation_type, "NULL");
                            strcpy(type1, "NULL");
                            verify = true;

                        }else if(type1 != "float"){
                            value1 = value <= calculate_float_expresion(token, syntax, j1, i1);
                            strcpy(operation_type, "NULL");
                            strcpy(type1, "NULL");
                            verify = true;

                        }

                }else if(operation_type == "<"){

                        if(type1 != "bool"){
                            value1 = value < calculate_bool_expresion(token, syntax, j1, i1);
                            strcpy(operation_type, "NULL");
                            strcpy(type1, "NULL");
                            verify = true;

                        }else if(type1 != "int"){
                            value1 = value < calculate_int_expresion(token, syntax, j1, i1);
                            strcpy(operation_type, "NULL");
                            strcpy(type1, "NULL");
                            verify = true;

                        }else if(type1 != "float"){
                            value1 = value < calculate_float_expresion(token, syntax, j1, i1);
                            strcpy(operation_type, "NULL");
                            strcpy(type1, "NULL");
                            verify = true;

                        }

                }else if(operation_type == ">="){

                        if(type1 != "bool"){
                            value1 = value >= calculate_bool_expresion(token, syntax, j1, i1);
                            strcpy(operation_type, "NULL");
                            strcpy(type1, "NULL");
                            verify = true;

                        }else if(type1 != "int"){
                            value1 = value >= calculate_int_expresion(token, syntax, j1, i1);
                            strcpy(operation_type, "NULL");
                            strcpy(type1, "NULL");
                            verify = true;

                        }else if(type1 != "float"){
                            value1 = value >= calculate_float_expresion(token, syntax, j1, i1);
                            strcpy(operation_type, "NULL");
                            strcpy(type1, "NULL");
                            verify = true;

                        }

                }else if(operation_type == ">"){

                        if(type1 != "bool"){
                            value1 = value > calculate_bool_expresion(token, syntax, j1, i1);
                            strcpy(operation_type, "NULL");
                            strcpy(type1, "NULL");
                            verify = true;

                        }else if(type1 != "int"){
                            value1 = value > calculate_int_expresion(token, syntax, j1, i1);
                            strcpy(operation_type, "NULL");
                            strcpy(type1, "NULL");
                            verify = true;

                        }else if(type1 != "float"){
                            value1 = value > calculate_float_expresion(token, syntax, j1, i1);
                            strcpy(operation_type, "NULL");
                            strcpy(type1, "NULL");
                            verify = true;

                        }

                }else if(operation_type == "||"){

                        if(type1 != "bool"){
                            value1 = value || calculate_bool_expresion(token, syntax, j1, i1);
                            strcpy(operation_type, "NULL");
                            strcpy(type1, "NULL");
                            verify = true;

                        }else if(type1 != "int"){
                            value1 = value || calculate_int_expresion(token, syntax, j1, i1);
                            strcpy(operation_type, "NULL");
                            strcpy(type1, "NULL");
                            verify = true;

                        }else if(type1 != "float"){
                            value1 = value || calculate_float_expresion(token, syntax, j1, i1);
                            strcpy(operation_type, "NULL");
                            strcpy(type1, "NULL");
                            verify = true;

                        }

                }



            }else if((operation_type != "NULL") & verify){
                            j++;
                            value = calculate_next_bool_expresion(token, syntax, value, operation_type, j, d_end);
        }
        }
    }
return value1;
}


///
float calculate_power_expresion(Token *token, Syntax *syntax, int d_start, int d_end){
float value;
float value1;
float value2;
int valuesss = 0;

int i = d_start;
                for(int n = 0; n < 2; n++){
                    int j;
                    int parentheses = 0;
                    int parentheses2 = 0;
                    for(j = i; j <= d_end; j++){
                        if(token->number[j].type == "(") parentheses++;
                        if(token->number[j].type == ")") parentheses--;
                        if(token->number[j].type == "[") parentheses2++;
                        if(token->number[j].type == "]") parentheses2--;
                        if((parentheses == 0) & (parentheses2 == 0) & (token->number[j].type == ",")) break;
                    }
                    if((parentheses != 0) & (parentheses2 == 0)){
                        printf("\nline %d !!!error:  parentheses not matched", token->number[i].line);
                    }
                    if(j < d_end) j--;

                    if(valuesss == 0){
                        value1 = calculate_float_expresion(token, syntax, i, j);
                    }else{
                        value2 = calculate_float_expresion(token, syntax, i, j);
                    }
                }
    value = pow(value1, value2);
return value;

}


///
bool verify_if_float_expresion(Token *token, Syntax *syntax, int d_start, int d_end){
    for(int j = d_start; j <= d_end; j++){
        if((token->number[j].type != "+") & (token->number[j].type != "trunc") & (token->number[j].type != "pow") & (token->number[j].type != " ") & (token->number[j].type != "[") & (token->number[j].type != "]") & (token->number[j].type != "(")  & (token->number[j].type != ")") & (token->number[j].type != "var_float") & (token->number[j].type != "var_int") & (token->number[j].type != "value_float") & (token->number[j].type != "value_int") & (token->number[j].type != "/") & (token->number[j].type != "-") & (token->number[j].type != "*")){
            if(token->number[j].type == "%") printf("\nline %d !!!error:  in int expressions you cant use %", token->number[j].line);
            return false;
        }
        if(token->number[j].type != "pow"){
            int i;
            int coma = 0;
                    int parentheses = 0;
                    int parentheses2 = 0;
                    for(i = j; i <= d_end; i++){
                        if(token->number[i].type == ",") coma++;
                        if(token->number[i].type == "(") parentheses++;
                        if(token->number[i].type == ")") parentheses--;
                        if(token->number[i].type == "[") parentheses2++;
                        if(token->number[i].type == "]") parentheses2--;
                        if((parentheses == 0) & (parentheses2 == 0) & ((token->number[i].type == "+")/* || (token->number[j].type == "^")*/ || (token->number[i].type == "-") || (token->number[i].type == "*") || (token->number[i].type == "/"))) break;
                    }
                    if((parentheses != 0) & (parentheses2 != 0)){
                        printf("\nline %d !!!error:  parentheses not matched", token->number[i].line);
                    }
                    if(i >= d_end){
                            for(i; i > j; i--){
                                if(token->number[i].type == ")") break;
                            }
                    }
                    j++;
                    i--;
                    if(verify_if_float_expresion){
                        i = j + 2;
                    }else{
                        printf("\nline %d !!!error:  power can process only float expressions", token->number[i].line);
                        return false;
                    }
                    if(coma != 1){
                        printf("\nline %d !!!error:  power is write with coma like that: pow(value1, value2)", token->number[i].line);
                        return false;
                    }

        }
    }
return true;
}


///
bool verify_if_int_expresion(Token *token, Syntax *syntax, int d_start, int d_end){
    for(int j = d_start; j <= d_end; j++){
        if((token->number[j].type != "+") & (token->number[j].type != "trunc") & (token->number[j].type != " ") & (token->number[j].type != "[") & (token->number[j].type != "]") & (token->number[j].type != "(")  & (token->number[j].type != ")") & (token->number[j].type != "var_int") & (token->number[j].type != "value_int") & (token->number[j].type != "%") & (token->number[j].type != "-") & (token->number[j].type != "*")){
        if(token->number[j].type == "/") printf("\nline %d !!!error:  in int expressions you cant use /", token->number[j].line);
            return false;
        }
        if(token->number[j].type == "trunc"){
            int i;
                    int parentheses = 0;
                    int parentheses2 = 0;
                    for(i = j; i <= d_end; i++){
                        if(token->number[i].type == "(") parentheses++;
                        if(token->number[i].type == ")") parentheses--;
                        if(token->number[i].type == "[") parentheses2++;
                        if(token->number[i].type == "]") parentheses2--;
                        if((parentheses == 0) & (parentheses2 == 0) & ((token->number[i].type == "+")/* || (token->number[j].type == "^")*/ || (token->number[i].type == "-") || (token->number[i].type == "*") || (token->number[i].type == "/"))) break;
                    }
                    if((parentheses != 0) & (parentheses2 != 0)){
                        printf("\nline %d !!!error:  parentheses not matched", token->number[i].line);
                    }
                    if(i >= d_end){
                            for(i; i > j; i--){
                                if(token->number[i].type == ")") break;
                            }
                    }
                    j++;
                    i--;
                    if(verify_if_float_expresion){
                        i = j + 2;
                    }else{
                        printf("\nline %d !!!error:  trunk can process only float expressions", token->number[i].line);
                        return false;
                    }
        }
    }
return true;
}




///
bool verify_if_bool_expresion(Token *token, Syntax *syntax, int d_start, int d_end){
    int j, i;
    int parentheses = 0;
    int parentheses2 = 0;
    int terms = 0;
    char type[6] = "NULL";

    for(j = d_start; j <= d_end; j++){
        if(token->number[j].content != syntax->d_ignore){

            if((token->number[j].type == "[") || (token->number[j].type == "]") || (token->number[j].type == "(")  || (token->number[j].type == ")")){
               for(i = j; i <= d_end; i++){
                            if(token->number[i].type == "(") parentheses++;
                            if(token->number[i].type == ")") parentheses--;
                            if(token->number[i].type == "[") parentheses2++;
                            if(token->number[i].type == "]") parentheses2--;
                            if((parentheses != 0) & (parentheses2 != 0) % ((token->number[j].type == "&") || (token->number[j].type == "<") || (token->number[j].type == ">") || (token->number[j].type == "=") || (token->number[j].type == "|"))) break;
                        }
                        if((parentheses != 0) & (parentheses2 != 0)){
                            printf("\nline %d !!!error:  parentheses not matched", token->number[j].line);
                        }else{
                                for(i; i > j; i--){
                                    if(token->number[i].type == ")") break;
                                    if(token->number[i].type == "]") break;
                                }

                                if(verify_if_bool_expresion(token, syntax, j++, i--)){
                                    strcpy(type, "bool");
                                    goto done;
                                }else if(verify_if_int_expresion(token, syntax, j++, i--)){
                                    strcpy(type, "int");
                                    goto done;
                                }else if(verify_if_float_expresion(token, syntax, j++, i--)){
                                    strcpy(type, "float");
                                    goto done;
                                }
                        }
                        done:
                        j = i + 2;
                        terms++;

            }

                if((token->number[j].type == "var_bool") || (token->number[j].type == "value_bool")){
                     terms++;
                }
                if((token->number[j].type == "var_int") || (token->number[j].type == "value_int")) {
                    terms++;
                }
                if((token->number[j].type == "var_float") || (token->number[j].type == "value_float")){
                    terms++;
                }

            if(token->number[j].type == "&"){
                terms--;
            }else if(token->number[j].type == "="){
                terms--;
            }else if(token->number[j].type == "!"){
                j++;
                if(token->number[j].type == "="){
                    terms--;
                }else{
                     printf("\nline %d !!!error:  it should be '!='(btw, no space betwen)", token->number[j].line);
                     return false;
                }
            }else if(token->number[j].type == "<"){
                j++;
                if(token->number[j].type == "="){
                    terms--;
                }else{
                    terms--;
                }
            }else if(token->number[j].type == ">"){
                j++;
                if(token->number[j].type == "="){
                    terms--;
                }else{
                    terms--;
                }
            }
        }
    }
    if(terms != 1) {printf("\nline %d !!!error:  probably you forgot something", token->number[j].line);return false;}
return true;
}
/*//
bool verify_if_bool_expresion(Token *token, Syntax *syntax, int d_start, int d_end){
    int j, i;
    int parentheses = 0;
    int parentheses2 = 0;
    int terms = 0;
    char type[] = "NULL";

    for(j = d_start; j <= d_end; j++){
        if(token->number[j].content != syntax->d_ignore){

            if((token->number[j].type == "[") || (token->number[j].type == "]") || (token->number[j].type == "(")  || (token->number[j].type == ")")){
               for(i = j; i <= d_end; i++){
                            if(token->number[i].type == "(") parentheses++;
                            if(token->number[i].type == ")") parentheses--;
                            if(token->number[i].type == "[") parentheses2++;
                            if(token->number[i].type == "]") parentheses2--;
                            if((parentheses != 0) & (parentheses2 != 0) % ((token->number[j].type == "&") || (token->number[j].type == "<") || (token->number[j].type == ">") || (token->number[j].type == "=") || (token->number[j].type == "|"))) break;
                        }
                        if((parentheses != 0) & (parentheses2 != 0)){
                            printf("\nline %d !!!error:  parentheses not matched", token->number[j].line);
                        }else{
                                for(i; i > j; i--){
                                    if(token->number[i].type == ")") break;
                                    if(token->number[i].type == "]") break;
                                }
                            if(type == "NULL"){
                                if(verify_if_bool_expresion(token, syntax, j++, i--)){
                                    strcpy(type, "bool");
                                    goto done;
                                }
                                if(verify_if_int_expresion(token, syntax, j++, i--)){
                                    strcpy(type, "int");
                                    goto done;
                                }
                                if(verify_if_float_expresion(token, syntax, j++, i--)){
                                    strcpy(type, "float");
                                    goto done;
                                }
                            }else{
                                if((type == "bool") & (verify_if_bool_expresion(token, syntax, j++, i--))) goto done;
                                if((type == "int") & (verify_if_int_expresion(token, syntax, j++, i--))) goto done;
                                if((type == "float") & (verify_if_float_expresion(token, syntax, j++, i--)))goto done;
                                printf("\nline %d !!!error:  you are trying to compare %s with something else", token->number[j].line, type);
                                return false;
                            }
                        }
                        done:
                        j = i + 2;
                        terms++;

            }

            if(type == "NULL"){
                if((type == "NULL") & ((token->number[j].type == "var_bool") || (token->number[j].type == "value_bool"))){
                        strcpy(type, "bool"); terms++;
                }
                if((type == "NULL") & ((token->number[j].type == "var_int") || (token->number[j].type == "value_int"))) {
                    strcpy(type, "int"); terms++;
                }
                if((type == "NULL") & ((token->number[j].type == "var_float") || (token->number[j].type == "value_float"))) {
                    strcpy(type, "float"); terms++;
                }
            }else if(terms == 0){
                if((type == "bool") & ((token->number[j].type == "var_bool") || (token->number[j].type == "value_bool"))) {terms++;}
                if((type == "int") & ((token->number[j].type == "var_int") || (token->number[j].type == "value_int"))) {terms++;}
                if((type == "float") & ((token->number[j].type == "var_float") || (token->number[j].type == "value_float"))) {terms++;}
            }

            if(token->number[j].type == "&"){
                terms--;
            }else if(token->number[j].type == "="){
                terms--;
            }else if(token->number[j].type == "!"){
                j++;
                if(token->number[j].type == "="){
                    terms--;
                }else{
                     printf("\nline %d !!!error:  it should be '!=' without space", token->number[j].line);
                     return false;
                }
            }else if(token->number[j].type == "<"){
                j++;
                if(token->number[j].type == "="){
                    terms--;
                }else{
                    terms--;
                }
            }else if(token->number[j].type == ">"){
                j++;
                if(token->number[j].type == "="){
                    terms--;
                }else{
                    terms--;
                }
            }
        }
    }
    if(terms != 1) {printf("\nline %d !!!error:  probably you forgot something or you put a random space", token->number[j].line);return false;}
return true;
}


*///
bool verify_if_char(Token *token, Syntax *syntax, int d_start, int d_end){
int comas = 0;
int chars = 0;
int i = d_start;
    for( i ; i <= d_end; i++){
        if(token->number[i].type == "\"") comas++;
        if((comas%2 == 1) & (token->number[i].type != "\"")) chars++;
    }
    if(comas%2 == 0){
        printf("\nline %d !!!error:  comas not matched", token->number[i].line);
        return false;
    }
    if(chars > 1){
        //printf("\nline %d !!!error:  string to char operator", token->number[i].line);
        return false;
    }
return true;
}


///
bool verify_if_string(Token *token, Syntax *syntax, int d_start, int d_end){
int comas = 0;
int i;
    for(i = d_start; i <= d_end; i++){
        if(token->number[i].type == "\"") comas++;
        //if((comas%2 == 1) & (token->number[i].type != "\"")) chars++;
    }
    if(comas%2 == 0){
        printf("\nline %d !!!error:  comas not matched", token->number[i].line);
        return false;
    }
return true;
}




///
void insert_int_in_var(Token *token, Syntax *syntax, int nr, int *value){
        for(int i = 0; i < nr; i++){
                if(token->number[i].type == "int"){
                   for(int j = i; j < nr; j++){
                        if(token->number[i].type != syntax->d_ignore){
                            if(token->number[i].type == "var_int"){
                                    if(token->number[i].content == token->number[nr].content){
                                        token->number[i].value_int = value;
                                        break;
                                    }
                            }
                        }
                   }
                }

        }
    printf("\n      !!!error:  %s first time used", token->number[nr].content);

}
///
int extract_int_from_var(Token *token, Syntax *syntax, int nr){

        for(int i = 0; i < nr; i++){
                if(token->number[i].type == "int"){
                   for(int j = i; j < nr; j++){
                        if(token->number[i].type != syntax->d_ignore){
                            if(token->number[i].type == "var_int"){
                                    if(token->number[i].content == token->number[nr].content){
                                        return *token->number[i].value_int;
                                        break;
                                    }
                            }
                        }
                   }
                }
        }
    printf("\n      !!!error:  %s first time used", token->number[nr].content);

return 0;
}



///
void insert_float_in_var(Token *token, Syntax *syntax, int nr, float *value){

        for(int i = 0; i < nr; i++){
                if(token->number[i].type == "float"){
                   for(int j = i; j < nr; j++){
                        if(token->number[i].type != syntax->d_ignore){
                            if(token->number[i].type == "var_float"){
                                    if(token->number[i].content == token->number[nr].content){
                                        token->number[i].value_float = value;
                                        break;
                                    }
                            }
                        }
                   }
                }

        }
    printf("\n      !!!error:  %s first time used", token->number[nr].content);

}
///
float extract_float_from_var(Token *token, Syntax *syntax, int nr){

        for(int i = 0; i < nr; i++){
                if(token->number[i].type == "float"){
                   for(int j = i; j < nr; j++){
                        if(token->number[i].type != syntax->d_ignore){
                            if(token->number[i].type == "var_float"){
                                    if(token->number[i].content == token->number[nr].content){
                                        return *token->number[i].value_float;
                                        break;
                                    }
                            }
                        }
                   }
                }
        }
    printf("\n      !!!error:  %s first time used", token->number[nr].content);

return 0;
}




///
bool extract_bool_from_var(Token *token, Syntax *syntax, int nr){



return true;
}



///
void insert_char_in_var(Token *token, Syntax *syntax, int nr, char *value){

        for(int i = 0; i < nr; i++){
                if(token->number[i].type == "char"){
                   for(int j = i; j < nr; j++){
                        if(token->number[i].type != syntax->d_ignore){
                            if(token->number[i].type == "var_char"){
                                    if(token->number[i].content == token->number[nr].content){
                                        token->number[i].value_char = value;
                                        break;
                                    }
                            }
                        }
                   }
                }

        }
    printf("\n      !!!error:  %s first time used", token->number[nr].content);



}
///
char extract_char_from_var(Token *token, Syntax *syntax, int nr){

        for(int i = 0; i < nr; i++){
                if(token->number[i].type == "char"){
                   for(int j = i; j < nr; j++){
                        if(token->number[i].type != syntax->d_ignore){
                            if(token->number[i].type == "var_char"){
                                    if(token->number[i].content == token->number[nr].content){
                                        return *token->number[i].value_char;
                                        break;
                                    }
                            }
                        }
                   }
                }

        }
    printf("\n      !!!error:  %s first time used", token->number[nr].content);

return '\0';
}




///
void insert_string_in_var(Token *token, Syntax *syntax, int nr, char value[]){

    size_t len = strlen(value);

            for(int i = 0; i < nr; i++){
                if(token->number[i].type == "char"){
                   for(int j = i; j < nr; j++){
                        if(token->number[i].type != syntax->d_ignore){
                            if(token->number[i].type == "var_char"){
                                    if(token->number[i].content == token->number[nr].content){
                                        if(*token->number[i].string_capacity >= len){
                                            token->number[i].value_char = value;
                                            break;
                                        }else{
                                            printf("\n      !!!error:  the string inserted is to big for %s", token->number[nr].content);
                                        }
                                    }
                            }
                        }
                   }
                }

        }
    printf("\n      !!!error:  %s first time used", token->number[nr].content);

}
///
char *extract_string_from_var(Token *token, Syntax *syntax, int nr){

            for(int i = 0; i < nr; i++){
                if(token->number[i].type == "char"){
                   for(int j = i; j < nr; j++){
                        if(token->number[i].type != syntax->d_ignore){
                            if(token->number[i].type == "var_char"){
                                    if(token->number[i].content == token->number[nr].content){
                                            return token->number[i].value_char;
                                            break;

                                    }
                            }
                        }
                   }
                }

        }
    printf("\n      !!!error:  %s first time used", token->number[nr].content);

}
///
void insert_one_char_string_in_var(Token *token, Syntax *syntax, int nr, char value, int where){

            for(int i = 0; i < nr; i++){
                if(token->number[i].type == "char"){
                   for(int j = i; j < nr; j++){
                        if(token->number[i].type != syntax->d_ignore){
                            if(token->number[i].type == "var_char"){
                                    if(token->number[i].content == token->number[nr].content){
                                        if(*token->number[i].string_capacity >= where){
                                            token->number[i].value_char[where] = value;
                                            break;
                                        }else{
                                            printf("\n      !!!error:  the char is placed out of %s", token->number[nr].content);
                                        }
                                    }
                            }
                        }
                   }
                }

        }
    printf("\n      !!!error:  %s first time used", token->number[nr].content);

}
///
char *extract_one_char_string_from_var(Token *token, Syntax *syntax, int nr, int where){

            for(int i = 0; i < nr; i++){
                if(token->number[i].type == "char"){
                   for(int j = i; j < nr; j++){
                        if(token->number[i].type != syntax->d_ignore){
                            if(token->number[i].type == "var_char"){
                                    if(token->number[i].content == token->number[nr].content){
                                            if(*token->number[i].string_capacity >= where){
                                            token->number[i].value_char[where];
                                            break;
                                        }else{
                                            printf("\n      !!!error:  the char is out of %s", token->number[nr].content);
                                        }

                                    }
                            }
                        }
                   }
                }

        }
    printf("\n      !!!error:  %s first time used", token->number[nr].content);

}






















