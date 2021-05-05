#pragma once

#define BUFFER_SIZE 1024
#define DEF_PORT 2410

#define EXIT_COM "EXIT"

enum codes { LGN_CD = 101, SU_CD, ERR_CD, SO_CD, GR_CD, GPR_CD, GPS_CD, GHS_CD, JR_CD, CR_CD, FAIL = 255 };

enum errors { EXSTS = 55, DSNT_EXST, LGD_IN, WRNG_PSWRD, DSRL, SRL };

typedef unsigned char Byte;
