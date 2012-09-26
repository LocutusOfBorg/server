/* -*- mode: C++; c-basic-offset: 4; indent-tabs-mode: nil -*- */
// vim: ft=cpp:expandtab:ts=8:sw=4:softtabstop=4:
#ident "$Id$"
#ident "Copyright (c) 2007-2012 Tokutek Inc.  All rights reserved."

#include <unistd.h>
#include <stdlib.h>
#include <sys/time.h>
#include "test.h"

#include "includes.h"

#ifndef MIN
#define MIN(x, y) (((x) < (y)) ? (x) : (y))
#endif
const double USECS_PER_SEC = 1000000.0;

static int
long_key_cmp(DB *UU(e), const DBT *a, const DBT *b)
{
    const long *CAST_FROM_VOIDP(x, a->data);
    const long *CAST_FROM_VOIDP(y, b->data);
    return (*x > *y) - (*x < *y);
}

static void
run_test(unsigned long eltsize, unsigned long nodesize, unsigned long repeat)
{
    int cur = 0;
    long keys[1024];
    char *vals[1024];
    for (int i = 0; i < 1024; ++i) {
        keys[i] = rand();
        XMALLOC_N(eltsize - (sizeof keys[i]), vals[i]);
        unsigned int j = 0;
        char *val = vals[i];
        for (; j < eltsize - (sizeof keys[i]) - sizeof(int); j += sizeof(int)) {
            int *p = cast_to_typeof(p) &val[j];
            *p = rand();
        }
        for (; j < eltsize - (sizeof keys[i]); ++j) {
            char *p = &val[j];
            *p = (rand() & 0xff);
        }
    }
    XIDS xids_0 = xids_get_root_xids();
    XIDS xids_123;
    int r = xids_create_child(xids_0, &xids_123, (TXNID)123);
    CKERR(r);

    NONLEAF_CHILDINFO bnc;
    long long unsigned nbytesinserted = 0;
    struct timeval t[2];
    gettimeofday(&t[0], NULL);

    for (unsigned int i = 0; i < repeat; ++i) {
        bnc = toku_create_empty_nl();
        for (; toku_bnc_nbytesinbuf(bnc) <= nodesize; ++cur) {
            toku_bnc_insert_msg(bnc,
                                &keys[cur % 1024], sizeof keys[cur % 1024],
                                vals[cur % 1024], eltsize - (sizeof keys[cur % 1024]),
                                FT_NONE, next_dummymsn(), xids_123, true,
                                NULL, long_key_cmp); assert_zero(r);
        }
        nbytesinserted += toku_bnc_nbytesinbuf(bnc);
        destroy_nonleaf_childinfo(bnc);
    }

    gettimeofday(&t[1], NULL);
    double dt;
    dt = (t[1].tv_sec - t[0].tv_sec) + ((t[1].tv_usec - t[0].tv_usec) / USECS_PER_SEC);
    double mbrate = ((double) nbytesinserted / (1 << 20)) / dt;
    long long unsigned eltrate = (long) (cur / dt);
    printf("%0.03lf MB/sec\n", mbrate);
    printf("%llu elts/sec\n", eltrate);
}

int
test_main (int argc __attribute__((__unused__)), const char *argv[] __attribute__((__unused__))) {
    unsigned long eltsize, nodesize, repeat;

    initialize_dummymsn();
    if (argc != 4) {
        fprintf(stderr, "Usage: %s <eltsize> <nodesize> <repeat>\n", argv[0]);
        return 2;
    }
    eltsize = strtoul(argv[1], NULL, 0);
    nodesize = strtoul(argv[2], NULL, 0);
    repeat = strtoul(argv[3], NULL, 0);

    run_test(eltsize, nodesize, repeat);

    return 0;
}
