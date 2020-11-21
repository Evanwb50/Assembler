#include <stdio.h>

// Pass 1 goes through file and removes comments/whitespace
// Created by evanw on 10/24/2020.
//

int removeWhitespace(char* fileName){
    FILE *original, *new;
    original = fopen(fileName, "r");
    new = fopen("modified.txt", "w");
    char buff[255];
    while(fgets(buff, 255, (FILE*)original) != NULL){
        if(buff[0] == '/' && buff [1] == '/'){
            // do nothing
        }
        else{
            fputs(buff, new);
        }

    }
    if(feof(original)){
        fclose(original);
        fclose(new);
        remove(fileName);
        rename("modified.txt", fileName);
        remove("modified.txt");
        return 0;
    }
    else{
        // do nothing
    }
    return 0;
}