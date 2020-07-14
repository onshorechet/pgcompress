MODULE_big = pgcompress
OBJS = pgcompress.o

EXTENSION = pgcompress
DATA = pgcompress--1.0.sql

REGRESS = pgcompress pg_eucjp
SHLIB_LINK += -lbrotlicommon -lbrotlienc -lbrotlidec
#SHLIB_LINK += -L/usr/local/lib -lbrotlicommon -lbrotlienc -lbrotlidec
PGFILEDESC = "pgcompress - provides deflate, inflate, gzip and brotli encode and decode functions for text and bytea"

PG_CONFIG = pg_config
PGXS := $(shell $(PG_CONFIG) --pgxs)
include $(PGXS)
