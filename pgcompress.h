#include "postgres.h"
#include "fmgr.h"
#include "zlib.h"
#include "common/pg_lzcompress.h"
#include "brotli/encode.h"
#include "brotli/decode.h"

#ifdef PG_MODULE_MAGIC
PG_MODULE_MAGIC;
#endif

const int ENZLIB = 0;
const int ENZLIBRAW = 1;
const int ENGZIP = 2;
const int ENBR = 3;


/**
 * delfate and inflate data from postgres, return a pointer to that data
 */
static struct varlena * PGCOMPRESSDeflate(struct varlena *source, int type, int level);
static struct varlena * PGCOMPRESSInflate(struct varlena *source, int type);
static struct varlena * PGCOMPRESSEncodeBrotli(struct varlena *source, int level);
static struct varlena * PGCOMPRESSDecodeBrotli(struct varlena *source);

Datum pgcompress_encode_compressed_text(PG_FUNCTION_ARGS);
Datum pgcompress_encode_compressed_bytea(PG_FUNCTION_ARGS);
Datum pgcompress_decode_compressed_text(PG_FUNCTION_ARGS);
Datum pgcompress_decode_compressed_bytea(PG_FUNCTION_ARGS);
PG_FUNCTION_INFO_V1(pgcompress_encode_compressed_text);
PG_FUNCTION_INFO_V1(pgcompress_encode_compressed_bytea);
PG_FUNCTION_INFO_V1(pgcompress_decode_compressed_text);
PG_FUNCTION_INFO_V1(pgcompress_decode_compressed_bytea);

/**
 * deflate text and bytea data
 */
Datum pgcompress_encode_zlib_text(PG_FUNCTION_ARGS);
Datum pgcompress_encode_zlib_bytea(PG_FUNCTION_ARGS);
Datum pgcompress_decode_zlib_text(PG_FUNCTION_ARGS);
Datum pgcompress_decode_zlib_bytea(PG_FUNCTION_ARGS);
PG_FUNCTION_INFO_V1(pgcompress_encode_zlib_text);
PG_FUNCTION_INFO_V1(pgcompress_encode_zlib_bytea);
PG_FUNCTION_INFO_V1(pgcompress_decode_zlib_text);
PG_FUNCTION_INFO_V1(pgcompress_decode_zlib_bytea);


Datum pgcompress_encode_zlib_raw_text(PG_FUNCTION_ARGS);
Datum pgcompress_encode_zlib_raw_bytea(PG_FUNCTION_ARGS);
Datum pgcompress_decode_zlib_raw_text(PG_FUNCTION_ARGS);
Datum pgcompress_decode_zlib_raw_bytea(PG_FUNCTION_ARGS);
PG_FUNCTION_INFO_V1(pgcompress_encode_zlib_raw_text);
PG_FUNCTION_INFO_V1(pgcompress_encode_zlib_raw_bytea);
PG_FUNCTION_INFO_V1(pgcompress_decode_zlib_raw_text);
PG_FUNCTION_INFO_V1(pgcompress_decode_zlib_raw_bytea);


Datum pgcompress_encode_gzip_text(PG_FUNCTION_ARGS);
Datum pgcompress_encode_gzip_bytea(PG_FUNCTION_ARGS);
Datum pgcompress_decode_gzip_text(PG_FUNCTION_ARGS);
Datum pgcompress_decode_gzip_bytea(PG_FUNCTION_ARGS);
PG_FUNCTION_INFO_V1(pgcompress_encode_gzip_text);
PG_FUNCTION_INFO_V1(pgcompress_encode_gzip_bytea);
PG_FUNCTION_INFO_V1(pgcompress_decode_gzip_text);
PG_FUNCTION_INFO_V1(pgcompress_decode_gzip_bytea);


Datum pgcompress_encode_br_text(PG_FUNCTION_ARGS);
Datum pgcompress_encode_br_bytea(PG_FUNCTION_ARGS);
Datum pgcompress_decode_br_text(PG_FUNCTION_ARGS);
Datum pgcompress_decode_br_bytea(PG_FUNCTION_ARGS);
PG_FUNCTION_INFO_V1(pgcompress_encode_br_text);
PG_FUNCTION_INFO_V1(pgcompress_encode_br_bytea);
PG_FUNCTION_INFO_V1(pgcompress_decode_br_text);
PG_FUNCTION_INFO_V1(pgcompress_decode_br_bytea);
