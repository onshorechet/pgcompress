#include "pgcompress.h"


/**
 * compress text data
 * returns bytea
 */
Datum pgcompress_encode_compressed_text(PG_FUNCTION_ARGS)
{
    // get the source text string
    text *source = PG_GETARG_TEXT_P(0);

    int level = Z_DEFAULT_COMPRESSION;

    //get the default or provided compression
    int type  = PG_GETARG_INT32(1);

    if (PG_NARGS() == 3) {
        level = PG_GETARG_INT32(2);
    }

    if(type < 0 || type > 3) {
        type = 0;
    }

    if(type != ENBR) {
        if (level < 0 || level > 9) {
            level = Z_DEFAULT_COMPRESSION;
        }
    } else {
        if (level < BROTLI_MIN_QUALITY || level > BROTLI_MAX_QUALITY) {
            level = BROTLI_DEFAULT_QUALITY;
        }
    }

    if(type != ENBR) {
        // compress and return the data to postgres as a bytea
        PG_RETURN_BYTEA_P(PGCOMPRESSDeflate((struct varlena *) source, type, level));
    } else {
        PG_RETURN_BYTEA_P(PGCOMPRESSEncodeBrotli((struct varlena *) source, level));
    }
}


/*
 * Create a compressed version of a bytea datum
 * return bytea
 */
Datum pgcompress_encode_compressed_bytea(PG_FUNCTION_ARGS)
{
    // get the source bytea
    bytea *source = PG_GETARG_BYTEA_P(0);

    //get the default or provided compression
    int type  = PG_GETARG_INT32(1);
    int level = Z_DEFAULT_COMPRESSION;
    if(type < 0 || type > 3) {
        type = 0;
    }

    if(type != ENBR) {
        if (level < 0 || level > 9) {
            level = Z_DEFAULT_COMPRESSION;
        }
    } else {
        if (level < BROTLI_MIN_QUALITY || level > BROTLI_MAX_QUALITY) {
            level = BROTLI_DEFAULT_QUALITY;
        }
    }

    if(type != ENBR) {
        // compress and return the data to postgres as a bytea
        PG_RETURN_BYTEA_P(PGCOMPRESSDeflate((struct varlena *) source, type, level));
    } else {
        PG_RETURN_BYTEA_P(PGCOMPRESSEncodeBrotli((struct varlena *) source, level));
    }
}

/*
 * Inflate a compressed version of bytea into text.
 */
Datum pgcompress_decode_compressed_text(PG_FUNCTION_ARGS)
{
    // get the source bytea of compressed data
    bytea *source = PG_GETARG_BYTEA_P(0);

    //get the default or provided compression
    int type  = PG_GETARG_INT32(1);
    if(type < 0 || type > 3) {
        type = 0;
    }

    if(type != ENBR) {
        // return the uncompressed data as a text string
        PG_RETURN_TEXT_P(PGCOMPRESSInflate((struct varlena *) source, type));
    } else {
        PG_RETURN_TEXT_P(PGCOMPRESSDecodeBrotli((struct varlena *) source));
    }
}


/*
 * Inflate a compressed version of bytea into bytea.
 */
Datum pgcompress_decode_compressed_bytea(PG_FUNCTION_ARGS)
{
    // get the source bytea of compressed data
    bytea *source = PG_GETARG_BYTEA_P(0);

    //get the default or provided compression
    int type  = PG_GETARG_INT32(1);
    if(type < 0 || type > 3) {
        type = 0;
    }

    if(type != ENBR) {
        // return the uncompressed data as a text string
        PG_RETURN_TEXT_P(PGCOMPRESSInflate((struct varlena *) source, type));
    } else {
        PG_RETURN_TEXT_P(PGCOMPRESSDecodeBrotli((struct varlena *) source));
    }
}


/**
 * compress text data
 * returns bytea
 */
Datum pgcompress_encode_zlib_text(PG_FUNCTION_ARGS)
{
    // get the source text string
    text *source = PG_GETARG_TEXT_P(0);

    //get the default or provided compression
    int level = Z_DEFAULT_COMPRESSION;
    if (PG_NARGS() == 2) {
        level = PG_GETARG_INT32(1);
    }

    if(level < 0 || level > 9) {
        level = Z_DEFAULT_COMPRESSION;
    }


    // compress and return the data to postgres as a bytea
    PG_RETURN_BYTEA_P(PGCOMPRESSDeflate((struct varlena *) source, ENZLIB, level));
}


/*
 * Create a compressed version of a bytea datum
 * return bytea
 */
Datum pgcompress_encode_zlib_bytea(PG_FUNCTION_ARGS)
{
    // get the source bytea
    bytea *source = PG_GETARG_BYTEA_P(0);

    //get the default or provided compression
    int level = Z_DEFAULT_COMPRESSION;
    if (PG_NARGS() == 2) {
        level = PG_GETARG_INT32(1);
    }

    if(level < 0 || level > 9) {
        level = Z_DEFAULT_COMPRESSION;
    }


    // compress and return the bytea to postgress
    PG_RETURN_BYTEA_P(PGCOMPRESSDeflate((struct varlena *) source, ENZLIB, level));
}

/**
 * compress text data
 * returns bytea
 */
Datum pgcompress_encode_zlib_raw_text(PG_FUNCTION_ARGS)
{
    // get the source text string
    text *source = PG_GETARG_TEXT_P(0);

    //get the default or provided compression
    int level = Z_DEFAULT_COMPRESSION;
    if (PG_NARGS() == 2) {
        level = PG_GETARG_INT32(1);
    }

    if(level < 0 || level > 9) {
        level = Z_DEFAULT_COMPRESSION;
    }



    // compress and return the data to postgres as a bytea
    PG_RETURN_BYTEA_P(PGCOMPRESSDeflate((struct varlena *) source, ENZLIBRAW, level));
}


/*
 * Create a compressed version of a bytea datum
 * return bytea
 */
Datum pgcompress_encode_zlib_raw_bytea(PG_FUNCTION_ARGS)
{
    // get the source bytea
    bytea *source = PG_GETARG_BYTEA_P(0);

    //get the default or provided compression
    int level = Z_DEFAULT_COMPRESSION;
    if (PG_NARGS() == 2) {
        level = PG_GETARG_INT32(1);
    }

    if(level < 0 || level > 9) {
        level = Z_DEFAULT_COMPRESSION;
    }


    // compress and return the bytea to postgress
    PG_RETURN_BYTEA_P(PGCOMPRESSDeflate((struct varlena *) source, ENZLIBRAW, level));
}


/**
 * compress text data
 * returns bytea
 */
Datum pgcompress_encode_gzip_text(PG_FUNCTION_ARGS)
{
    // get the source text string
    text *source = PG_GETARG_TEXT_P(0);

    //get the default or provided compression
    int level = Z_DEFAULT_COMPRESSION;
    if (PG_NARGS() == 2) {
        level = PG_GETARG_INT32(1);
    }

    if(level < 0 || level > 9) {
        level = Z_DEFAULT_COMPRESSION;
    }


    // compress and return the data to postgres as a bytea
    PG_RETURN_BYTEA_P(PGCOMPRESSDeflate((struct varlena *) source, ENGZIP, level));
}


/*
 * Create a compressed version of a bytea datum
 * return bytea
 */
Datum pgcompress_encode_gzip_bytea(PG_FUNCTION_ARGS)
{
    // get the source bytea
    bytea *source = PG_GETARG_BYTEA_P(0);

    //get the default or provided compression
    int level = Z_DEFAULT_COMPRESSION;
    if (PG_NARGS() == 2) {
        level = PG_GETARG_INT32(1);
    }

    if(level < 0 || level > 9) {
        level = Z_DEFAULT_COMPRESSION;
    }


    // compress and return the bytea to postgress
    PG_RETURN_BYTEA_P(PGCOMPRESSDeflate((struct varlena *) source, ENGZIP, level));
}


/**
 * compress text data
 * returns bytea
 */
Datum pgcompress_encode_br_text(PG_FUNCTION_ARGS)
{
    // get the source text string
    text *source = PG_GETARG_TEXT_P(0);

    //get the default or provided compression
    int level = BROTLI_DEFAULT_QUALITY;
    if (PG_NARGS() == 2) {
        level = PG_GETARG_INT32(1);
    }

    if(level < BROTLI_MIN_QUALITY || level > BROTLI_MAX_QUALITY) {
        level = BROTLI_DEFAULT_QUALITY;
    }


    // compress and return the data to postgres as a bytea
    PG_RETURN_BYTEA_P(PGCOMPRESSEncodeBrotli((struct varlena *) source, level));
}


/*
 * Create a compressed version of a bytea datum
 * return bytea
 */
Datum pgcompress_encode_br_bytea(PG_FUNCTION_ARGS)
{
    // get the source bytea
    bytea *source = PG_GETARG_BYTEA_P(0);

    //get the default or provided compression
    int level = Z_DEFAULT_COMPRESSION;
    if (PG_NARGS() == 2) {
        level = PG_GETARG_INT32(1);
    }

    if(level < BROTLI_MIN_QUALITY || level > BROTLI_MAX_QUALITY) {
        level = BROTLI_DEFAULT_QUALITY;
    }


    // compress and return the bytea to postgress
    PG_RETURN_BYTEA_P(PGCOMPRESSEncodeBrotli((struct varlena *) source, level));
}


/*
 * Inflate a compressed version of bytea into text.
 */
Datum pgcompress_decode_zlib_text(PG_FUNCTION_ARGS)
{
    // get the source bytea of compressed data
    bytea *source = PG_GETARG_BYTEA_P(0);

    // return the uncompressed data as a text string
    PG_RETURN_TEXT_P(PGCOMPRESSInflate((struct varlena *) source, ENZLIB));
}


/*
 * Inflate a compressed version of bytea into bytea.
 */
Datum pgcompress_decode_zlib_bytea(PG_FUNCTION_ARGS)
{
    // get the source bytea of compressed data
    bytea *source = PG_GETARG_BYTEA_P(0);

    // return the uncompressed data as a bytea
    PG_RETURN_BYTEA_P(PGCOMPRESSInflate((struct varlena *) source, ENZLIB));
}


/*
 * Inflate a compressed version of bytea into text.
 */
Datum pgcompress_decode_zlib_raw_text(PG_FUNCTION_ARGS)
{
    // get the source bytea of compressed data
    bytea *source = PG_GETARG_BYTEA_P(0);

    // return the uncompressed data as a text string
    PG_RETURN_TEXT_P(PGCOMPRESSInflate((struct varlena *) source, ENZLIBRAW));
}


/*
 * Inflate a compressed version of bytea into bytea.
 */
Datum pgcompress_decode_zlib_raw_bytea(PG_FUNCTION_ARGS)
{
    // get the source bytea of compressed data
    bytea *source = PG_GETARG_BYTEA_P(0);

    // return the uncompressed data as a bytea
    PG_RETURN_BYTEA_P(PGCOMPRESSInflate((struct varlena *) source, ENZLIBRAW));
}


/*
 * Inflate a compressed version of bytea into text.
 */
Datum pgcompress_decode_gzip_text(PG_FUNCTION_ARGS)
{
    // get the source bytea of compressed data
    bytea *source = PG_GETARG_BYTEA_P(0);

    // return the uncompressed data as a text string
    PG_RETURN_TEXT_P(PGCOMPRESSInflate((struct varlena *) source, ENGZIP));
}


/*
 * Inflate a compressed version of bytea into bytea.
 */
Datum pgcompress_decode_gzip_bytea(PG_FUNCTION_ARGS)
{
    // get the source bytea of compressed data
    bytea *source = PG_GETARG_BYTEA_P(0);

    // return the uncompressed data as a bytea
    PG_RETURN_BYTEA_P(PGCOMPRESSInflate((struct varlena *) source, ENGZIP));
}


/*
 * Inflate a compressed version of bytea into text.
 */
Datum pgcompress_decode_br_text(PG_FUNCTION_ARGS)
{
    // get the source bytea of compressed data
    bytea *source = PG_GETARG_BYTEA_P(0);

    // return the uncompressed data as a text string
    PG_RETURN_TEXT_P(PGCOMPRESSDecodeBrotli((struct varlena *) source));
}


/*
 * Inflate a compressed version of bytea into bytea.
 */
Datum pgcompress_decode_br_bytea(PG_FUNCTION_ARGS)
{
    // get the source bytea of compressed data
    bytea *source = PG_GETARG_BYTEA_P(0);

    // return the uncompressed data as a bytea
    PG_RETURN_BYTEA_P(PGCOMPRESSDecodeBrotli((struct varlena *) source));
}

void *myalloc OF((void *, unsigned, unsigned));
void myfree OF((void *, void *));

void *myalloc(q, n, m)
    void *q;
    unsigned n, m;
{
    return palloc0(n * m);
}

void myfree(void *q, void *p)
{
    (void)q;
    pfree(p);
}

static alloc_func zalloc = myalloc;
static free_func zfree = myfree;


/*
 * Create a compressed version of a varlena datum
 */
static struct varlena * PGCOMPRESSDeflate(struct varlena *source, int type, int level)
{

    // zlib struct
    z_stream stream;

    //data structure for the compressed data
    struct varlena *dest;

    //used to swithc types
    int window_bits = MAX_WBITS;

    /* conservative upper bound for compressed data */
    uLong complen;
    complen = VARSIZE(source) + ((VARSIZE(source) + 7) >> 3) + ((VARSIZE(source) + 63) >> 6) + 5 + 18;

    dest = (struct varlena *) palloc0(complen + VARHDRSZ);

    // zlib deflate object
    stream.zalloc = zalloc;
    stream.zfree  = zfree;
    stream.opaque = Z_NULL;

    stream.next_in   = (Bytef *) VARDATA(source); // input char array
    stream.avail_in  = VARSIZE(source) - VARHDRSZ;
    stream.avail_out = complen;
    stream.next_out  = (Bytef *) VARDATA(dest); // output char array

    if(type == ENZLIBRAW) {
        window_bits = -window_bits;
    } else if(type == ENGZIP) {
        window_bits += 16;
    }

    deflateInit2(&stream, level, Z_DEFLATED, window_bits, Z_DEFLATED, Z_DEFAULT_STRATEGY);
    deflate(&stream, Z_FINISH);
    deflateEnd(&stream);

    //tell postgres about actual size of the compressed data
    SET_VARSIZE(dest,  stream.total_out + VARHDRSZ);
    return dest;
}

static void*
brotli_g_malloc_wrapper(void *opaque, size_t size)
{
    return palloc(size);
}

static void
brotli_g_free_wrapper(void *opaque, void *address)
{
    pfree(address);
}

/*
 * Create a compressed version of a varlena datum
 */
static struct varlena * PGCOMPRESSEncodeBrotli(struct varlena *source, int level)
{

    // zlib struct
    BrotliEncoderState* stream;

    //data structure for the compressed data
    struct varlena *dest;

    /* conservative upper bound for compressed data */
    uLong complen;

    stream = BrotliEncoderCreateInstance(
        &brotli_g_malloc_wrapper /*alloc_func*/,
        &brotli_g_free_wrapper /*free_func*/,
        NULL /*opaque*/
    );

    BrotliEncoderSetParameter(stream, BROTLI_PARAM_QUALITY, level);

    complen = BrotliEncoderMaxCompressedSize(VARSIZE(source));

    dest = (struct varlena *) palloc0(complen + VARHDRSZ);

    BrotliEncoderCompress(
        level,
        BROTLI_DEFAULT_WINDOW,
        BROTLI_DEFAULT_MODE,
        VARSIZE(source),
        (Bytef *) VARDATA(source),
        &complen,
        (Bytef *) VARDATA(dest)
    );

    //tell postgres about actual size of the compressed data
    SET_VARSIZE(dest,  complen + VARHDRSZ);
    return dest;
}


/*
 * Inflate a compressed version of a varlena datum.
 */
static struct varlena * PGCOMPRESSInflate(struct varlena *source, int type)
{
    const unsigned int MAX_CHUNKS = 1000;

    //data structure for the uncompressed data
    struct varlena *dest;

    //used to swithc types
    int window_bits = MAX_WBITS;

    z_stream stream;
    int err;
    uLongf sourceLen = VARSIZE(source) - VARHDRSZ;

    int chunksize  = 1;
    int chunkindex = 0;
    Bytef **chunks = (Bytef **) palloc(MAX_CHUNKS * sizeof(Bytef *));


    stream.next_in   = (Bytef *) VARDATA(source);
    stream.avail_in  = sourceLen;
    stream.avail_out = 0;

    stream.zalloc = zalloc;
    stream.zfree = zfree;
    stream.opaque = (voidpf)0;


    if(type == ENZLIBRAW) {
        window_bits = -window_bits;
    } else if(type == ENGZIP) {
        window_bits += 32;
    }

    inflateInit2(&stream, window_bits);
    do {
        if (stream.avail_out == 0) {
            chunks[chunkindex] = (Bytef *) palloc0(chunksize);
            stream.next_out  = chunks[chunkindex];
            stream.avail_out = chunksize;
            chunkindex++;
        }
        err = inflate(&stream, Z_NO_FLUSH);
    } while (err == Z_OK && chunkindex < MAX_CHUNKS);
    inflateEnd(&stream);

    //fill the postgresql datastructure
    dest = (struct varlena *) palloc0(stream.total_out + VARHDRSZ);

    for(int i= 0; i<chunkindex; i++) {
        memcpy(
            VARDATA(dest) + i * chunksize,
            chunks[i],
            i * chunksize < stream.total_out ? chunksize : i * chunksize - stream.total_out
        );
    }

    //tell postgres about actual size of the uncompressed data
    SET_VARSIZE(dest, stream.total_out + VARHDRSZ);
    return dest;
}

/*
 * Inflate a compressed version of a varlena datum.
 */
static struct varlena * PGCOMPRESSDecodeBrotli(struct varlena *source)
{
    const unsigned int MAX_CHUNKS = 1000;

    //data structure for the uncompressed data
    struct varlena *dest;

    const uint8_t * next_in;
    uLongf available_in;
    uLongf available_out;
    uint8_t * next_out;
    size_t total_out;
    int chunksize  = 1;
    int chunkindex = 0;
    uint8_t **chunks;
    BrotliDecoderResult result;
    BrotliDecoderState  *decoder;

    decoder = BrotliDecoderCreateInstance(
        &brotli_g_malloc_wrapper /*alloc_func*/,
        &brotli_g_free_wrapper /*free_func*/,
        NULL /*opaque*/
    );

    available_in = VARSIZE(source) - VARHDRSZ;

    available_out = 0;
    total_out = 0;


    chunks = (uint8_t **) palloc(MAX_CHUNKS * sizeof(uint8_t *));
    next_in = (const uint8_t *) VARDATA(source);
    do {
        chunks[chunkindex] = (uint8_t *) palloc0(chunksize);
        next_out = chunks[chunkindex];
        available_out = chunksize;
        chunkindex++;

        result = BrotliDecoderDecompressStream(
            decoder,
            &available_in,
            &next_in,
            &available_out,
            &next_out,
            &total_out
        );

    } while (result == BROTLI_DECODER_RESULT_NEEDS_MORE_OUTPUT && chunkindex < MAX_CHUNKS);

    //fill the postgresql datastructure
    dest = (struct varlena *) palloc0(total_out + VARHDRSZ);

    for(int i= 0; i<chunkindex; i++) {
        memcpy(
            VARDATA(dest) + i * chunksize,
            chunks[i],
            i * chunksize < total_out ? chunksize : i * chunksize - total_out
        );
    }

    //tell postgres about actual size of the uncompressed data
    SET_VARSIZE(dest, total_out + VARHDRSZ);
    return dest;
}
