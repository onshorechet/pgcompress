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
    if(type < 0 || type > 3) {
        type = 0;
    }

    if(type == ENBR) {
        level = BROTLI_DEFAULT_QUALITY;
    }

    if (PG_NARGS() == 3) {
        level = PG_GETARG_INT32(2);
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
        PG_RETURN_BYTEA_P(PGCOMPRESSDeflate((Bytef *) VARDATA(source), VARSIZE(source) - VARHDRSZ, type, level));
    } else {
        PG_RETURN_BYTEA_P(PGCOMPRESSEncodeBrotli((Bytef *) VARDATA(source), VARSIZE(source) - VARHDRSZ, level));
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

    int level = Z_DEFAULT_COMPRESSION;

    //get the default or provided compression
    int type  = PG_GETARG_INT32(1);
    if(type < 0 || type > 3) {
        type = 0;
    }

    if(type == ENBR) {
        level = BROTLI_DEFAULT_QUALITY;
    }

    if (PG_NARGS() == 3) {
        level = PG_GETARG_INT32(2);
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
        PG_RETURN_BYTEA_P(PGCOMPRESSDeflate((Bytef *) VARDATA(source), VARSIZE(source) - VARHDRSZ, type, level));
    } else {
        PG_RETURN_BYTEA_P(PGCOMPRESSEncodeBrotli((Bytef *) VARDATA(source), VARSIZE(source) - VARHDRSZ, level));
    }
}


/*
 * Create a compressed version of a bytea datum
 * return bytea
 */
Datum pgcompress_encode_compressed_jsonb(PG_FUNCTION_ARGS)
{
    // get the source bytea
    StringInfo source = JsonbToStringInfo(PG_GETARG_JSONB_P(0));

    int level = Z_DEFAULT_COMPRESSION;

    //get the default or provided compression
    int type  = PG_GETARG_INT32(1);
    if(type < 0 || type > 3) {
        type = 0;
    }

    if(type == ENBR) {
        level = BROTLI_DEFAULT_QUALITY;
    }

    if (PG_NARGS() == 3) {
        level = PG_GETARG_INT32(2);
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
        PG_RETURN_BYTEA_P(PGCOMPRESSDeflate((Bytef *) source->data, source->len, type, level));
    } else {
        PG_RETURN_BYTEA_P(PGCOMPRESSEncodeBrotli((Bytef *) source->data, source->len, level));
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


/*
 * Inflate a compressed version of bytea into bytea.
 */
//Datum pgcompress_decode_compressed_jsonb(PG_FUNCTION_ARGS)
//{
//    // get the source bytea of compressed data
//    bytea *source = PG_GETARG_BYTEA_P(0);
//
//    //get the default or provided compression
//    int type  = PG_GETARG_INT32(1);
//    if(type < 0 || type > 3) {
//        type = 0;
//    }
//
//    if(type != ENBR) {
//        // return the uncompressed data as a text string
//        PG_RETURN_TEXT_P(PGCOMPRESSInflate((struct varlena *) source, type));
//    } else {
//        PG_RETURN_TEXT_P(PGCOMPRESSDecodeBrotli((struct varlena *) source));
//    }
//}


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
    PG_RETURN_BYTEA_P(PGCOMPRESSDeflate((Bytef *) VARDATA(source), VARSIZE(source) - VARHDRSZ, ENZLIB, level));
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
    PG_RETURN_BYTEA_P(PGCOMPRESSDeflate((Bytef *) VARDATA(source), VARSIZE(source) - VARHDRSZ, ENZLIB, level));
}

/*
 * Create a compressed version of a bytea datum
 * return bytea
 */
Datum pgcompress_encode_zlib_jsonb(PG_FUNCTION_ARGS)
{
    // get the source jsonb
    StringInfo source = JsonbToStringInfo(PG_GETARG_JSONB_P(0));

    //get the default or provided compression
    int level = Z_DEFAULT_COMPRESSION;
    if (PG_NARGS() == 2) {
        level = PG_GETARG_INT32(1);
    }

    if(level < 0 || level > 9) {
        level = Z_DEFAULT_COMPRESSION;
    }

    // compress and return the bytea to postgress
    PG_RETURN_BYTEA_P(PGCOMPRESSDeflate((Bytef *) source->data, source->len, ENZLIB, level));
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
    PG_RETURN_BYTEA_P(PGCOMPRESSDeflate((Bytef *) VARDATA(source), VARSIZE(source) - VARHDRSZ, ENZLIBRAW, level));
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
    PG_RETURN_BYTEA_P(PGCOMPRESSDeflate((Bytef *) VARDATA(source), VARSIZE(source) - VARHDRSZ, ENZLIBRAW, level));
}

/*
 * Create a compressed version of a bytea datum
 * return bytea
 */
Datum pgcompress_encode_zlib_raw_jsonb(PG_FUNCTION_ARGS)
{
    // get the source jsonb
    StringInfo source = JsonbToStringInfo(PG_GETARG_JSONB_P(0));

    //get the default or provided compression
    int level = Z_DEFAULT_COMPRESSION;
    if (PG_NARGS() == 2) {
        level = PG_GETARG_INT32(1);
    }

    if(level < 0 || level > 9) {
        level = Z_DEFAULT_COMPRESSION;
    }

    // compress and return the bytea to postgress
    PG_RETURN_BYTEA_P(PGCOMPRESSDeflate((Bytef *) source->data, source->len, ENZLIBRAW, level));
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
    PG_RETURN_BYTEA_P(PGCOMPRESSDeflate((Bytef *) VARDATA(source), VARSIZE(source) - VARHDRSZ, ENGZIP, level));
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
    PG_RETURN_BYTEA_P(PGCOMPRESSDeflate((Bytef *) VARDATA(source), VARSIZE(source) - VARHDRSZ, ENGZIP, level));
}


/*
 * Create a compressed version of a bytea datum
 * return bytea
 */
Datum pgcompress_encode_gzip_jsonb(PG_FUNCTION_ARGS)
{
    // get the source jsonb
    StringInfo source = JsonbToStringInfo(PG_GETARG_JSONB_P(0));

    //get the default or provided compression
    int level = Z_DEFAULT_COMPRESSION;
    if (PG_NARGS() == 2) {
        level = PG_GETARG_INT32(1);
    }

    if(level < 0 || level > 9) {
        level = Z_DEFAULT_COMPRESSION;
    }

    // compress and return the bytea to postgress
    PG_RETURN_BYTEA_P(PGCOMPRESSDeflate((Bytef *) source->data, source->len, ENGZIP, level));
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
    PG_RETURN_BYTEA_P(PGCOMPRESSEncodeBrotli((Bytef *) VARDATA(source), VARSIZE(source) - VARHDRSZ, level));
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
    int level = BROTLI_DEFAULT_QUALITY;
    if (PG_NARGS() == 2) {
        level = PG_GETARG_INT32(1);
    }

    if(level < BROTLI_MIN_QUALITY || level > BROTLI_MAX_QUALITY) {
        level = BROTLI_DEFAULT_QUALITY;
    }

    // compress and return the bytea to postgress
    PG_RETURN_BYTEA_P(PGCOMPRESSEncodeBrotli((Bytef *) VARDATA(source), VARSIZE(source) - VARHDRSZ, level));
}


/*
 * Create a compressed version of a bytea datum
 * return bytea
 */
Datum pgcompress_encode_br_jsonb(PG_FUNCTION_ARGS)
{
    // get the source jsonb
    StringInfo source = JsonbToStringInfo(PG_GETARG_JSONB_P(0));

    //get the default or provided compression
    int level = BROTLI_DEFAULT_QUALITY;
    if (PG_NARGS() == 2) {
        level = PG_GETARG_INT32(1);
    }

    if(level < BROTLI_MIN_QUALITY || level > BROTLI_MAX_QUALITY) {
        level = BROTLI_DEFAULT_QUALITY;
    }


    // compress and return the bytea to postgress
    PG_RETURN_BYTEA_P(PGCOMPRESSEncodeBrotli((Bytef *) source->data, source->len, level));
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
    PG_RETURN_BYTEA_P(PointerGetDatum(PGCOMPRESSInflate((struct varlena *) source, ENZLIB)));
}


/*
 * Inflate a compressed version of bytea into bytea.
 */
//Datum pgcompress_decode_zlib_jsonb(PG_FUNCTION_ARGS)
//{
//    // get the source bytea of compressed data
//    bytea *source = PG_GETARG_BYTEA_P(0);
//
//    // return the uncompressed data as a bytea
//    PG_RETURN_BYTEA_P(PGCOMPRESSInflate((struct varlena *) source, ENZLIB));
//
//    //JsonbFromCString
//    return JsonbFromCString((Bytef *) VARDATA(source), VARSIZE(source) - VARHDRSZ);
//}


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
static struct varlena * PGCOMPRESSDeflate(Bytef * source, int length, int type, int level)
{

    // zlib struct
    z_stream stream;

    //data structure for the compressed data
    struct varlena *dest;

    //used to swithc types
    int window_bits = MAX_WBITS;

    /* conservative upper bound for compressed data */
    uLong complen;
    complen = length + ((length + 7) >> 3) + ((length + 63) >> 6) + 5 + 18;

    dest = (struct varlena *) palloc0(complen + VARHDRSZ);

    // zlib deflate object
    stream.zalloc = zalloc;
    stream.zfree  = zfree;
    stream.opaque = Z_NULL;

    stream.next_in   = source; // input char array
    stream.avail_in  = length;
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
    //if the input is too small br will not create vars
    //for all of the memory it tries to clear
    if(address) {
        pfree(address);
    }
}

/*
 * Create a compressed version of a varlena datum
 */
static struct varlena * PGCOMPRESSEncodeBrotli(Bytef * source, int length, int level)
{
    //data structure for the compressed data
    struct varlena *dest;

    /* conservative upper bound for compressed data */
    uLong complen;

    complen = BrotliEncoderMaxCompressedSize(length) + 1;

    dest = (struct varlena *) palloc0(complen + VARHDRSZ);

    BrotliEncoderCompress(
        level,
        BROTLI_DEFAULT_WINDOW,
        BROTLI_DEFAULT_MODE,
        length,
        source,
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
    //data structure for the uncompressed data
    struct varlena *dest;

    //used to swithc types
    int window_bits = MAX_WBITS;

    z_stream stream;
    int err;
    uLongf sourceLen = VARSIZE(source) - VARHDRSZ;

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
            chunks[chunkindex] = (Bytef *) palloc0(CHUNKSIZE);
            stream.next_out  = chunks[chunkindex];
            stream.avail_out = CHUNKSIZE;
            chunkindex++;
        }
        err = inflate(&stream, Z_NO_FLUSH);
    } while (err == Z_OK && chunkindex < MAX_CHUNKS);
    inflateEnd(&stream);

    //fill the postgresql datastructure
    dest = (struct varlena *) palloc0(stream.total_out + VARHDRSZ);
    if (stream.total_out < CHUNKSIZE) {
        memcpy(
            VARDATA(dest),
            chunks[0],
            stream.total_out
        );
        pfree(chunks[0]);
    } else {
        for(int i= 0; i<chunkindex; i++) {
            memcpy(
                VARDATA(dest) + i * CHUNKSIZE,
                chunks[i],
                i * CHUNKSIZE < stream.total_out ? CHUNKSIZE : i * CHUNKSIZE - stream.total_out
            );
            pfree(chunks[i]);
        }
    }
    pfree(chunks);

    //tell postgres about actual size of the uncompressed data
    SET_VARSIZE(dest, stream.total_out + VARHDRSZ);
    return dest;
}

/*
 * Inflate a compressed version of a varlena datum.
 */
static struct varlena * PGCOMPRESSDecodeBrotli(struct varlena *source)
{
    //data structure for the uncompressed data
    struct varlena *dest;

    const uint8_t * next_in;
    uLongf available_in;
    uLongf available_out;
    uint8_t * next_out;
    size_t total_out;
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
        chunks[chunkindex] = (uint8_t *) palloc0(CHUNKSIZE);
        next_out = chunks[chunkindex];
        available_out = CHUNKSIZE;
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

    if (total_out < CHUNKSIZE) {
        memcpy(
            VARDATA(dest),
            chunks[0],
            total_out
        );
        pfree(chunks[0]);
    } else {
        for(int i= 0; i<chunkindex; i++) {
            memcpy(
                VARDATA(dest) + i * CHUNKSIZE,
                chunks[i],
                i * CHUNKSIZE < total_out ? CHUNKSIZE : i * CHUNKSIZE - total_out
            );
            pfree(chunks[i]);
        }
    }

    pfree(chunks);

    //tell postgres about actual size of the uncompressed data
    SET_VARSIZE(dest, total_out + VARHDRSZ);
    return dest;
}

/*
 * SQL function jsonb_pretty (jsonb)
 *
 * Converts jsonb to string and length for compression
 *Jsonb	   *jb = PG_GETARG_JSONB_P(0);
 * str->data, str->len;
 */
StringInfo JsonbToStringInfo(Jsonb *jb)
{
	StringInfo str = makeStringInfo();

	JsonbToCString(str, &jb->root, VARSIZE(jb));

	return str;
}
