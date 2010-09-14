#include "lolevel.h"
#include "platform.h"
#include "core.h"

static long *nrflag = (long*)0x6DB0;    // ?!? ROM:FF970AA0 at taskcreate_ShutterSoundTask()

#include "../../../generic/capt_seq.c"

