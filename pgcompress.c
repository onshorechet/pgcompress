#include "pgcompress.h"

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
static struct varlena * PGCOMPRESSDeflate(struct varlena *source, bool gzip)
{

    // zlib struct
    z_stream stream;

    //data structure for the compressed data
    struct varlena *dest;

    /* conservative upper bound for compressed data */
    uLong complen;
    complen = VARSIZE(source) + ((VARSIZE(source) + 7) >> 3) + ((VARSIZE(source) + 63) >> 6) + 5 + 18;

    // only allow 200MB of memory consumption
    //if (complen > 200000000) {
    //    ereport(ERROR, (errcode(ERRCODE_FEATURE_NOT_SUPPORTED), errmsg("Deflate limited to 200MB of memory.")));
    //    dest = (struct varlena *) palloc(VARHDRSZ);
    //    SET_VARSIZE(dest, VARHDRSZ);

    //    //return the dest pointer
    //    return dest;
    //}

    dest = (struct varlena *) palloc0(complen + VARHDRSZ);

    // zlib deflate object
    stream.zalloc = zalloc;
    stream.zfree  = zfree;
    stream.opaque = Z_NULL;

    stream.next_in   = (Bytef *) VARDATA(source); // input char array
    stream.avail_in  = VARSIZE(source) - VARHDRSZ;
    stream.avail_out = complen;
    stream.next_out  = (Bytef *) VARDATA(dest); // output char array

    deflateInit2(&stream, Z_DEFAULT_COMPRESSION, Z_DEFLATED, gzip ? MAX_WBITS + 16: MAX_WBITS, MAX_MEM_LEVEL, Z_DEFAULT_STRATEGY);


    deflate(&stream, Z_FINISH);

    deflateEnd(&stream);

    //tell postgres about actual size of the compressed data
    SET_VARSIZE(dest,  stream.total_out + VARHDRSZ);

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

    z_stream stream;
    int err;
    long unsigned int i = 2;
    uLongf sourceLen = VARSIZE(source) - VARHDRSZ;

    stream.next_in = (Bytef *) VARDATA(source);
    stream.avail_in = sourceLen;

    dest = palloc0(20 + VARHDRSZ);
    stream.next_out  = (Bytef *) VARDATA(dest);
    stream.avail_out = 20;

    stream.zalloc = zalloc;
    stream.zfree = zfree;
    stream.opaque = (voidpf)0;

    //15+32 = detect if gzip or deflate via headers
    inflateInit2(&stream, 15+32);

    do {
        if (stream.avail_out == 0) {
            dest             = repalloc(dest, sourceLen * i + VARHDRSZ);
            stream.next_out  = (Bytef *) (&(VARDATA(dest))[sourceLen * i]);
            stream.avail_out = sourceLen;
            i++;
        }
        err = inflate(&stream, Z_SYNC_FLUSH);
    } while (err == Z_OK);

    //tell postgres about actual size of the uncompressed data
    SET_VARSIZE(dest, stream.total_out + VARHDRSZ);

    inflateEnd(&stream);

    return dest;
}
