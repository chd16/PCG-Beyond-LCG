/*         Gen Numbering           */
/*             0: LCG              */
/*             1: XOR              */
/*             2: MLFG             */
/*          3: LCG FCTRL           */
/*		4: MT		   */
#ifndef _select_gen_h_
#define _select_gen_h_


#include "generator.h"
#include "xor.h"
#include "lcg.h"
#include "mlfg.h"
#include "lcg_fctrl.h"
#include "MT.h"

generator* select_generator(int type);










#endif
