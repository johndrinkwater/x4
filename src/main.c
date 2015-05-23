#include <stdio.h>
#include <time.h>
#include <unistd.h>

#include "init.h"
#include "engine.h"
#include "log.h"
#include "timers.h"
#include "config.h"
#include "version.h"

int main(int argc, char* argv[])
{
    int fork = 0; /* We'll default this back to 1 later in development. */

    log_stdout("core/main", 1, "Starting X4 %s+[%s]", version, cvs_version);
    log_stdout("core/main", 1, "forking");

    engine_init(MAXCONNECTIONS);

    init(&fork);

    if (engine_init(MAXCONNECTIONS) != 0)
    {
        log_stderr("core/main", 1, "unable to initialize IO engine");
        return -1;
    }

    while(1) {
        struct TimerInfo *ti = timer_next();
        int delay = 1;

        if (ti != NULL)
            delay = ti->ti_timestamp - time(NULL);

        sleep(delay);
        /* TODO: add main daemon loop */
    }
    return 0;
}
