#include <stdio.h>
#include "pass1.h"
#include "pass2.h"
#include "pass3.h"
#include "pass4.h"

int main(int argc, char *argv[]) {
    char* file = argv[1];
    removeWhitespace(file);
    assignAddresses(file);
    addressLabels(file);
    removeLabels(file);
    assemble(file);
    return 0;
}



