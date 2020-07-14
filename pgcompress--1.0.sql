--General Encode/Decode

CREATE FUNCTION encode_compressed(text) RETURNS bytea
  AS 'pgcompress', 'pgcompress_encode_zlib_text'
  LANGUAGE C STRICT;
CREATE FUNCTION encode_compressed(text, int) RETURNS bytea
  AS 'pgcompress', 'pgcompress_encode_compressed_text'
  LANGUAGE C STRICT;
CREATE FUNCTION encode_compressed(text, int, int) RETURNS bytea
  AS 'pgcompress', 'pgcompress_encode_compressed_text'
  LANGUAGE C STRICT;

CREATE FUNCTION encode_compressed(bytea) RETURNS bytea
  AS 'pgcompress', 'pgcompress_encode_zlib_bytea'
  LANGUAGE C STRICT;
CREATE FUNCTION encode_compressed(bytea, int) RETURNS bytea
  AS 'pgcompress', 'pgcompress_encode_compressed_bytea'
  LANGUAGE C STRICT;
CREATE FUNCTION encode_compressed(bytea, int, int) RETURNS bytea
  AS 'pgcompress', 'pgcompress_encode_compressed_bytea'
  LANGUAGE C STRICT;


CREATE FUNCTION decode_compressed(bytea) RETURNS text
  AS 'pgcompress', 'pgcompress_decode_zlib_text'
  LANGUAGE C STRICT;
CREATE FUNCTION decode_compressed_bytea(bytea) RETURNS bytea
  AS 'pgcompress', 'pgcompress_decode_zlib_bytea'
  LANGUAGE C STRICT;

CREATE FUNCTION decode_compressed(bytea, int) RETURNS text
  AS 'pgcompress', 'pgcompress_decode_compressed_text'
  LANGUAGE C STRICT;
CREATE FUNCTION decode_compressed_bytea(bytea, int) RETURNS bytea
  AS 'pgcompress', 'pgcompress_decode_compressed_bytea'
  LANGUAGE C STRICT;


--Zlib functions ie deflate/inflate
CREATE FUNCTION encode_zlib(text) RETURNS bytea
  AS 'pgcompress', 'pgcompress_encode_zlib_text'
  LANGUAGE C STRICT;
CREATE FUNCTION encode_zlib(text, int) RETURNS bytea
  AS 'pgcompress', 'pgcompress_encode_zlib_text'
  LANGUAGE C STRICT;
CREATE FUNCTION encode_zlib(bytea) RETURNS bytea
  AS 'pgcompress', 'pgcompress_encode_zlib_bytea'
  LANGUAGE C STRICT;
CREATE FUNCTION encode_zlib(bytea, int) RETURNS bytea
  AS 'pgcompress', 'pgcompress_encode_zlib_bytea'
  LANGUAGE C STRICT;

CREATE FUNCTION decode_zlib(bytea) RETURNS text
  AS 'pgcompress', 'pgcompress_decode_zlib_text'
  LANGUAGE C STRICT;
CREATE FUNCTION decode_zlib_bytea(bytea) RETURNS bytea
  AS 'pgcompress', 'pgcompress_decode_zlib_bytea'
  LANGUAGE C STRICT;


--Zlib RAW functions ie. deflate/inflate without the header and trailer
CREATE FUNCTION encode_zlib_raw(text) RETURNS bytea
  AS 'pgcompress', 'pgcompress_encode_zlib_raw_text'
  LANGUAGE C STRICT;
CREATE FUNCTION encode_zlib_raw(text, int) RETURNS bytea
  AS 'pgcompress', 'pgcompress_encode_zlib_raw_text'
  LANGUAGE C STRICT;
CREATE FUNCTION encode_zlib_raw(bytea) RETURNS bytea
  AS 'pgcompress', 'pgcompress_encode_zlib_bytea'
  LANGUAGE C STRICT;
CREATE FUNCTION encode_zlib_raw(bytea, int) RETURNS bytea
  AS 'pgcompress', 'pgcompress_encode_zlib_bytea'
  LANGUAGE C STRICT;

CREATE FUNCTION decode_zlib_raw(bytea) RETURNS text
  AS 'pgcompress', 'pgcompress_decode_zlib_raw_text'
  LANGUAGE C STRICT;
CREATE FUNCTION decode_zlib_raw_bytea(bytea) RETURNS bytea
  AS 'pgcompress', 'pgcompress_decode_zlib_raw_bytea'
  LANGUAGE C STRICT;


--Gzip functions
CREATE FUNCTION encode_gzip(text) RETURNS bytea
  AS 'pgcompress', 'pgcompress_encode_gzip_text'
  LANGUAGE C STRICT;
CREATE FUNCTION encode_gzip(text, int) RETURNS bytea
  AS 'pgcompress', 'pgcompress_encode_gzip_text'
  LANGUAGE C STRICT;
CREATE FUNCTION encode_gzip(bytea) RETURNS bytea
  AS 'pgcompress', 'pgcompress_encode_gzip_bytea'
  LANGUAGE C STRICT;
CREATE FUNCTION encode_gzip(bytea, int) RETURNS bytea
  AS 'pgcompress', 'pgcompress_encode_gzip_bytea'
  LANGUAGE C STRICT;

CREATE FUNCTION decode_gzip(bytea) RETURNS text
  AS 'pgcompress', 'pgcompress_decode_gzip_text'
  LANGUAGE C STRICT;
CREATE FUNCTION decode_gzip_bytea(bytea) RETURNS bytea
  AS 'pgcompress', 'pgcompress_decode_gzip_bytea'
  LANGUAGE C STRICT;



--Brotli functions
CREATE FUNCTION encode_br(text) RETURNS bytea
  AS 'pgcompress', 'pgcompress_encode_br_text'
  LANGUAGE C STRICT;
CREATE FUNCTION encode_br(text, int) RETURNS bytea
  AS 'pgcompress', 'pgcompress_encode_br_text'
  LANGUAGE C STRICT;
CREATE FUNCTION encode_br(bytea) RETURNS bytea
  AS 'pgcompress', 'pgcompress_encode_br_bytea'
  LANGUAGE C STRICT;
CREATE FUNCTION encode_br(bytea, int) RETURNS bytea
  AS 'pgcompress', 'pgcompress_encode_br_bytea'
  LANGUAGE C STRICT;


CREATE FUNCTION decode_br(bytea) RETURNS text
  AS 'pgcompress', 'pgcompress_decode_br_text'
  LANGUAGE C STRICT;
CREATE FUNCTION decode_br_bytea(bytea) RETURNS bytea
  AS 'pgcompress', 'pgcompress_decode_br_bytea'
  LANGUAGE C STRICT;

