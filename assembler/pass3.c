//Pass 3 is technically 2 passes. First, it maps labels to addresses. Then, it goes through and removes labels from the code
// Created by evanw on 10/24/2020.
//

#include <stdio.h>
#include "pass2.h"
#include <stdlib.h>
#include <string.h>

int addressLabels(char* fileName){
    FILE *original, *labelMap, *tmp;
    original = fopen(fileName, "r");
    tmp = fopen("tmp.txt", "r");
    labelMap = fopen("labelmap.txt", "w");
    char buff[255];
    char buff2[255];
    int last = 0;
    int tmpAddress = 0;
    while(fgets(buff, 255, (FILE*)original) != NULL){
        fgets(buff2, 255, (FILE*)tmp);
        int address = atoi(buff2);
        if(address != 0){
            last = address;
        }
        char inst[255];
        int i = 0;
        while(buff[i] != ' '){
            if(buff[i] == '\n'){
                break;
            }
            inst[i] = buff[i];
            i++;
        }
        inst[i] = '\0';
        char mapString[255];
        char pcRelLabel[255];
        if(strcmp(inst, "bl") == 0){
            tmpAddress = address + 2;
            i++;
            int j = 0;
            while(buff[i] != ' '){
                if(buff[i] == '\n'){
                    break;
                }
                pcRelLabel[j] = buff[i];
                i++;
                j++;
            }
            pcRelLabel[j] = ':';
            pcRelLabel[j+1] = '\0';
        }
        if(isALabel(inst) == 1){
            address = last + 2;
            int placeholder = address;
            if(strcmp(inst, pcRelLabel) == 0){
                address = (address - tmpAddress) / 2;
            }
            int buffLen = strlen(buff);
            buff[buffLen-2] = '\0';
            strcpy(mapString, buff);
            strcat(mapString, " ");
            sprintf(mapString + strlen(mapString), "%d\n", address);
            fputs(mapString, labelMap);
            address = placeholder;
        }
    }
    if(feof(original)){
        fclose(original);
        fclose(tmp);
        fclose(labelMap);
        return 0;
    }
    else{
        // do nothing
    }
    return 0;
}

int removeLabels(char* fileName){
    FILE *original, *new;
    original = fopen(fileName, "r");
    new = fopen("new.txt", "w");
    char buff[255];;
    while(fgets(buff, 255, (FILE*)original) != NULL){
        char inst[255];
        int i = 0;
        while(buff[i] != ' '){
            if(buff[i] == '\n'){
                break;
            }
            inst[i] = buff[i];
            i++;
        }
        inst[i] = '\0';
        if(isALabel(inst) == 0){
            int buffLen = strlen(buff);
            buff[buffLen - 1] = ' ';
            buff[buffLen] = '\n';
            buff[buffLen + 1] = '\0';
            fputs(buff, new);
        }
    }
    if(feof(original)){
        fclose(original);
        fclose(new);
        remove("tmp.txt");
        return 0;
    }
    else{
        // do nothing
    }
    return 0;
}