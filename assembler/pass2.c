#include <stdio.h>
#include <string.h>

// Pass 2 assigns addresses to each line sequentially (skipping labels)
// Created by evanw on 10/24/2020.
//

int isALabel(char* buff){
    char intstructions[13][5] = {
            "ad",
            "su",
            "lo",
            "st",
            "lb",
            "br",
            "bl",
            "sl",
            "ls",
            "rs",
            "be",
            "bn",
            "or"
    };

    for(int i = 0; i < 13; i++){
        if(strcmp(intstructions[i], buff) == 0) {
            return 0;
        }
    }
    return 1;
}

int assignAddresses(char* fileName){
    FILE *fp, *tmp;
    fp = fopen(fileName, "r");
    tmp = fopen("tmp.txt", "w");
    char buff[255];
    int address = 0x0000;
    while(fgets(buff, 255, (FILE*)fp) != NULL){
        char num[255];
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
            sprintf(num, "%d", address);
            strcat(num, " ");
            strcat(num, buff);
            address += 2;
            fputs(num, tmp);
        } else{
            fputs(buff, tmp);
        }
    }
    if(feof(fp)){
        fclose(fp);
        fclose(tmp);
        return 0;
    }
    else{
        //find out what else to do
    }
    return 0;
}