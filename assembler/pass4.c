//Pass 4 turns all of the instructions to assembly
// Created by evanw on 10/24/2020.
//
#include <stdio.h>
#include "pass2.h"
#include "parser.h"
#include <string.h>
int assemble(char* fileName){
    FILE *original, *final;
    original = fopen("new.txt", "r");
    final = fopen("final.txt", "w");
    char buff[255];
    while(fgets(buff, 255, (FILE*)original) != NULL){
        int i = 0;
        int tokenLength = 0;
        int bType = 0;
        int flipOrder = 0;
        int fsrc = 0;
        int secondRegister = 0;
        char* wordTmp = "";
        while(buff[i] != '\n'){
            if(buff[strlen(buff) - 4] == '*' || buff[strlen(buff) - 8] == '*'){
                fsrc = 1;
            }
            char token[255];
            if(buff[i] == ' '  || buff[i] == ',' || buff[i] == ')' || buff[i] == '(' || buff[i] == ':'){
                if(isALabel(token) == 0){
                    if(strcmp(token, "bl") == 0 || strcmp(token, "lb") == 0){
                        bType = 1;
                    } else{
                        bType = 0;
                    }
                    if(strcmp(token, "lo") == 0 || strcmp(token, "st") == 0){
                        flipOrder = 1;
                    } else {
                        flipOrder = 0;
                    }
                   fputs(getInstruction(token), final);
                }
                else if(token[0] == '*'){
                    if (flipOrder == 1){
                        wordTmp = getImmediate(token, bType);
                    } else {
                        fputs(getImmediate(token, bType), final);
                    }
                }
                else if((token[0] == 'R' && tokenLength <= 3) || (token[0] == 'A' && strlen(token) <= 3) || (strncmp("SP", token, 2) == 0 && tokenLength <= 3)){
                    if (buff[i-1] != ')'){
                        if(fsrc == 1 && secondRegister == 1){
                            if (flipOrder == 1){
                                fputs(getFsrc(token), final);
                                fputs(wordTmp, final);
                            } else{
                                fputs(getFsrc(token), final);
                            }
                        } else {
                            if (flipOrder == 1) {
                                fputs(getRegister(token), final);
                                fputs(wordTmp, final);
                            } else {
                                fputs(getRegister(token), final);
                            }
                        }
                        if(secondRegister == 0){
                            secondRegister = 1;
                        }
                    }
                }
                else{
                    fputs(getLabel(token), final);
                }
                tokenLength = 0;
                if(buff[i] == ','){
                    i++;
                }
            } else {
                if(buff[i] != '(') {
                    token[tokenLength] = buff[i];
                    tokenLength += 1;
                    token[tokenLength] = '\0';
                }
            }
            i++;
        }
        fputs("\n", final);
    }
    if(feof(original)){
        fclose(original);
        fclose(final);
        return 0;
    }
    else{
        // do nothing
    }
    return 0;
}