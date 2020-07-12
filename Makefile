MODULE_big = pgcompress
OBJS = pgcompress.o

EXTENSION = pgcompress
DATA = pgcompress--1.0.sql

REGRESS = pgcompress pg_eucjp

PGFILEDESC = "pgcompress - provides deflate, inflate and gzip functions"

PG_CONFIG = pg_config
PGXS := $(shell $(PG_CONFIG) --pgxs)
include $(PGXS)
