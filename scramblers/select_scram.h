/*	Scrambler Numbering	*/
/*	    0: lk_hash		*/
/*    1: dropbit random shift	*/
/*       2: random rotate	*/
/*      3: random xorshift	*/
/*      4: fixed xorshift	*/
/*      5: const multiplier	*/
/*      6: fixed dropshift	*/
/*        7: right shift	*/

#ifndef _select_scram_h_
#define _select_scram_h_

#include "scrambler.h"
#include "lk_hash.h"
#include "pcg_random_dropshift.h"
#include "pcg_random_rotate.h"
#include "pcg_random_xorshift.h"
#include "pcg_fixed_xorshift.h"
#include "constant_multiplier.h"
#include "fixed_dropshift.h"
#include "rightshift.h"

#include "scrambler_mixer.h"
scrambler_mixer* get_mixer();
scrambler* select_scrambler(int type);



#endif
