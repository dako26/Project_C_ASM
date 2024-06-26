//
// Created by dako6 on 20/06/2024.
//

#ifndef PROJECT_C_ASM_INPUTVALIDATION_H
#define PROJECT_C_ASM_INPUTVALIDATION_H

#include "main.h"
typedef enum {LabelLine,
              DataLine,
              StringLine,
              InstructionLine,
              EntryLine,
              ExternLine,
              CommentLine,
              EmptyLine,
              ErrorLine
}lineType;

int checkLabel(char *line);
int checkData(char *line);
int checkString(char *line);
int checkInstruction(char *line);
int checkEntryAndExtern(char *line);
int checkComment(char *line);
int checkEmpty(char *line);
int checkCommandIfTwoOperands(char *line);
int checkCommandIfOneOperand(char *line);
int checkCommandIfZeroOperand(char *line);
int checkCommand(char *line);
int validateLine(char *line);

#endif //PROJECT_C_ASM_INPUTVALIDATION_H
