/* SPDX-License-Identifier: LGPL-2.1+ */
#pragma once

/***
  This file is part of systemd.

  Copyright 2010 Lennart Poettering
***/

#include <stdbool.h>
#include <sys/stat.h>
#include <sys/types.h>

#include "macro.h"

static inline void umaskp(mode_t *u) {
        umask(*u);
}

#define _cleanup_umask_ _cleanup_(umaskp)

struct _umask_struct_ {
        mode_t mask;
        bool quit;
};

static inline void _reset_umask_(struct _umask_struct_ *s) {
        umask(s->mask);
};

#define RUN_WITH_UMASK(mask)                                            \
        for (_cleanup_(_reset_umask_) struct _umask_struct_ _saved_umask_ = { umask(mask), false }; \
             !_saved_umask_.quit ;                                      \
             _saved_umask_.quit = true)
