//
// Created by evanw on 11/2/2020.
// each function should return the number corresponding to the binary which needs to be written to the final file
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct {
    char *inst;
    char *binary;
}
        instMap[] = {
        {"ad", "0000"},
        {"su", "0001"},
        {"lo", "0010"},
        {"st", "0011"},
        {"lb", "0100"},
        {"br", "010100000000"},
        {"bl", "01100000"},
        {"sl", "0111"},
        {"ls", "1000"},
        {"rs", "1001"},
        {"be", "1010"},
        {"bn", "1011"},
        {"or", "1100"}
};

struct {
    char *reg;
    char *binary;
}
        regMap[] = {
        {"R6", "0110"},
        {"R7", "0111"},
        {"R8", "1000"},
        {"R9", "1001"},
        {"R10","1010"},
        {"R11","1011"},
        {"R12","1100"},
        {"R13","1101"},
        {"R14","1110"},
        {"R15","1111"},
        {"A1", "0011"},
        {"A2", "0100"},
        {"A3", "0101"},
        {"SP", "0010"},
        {"RA", "0001"},
        {"R0", "0000"},

};

struct {
    char *reg;
    char *binary;
}
        fsrcMap[] = {
        {"R6", "1101"},
        {"R7", "1111"},
        {"A1", "1011"},
        {"A2", "1001"},
        {"A3", "0111"},
        {"SP", "0101"},
        {"RA", "0011"},
        {"R0", "0001"},

};


char* getFsrc(char* reg){
    for (int i = 0; fsrcMap[i].reg != NULL; i++){
        if (strcmp(fsrcMap[i].reg, reg) == 0){
            return fsrcMap[i].binary;
        }
    }
}

char* getInstruction(char* inst){
    for (int i = 0; instMap[i].inst != NULL; i++){
        if (strcmp(instMap[i].inst, inst) == 0){
            return instMap[i].binary;
        }
    }
    return "XXXX";
}

char* getRegister(char* reg){
    for(int i = 0; regMap[i].reg != NULL; i++){
        if(strcmp(regMap[i].reg, reg) == 0){
            return regMap[i].binary;
        }
    }
    return "XXXX";
}

char* immToBinary(char* immInput, int bType){
    char imm[255];
    if(immInput[0] == '*'){
        int j = 0;
        for(int i = 1; i < strlen(imm); i++){
            imm[j] = immInput[i];
            j++;
        }
    } else{
        int j = 0;
        for(int i = 0; i < strlen(imm); i++){
            imm[j] = immInput[i];
            j++;
        }
    }
    int immediate = atoi(imm);
    char binaryNumber[255];
    char binaryTmp[255];
    int i = 0;
    char result[2];
    while(immediate > 0){
        sprintf(result, "%d", immediate % 2);
        binaryTmp[i] = result[0];
        immediate = immediate / 2;
        i++;
    }
    int k = 0;
    for (int j = i -1; j >= 0; j--){
        binaryNumber[k] = binaryTmp[j];
        k++;
    }
    binaryNumber[k] = '\0';
    if(strlen(binaryNumber) < 8){
        strcpy(binaryTmp, binaryNumber);
        int i = 0;
        int difference = 0;
        if(bType == 1){
            difference = 8 - strlen(binaryNumber);
        } else{
            difference = 4 - strlen(binaryNumber);
        }
        while (i < difference){
            binaryNumber[i] = '0';
            i++;
        }
        binaryNumber[difference] = '\0';
        strcpy(binaryNumber + strlen(binaryNumber), binaryTmp);
    }
    if(strlen(binaryNumber) > 8){

    }
    char* binaryNum;
    binaryNum = binaryNumber;
    return binaryNum;
}

char* getImmediate(char* imm, int bType){
    return immToBinary(imm, bType);
}

char* getLabel(char* inputLabel){
    FILE *labelMap;
    labelMap = fopen("labelmap.txt", "r");
    char buff[255];
    while(fgets(buff, 255, (FILE*)labelMap) != NULL){
        int i = 0;
        char label[255];
        while(buff[i] != ' '){
            if(buff[i] == '\n'){
                break;
            }
            label[i] = buff[i];
            i++;
        }
        label[i] = '\0';
        i++;
        if(strcmp(label, inputLabel) == 0){
            char imm[255];
            int j = 0;
            while(buff[i] != ' '){
                if(buff[i] == '\n'){
                    break;
                }
                imm[j] = buff[i];
                j++;
                i++;
            }
            imm[j] = '\0';
            char* number = immToBinary(imm, 1);
            return number;
        }
    }
    if(feof(labelMap)){
        fclose(labelMap);
        return "XXXX eof";
        // also do nothing
    }
    else{
        // do nothing
    }
    return "XXXX last";
}