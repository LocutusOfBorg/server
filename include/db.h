#ifndef _DB_H
#define _DB_H
/* This code generated by make_db_h.   Copyright (c) 2007, 2008 Tokutek */
#ident "Copyright (c) 2007, 2008 Tokutek Inc.  All rights reserved."
#include <sys/types.h>
/*stdio is needed for the FILE* in db->verify*/
#include <stdio.h>
#if defined(__cplusplus)
extern "C" {
#endif
#define TOKUDB 1
#define TOKUDB_NATIVE_H 0
#define DB_VERSION_MAJOR 4
#define DB_VERSION_MINOR 6
#define DB_VERSION_PATCH 21
#ifndef _TOKUDB_WRAP_H
#define DB_VERSION_STRING "Tokutek: TokuDB 4.6.21"
#else
#define DB_VERSION_STRING_ydb "Tokutek: TokuDB (wrapped bdb)"
#endif
#ifndef TOKU_OFF_T_DEFINED
#define TOKU_OFF_T_DEFINED
typedef int64_t toku_off_t;
#endif
typedef struct __toku_db_env DB_ENV;
typedef struct __toku_db_key_range DB_KEY_RANGE;
typedef struct __toku_db_lsn DB_LSN;
typedef struct __toku_db DB;
typedef struct __toku_db_txn DB_TXN;
typedef struct __toku_db_txn_active DB_TXN_ACTIVE;
typedef struct __toku_db_txn_stat DB_TXN_STAT;
typedef struct __toku_dbc DBC;
typedef struct __toku_dbt DBT;
typedef u_int32_t db_recno_t;
typedef int(*YDB_CALLBACK_FUNCTION)(DBT const*, DBT const*, void*);
typedef int(*YDB_HEAVISIDE_CALLBACK_FUNCTION)(DBT const *key, DBT const *value, void *extra_f, int r_h);
typedef int(*YDB_HEAVISIDE_FUNCTION)(const DBT *key, const DBT *value, void *extra_h);
#include <tdb-internal.h>
typedef struct __toku_db_btree_stat64 {
  u_int64_t bt_nkeys; /* how many unique keys (guaranteed only to be an estimate, even when flattened)          */
  u_int64_t bt_ndata; /* how many key-value pairs (an estimate, but exact when flattened)                       */
  u_int64_t bt_dsize; /* how big are the keys+values (not counting the lengths) (an estimate, unless flattened) */
  u_int64_t bt_fsize; /* how big is the underlying file                                                         */
} DB_BTREE_STAT64;
typedef enum {
 DB_BTREE=1,
 DB_UNKNOWN=5
} DBTYPE;
#ifndef _TOKUDB_WRAP_H
#define DB_VERB_DEADLOCK 1
#define DB_VERB_RECOVERY 8
#define DB_VERB_REPLICATION 32
#define DB_VERB_WAITSFOR 64
#define DB_DBT_MALLOC 8
#define DB_DBT_REALLOC 64
#define DB_DBT_USERMEM 256
#define DB_DBT_DUPOK 2
#define DB_ARCH_ABS 1
#define DB_ARCH_LOG 4
#define DB_CREATE 1
#define DB_CXX_NO_EXCEPTIONS 1
#define DB_EXCL 16384
#define DB_PRIVATE 8388608
#define DB_RDONLY 32
#define DB_RECOVER 64
#define DB_RUNRECOVERY -30975
#define DB_THREAD 128
#define DB_TXN_NOSYNC 512
#define DB_LOCK_DEFAULT 1
#define DB_LOCK_OLDEST 7
#define DB_LOCK_RANDOM 8
#define DB_DUP 32768
#define DB_DUPSORT 65536
#define DB_KEYFIRST 13
#define DB_KEYLAST 14
#define DB_NODUPDATA 19
#define DB_NOOVERWRITE 20
#define DB_YESOVERWRITE 254
#define DB_OPFLAGS_MASK 255
#define DB_AUTO_COMMIT 33554432
#define DB_INIT_LOCK 131072
#define DB_INIT_LOG 262144
#define DB_INIT_MPOOL 524288
#define DB_INIT_TXN 2097152
#define DB_USE_ENVIRON 16384
#define DB_USE_ENVIRON_ROOT 32768
#define DB_READ_UNCOMMITTED 134217728
#define DB_KEYEXIST -30996
#define DB_LOCK_DEADLOCK -30995
#define DB_LOCK_NOTGRANTED -30994
#define DB_NOTFOUND -30989
#define DB_SECONDARY_BAD -30974
#define DB_DONOTINDEX -30998
#define DB_BUFFER_SMALL -30999
#define DB_BADFORMAT -30500
#define DB_DELETE_ANY 65536
#define DB_TRUNCATE_WITHCURSORS 131072
#define DB_FIRST 7
#define DB_GET_BOTH 8
#define DB_GET_BOTH_RANGE 10
#define DB_LAST 15
#define DB_CURRENT 6
#define DB_NEXT 16
#define DB_NEXT_DUP 17
#define DB_NEXT_NODUP 18
#define DB_PREV 23
#define DB_PREV_DUP 24
#define DB_PREV_NODUP 25
#define DB_SET 26
#define DB_SET_RANGE 27
#define DB_CURRENT_BINDING 253
#define DB_SET_RANGE_REVERSE 252
#define DB_GET_BOTH_RANGE_REVERSE 251
#define DB_RMW 1073741824
#define DB_PRELOCKED 0x00800000
#define DB_PRELOCKED_WRITE 0x00400000
#define DB_DBT_APPMALLOC 1
#define DB_DBT_MULTIPLE 16
#define DB_LOG_AUTOREMOVE 524288
#define DB_TXN_WRITE_NOSYNC 4096
#define DB_TXN_NOWAIT 1024
#define DB_TXN_SYNC 16384
#endif
/* TOKUDB specific error codes */
#define TOKUDB_OUT_OF_LOCKS -100000
#define TOKUDB_SUCCEEDED_EARLY -100001
#define TOKUDB_DICTIONARY_TOO_OLD -100004
#define TOKUDB_DICTIONARY_TOO_NEW -100005
#define TOKUDB_DICTIONARY_NO_HEADER -100006
#define TOKUDB_FOUND_BUT_REJECTED -100002
#define TOKUDB_USER_CALLBACK_ERROR -100003
/* in wrap mode, top-level function txn_begin is renamed, but the field isn't renamed, so we have to hack it here.*/
#ifdef _TOKUDB_WRAP_H
#undef txn_begin
#endif
struct __toku_db_env {
  struct __toku_db_env_internal *i;
#define db_env_struct_i(x) ((x)->i)
  int (*checkpointing_set_period)             (DB_ENV*, u_int32_t) /* Change the delay between automatic checkpoints.  0 means disabled. */;
  int (*checkpointing_get_period)             (DB_ENV*, u_int32_t*) /* Retrieve the delay between automatic checkpoints.  0 means disabled. */;
  int (*checkpointing_postpone)               (DB_ENV*) /* Use for 'rename table' or any other operation that must be disjoint from a checkpoint */;
  int (*checkpointing_resume)                 (DB_ENV*) /* Alert tokudb 'postpone' is no longer necessary */;
  int (*checkpointing_begin_atomic_operation) (DB_ENV*) /* Begin a set of operations (that must be atomic as far as checkpoints are concerned). i.e. inserting into every index in one table */;
  int (*checkpointing_end_atomic_operation)   (DB_ENV*) /* End   a set of operations (that must be atomic as far as checkpoints are concerned). */;
  int (*set_default_bt_compare)  (DB_ENV*,int (*bt_compare) (DB *, const DBT *, const DBT *)) /* Set default (key) comparison function for all DBs in this environment.  Required for RECOVERY since you cannot open the DBs manually. */;
  int (*set_default_dup_compare) (DB_ENV*,int (*bt_compare) (DB *, const DBT *, const DBT *)) /* Set default (val) comparison function for all DBs in this environment.  Required for RECOVERY since you cannot open the DBs manually. */;
  void* __toku_dummy0[4];
  void *app_private; /* 32-bit offset=52 size=4, 64=bit offset=104 size=8 */
  void* __toku_dummy1[39];
  char __toku_dummy2[144];
  void *api1_internal; /* 32-bit offset=356 size=4, 64=bit offset=568 size=8 */
  void* __toku_dummy3[8];
  int  (*close) (DB_ENV *, u_int32_t); /* 32-bit offset=392 size=4, 64=bit offset=640 size=8 */
  void* __toku_dummy4[2];
  void (*err) (const DB_ENV *, int, const char *, ...); /* 32-bit offset=404 size=4, 64=bit offset=664 size=8 */
  void* __toku_dummy5[3];
  int (*get_cachesize) (DB_ENV *, u_int32_t *, u_int32_t *, int *); /* 32-bit offset=420 size=4, 64=bit offset=696 size=8 */
  void* __toku_dummy6[5];
  int (*get_flags) (DB_ENV *, u_int32_t *); /* 32-bit offset=444 size=4, 64=bit offset=744 size=8 */
  void* __toku_dummy7[4];
  int  (*get_lg_max) (DB_ENV *, u_int32_t*); /* 32-bit offset=464 size=4, 64=bit offset=784 size=8 */
  void* __toku_dummy8[4];
  int  (*get_lk_max_locks) (DB_ENV *, u_int32_t *); /* 32-bit offset=484 size=4, 64=bit offset=824 size=8 */
  void* __toku_dummy9[22];
  int  (*log_archive) (DB_ENV *, char **[], u_int32_t); /* 32-bit offset=576 size=4, 64=bit offset=1008 size=8 */
  void* __toku_dummy10[2];
  int  (*log_flush) (DB_ENV *, const DB_LSN *); /* 32-bit offset=588 size=4, 64=bit offset=1032 size=8 */
  void* __toku_dummy11[25];
  int  (*open) (DB_ENV *, const char *, u_int32_t, int); /* 32-bit offset=692 size=4, 64=bit offset=1240 size=8 */
  void* __toku_dummy12[30];
  int  (*set_cachesize) (DB_ENV *, u_int32_t, u_int32_t, int); /* 32-bit offset=816 size=4, 64=bit offset=1488 size=8 */
  void* __toku_dummy13[1];
  int  (*set_data_dir) (DB_ENV *, const char *); /* 32-bit offset=824 size=4, 64=bit offset=1504 size=8 */
  void* __toku_dummy14[1];
  void (*set_errcall) (DB_ENV *, void (*)(const DB_ENV *, const char *, const char *)); /* 32-bit offset=832 size=4, 64=bit offset=1520 size=8 */
  void (*set_errfile) (DB_ENV *, FILE*); /* 32-bit offset=836 size=4, 64=bit offset=1528 size=8 */
  void (*set_errpfx) (DB_ENV *, const char *); /* 32-bit offset=840 size=4, 64=bit offset=1536 size=8 */
  void* __toku_dummy15[2];
  int  (*set_flags) (DB_ENV *, u_int32_t, int); /* 32-bit offset=852 size=4, 64=bit offset=1560 size=8 */
  void* __toku_dummy16[2];
  int  (*set_lg_bsize) (DB_ENV *, u_int32_t); /* 32-bit offset=864 size=4, 64=bit offset=1584 size=8 */
  int  (*set_lg_dir) (DB_ENV *, const char *); /* 32-bit offset=868 size=4, 64=bit offset=1592 size=8 */
  void* __toku_dummy17[1];
  int  (*set_lg_max) (DB_ENV *, u_int32_t); /* 32-bit offset=876 size=4, 64=bit offset=1608 size=8 */
  void* __toku_dummy18[2];
  int  (*set_lk_detect) (DB_ENV *, u_int32_t); /* 32-bit offset=888 size=4, 64=bit offset=1632 size=8 */
  void* __toku_dummy19[1];
  int  (*set_lk_max_locks) (DB_ENV *, u_int32_t); /* 32-bit offset=896 size=4, 64=bit offset=1648 size=8 */
  void* __toku_dummy20[14];
  int  (*set_tmp_dir) (DB_ENV *, const char *); /* 32-bit offset=956 size=4, 64=bit offset=1768 size=8 */
  void* __toku_dummy21[2];
  int  (*set_verbose) (DB_ENV *, u_int32_t, int); /* 32-bit offset=968 size=4, 64=bit offset=1792 size=8 */
  void* __toku_dummy22[1];
  int  (*txn_begin) (DB_ENV *, DB_TXN *, DB_TXN **, u_int32_t); /* 32-bit offset=976 size=4, 64=bit offset=1808 size=8 */
  int  (*txn_checkpoint) (DB_ENV *, u_int32_t, u_int32_t, u_int32_t); /* 32-bit offset=980 size=4, 64=bit offset=1816 size=8 */
  void* __toku_dummy23[1];
  int  (*txn_stat) (DB_ENV *, DB_TXN_STAT **, u_int32_t); /* 32-bit offset=988 size=4, 64=bit offset=1832 size=8 */
  void* __toku_dummy24[2]; /* Padding at the end */ 
  char __toku_dummy25[16];  /* Padding at the end */ 
};
struct __toku_db_key_range {
  double less; /* 32-bit offset=0 size=8, 64=bit offset=0 size=8 */
  double equal; /* 32-bit offset=8 size=8, 64=bit offset=8 size=8 */
  double greater; /* 32-bit offset=16 size=8, 64=bit offset=16 size=8 */
  void* __toku_dummy0[214]; /* Padding at the end */ 
  char __toku_dummy1[136];  /* Padding at the end */ 
};
struct __toku_db_lsn {
  char __toku_dummy0[8];  /* Padding at the end */ 
};
struct __toku_dbt {
  void*data; /* 32-bit offset=0 size=4, 64=bit offset=0 size=8 */
  u_int32_t size; /* 32-bit offset=4 size=4, 64=bit offset=8 size=4 */
  u_int32_t ulen; /* 32-bit offset=8 size=4, 64=bit offset=12 size=4 */
  void* __toku_dummy0[1];
  char __toku_dummy1[8];
  u_int32_t flags; /* 32-bit offset=24 size=4, 64=bit offset=32 size=4 */
  /* 4 more bytes of alignment in the 64-bit case. */
};
typedef int (*toku_dbt_upgradef)(DB*,
                                 u_int32_t old_version, const DBT *old_descriptor, const DBT *old_key, const DBT *old_val,
                                 u_int32_t new_version, const DBT *new_descriptor, const DBT *new_key, const DBT *new_val);
struct __toku_db {
  struct __toku_db_internal *i;
#define db_struct_i(x) ((x)->i)
  int (*key_range64)(DB*, DB_TXN *, DBT *, u_int64_t *less, u_int64_t *equal, u_int64_t *greater, int *is_exact);
  int (*stat64)(DB *, DB_TXN *, DB_BTREE_STAT64 *);
  char __toku_dummy0[8];
  void *app_private; /* 32-bit offset=20 size=4, 64=bit offset=32 size=8 */
  DB_ENV *dbenv; /* 32-bit offset=24 size=4, 64=bit offset=40 size=8 */
  int (*pre_acquire_read_lock)(DB*, DB_TXN*, const DBT*, const DBT*, const DBT*, const DBT*);
  int (*pre_acquire_table_lock)(DB*, DB_TXN*);
  const DBT* (*dbt_pos_infty)(void) /* Return the special DBT that refers to positive infinity in the lock table.*/;
  const DBT* (*dbt_neg_infty)(void)/* Return the special DBT that refers to negative infinity in the lock table.*/;
  int (*delboth) (DB*, DB_TXN*, DBT*, DBT*, u_int32_t) /* Delete the key/value pair. */;
  int (*row_size_supported) (DB*, u_int32_t) /* Test whether a row size is supported. */;
  const DBT *descriptor /* saved row/dictionary descriptor for aiding in comparisons */;
  int (*set_descriptor) (DB*, u_int32_t version, const DBT* descriptor, toku_dbt_upgradef dbt_userformat_upgrade) /* set row/dictionary descriptor for a db.  Available only while db is open */;
  int (*getf_set)(DB*, DB_TXN*, u_int32_t, DBT*, YDB_CALLBACK_FUNCTION, void*) /* same as DBC->c_getf_set without a persistent cursor) */;
  int (*getf_get_both)(DB*, DB_TXN*, u_int32_t, DBT*, DBT*, YDB_CALLBACK_FUNCTION, void*) /* same as DBC->c_getf_get_both without a persistent cursor) */;
  int (*flatten)(DB*, DB_TXN*) /* Flatten a dictionary, similar to (but faster than) a table scan */;
  void* __toku_dummy1[31];
  char __toku_dummy2[80];
  void *api_internal; /* 32-bit offset=276 size=4, 64=bit offset=464 size=8 */
  void* __toku_dummy3[5];
  int (*close) (DB*, u_int32_t); /* 32-bit offset=300 size=4, 64=bit offset=512 size=8 */
  void* __toku_dummy4[1];
  int (*cursor) (DB *, DB_TXN *, DBC **, u_int32_t); /* 32-bit offset=308 size=4, 64=bit offset=528 size=8 */
  int (*del) (DB *, DB_TXN *, DBT *, u_int32_t); /* 32-bit offset=312 size=4, 64=bit offset=536 size=8 */
  void* __toku_dummy5[3];
  int (*fd) (DB *, int *); /* 32-bit offset=328 size=4, 64=bit offset=568 size=8 */
  int (*get) (DB *, DB_TXN *, DBT *, DBT *, u_int32_t); /* 32-bit offset=332 size=4, 64=bit offset=576 size=8 */
  void* __toku_dummy6[8];
  int (*get_flags) (DB *, u_int32_t *); /* 32-bit offset=368 size=4, 64=bit offset=648 size=8 */
  void* __toku_dummy7[7];
  int (*get_pagesize) (DB *, u_int32_t *); /* 32-bit offset=400 size=4, 64=bit offset=712 size=8 */
  void* __toku_dummy8[9];
  int (*key_range) (DB *, DB_TXN *, DBT *, DB_KEY_RANGE *, u_int32_t); /* 32-bit offset=440 size=4, 64=bit offset=792 size=8 */
  int (*open) (DB *, DB_TXN *, const char *, const char *, DBTYPE, u_int32_t, int); /* 32-bit offset=444 size=4, 64=bit offset=800 size=8 */
  void* __toku_dummy9[1];
  int (*put) (DB *, DB_TXN *, DBT *, DBT *, u_int32_t); /* 32-bit offset=452 size=4, 64=bit offset=816 size=8 */
  int (*remove) (DB *, const char *, const char *, u_int32_t); /* 32-bit offset=456 size=4, 64=bit offset=824 size=8 */
  int (*rename) (DB *, const char *, const char *, const char *, u_int32_t); /* 32-bit offset=460 size=4, 64=bit offset=832 size=8 */
  void* __toku_dummy10[2];
  int (*set_bt_compare) (DB *, int (*)(DB *, const DBT *, const DBT *)); /* 32-bit offset=472 size=4, 64=bit offset=856 size=8 */
  void* __toku_dummy11[3];
  int (*set_dup_compare) (DB *, int (*)(DB *, const DBT *, const DBT *)); /* 32-bit offset=488 size=4, 64=bit offset=888 size=8 */
  void* __toku_dummy12[2];
  void (*set_errfile) (DB *, FILE*); /* 32-bit offset=500 size=4, 64=bit offset=912 size=8 */
  void* __toku_dummy13[2];
  int (*set_flags) (DB *, u_int32_t); /* 32-bit offset=512 size=4, 64=bit offset=936 size=8 */
  void* __toku_dummy14[7];
  int (*set_pagesize) (DB *, u_int32_t); /* 32-bit offset=544 size=4, 64=bit offset=1000 size=8 */
  void* __toku_dummy15[7];
  int (*stat) (DB *, void *, u_int32_t); /* 32-bit offset=576 size=4, 64=bit offset=1064 size=8 */
  void* __toku_dummy16[2];
  int (*truncate) (DB *, DB_TXN *, u_int32_t *, u_int32_t); /* 32-bit offset=588 size=4, 64=bit offset=1088 size=8 */
  void* __toku_dummy17[1];
  int (*verify) (DB *, const char *, const char *, FILE *, u_int32_t); /* 32-bit offset=596 size=4, 64=bit offset=1104 size=8 */
  void* __toku_dummy18[5]; /* Padding at the end */ 
  char __toku_dummy19[16];  /* Padding at the end */ 
};
struct __toku_db_txn_active {
  u_int32_t txnid; /* 32-bit offset=0 size=4, 64=bit offset=0 size=4 */
  void* __toku_dummy0[2];
  char __toku_dummy1[4];
  DB_LSN lsn; /* 32-bit offset=16 size=8, 64=bit offset=24 size=8 */
  char __toku_dummy2[200];  /* Padding at the end */ 
};
struct txn_stat {
  u_int64_t rolltmp_raw_count;
};
struct __toku_db_txn {
  DB_ENV *mgrp /*In TokuDB, mgrp is a DB_ENV not a DB_TXNMGR*/; /* 32-bit offset=0 size=4, 64=bit offset=0 size=8 */
  DB_TXN *parent; /* 32-bit offset=4 size=4, 64=bit offset=8 size=8 */
  struct __toku_db_txn_internal *i;
#define db_txn_struct_i(x) ((x)->i)
  int (*txn_stat)(DB_TXN *, struct txn_stat **);
  void* __toku_dummy0[16];
  char __toku_dummy1[8];
  void *api_internal; /* 32-bit offset=88 size=4, 64=bit offset=168 size=8 */
  void* __toku_dummy2[2];
  int (*abort) (DB_TXN *); /* 32-bit offset=100 size=4, 64=bit offset=192 size=8 */
  int (*commit) (DB_TXN*, u_int32_t); /* 32-bit offset=104 size=4, 64=bit offset=200 size=8 */
  void* __toku_dummy3[2];
  u_int32_t (*id) (DB_TXN *); /* 32-bit offset=116 size=4, 64=bit offset=224 size=8 */
  void* __toku_dummy4[5]; /* Padding at the end */ 
};
struct __toku_db_txn_stat {
  void* __toku_dummy0[2];
  char __toku_dummy1[28];
  u_int32_t st_nactive; /* 32-bit offset=36 size=4, 64=bit offset=44 size=4 */
  void* __toku_dummy2[1];
  char __toku_dummy3[8];
  DB_TXN_ACTIVE *st_txnarray; /* 32-bit offset=52 size=4, 64=bit offset=64 size=8 */
  void* __toku_dummy4[1]; /* Padding at the end */ 
  char __toku_dummy5[8];  /* Padding at the end */ 
};
struct __toku_dbc {
  DB *dbp; /* 32-bit offset=0 size=4, 64=bit offset=0 size=8 */
  struct __toku_dbc_internal *i;
#define dbc_struct_i(x) ((x)->i)
  int (*c_getf_first)(DBC *, u_int32_t, YDB_CALLBACK_FUNCTION, void *);
  int (*c_getf_last)(DBC *, u_int32_t, YDB_CALLBACK_FUNCTION, void *);
  int (*c_getf_next)(DBC *, u_int32_t, YDB_CALLBACK_FUNCTION, void *);
  int (*c_getf_next_dup)(DBC *, u_int32_t, YDB_CALLBACK_FUNCTION, void *);
  int (*c_getf_next_nodup)(DBC *, u_int32_t, YDB_CALLBACK_FUNCTION, void *);
  int (*c_getf_prev)(DBC *, u_int32_t, YDB_CALLBACK_FUNCTION, void *);
  int (*c_getf_prev_dup)(DBC *, u_int32_t, YDB_CALLBACK_FUNCTION, void *);
  int (*c_getf_prev_nodup)(DBC *, u_int32_t, YDB_CALLBACK_FUNCTION, void *);
  int (*c_getf_current)(DBC *, u_int32_t, YDB_CALLBACK_FUNCTION, void *);
  int (*c_getf_current_binding)(DBC *, u_int32_t, YDB_CALLBACK_FUNCTION, void *);
  int (*c_getf_heaviside)(DBC *, u_int32_t, YDB_HEAVISIDE_CALLBACK_FUNCTION f, void *extra_f, YDB_HEAVISIDE_FUNCTION h, void *extra_h, int direction);
  int (*c_getf_set)(DBC *, u_int32_t, DBT *, YDB_CALLBACK_FUNCTION, void *);
  int (*c_getf_set_range)(DBC *, u_int32_t, DBT *, YDB_CALLBACK_FUNCTION, void *);
  int (*c_getf_set_range_reverse)(DBC *, u_int32_t, DBT *, YDB_CALLBACK_FUNCTION, void *);
  int (*c_getf_get_both)(DBC *, u_int32_t, DBT *, DBT *, YDB_CALLBACK_FUNCTION, void *);
  int (*c_getf_get_both_range)(DBC *, u_int32_t, DBT *, DBT *, YDB_CALLBACK_FUNCTION, void *);
  int (*c_getf_get_both_range_reverse)(DBC *, u_int32_t, DBT *, DBT *, YDB_CALLBACK_FUNCTION, void *);
  void* __toku_dummy0[16];
  char __toku_dummy1[104];
  int (*c_close) (DBC *); /* 32-bit offset=244 size=4, 64=bit offset=384 size=8 */
  int (*c_count) (DBC *, db_recno_t *, u_int32_t); /* 32-bit offset=248 size=4, 64=bit offset=392 size=8 */
  int (*c_del) (DBC *, u_int32_t); /* 32-bit offset=252 size=4, 64=bit offset=400 size=8 */
  void* __toku_dummy2[1];
  int (*c_get) (DBC *, DBT *, DBT *, u_int32_t); /* 32-bit offset=260 size=4, 64=bit offset=416 size=8 */
  void* __toku_dummy3[10]; /* Padding at the end */ 
};
#ifdef _TOKUDB_WRAP_H
#define txn_begin txn_begin_tokudb
#endif
int db_env_create(DB_ENV **, u_int32_t) __attribute__((__visibility__("default")));
int db_create(DB **, DB_ENV *, u_int32_t) __attribute__((__visibility__("default")));
char *db_strerror(int) __attribute__((__visibility__("default")));
const char *db_version(int*,int *,int *) __attribute__((__visibility__("default")));
int log_compare (const DB_LSN*, const DB_LSN *) __attribute__((__visibility__("default")));
int db_env_set_func_fsync (int (*)(int)) __attribute__((__visibility__("default")));
int toku_set_trace_file (char *fname) __attribute__((__visibility__("default")));
int toku_close_trace_file (void) __attribute__((__visibility__("default")));
int db_env_set_func_free (void (*)(void*)) __attribute__((__visibility__("default")));
int db_env_set_func_malloc (void *(*)(size_t)) __attribute__((__visibility__("default")));
int db_env_set_func_pwrite (ssize_t (*)(int, const void *, size_t, toku_off_t)) __attribute__((__visibility__("default")));
int db_env_set_func_write (ssize_t (*)(int, const void *, size_t)) __attribute__((__visibility__("default")));
int db_env_set_func_realloc (void *(*)(void*, size_t)) __attribute__((__visibility__("default")));
void db_env_set_checkpoint_callback (void (*)(void*), void*) __attribute__((__visibility__("default")));
#if defined(__cplusplus)
}
#endif
#endif
