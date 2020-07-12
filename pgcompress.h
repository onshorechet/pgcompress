#include "postgres.h"
#include "fmgr.h"
#include "zlib.h"
#include "common/pg_lzcompress.h"
#include "math.h"

#ifdef PG_MODULE_MAGIC
PG_MODULE_MAGIC;
#endif

#define radians(angleDegrees) (angleDegrees * M_PI / 180.0)

/**
 * compute the distance between two points using real or double data types
 */
Datum pgcompress_geodistance_real(PG_FUNCTION_ARGS);
Datum pgcompress_geodistance_double(PG_FUNCTION_ARGS);


/**
 * delfate and inflate data from postgres, return a pointer to that data
 */
static struct varlena * PGCOMPRESSDeflate(struct varlena *source);
static struct varlena * PGCOMPRESSInflate(struct varlena *source);


/**
 * deflate text and bytea data
 */
Datum pgcompress_deflate_text(PG_FUNCTION_ARGS);
Datum pgcompress_deflate_bytea(PG_FUNCTION_ARGS);


/**
 * inflate to text and bytea
 */
Datum pgcompress_inflate_text(PG_FUNCTION_ARGS);
Datum pgcompress_inflate_bytea(PG_FUNCTION_ARGS);


/**
 * tell postgres about all these functions
 */
PG_FUNCTION_INFO_V1(pgcompress_geodistance_real);
PG_FUNCTION_INFO_V1(pgcompress_geodistance_double);

PG_FUNCTION_INFO_V1(pgcompress_deflate_text);
PG_FUNCTION_INFO_V1(pgcompress_deflate_bytea);

PG_FUNCTION_INFO_V1(pgcompress_inflate_text);
PG_FUNCTION_INFO_V1(pgcompress_inflate_bytea);
