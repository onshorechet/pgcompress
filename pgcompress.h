#include "postgres.h"
#include "fmgr.h"
#include "zlib.h"
#include "common/pg_lzcompress.h"
#include "brotli/decode.h"
#include "brotli/encode.h"
#include "utils/jsonb.h"

#ifdef PG_MODULE_MAGIC
PG_MODULE_MAGIC;
#endif

const int ENZLIB = 0;
const int ENZLIBRAW = 1;
const int ENGZIP = 2;
const int ENBR = 3;

//inflation chunksize in bytes ie 4MB
const int CHUNKSIZE = 4194304;

//CHUNKSIZE * MAX_CHUNKS can support 4GB of decoding
//Maximum number of chunks to support when decoding
const unsigned int MAX_CHUNKS = 1024;

/**
 * delfate and inflate data from postgres, return a pointer to that data
 */
static struct varlena * PGCOMPRESSDeflate(Bytef *source, int length, int type, int level);
static struct varlena * PGCOMPRESSInflate(struct varlena *source, int type);
static struct varlena * PGCOMPRESSEncodeBrotli(Bytef *source, int length, int level);
static struct varlena * PGCOMPRESSDecodeBrotli(struct varlena *source);

StringInfo JsonbToStringInfo(Jsonb *jb);

//General Pramiterized Functions
Datum pgcompress_encode_compressed_text(PG_FUNCTION_ARGS);
Datum pgcompress_encode_compressed_bytea(PG_FUNCTION_ARGS);
Datum pgcompress_encode_compressed_jsonb(PG_FUNCTION_ARGS);

Datum pgcompress_decode_compressed_text(PG_FUNCTION_ARGS);
Datum pgcompress_decode_compressed_bytea(PG_FUNCTION_ARGS);
//Datum pgcompress_decode_compressed_jsonb(PG_FUNCTION_ARGS);

PG_FUNCTION_INFO_V1(pgcompress_encode_compressed_text);
PG_FUNCTION_INFO_V1(pgcompress_encode_compressed_bytea);
PG_FUNCTION_INFO_V1(pgcompress_encode_compressed_jsonb);

PG_FUNCTION_INFO_V1(pgcompress_decode_compressed_text);
PG_FUNCTION_INFO_V1(pgcompress_decode_compressed_bytea);
//PG_FUNCTION_INFO_V1(pgcompress_decode_compressed_jsonb);



//Zlib Functions
Datum pgcompress_encode_zlib_text(PG_FUNCTION_ARGS);
Datum pgcompress_encode_zlib_bytea(PG_FUNCTION_ARGS);
Datum pgcompress_encode_zlib_jsonb(PG_FUNCTION_ARGS);

Datum pgcompress_decode_zlib_text(PG_FUNCTION_ARGS);
Datum pgcompress_decode_zlib_bytea(PG_FUNCTION_ARGS);
//Datum pgcompress_decode_zlib_jsonb(PG_FUNCTION_ARGS);

PG_FUNCTION_INFO_V1(pgcompress_encode_zlib_text);
PG_FUNCTION_INFO_V1(pgcompress_encode_zlib_bytea);
PG_FUNCTION_INFO_V1(pgcompress_encode_zlib_jsonb);

PG_FUNCTION_INFO_V1(pgcompress_decode_zlib_text);
PG_FUNCTION_INFO_V1(pgcompress_decode_zlib_bytea);
//PG_FUNCTION_INFO_V1(pgcompress_decode_zlib_jsonb);




//Zlib Raw Functions
Datum pgcompress_encode_zlib_raw_text(PG_FUNCTION_ARGS);
Datum pgcompress_encode_zlib_raw_bytea(PG_FUNCTION_ARGS);
Datum pgcompress_encode_zlib_raw_jsonb(PG_FUNCTION_ARGS);

Datum pgcompress_decode_zlib_raw_text(PG_FUNCTION_ARGS);
Datum pgcompress_decode_zlib_raw_bytea(PG_FUNCTION_ARGS);
//Datum pgcompress_decode_zlib_raw_jsonb(PG_FUNCTION_ARGS);

PG_FUNCTION_INFO_V1(pgcompress_encode_zlib_raw_text);
PG_FUNCTION_INFO_V1(pgcompress_encode_zlib_raw_bytea);
PG_FUNCTION_INFO_V1(pgcompress_encode_zlib_raw_jsonb);

PG_FUNCTION_INFO_V1(pgcompress_decode_zlib_raw_text);
PG_FUNCTION_INFO_V1(pgcompress_decode_zlib_raw_bytea);
//PG_FUNCTION_INFO_V1(pgcompress_decode_zlib_raw_jsonb);



//Gzip Functions
Datum pgcompress_encode_gzip_text(PG_FUNCTION_ARGS);
Datum pgcompress_encode_gzip_bytea(PG_FUNCTION_ARGS);
Datum pgcompress_encode_gzip_jsonb(PG_FUNCTION_ARGS);

Datum pgcompress_decode_gzip_text(PG_FUNCTION_ARGS);
Datum pgcompress_decode_gzip_bytea(PG_FUNCTION_ARGS);
//Datum pgcompress_decode_gzip_jsonb(PG_FUNCTION_ARGS);

PG_FUNCTION_INFO_V1(pgcompress_encode_gzip_text);
PG_FUNCTION_INFO_V1(pgcompress_encode_gzip_bytea);
PG_FUNCTION_INFO_V1(pgcompress_encode_gzip_jsonb);

PG_FUNCTION_INFO_V1(pgcompress_decode_gzip_text);
PG_FUNCTION_INFO_V1(pgcompress_decode_gzip_bytea);
//PG_FUNCTION_INFO_V1(pgcompress_decode_gzip_jsonb);



//Brotli Functions
Datum pgcompress_encode_br_text(PG_FUNCTION_ARGS);
Datum pgcompress_encode_br_bytea(PG_FUNCTION_ARGS);
Datum pgcompress_encode_br_jsonb(PG_FUNCTION_ARGS);

Datum pgcompress_decode_br_text(PG_FUNCTION_ARGS);
Datum pgcompress_decode_br_bytea(PG_FUNCTION_ARGS);
//Datum pgcompress_decode_br_jsonb(PG_FUNCTION_ARGS);

PG_FUNCTION_INFO_V1(pgcompress_encode_br_text);
PG_FUNCTION_INFO_V1(pgcompress_encode_br_bytea);
PG_FUNCTION_INFO_V1(pgcompress_encode_br_jsonb);

PG_FUNCTION_INFO_V1(pgcompress_decode_br_text);
PG_FUNCTION_INFO_V1(pgcompress_decode_br_bytea);
//PG_FUNCTION_INFO_V1(pgcompress_decode_br_jsonb);
