//
// Created by evanw on 11/2/2020.
//

#ifndef ASSEMBLER_PARSER_H
#define ASSEMBLER_PARSER_H
char* getInstruction(char* inst);
char* getRegister(char* reg);
char* getLabel(char* label);
char* getImmediate(char* imm, int bType);
char* getFsrc(char* reg);
#endif //ASSEMBLER_PARSER_H
