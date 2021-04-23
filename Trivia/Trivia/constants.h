#pragma once

#define BUFFER_SIZE 1024
#define DEF_PORT 2410

#define EXIT_COM "EXIT"

enum codes { LGN_CD = 101, SU_CD, ERR_CD, FAIL = 255 };

enum errors { EXSTS = 55, DSNT_EXST, LGD_IN, WRNG_PSWRD, DSRL, SRL };

typedef unsigned char Byte;
