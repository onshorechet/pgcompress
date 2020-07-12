#include "pgcompress.h"

#define R 6371
#define TO_RAD (3.1415926536 / 180)

/**
 * compute the distance between two points using real data types
 */
Datum pgcompress_geodistance_real(PG_FUNCTION_ARGS)
{
    float4 alat = PG_GETARG_FLOAT4(0);
    float4 alon = PG_GETARG_FLOAT4(1);
    float4 blat = PG_GETARG_FLOAT4(2);
    float4 blon = PG_GETARG_FLOAT4(3);
    float4 dx, dy, dz;
    alon -= blon;
    alon *= TO_RAD, alat *= TO_RAD, blat *= TO_RAD;

    dz = sin(alat) - sin(blat);
    dx = cos(alon) * cos(alat) - cos(blat);
    dy = sin(alon) * cos(alat);
    PG_RETURN_FLOAT4(asin(sqrt(dx * dx + dy * dy + dz * dz) / 2) * 2 * R);
}


/**
 * compute the distance between two points using double data types
 */
Datum pgcompress_geodistance_double(PG_FUNCTION_ARGS)
{
    float4 alat = PG_GETARG_FLOAT8(0);
    float4 alon = PG_GETARG_FLOAT8(1);
    float4 blat = PG_GETARG_FLOAT8(2);
    float4 blon = PG_GETARG_FLOAT8(3);
    float4 dx, dy, dz;
    alon -= blon;
    alon *= TO_RAD, alat *= TO_RAD, blat *= TO_RAD;

    dz = sin(alat) - sin(blat);
    dx = cos(alon) * cos(alat) - cos(blat);
    dy = sin(alon) * cos(alat);
    PG_RETURN_FLOAT8(asin(sqrt(dx * dx + dy * dy + dz * dz) / 2) * 2 * R);
}


/**
 * compress text data
 * returns bytea
 */
Datum pgcompress_deflate_text(PG_FUNCTION_ARGS)
{
    // get the source text string
    text *source = PG_GETARG_TEXT_P(0);

    // compress and return the data to postgres as a bytea
    PG_RETURN_BYTEA_P(PGCOMPRESSDeflate((struct varlena *) source, false));
}


/*
 * Create a compressed version of a bytea datum
 * return bytea
 */
Datum pgcompress_deflate_bytea(PG_FUNCTION_ARGS)
{
    // get the source bytea
    bytea *source = PG_GETARG_BYTEA_P(0);

    // compress and return the bytea to postgress
    PG_RETURN_BYTEA_P(PGCOMPRESSDeflate((struct varlena *) source, false));
}

/**
 * compress text data
 * returns bytea
 */
Datum pgcompress_gzip_text(PG_FUNCTION_ARGS)
{
    // get the source text string
    text *source = PG_GETARG_TEXT_P(0);

    // compress and return the data to postgres as a bytea
    PG_RETURN_BYTEA_P(PGCOMPRESSDeflate((struct varlena *) source, true));
}


/*
 * Create a compressed version of a bytea datum
 * return bytea
 */
Datum pgcompress_gzip_bytea(PG_FUNCTION_ARGS)
{
    // get the source bytea
    bytea *source = PG_GETARG_BYTEA_P(0);

    // compress and return the bytea to postgress
    PG_RETURN_BYTEA_P(PGCOMPRESSDeflate((struct varlena *) source, true));
}


/*
 * Inflate a compressed version of bytea into text.
 */
Datum pgcompress_inflate_text(PG_FUNCTION_ARGS)
{
    // get the source bytea of compressed data
    bytea *source = PG_GETARG_BYTEA_P(0);

    // return the uncompressed data as a text string
    PG_RETURN_TEXT_P(PGCOMPRESSInflate((struct varlena *) source));
}


/*
 * Inflate a compressed version of bytea into bytea.
 */
Datum pgcompress_inflate_bytea(PG_FUNCTION_ARGS)
{
    // get the source bytea of compressed data
    bytea *source = PG_GETARG_BYTEA_P(0);

    // return the uncompressed data as a bytea
    PG_RETURN_BYTEA_P(PGCOMPRESSInflate((struct varlena *) source));
}


/*
 * Create a compressed version of a varlena datum
 */
static struct varlena * PGCOMPRESSDeflate(struct varlena *source, bool gzip)
{
    //data structure for the compressed data
    struct varlena *dest;

    // zlib struct
    z_stream defstream;

    // only allow 200MB of memory consumption
    if (((VARSIZE(source) - VARHDRSZ) * 2 + VARHDRSZ) > 200000000) {
        ereport(ERROR, (errcode(ERRCODE_FEATURE_NOT_SUPPORTED), errmsg("Deflate limited to 200MB of memory.")));
        SET_VARSIZE(dest, VARHDRSZ);
        return dest;
    }

    // alocate memory
    dest = (struct varlena *) palloc((VARSIZE(source) - VARHDRSZ) * 2 + VARHDRSZ);

    // zlib deflate object
    defstream.zalloc = Z_NULL;
    defstream.zfree  = Z_NULL;
    defstream.opaque = Z_NULL;

    // setup "a" as the input and "b" as the compressed output
    defstream.avail_in  = (uInt)(VARSIZE(source) - VARHDRSZ); // size of input, string + terminator
    defstream.next_in   = (Bytef *) VARDATA(source); // input char array
    defstream.avail_out = (VARSIZE(source) - VARHDRSZ) * 2; // size of output
    defstream.next_out  = (Bytef *) VARDATA(dest); // output char array

    // the actual compression work.
    window_bits = MAX_WBITS;
    if(gzip) {
        window_bits += 16;
    }

    deflateInit2(&defstream, Z_DEFAULT_COMPRESSION, Z_DEFLATED, window_bits, DEF_MEM_LEVEL, Z_DEFAULT_STRATEGY);
    deflate(&defstream, Z_FINISH);
    deflateEnd(&defstream);

    //tell postgres about actual size of the compressed data
    SET_VARSIZE(dest,  defstream.total_out + VARHDRSZ);

    //return the dest pointer
    return dest;
}


/*
 * Inflate a compressed version of a varlena datum.
 */
static struct varlena * PGCOMPRESSInflate(struct varlena *source)
{
    //data structure for the uncompressed data
    struct varlena *dest;

    //compute compressed and uncompressed bounds
    uLongf compSize  = VARSIZE(source) - VARHDRSZ;
    uLongf ucompSize = compressBound(compSize) * 100;

    // only allow 200MB of memory consumption
    if (ucompSize > 20000000) {
        ereport(ERROR, (errcode(ERRCODE_FEATURE_NOT_SUPPORTED), errmsg("Deflate limited to 200MB of memory.")));
        SET_VARSIZE(dest, VARHDRSZ);
        return dest;
    }

    // alocate memory
    dest = (struct varlena *) palloc(ucompSize + VARHDRSZ);

    // Inflate - uncompress the data and update ucompSize
    uncompress((Bytef *)VARDATA(dest), &ucompSize, (Bytef *)VARDATA(source), compSize);

    //tell postgres about actual size of the uncompressed data
    SET_VARSIZE(dest, ucompSize + VARHDRSZ);

    //return the dest pointer
    return dest;
}
