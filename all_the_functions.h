#include "second_part.h"
#include <ctype.h>


int *create_var_int();
float *create_var_float();
char *create_var_char();
char *create_var_string(size_t capacity);

bool verify_if_valid_var(Token *token,Syntax *syntax, int nr);
void print_this_pls(Token *token,Syntax *syntax, int d_start, int d_end);

bool verify_if_var_int(Token *token, int nr);
bool verify_if_var_float(Token *token, int nr);
bool verify_if_var_char(Token *token, int nr);
bool verify_if_var_string(Token *token, int nr);


bool verify_if_value_int(Token *token, int nr);
bool verify_if_value_float(Token *token, int nr);
bool verify_if_value_char(Token *token, int nr);
bool verify_if_value_string(Token *token, int nr);


char *verify_type_expresion(Token *token,Syntax *syntax, int d_start, int d_end);
char *verify_type_var(Token *token, int d_start, int d_end);


///
void print_all_tokens_details(Token *token){
    printf("\n nr = %d", token->nr);
    for(int i = 0; i < token->nr; i++){
     printf("\ntoken[%d] = %s",i ,token->number[i].content);
     printf("\ntoken_type[%d] = %s",i ,token->number[i].type);
     printf("\ntoken_line[%d] = %s",i ,token->number[i].line);
     printf("\ntoken_value_int[%d] = %s",i ,token->number[i].value_int);
     printf("\ntoken_value_float[%d] = %s",i ,token->number[i].value_float);
     printf("\ntoken_value_char[%d] = %s",i ,token->number[i].value_char);
     printf("\ntoken_value_string[%d] = %s",i ,token->number[i].value_string);
    }
}


///
void program(Token *token, Syntax *syntax, int d_begin, int d_end){

//print_all_tokens(token);
//printf("\ndddd %s and %zu", token->number[2].content, strlen(token->number[2].content));

    for(int i = d_begin; i <= d_end; i++){
printf(" %d", i);

        if(strcmp(token->number[i].content, syntax->d_integer) == 0){
                        token->number[i].type = "int";
                        i++;

                        if(strcmp(token->number[i].content, syntax->d_must_have_too) == 0){

                                bool verify = false;
                                i++;
                                int j = i;

                            for(j; j <= d_end; j++){

                                if(strcmp(token->number[j].content, syntax->d_end_of_something) == 0){
                                    if(verify){//printf("\ndddd");
                                        j--;
                                        break;
                                    }else{
                                        j--;
                                        printf("\nline %d !!!error:  invalid name operator", token->number[i].line);
                                        break;
                                    }
                                }

                                if(strcmp(token->number[j].content, syntax->d_ignore) != 0){
                                    if(verify_if_valid_var(token,syntax, j)){
                                        token->number[j].value_int = create_var_int();
                                        token->number[j].type = "var_int";
                                        verify = true;
                                    }else{
                                        printf("\nline %d !!!error:  invalid name operator", token->number[j].line);
                                    }

                                    //if(verify)
                                    //    printf("\nline %d !!!error:  invalid name operator", token->number[i].line);
                                    //
                                }

                            }
                            i = j;
                        }
            //printf("\ntoken[%d] = %s", 4, token->number[4].type);


        }else if(strcmp(token->number[i].content, syntax->d_float) == 0){
            token->number[i].type = "float";

                        i++;

                        if(strcmp(token->number[i].content, syntax->d_must_have_too) == 0){
                                bool verify = false;
                                i++;
                                int j = i;

                            for( j; j <= d_end; j++){

                                if(strcmp(token->number[j].content, syntax->d_end_of_something) == 0){
                                    if(verify){//printf("\ndddd");
                                        j--;
                                        break;
                                    }else{
                                        j--;
                                        printf("\nline %d !!!error:  invalid name operator", token->number[i].line);
                                        break;
                                    }
                                }

                                if(strcmp(token->number[j].content, syntax->d_ignore) != 0){
                                    if(verify_if_valid_var(token,syntax, j)){
                                        token->number[j].value_float = create_var_float();
                                        token->number[j].type = "var_float";
                                        verify = true;
                                    }else{
                                        printf("\nline %d !!!error:  invalid name operator", token->number[j].line);
                                    }

                                    //if(verify)
                                    //    printf("\nline %d !!!error:  invalid name operator", token->number[i].line);
                                    //
                                }

                            }
                            i = j;
                        }

                //printf("\ntoken[%d] = %s", 4, token->number[4].type);


        }else if(strcmp(token->number[i].content, syntax->d_char) == 0){
            token->number[i].type = "char";
                        i++;

                        if(token->number[i].content == syntax->d_must_have_too){
                                bool verify = false;
                                i++;
                                int j =i;

                            for( j; j <= d_end; j++){

                                if(token->number[j].content == syntax->d_end_of_something){
                                    if(verify){
                                        j--;
                                        break;
                                    }else{
                                        j--;
                                        printf("\nline %d !!!error:  invalid name operator", token->number[i].line);
                                        break;
                                    }
                                }

                                if(strcmp(token->number[j].content, syntax->d_ignore) != 0){
                                    if(verify_if_valid_var(token,syntax, i)){
                                        token->number[j].value_char = create_var_char();
                                        token->number[j].type = "var_char";
                                        verify = true;
                                    }else{
                                        printf("\nline %d !!!error:  invalid name operator", token->number[i].line);
                                    }

                                    //if(verify)
                                    //    printf("\nline %d !!!error:  invalid name operator", token->number[i].line);
                                    //
                                }

                            }
                            i = j;
                        }


        }else if(strcmp(token->number[i].content, syntax->d_string) == 0){
            token->number[i].type = "string";

                        i++;

                        if(strcmp(token->number[i].content, syntax->d_must_have_too) == 0){
                                bool verify = false;
                                i++;

                            for( i; i <= d_end; i++){

                                if(strcmp(token->number[i].content, syntax->d_end_of_something) == 0){
                                    if(verify){
                                        i--;
                                        break;
                                    }else{
                                        i--;
                                        printf("\nline %d !!!error:  invalid name operator", token->number[i].line);
                                        break;
                                    }
                                }

                                if(strcmp(token->number[i].content, syntax->d_ignore) != 0){
                                    if(verify_if_valid_var(token,syntax, i)){
                                            i++;
                                                int j;
                                                int parentheses = 0;
                                                int parentheses2 = 0;
                                                int ssstart = 0;
                                                int dddend = 0;
                                                for(j = i; j <= d_end; j++){
                                                    if(strcmp(token->number[j].content, "(") == 0) parentheses++;
                                                    if(strcmp(token->number[j].content, ")") == 0) parentheses--;
                                                    if(strcmp(token->number[j].content, "[") == 0) {
                                                            parentheses2++;
                                                            ssstart = j + 1;
                                                    }
                                                    if(strcmp(token->number[j].content, "]") == 0) {
                                                            parentheses2--;
                                                            dddend = j - 1;
                                                    }
                                                    if((parentheses == 0) & (parentheses2 == 0) & (strcmp(token->number[j].content, syntax->d_end_of_something) == 0)){
                                                            break;
                                                            j--;
                                                    }
                                                }

                                                if((parentheses != 0) & (parentheses2 != 0)){
                                                    printf("\nline %d !!!error:  parentheses not matched", token->number[i].line);
                                                }

                                                if(strcmp(verify_type_expresion(token,syntax, ssstart, dddend), "int_expresion") == 0){
                                                    token->number[i].string_capacity = calculate_int_expresion(token, syntax, i, j);;
                                                    i = j;
                                                    token->number[i].value_string = create_var_string(token->number[i].string_capacity);
                                                    token->number[i].type = "var_string";
                                                }else{
                                                    printf("\nline %d !!!error:  invalid string capacity", token->number[i].line);
                                                }

                                    }else{
                                        printf("\nline %d !!!error:  invalid name operator", token->number[i].line);
                                    }

                                    //if(verify)
                                    //    printf("\nline %d !!!error:  invalid name operator", token->number[i].line);
                                    //
                                }

                            }
                        }

        }else if(strcmp(token->number[i].content, syntax->d_while_begin) == 0){

                        i++;
                        if(strcmp(token->number[i].content, syntax->d_must_have_too) == 0){

                                                int j;
                                                int parentheses = 0;
                                                int parentheses2 = 0;
                                                int ssstart = 0;
                                                int dddend = 0;
                                                for(j = i; j <= d_end; j++){
                                                    if(strcmp(token->number[j].content, "[") == 0) parentheses2++;
                                                    if(strcmp(token->number[j].content, "]") == 0) parentheses2--;
                                                    if(strcmp(token->number[j].content, "(") == 0) {
                                                            parentheses++;
                                                            ssstart = j + 1;
                                                    }
                                                    if(strcmp(token->number[j].content, ")") == 0) {
                                                            parentheses--;
                                                            dddend = j - 1;
                                                    }
                                                    if((parentheses == 0) & (parentheses2 == 0) & ((strcmp(token->number[j].content, syntax->d_while_start) == 0) || (strcmp(token->number[j].content, syntax->d_end_of_something) == 0))){
                                                            break;
                                                            j--;
                                                    }
                                                }

                                                if((parentheses != 0) & (parentheses2 != 0)){
                                                    printf("\nline %d !!!error:  parentheses not matched", token->number[i].line);
                                                }

                                                if(verify_type_expresion(token,syntax, ssstart, dddend) == "bool_expresion"){

                                                                i = j + 2;
                                                                    if(strcmp(token->number[i].content, syntax->d_must_have_too) == 0){
                                                                                    for(j = i; j <= d_end; i++){
                                                                                            if(strcmp(token->number[j].content, syntax->d_ignore) != 0){
                                                                                                    if(strcmp(token->number[j].content, syntax->d_begin_of_program) == 0){
                                                                                                            j++;

                                                                                                                for(int n = j; n <= d_end; n++){
                                                                                                                        if(strcmp(token->number[n].content, syntax->d_end_of_program) == 0){
                                                                                                                            n--;
                                                                                                                            while (calculate_bool_expresion(token,syntax, ssstart, dddend)){
                                                                                                                                program(token, syntax, j, n);
                                                                                                                            }

                                                                                                                            j = n++;
                                                                                                                        }
                                                                                                                }


                                                                                                    }else{
                                                                                                            j++;

                                                                                                                for(int n = j; n <= d_end; n++){
                                                                                                                        if(strcmp(token->number[n].content, syntax->d_end_of_something) == 0){
                                                                                                                            n--;
                                                                                                                            while (calculate_bool_expresion(token, syntax, ssstart, dddend)){
                                                                                                                                program(token, syntax, j, n);
                                                                                                                            }
                                                                                                                            j = n;
                                                                                                                        }
                                                                                                                }
                                                                                                    }

                                                                                                        //if(verify)
                                                                                                        //    printf("\nline %d !!!error:  invalid name operator", token->number[i].line);
                                                                                                        //
                                                                                            }
                                                                                    }
                                                                                    i = j;
                                                                    }

                                                }else{
                                                    printf("\nline %d !!!error:  invalid while operation", token->number[i].line);
                                                }

                        }
        }else if(strcmp(token->number[i].content, syntax->d_if) == 0){
                        i++;
                        if(strcmp(token->number[i].content, syntax->d_must_have_too) == 0){

                                                int j;
                                                int parentheses = 0;
                                                int parentheses2 = 0;
                                                int ssstart = 0;
                                                int dddend = 0;
                                                bool verify = true;
                                                for(j = i; j <= d_end; j++){
                                                    if(strcmp(token->number[j].content, "[") == 0) parentheses2++;
                                                    if(strcmp(token->number[j].content, "]") == 0) parentheses2--;
                                                    if(strcmp(token->number[j].content, "(") == 0) {
                                                            parentheses++;
                                                            ssstart = j + 1;
                                                    }
                                                    if(strcmp(token->number[j].content, ")") == 0) {
                                                            parentheses--;
                                                            dddend = j - 1;

                                                    }
                                                    if((parentheses == 0) & (parentheses2 == 0) & ((strcmp(token->number[j].content, syntax->d_then) == 0) || (strcmp(token->number[j].content, syntax->d_end_of_something) == 0))){
                                                            break;
                                                            j--;
                                                    }
                                                }

                                                if((parentheses != 0) & (parentheses2 != 0)){
                                                    printf("\nline %d !!!error:  parentheses not matched", token->number[i].line);
                                                }

                                                if(verify_type_expresion(token,syntax, ssstart, dddend) == "bool_expresion"){

                                                                i = j + 2;
                                                                    if(strcmp(token->number[j].content, syntax->d_must_have_too) == 0){
                                                                                    for(j = i; j <= d_end; i++){
                                                                                            if(strcmp(token->number[j].content, syntax->d_ignore) != 0){
                                                                                                    if(verify){
                                                                                                            if(strcmp(token->number[j].content, syntax->d_begin_of_program) == 0){
                                                                                                                    j++;

                                                                                                                        for(int n = j; n <= d_end; n++){
                                                                                                                                if(strcmp(token->number[n].content, syntax->d_end_of_program) == 0){
                                                                                                                                    n--;
                                                                                                                                    if (calculate_bool_expresion(token,syntax, ssstart, dddend)){
                                                                                                                                        program(token, syntax, j, n);
                                                                                                                                    }else{
                                                                                                                                        verify = false;
                                                                                                                                    }


                                                                                                                                    j = n++;

                                                                                                                                }
                                                                                                                        }


                                                                                                            }else{
                                                                                                                    j++;

                                                                                                                        for(int n = j; n <= d_end; n++){
                                                                                                                                if((strcmp(token->number[n].content, syntax->d_end_of_something) == 0) || (strcmp(token->number[n].content, syntax->d_else) == 0)){
                                                                                                                                    n--;
                                                                                                                                    if (calculate_bool_expresion(token, syntax, ssstart, dddend)){
                                                                                                                                        program(token, syntax, j, n);
                                                                                                                                    }else{
                                                                                                                                        verify = false;
                                                                                                                                    }
                                                                                                                                    j = n;

                                                                                                                                }
                                                                                                                        }
                                                                                                            }
                                                                                                    }else{
                                                                                                            if(strcmp(token->number[j].content, syntax->d_else) == 0){
                                                                                                                    if(strcmp(token->number[j].content, syntax->d_begin_of_program) == 0){
                                                                                                                            j++;

                                                                                                                                for(int n = j; n <= d_end; n++){
                                                                                                                                        if(strcmp(token->number[n].content, syntax->d_end_of_program) == 0){
                                                                                                                                            n--;
                                                                                                                                            if (!(calculate_bool_expresion(token,syntax, ssstart, dddend))){
                                                                                                                                                program(token, syntax, j, n);
                                                                                                                                            }

                                                                                                                                            j = n++;

                                                                                                                                        }
                                                                                                                                }


                                                                                                                    }else{
                                                                                                                            j++;

                                                                                                                                for(int n = j; n <= d_end; n++){
                                                                                                                                        if(strcmp(token->number[n].content, syntax->d_end_of_something) == 0){
                                                                                                                                            n--;
                                                                                                                                            if (!(calculate_bool_expresion(token, syntax, ssstart, dddend))){
                                                                                                                                                program(token, syntax, j, n);
                                                                                                                                            }
                                                                                                                                            j = n;

                                                                                                                                        }
                                                                                                                                }
                                                                                                                    }
                                                                                                            }






                                                                                                    }




                                                                                                        //if(verify)
                                                                                                        //    printf("\nline %d !!!error:  invalid name operator", token->number[i].line);
                                                                                                        //
                                                                                            }
                                                                                    }
                                                                                    i = j;
                                                                    }

                                                }else{
                                                    printf("\nline %d !!!error:  invalid while operation", token->number[i].line);
                                                }

                        }






        }else if(strcmp(token->number[i].content, syntax->d_print) == 0){
                        int j = i++;
                                int ssstart = 0;
                                int dddend = 0;
                        for(j; j <= d_end; j++){
                            if(strcmp(token->number[j].content, syntax->d_ignore) != 0){

                                int parantheses = 0;
                                int comas1 = 0;
                                int comas2 = 0;
                                bool verify = false;


                                if((ssstart == 0) & (dddend == 0) & (comas2 == 0) & (comas1 == 0) & (strcmp(token->number[j].content, "(") == 0)) {
                                        ssstart = j + 1;
                                }
                                if((ssstart != 0) & (dddend == 0) & (comas2 == 0) & (comas1 == 0) & (strcmp(token->number[j].content, "\"") == 0)){
                                        comas1 = 1;
                                }
                                if((ssstart != 0) & (dddend == 0) & (strcmp(token->number[j].content, ")") == 0)) {
                                        dddend = j - 1;
                                }
                                if((verify || ((ssstart != 0) & (dddend == 0) & (comas2 == 0) & (comas1 != 0))) & (strcmp(token->number[j].content, "\"") == 0)){
                                        comas2 = 1;
                                }
                                if((ssstart != 0) & (dddend == 0) & (strcmp(token->number[j].content, ",") == 0)){
                                    comas1 = 0;
                                    comas2 = 0;
                                    j++;
                                    verify = true;
                                }
                                if(strcmp(token->number[j].content, syntax->d_end_of_something) == 0){
                                        if((ssstart != 0) & (dddend != 0)){
                                                break;
                                                j--;
                                        }else{
                                            printf("\nline %d !!!error:  invalid print output", token->number[i].line);
                                        }
                            }

                            }
                        }
                        printf("\n");
                        print_this_pls(token, syntax, ssstart, dddend);

        }else if(strcmp(token->number[i].content, syntax->d_end_of_something) == 0){
            //printf("\ndddd");

                        int j = i + 1;
                        for(j; j <= d_end; j++){
                            if((strcmp(token->number[j].content, syntax->d_end_of_something) != 0) & (strcmp(token->number[j].content, syntax->d_ignore) != 0)){
                            if(verify_if_valid_var(token, syntax, i)){
                                if(verify_if_var_int(token, j)){
                                            j++;
                                            int var = j - 1;
                                            for(j; j <= d_end; j++){
                                                if((strcmp(token->number[j].content, syntax->d_end_of_something) != 0) & (strcmp(token->number[j].content, syntax->d_ignore) != 0)){
                                                   if(strcmp(token->number[j].content, syntax->d_atribution) == 0){
                                                        j++;
                                                        for(int n = j; n <= d_end; n++){
                                                            if(strcmp(token->number[n].content, syntax->d_end_of_something) == 0){
                                                                    n--;
                                                                if(verify_type_expresion(token,syntax, j, n) == "int_expresion"){
                                                                    insert_int_in_var(token, syntax, var, calculate_int_expresion(token, syntax, j, n));
                                                                    i = n++;
                                                                }
                                                            }
                                                        }

                                                   }
                                                }
                                            }





                                }else if(verify_if_var_float(token, j)){

                                    j++;
                                            int var = j - 1;
                                            for(j; j <= d_end; j++){
                                                if((strcmp(token->number[j].content, syntax->d_end_of_something) != 0) & (strcmp(token->number[j].content, syntax->d_ignore) != 0)){
                                                   if(strcmp(token->number[j].content, syntax->d_atribution) == 0){
                                                        j++;
                                                        for(int n = j; n <= d_end; n++){
                                                            if(strcmp(token->number[n].content, syntax->d_end_of_something) == 0){
                                                                    n--;
                                                                if(verify_type_expresion(token,syntax, j, n) == "float_expresion"){

                                                                    insert_float_in_var(token, syntax, var, calculate_float_expresion(token, syntax, j, n));
                                                                    i = n++;
                                                                }
                                                            }
                                                        }

                                                   }
                                                }
                                            }

                                }else if(verify_if_var_char(token, j)){

                                    j++;
                                            int var = j - 1;
                                            for(j; j <= d_end; j++){
                                                if((strcmp(token->number[j].content, syntax->d_end_of_something) != 0) & (strcmp(token->number[j].content, syntax->d_ignore) != 0)){
                                                   if(token->number[j].content == syntax->d_atribution){
                                                        j++;
                                                        for(int n = j; n <= d_end; n++){
                                                            if(strcmp(token->number[n].content, syntax->d_end_of_something) == 0){
                                                                    n--;

                                                                if(verify_type_expresion(token,syntax, j, n) == "char_expresion"){
                                                                        char *something;
                                                                        int comas1 = 0;
                                                                        int comas2 = 0;
                                                                        bool verify = false;

                                                                    for(int v = n; v <=d_end; v++){
                                                                        if((comas2 == 0) & (comas1 == 0) & (strcmp(token->number[v].content, "\"") == 0)){
                                                                                comas1 = 1;
                                                                        }
                                                                        if((comas2 == 0) & (comas1 != 0) & (strcmp(token->number[v].content, "\"") != 0)){
                                                                                something = token->number[v].content;
                                                                        }
                                                                        if((comas2 == 0) & (comas1 != 0) & (strcmp(token->number[v].content, "\"") == 0)){
                                                                                comas2 = 1;
                                                                        }
                                                                        if((comas1 != 0) & (comas2 != 0) & (strcmp(token->number[v].content, syntax->d_end_of_something) == 0)){
                                                                                break;
                                                                                v--;
                                                                        }else{
                                                                            printf("\nline %d !!!error:  invalid character", token->number[i].line);
                                                                        }
                                                                    }

                                                                    insert_char_in_var(token, syntax, var, something[0]);
                                                                    i = n++;
                                                                }
                                                            }
                                                        }

                                                   }
                                                }
                                            }

                                }else if(verify_if_var_string(token, j)){

                                    j++;
                                    bool place = false;
                                    int where;
                                    bool if_char = false;

                                            int var = j - 1;
                                            for(j; j <= d_end; j++){
                                                if((strcmp(token->number[j].content, syntax->d_end_of_something) != 0) & (strcmp(token->number[j].content, syntax->d_end_of_something) != 0)){

                                                   if(strcmp(token->number[j].content, syntax->d_atribution) == 0){
                                                        j++;
                                                        for(int n = j; n <= d_end; n++){
                                                            if(strcmp(token->number[n].content, syntax->d_end_of_something) == 0){
                                                                    n--;

                                                                if(verify_type_expresion(token,syntax, j, n) == "string_expresion"){
                                                                        if(verify_type_expresion(token,syntax, j, n) == "char_expresion"){
                                                                            if_char = true;
                                                                        }

                                                                        size_t base_size = 100;
                                                                        char *something = (char *)malloc(base_size * sizeof(char));
                                                                        if (something == NULL) {
                                                                            printf("Memory allocation failed.\n");

                                                                        }

                                                                        size_t tsize = 0;
                                                                        char ch;

                                                                        int comas1 = 0;
                                                                        int comas2 = 0;
                                                                        bool verify = false;

                                                                    for(int v = n; v <=d_end; v++){
                                                                        if((comas2 == 0) & (comas1 == 0) & (strcmp(token->number[v].content, "\"") == 0)){
                                                                                comas1 = 1;
                                                                        }
                                                                        if((comas2 == 0) & (comas1 != 0) & (strcmp(token->number[v].content, "\"") != 0)){


                                                                                        //something[tsize] = ch;


                                                                                        if (token->number[v].capacity >= base_size - tsize - 1) {
                                                                                            base_size = base_size + 100 + token->number[v].capacity;
                                                                                            char *new_buffer = (char *)realloc(something, base_size * sizeof(char));

                                                                                            if (new_buffer == NULL) {
                                                                                                printf("Memory reallocation failed.\n");
                                                                                                free(something);

                                                                                            }

                                                                                            something = new_buffer;
                                                                                        }
                                                                                        tsize = tsize + token->number[v].capacity;
                                                                                        strcat(something, token->number[v].content);

                                                                        }
                                                                        if((comas2 == 0) & (comas1 != 0) & (token->number[v].content == "\"")){
                                                                                comas2 = 1;
                                                                        }
                                                                        if((comas1 != 0) & (comas2 != 0) & (token->number[v].content == syntax->d_end_of_something)){
                                                                                something[tsize] = '\0';
                                                                                break;
                                                                                v--;
                                                                        }else{
                                                                            printf("\nline %d !!!error:  invalid string", token->number[i].line);
                                                                        }
                                                                    }
                                                                    if(place){
                                                                            if(if_char){
                                                                                insert_one_char_string_in_var(token, syntax, var, something[0],where);
                                                                                i = n++;
                                                                            }else{
                                                                                printf("\nline %d !!!error:  invalid character", token->number[i].line);
                                                                            }


                                                                    }else{
                                                                        insert_string_in_var(token, syntax, var, something);
                                                                        i = n++;
                                                                    }

                                                                }
                                                            }
                                                        }

                                                   }else if(strcmp(token->number[j].content, "[") == 0){

                                                            j--;
                                                            int parantheses = 0;
                                                            bool verify = false;
                                                            int ssstart;
                                                            int dddend;

                                                        for(j; j < d_end; j++){
                                                            if(strcmp(token->number[j].content, "[") == 0) {
                                                                    parantheses++;
                                                                    ssstart = j + 1;
                                                            }
                                                            if((strcmp(token->number[j].content, "]") == 0)) {
                                                                    parantheses--;
                                                                    ssstart = j - 1;
                                                            }
                                                            if(strcmp(token->number[j].content, syntax->d_atribution) == 0){
                                                                    if(parantheses == 0){
                                                                        if(verify_if_int_expresion(token, syntax, ssstart, dddend)){
                                                                            where = calculate_int_expresion(token, syntax, ssstart, dddend);
                                                                        }else{
                                                                            printf("\nline %d !!!error:  between parentheses should be integervalue", token->number[i].line);
                                                                        }
                                                                        place = true;
                                                                        break;
                                                                        j--;
                                                                    }else{
                                                                        printf("\nline %d !!!error:  parentheses not matched", token->number[i].line);
                                                                    }
                                                            }
                                                        }



                                                   }
                                                }
                                            }

                                }
                            }
                            }
                        }

        }







    }


//printf("\ndddd");
print_all_tokens_details(token);
//printf("\ntoken[%d] = %s", 4, token->number[4].type);

}



///
int *create_var_int(){
    int *buffer = (int*) malloc(sizeof(int));
    if (buffer == NULL) printf("\n      error: Failed memory alocation");
    return buffer;
 }
///
float *create_var_float(){
    float *buffer = (float*) malloc(sizeof(float));
    if (buffer == NULL) printf("\n      error: Failed memory alocation");
    return buffer;
}
///
char *create_var_char(){
    char *buffer = (char*) malloc(sizeof(char));
    if (buffer == NULL) printf("\n      error: Failed memory alocation");
    return buffer;
}
///
char *create_var_string(size_t capacity){
    char *buffer = (char*) malloc(capacity * sizeof(char));
    if (buffer == NULL) printf("\n      error: Failed memory alocation");
    return buffer;
}
///



///
bool verify_if_valid_var(Token *token,Syntax *syntax, int nr){

    char *endend = syntax->d_end_of_program;
    strcat(endend, syntax->d_end_of_end);

    if((strcmp(token->number[nr].content, syntax->d_atribution) != 0)& (strcmp(token->number[nr].content, endend) != 0) & (strcmp(token->number[nr].content, syntax->d_while_start) != 0) & (strcmp(token->number[nr].content, syntax->d_while_begin) != 0) & (strcmp(token->number[nr].content, syntax->d_trunc) != 0) & (strcmp(token->number[nr].content, syntax->d_then) != 0) & (strcmp(token->number[nr].content, syntax->d_string) != 0) & (strcmp(token->number[nr].content, syntax->d_print) != 0) & (strcmp(token->number[nr].content, syntax->d_power) != 0) & (strcmp(token->number[nr].content, syntax->d_integer) != 0) & (strcmp(token->number[nr].content, syntax->d_if) != 0) & (strcmp(token->number[nr].content, syntax->d_float) != 0) & (strcmp(token->number[nr].content, syntax->d_end_of_program) != 0) & (strcmp(token->number[nr].content, syntax->d_end_of_end) != 0) & (strcmp(token->number[nr].content, syntax->d_else) != 0) & (strcmp(token->number[nr].content, syntax->d_char) != 0) & (strcmp(token->number[nr].content, syntax->d_begin_of_program) != 0)){
        if((strcmp(token->number[nr].content, "<") != 0) & (strcmp(token->number[nr].content, ">") != 0) & (strcmp(token->number[nr].content, "!") != 0) & (strcmp(token->number[nr].content, "?") != 0) & (strcmp(token->number[nr].content, ",") != 0) & (strcmp(token->number[nr].content, "|") != 0) & (strcmp(token->number[nr].content, "@") != 0) & (strcmp(token->number[nr].content, "#") != 0) & (strcmp(token->number[nr].content, "$") != 0) & (strcmp(token->number[nr].content, "%") != 0) & (strcmp(token->number[nr].content, "^") != 0) & (strcmp(token->number[nr].content, "*") != 0) & (strcmp(token->number[nr].content, "(") != 0) & (strcmp(token->number[nr].content, ")") != 0) & (strcmp(token->number[nr].content, "_") != 0) & (strcmp(token->number[nr].content, "-") != 0) & (strcmp(token->number[nr].content, "=") != 0) & (strcmp(token->number[nr].content, "+") != 0)){
            if((strcmp(token->number[nr].content, "[") != 0) & (strcmp(token->number[nr].content, "]") != 0) & (strcmp(token->number[nr].content, "{") != 0) & (strcmp(token->number[nr].content, "}") != 0) & (strcmp(token->number[nr].content, ";") != 0) & (strcmp(token->number[nr].content, ":") != 0) & (strcmp(token->number[nr].content, "'") != 0) & (strcmp(token->number[nr].content, "\"") != 0) & (strcmp(token->number[nr].content, "\\") != 0) & (strcmp(token->number[nr].content, ",") != 0) & (strcmp(token->number[nr].content, "/") != 0)){
                if(((token->number[nr].content[0] >= 'a') & (token->number[nr].content[0] <= 'z')) || ((token->number[nr].content[0] >= 'A') & (token->number[nr].content[0] <= 'Z'))){
                    //printf("\ndddd");
                    return true;
                }
            }
        }
    }
//
return false;
}
///
void print_this_pls(Token *token, Syntax *syntax, int d_start, int d_end){

    int i = d_start;
    int until;

    for(until = d_start; until <= d_end; until++){
        if((strcmp(token->number[i].content, "\"") == 0) || (strcmp(token->number[i].content, ",") == 0)){
            until--;
            break;
        }
    }


    for( i; i <= d_end; i++){
        if(strcmp(token->number[i].content, syntax->d_ignore) != 0){

            if(strcmp(token->number[i].content, "\"") == 0){

                    size_t base_size = 100;
                    char *something = (char *)malloc(base_size * sizeof(char));
                    if (something == NULL) {
                        printf("Memory allocation failed.\n");

                    }

                    size_t tsize = 0;
                    char ch;

                    int comas1 = 0;
                    int comas2 = 0;

                for(int j = i; j <= d_end; j++){

                                int comas1 = 0;
                                int comas2 = 0;
                                bool verify = false;

                                if((comas2 == 0) & (comas1 == 0) & (strcmp(token->number[j].content, "\"") == 0)){
                                        comas1 = 1;
                                }
                                if((comas2 == 0) & (comas1 != 0) & (strcmp(token->number[j].content, "\"") != 0)){



                                    if (token->number[j].capacity >= base_size - tsize - 1) {
                                        base_size = base_size + 100 + token->number[j].capacity;
                                        char *new_buffer = (char *)realloc(something, base_size * sizeof(char));

                                        if (new_buffer == NULL) {
                                            printf("Memory reallocation failed.\n");
                                            free(something);

                                        }

                                        something = new_buffer;
                                    }
                                    tsize = tsize + token->number[j].capacity;
                                    strcat(something, token->number[j].content);

                                }



                                if((comas2 == 0) & (comas1 != 0) & (strcmp(token->number[j].content, "\"") == 0)){
                                        comas2 = 1;
                                }
                                if((comas2 != 0) & (comas1 != 0) & (strcmp(token->number[j].content, ",") == 0)){
                                    comas1 = 0;
                                    comas2 = 0;
                                    i = j--;
                                }
                }
                printf("%s",something);

            }else if(strcmp(token->number[i].content, ",") == 0){
                i++;
                print_this_pls(token, syntax, i, d_end);
            }else if(verify_type_expresion(token,syntax, i, until) == "int_expresion"){
                printf("\ndddd");
                printf("%d", calculate_int_expresion(token, syntax, i, until));
                i = until;

            }else if(verify_type_expresion(token,syntax, i, until) == "float_expresion"){
                printf("%d", calculate_float_expresion(token, syntax, i, until));
                i = until;

            }else if(verify_type_expresion(token,syntax, i, until) == "bool_expresion"){
                printf("%d", calculate_bool_expresion(token, syntax, i, until));
                i = until;

            }else if(verify_if_valid_var(token, syntax, i)){
                if(verify_if_var_char(token, i)){
                    printf("%c", extract_char_from_var(token, syntax, i));

                }else if(verify_if_var_string(token, i)){
                    printf("%s", extract_string_from_var(token, syntax, i));

                }
            }

        }
    }




}



///
bool verify_if_var_int(Token *token, int nr){
//printf("\ndddd");
        for(int i = 0; i <= nr; i++){
                if(strcmp(token->number[i].type, "int") == 0){
                   for(int j = i; j <= nr; j++){
                            if(strcmp(token->number[i].type, "var_int") == 0){
                                    if(token->number[i].content == token->number[nr].content){
                                        printf("\ndddd");
                                        return true;
                                    }
                            }
                   }
                }
        }
return false;
}
///
bool verify_if_var_float(Token *token, int nr){

    for(int i = 0; i <= nr; i++){
                if(token->number[i].type == "float"){
                   for(int j = i; j <= nr; j++){

                            if(token->number[i].type == "var_float"){
                                    if(token->number[i].content == token->number[nr].content){
                                        return true;
                                        break;
                                    }
                            }

                   }
                }
        }
return false;
}
///
bool verify_if_var_char(Token *token, int nr){
    for(int i = 0; i <= nr; i++){
                if(token->number[i].type == "char"){
                   for(int j = i; j <= nr; j++){

                            if(token->number[i].type == "var_char"){
                                    if(token->number[i].content == token->number[nr].content){
                                        return true;
                                        break;
                                    }
                            }
                        }

                }
        }
return false;
}
///
bool verify_if_var_string(Token *token, int nr){

    for(int i = 0; i <= nr; i++){
                if(token->number[i].type == "string"){
                   for(int j = i; j < nr; j++){

                            if(token->number[i].type == "var_string"){
                                    if(token->number[i].content == token->number[nr].content){
                                        return true;
                                        break;
                                    }
                            }

                   }
                }
        }
return false;
}





///
bool verify_if_value_int(Token *token, int nr){
    if (token->number[nr].content == NULL || *token->number[nr].content == '\0') {
        return false;
    }
    int i;
    while (token->number[nr].content[i] != '\0') {
        if (!isdigit(token->number[nr].content[i]) && token->number[nr].content[i] != '-' && token->number[nr].content[i] != '+') {
            return false;
        }
        i++;
    }
    return true;
}
///
bool verify_if_value_float(Token *token, int nr){
    int len;
    float floatu = 0.0;
    if (sscanf(token->number[nr].content, "%f %len", &floatu, &len) == 1 && len == (int)strlen(token->number[nr].content))
        return true;
    else return false;
}
///
bool verify_if_value_char(Token *token, int nr){
    if(strlen(token->number[nr].content) == 1 ) return true;
    else return false;
}
///
bool verify_if_value_string(Token *token, int nr){
}



///
char *verify_type_expresion(Token *token,Syntax *syntax, int d_start, int d_end){


    char *int_expresion = "int_expresion";
    char *float_expresion = "float_expresion";
    char *bool_expresion = "bool_expresion";
    char *char_expresion = "char";
    char *string_expresion = "string";

    char *var_int = "var_int";
    char *var_float = "var_float";
    char *var_char = "var_char";
    char *var_string = "var_string";

    char *value_int = "value_int";
    char *value_float = "value_float";
    char *value_char = "value_char";
    char *value_string = "value_string";

    for(int i = d_start; i <= d_end; i++){

        if(strcmp(token->number[i].content, "+") == 0){
            token->number[i].type = "+";

        }else if(strcmp(token->number[i].content, "-") == 0){
            token->number[i].type = "-";

        }else if(strcmp(token->number[i].content, "*") == 0){
            token->number[i].type = "*";

        }else if(strcmp(token->number[i].content, "\"") == 0){
            token->number[i].type = "\"";

        }else if(strcmp(token->number[i].content, "%") == 0){
            token->number[i].type = "%";

        }else if(strcmp(token->number[i].content, "!") == 0){
            token->number[i].type = "!";

        }else if(strcmp(token->number[i].content, "&") == 0){
            token->number[i].type = "&";

        }else if(strcmp(token->number[i].content, "(") == 0){
            token->number[i].type = "(";

        }else if(strcmp(token->number[i].content, ")") == 0){
            token->number[i].type = ")";

        }else if(strcmp(token->number[i].content, "=") == 0){
            token->number[i].type = "=";

        }else if(strcmp(token->number[i].content, "[") == 0){
            token->number[i].type = "[";

        }else if(strcmp(token->number[i].content, "]") == 0){
            token->number[i].type = "]";

        }else if(strcmp(token->number[i].content, "|") == 0){
            token->number[i].type = "|";

        }else if(strcmp(token->number[i].content, "<") == 0){
            token->number[i].type = "<";

        }else if(strcmp(token->number[i].content, ">") == 0){
            token->number[i].type = ">";

        }else if(strcmp(token->number[i].content, "\\") == 0){
            token->number[i].type = "\\";

        }else if(verify_if_valid_var(token, syntax, i)){

                char *type = verify_type_var(token, i, d_end);

                if(strcmp(type, var_int) == 0){
                    token->number[i].type = var_int;

                }else if(strcmp(type, var_float) == 0){
                    token->number[i].type = var_float;

                }else if(strcmp(type, var_char) == 0){
                    token->number[i].type = var_char;

                }else if(strcmp(type, var_string) == 0){
                    token->number[i].type = var_string;

                }

        }else if(strcmp(token->number[i].content, syntax->d_power) == 0){
            token->number[i].type = syntax->d_power;

        }else if(strcmp(token->number[i].content, syntax->d_trunc) == 0){
            token->number[i].type = syntax->d_trunc;

        }else if(verify_if_value_int(token, i)){
            token->number[i].type = value_int;

        }else if(verify_if_value_float(token, i)){
            token->number[i].type = value_float;

        }else if(verify_if_var_char){
            token->number[i].type = value_char;
        }else{
            token->number[i].type = value_string;
        }



    }printf("\nnnnnn");


    if(verify_if_int_expresion(token, syntax, d_start, d_end)){
        return int_expresion;
    }else if(verify_if_float_expresion(token, syntax, d_start, d_end)){
        return float_expresion;
    }else if(verify_if_bool_expresion(token, syntax, d_start, d_end)){
        return bool_expresion;
    }else if(verify_if_char(token, syntax, d_start, d_end)){
        return char_expresion;
    }else if(verify_if_string(token, syntax, d_start, d_end)){
        return string_expresion;
    }
}
///
char *verify_type_var(Token *token, int d_start, int d_end){

    for(int i = d_start; i <= d_end ; i++){
                if(token->number[i].type == "int"){
                   for(int j = i; j < d_end; j++){
                            if(token->number[j].type == "var_int"){
                                    if(token->number[j].content == token->number[d_end].content){
                                        return "var_int";
                                    }
                            }
                   }
                }else if(token->number[i].type == "float"){
                   for(int j = i; j < d_end; j++){
                            if(token->number[j].type == "var_float"){
                                    if(token->number[j].content == token->number[d_end].content){
                                        return "var_float";
                                    }
                            }
                   }
                }else if(token->number[i].type == "char"){
                   for(int j = i; j < d_end; j++){
                            if(token->number[j].type == "var_char"){
                                    if(token->number[j].content == token->number[d_end].content){
                                        return "var_char";
                                    }
                            }
                   }
                }else if(token->number[i].type == "string"){
                   for(int j = i; j < d_end; j++){
                            if(token->number[j].type == "var_string"){
                                    if(token->number[j].content == token->number[d_end].content){
                                        return "var_string";
                                    }
                            }
                   }
                }
        }

}


































































