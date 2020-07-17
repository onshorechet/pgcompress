--General Encode/Decode

--defaults to these are zlib and at its default compression
--to encode different types pass 0-3 as the first int argument
--zlib = 0; zlib_raw = 1; gzip = 2; br = 3;
--the last argument is the compression level
--for zlib - gzip the compression levels are 0-9
--for br it is 0-11 because 11 is louder
CREATE FUNCTION encode_compressed(text) RETURNS bytea
  AS 'pgcompress', 'pgcompress_encode_zlib_text'
  LANGUAGE C IMMUTABLE STRICT PARALLEL SAFE;
CREATE FUNCTION encode_compressed(text, int) RETURNS bytea
  AS 'pgcompress', 'pgcompress_encode_compressed_text'
  LANGUAGE C IMMUTABLE STRICT PARALLEL SAFE;
CREATE FUNCTION encode_compressed(text, int, int) RETURNS bytea
  AS 'pgcompress', 'pgcompress_encode_compressed_text'
  LANGUAGE C IMMUTABLE STRICT PARALLEL SAFE;

CREATE FUNCTION encode_compressed(bytea) RETURNS bytea
  AS 'pgcompress', 'pgcompress_encode_zlib_bytea'
  LANGUAGE C IMMUTABLE STRICT PARALLEL SAFE;
CREATE FUNCTION encode_compressed(bytea, int) RETURNS bytea
  AS 'pgcompress', 'pgcompress_encode_compressed_bytea'
  LANGUAGE C IMMUTABLE STRICT PARALLEL SAFE;
CREATE FUNCTION encode_compressed(bytea, int, int) RETURNS bytea
  AS 'pgcompress', 'pgcompress_encode_compressed_bytea'
  LANGUAGE C IMMUTABLE STRICT PARALLEL SAFE;

CREATE FUNCTION encode_compressed(jsonb) RETURNS bytea
  AS 'pgcompress', 'pgcompress_encode_zlib_jsonb'
  LANGUAGE C IMMUTABLE STRICT PARALLEL SAFE;
CREATE FUNCTION encode_compressed(jsonb, int) RETURNS bytea
  AS 'pgcompress', 'pgcompress_encode_compressed_jsonb'
  LANGUAGE C IMMUTABLE STRICT PARALLEL SAFE;
CREATE FUNCTION encode_compressed(jsonb, int, int) RETURNS bytea
  AS 'pgcompress', 'pgcompress_encode_compressed_jsonb'
  LANGUAGE C IMMUTABLE STRICT PARALLEL SAFE;

CREATE FUNCTION encode_compressed(json) RETURNS bytea
  AS 'pgcompress', 'pgcompress_encode_zlib_text'
  LANGUAGE C IMMUTABLE STRICT PARALLEL SAFE;
CREATE FUNCTION encode_compressed(json, int) RETURNS bytea
  AS 'pgcompress', 'pgcompress_encode_compressed_text'
  LANGUAGE C IMMUTABLE STRICT PARALLEL SAFE;
CREATE FUNCTION encode_compressed(json, int, int) RETURNS bytea
  AS 'pgcompress', 'pgcompress_encode_compressed_text'
  LANGUAGE C IMMUTABLE STRICT PARALLEL SAFE;






CREATE FUNCTION decode_compressed(bytea) RETURNS text
  AS 'pgcompress', 'pgcompress_decode_zlib_text'
  LANGUAGE C IMMUTABLE STRICT PARALLEL SAFE;
CREATE FUNCTION decode_compressed_bytea(bytea) RETURNS bytea
  AS 'pgcompress', 'pgcompress_decode_zlib_bytea'
  LANGUAGE C IMMUTABLE STRICT PARALLEL SAFE;
CREATE FUNCTION decode_compressed_json(bytea) RETURNS json
  AS 'pgcompress', 'pgcompress_decode_zlib_text'
  LANGUAGE C IMMUTABLE STRICT PARALLEL SAFE;
--CREATE FUNCTION decode_compressed_jsonb(bytea) RETURNS jsonb
--  AS 'pgcompress', 'pgcompress_decode_zlib_jsonb'
--  LANGUAGE C IMMUTABLE STRICT PARALLEL SAFE;
CREATE FUNCTION decode_compressed_jsonb(in_compressed bytea) RETURNS jsonb AS $$
BEGIN
    RETURN decode_compressed_json(in_compressed)::jsonb;
END; $$
LANGUAGE PLPGSQL IMMUTABLE PARALLEL SAFE;

CREATE FUNCTION decode_compressed(bytea, int) RETURNS text
  AS 'pgcompress', 'pgcompress_decode_compressed_text'
  LANGUAGE C IMMUTABLE STRICT PARALLEL SAFE;
CREATE FUNCTION decode_compressed_bytea(bytea, int) RETURNS bytea
  AS 'pgcompress', 'pgcompress_decode_compressed_bytea'
  LANGUAGE C IMMUTABLE STRICT PARALLEL SAFE;
CREATE FUNCTION decode_compressed_json(bytea, int) RETURNS json
  AS 'pgcompress', 'pgcompress_decode_compressed_text'
  LANGUAGE C IMMUTABLE STRICT PARALLEL SAFE;
--CREATE FUNCTION decode_compressed_jsonb(bytea, int) RETURNS jsonb
--  AS 'pgcompress', 'pgcompress_decode_compressed_jsonb'
--  LANGUAGE C IMMUTABLE STRICT PARALLEL SAFE;
CREATE FUNCTION decode_compressed_jsonb(in_compressed bytea, in_type int) RETURNS jsonb AS $$
BEGIN
    RETURN decode_compressed_json(in_compressed, in_type)::jsonb;
END; $$
LANGUAGE PLPGSQL IMMUTABLE PARALLEL SAFE;



--Zlib functions ie deflate/inflate
CREATE FUNCTION encode_zlib(text) RETURNS bytea
  AS 'pgcompress', 'pgcompress_encode_zlib_text'
  LANGUAGE C IMMUTABLE STRICT PARALLEL SAFE;
CREATE FUNCTION encode_zlib(text, int) RETURNS bytea
  AS 'pgcompress', 'pgcompress_encode_zlib_text'
  LANGUAGE C IMMUTABLE STRICT PARALLEL SAFE;

CREATE FUNCTION encode_zlib(bytea) RETURNS bytea
  AS 'pgcompress', 'pgcompress_encode_zlib_bytea'
  LANGUAGE C IMMUTABLE STRICT PARALLEL SAFE;
CREATE FUNCTION encode_zlib(bytea, int) RETURNS bytea
  AS 'pgcompress', 'pgcompress_encode_zlib_bytea'
  LANGUAGE C IMMUTABLE STRICT PARALLEL SAFE;

CREATE FUNCTION encode_zlib(jsonb) RETURNS bytea
  AS 'pgcompress', 'pgcompress_encode_zlib_jsonb'
  LANGUAGE C IMMUTABLE STRICT PARALLEL SAFE;
CREATE FUNCTION encode_zlib(jsonb, int) RETURNS bytea
  AS 'pgcompress', 'pgcompress_encode_zlib_jsonb'
  LANGUAGE C IMMUTABLE STRICT PARALLEL SAFE;

CREATE FUNCTION encode_zlib(json) RETURNS bytea
  AS 'pgcompress', 'pgcompress_encode_zlib_text'
  LANGUAGE C IMMUTABLE STRICT PARALLEL SAFE;
CREATE FUNCTION encode_zlib(json, int) RETURNS bytea
  AS 'pgcompress', 'pgcompress_encode_zlib_text'
  LANGUAGE C IMMUTABLE STRICT PARALLEL SAFE;

CREATE FUNCTION decode_zlib(bytea) RETURNS text
  AS 'pgcompress', 'pgcompress_decode_zlib_text'
  LANGUAGE C IMMUTABLE STRICT PARALLEL SAFE;
CREATE FUNCTION decode_zlib_bytea(bytea) RETURNS bytea
  AS 'pgcompress', 'pgcompress_decode_zlib_bytea'
  LANGUAGE C IMMUTABLE STRICT PARALLEL SAFE;
CREATE FUNCTION decode_zlib_json(bytea) RETURNS json
  AS 'pgcompress', 'pgcompress_decode_zlib_text'
  LANGUAGE C IMMUTABLE STRICT PARALLEL SAFE;
--CREATE FUNCTION decode_zlib_jsonb(bytea) RETURNS jsonb
--  AS 'pgcompress', 'pgcompress_decode_zlib_jsonb'
--  LANGUAGE C IMMUTABLE STRICT PARALLEL SAFE;
CREATE FUNCTION decode_zlib_jsonb(in_compressed bytea) RETURNS jsonb AS $$
BEGIN
    RETURN decode_zlib_json(in_compressed)::jsonb;
END; $$
LANGUAGE PLPGSQL IMMUTABLE PARALLEL SAFE;





--Zlib RAW functions ie. deflate/inflate without the header and trailer
CREATE FUNCTION encode_zlib_raw(text) RETURNS bytea
  AS 'pgcompress', 'pgcompress_encode_zlib_raw_text'
  LANGUAGE C IMMUTABLE STRICT PARALLEL SAFE;
CREATE FUNCTION encode_zlib_raw(text, int) RETURNS bytea
  AS 'pgcompress', 'pgcompress_encode_zlib_raw_text'
  LANGUAGE C IMMUTABLE STRICT PARALLEL SAFE;

CREATE FUNCTION encode_zlib_raw(bytea) RETURNS bytea
  AS 'pgcompress', 'pgcompress_encode_zlib_raw_bytea'
  LANGUAGE C IMMUTABLE STRICT PARALLEL SAFE;
CREATE FUNCTION encode_zlib_raw(bytea, int) RETURNS bytea
  AS 'pgcompress', 'pgcompress_encode_zlib_raw_bytea'
  LANGUAGE C IMMUTABLE STRICT PARALLEL SAFE;

CREATE FUNCTION encode_zlib_raw(jsonb) RETURNS bytea
  AS 'pgcompress', 'pgcompress_encode_zlib_raw_jsonb'
  LANGUAGE C IMMUTABLE STRICT PARALLEL SAFE;
CREATE FUNCTION encode_zlib_raw(jsonb, int) RETURNS bytea
  AS 'pgcompress', 'pgcompress_encode_zlib_raw_jsonb'
  LANGUAGE C IMMUTABLE STRICT PARALLEL SAFE;

CREATE FUNCTION encode_zlib_raw(json) RETURNS bytea
  AS 'pgcompress', 'pgcompress_encode_zlib_raw_text'
  LANGUAGE C IMMUTABLE STRICT PARALLEL SAFE;
CREATE FUNCTION encode_zlib_raw(json, int) RETURNS bytea
  AS 'pgcompress', 'pgcompress_encode_zlib_raw_text'
  LANGUAGE C IMMUTABLE STRICT PARALLEL SAFE;

CREATE FUNCTION decode_zlib_raw(bytea) RETURNS text
  AS 'pgcompress', 'pgcompress_decode_zlib_raw_text'
  LANGUAGE C IMMUTABLE STRICT PARALLEL SAFE;
CREATE FUNCTION decode_zlib_raw_bytea(bytea) RETURNS bytea
  AS 'pgcompress', 'pgcompress_decode_zlib_raw_bytea'
  LANGUAGE C IMMUTABLE STRICT PARALLEL SAFE;
CREATE FUNCTION decode_zlib_raw_json(bytea) RETURNS json
  AS 'pgcompress', 'pgcompress_decode_zlib_raw_text'
  LANGUAGE C IMMUTABLE STRICT PARALLEL SAFE;
--CREATE FUNCTION decode_zlib_raw_jsonb(bytea) RETURNS jsonb
--  AS 'pgcompress', 'pgcompress_decode_zlib_raw_jsonb'
--  LANGUAGE C IMMUTABLE STRICT PARALLEL SAFE;
CREATE FUNCTION decode_zlib_raw_jsonb(in_compressed bytea) RETURNS jsonb AS $$
BEGIN
    RETURN decode_zlib_raw_json(in_compressed)::jsonb;
END; $$
LANGUAGE PLPGSQL IMMUTABLE PARALLEL SAFE;



--Gzip functions
CREATE FUNCTION encode_gzip(text) RETURNS bytea
  AS 'pgcompress', 'pgcompress_encode_gzip_text'
  LANGUAGE C IMMUTABLE STRICT PARALLEL SAFE;
CREATE FUNCTION encode_gzip(text, int) RETURNS bytea
  AS 'pgcompress', 'pgcompress_encode_gzip_text'
  LANGUAGE C IMMUTABLE STRICT PARALLEL SAFE;

CREATE FUNCTION encode_gzip(bytea) RETURNS bytea
  AS 'pgcompress', 'pgcompress_encode_gzip_bytea'
  LANGUAGE C IMMUTABLE STRICT PARALLEL SAFE;
CREATE FUNCTION encode_gzip(bytea, int) RETURNS bytea
  AS 'pgcompress', 'pgcompress_encode_gzip_bytea'
  LANGUAGE C IMMUTABLE STRICT PARALLEL SAFE;

CREATE FUNCTION encode_gzip(jsonb) RETURNS bytea
  AS 'pgcompress', 'pgcompress_encode_gzip_jsonb'
  LANGUAGE C IMMUTABLE STRICT PARALLEL SAFE;
CREATE FUNCTION encode_gzip(jsonb, int) RETURNS bytea
  AS 'pgcompress', 'pgcompress_encode_gzip_jsonb'
  LANGUAGE C IMMUTABLE STRICT PARALLEL SAFE;

CREATE FUNCTION encode_gzip(json) RETURNS bytea
  AS 'pgcompress', 'pgcompress_encode_gzip_text'
  LANGUAGE C IMMUTABLE STRICT PARALLEL SAFE;
CREATE FUNCTION encode_gzip(json, int) RETURNS bytea
  AS 'pgcompress', 'pgcompress_encode_gzip_text'
  LANGUAGE C IMMUTABLE STRICT PARALLEL SAFE;

CREATE FUNCTION decode_gzip(bytea) RETURNS text
  AS 'pgcompress', 'pgcompress_decode_gzip_text'
  LANGUAGE C IMMUTABLE STRICT PARALLEL SAFE;
CREATE FUNCTION decode_gzip_bytea(bytea) RETURNS bytea
  AS 'pgcompress', 'pgcompress_decode_gzip_bytea'
  LANGUAGE C IMMUTABLE STRICT PARALLEL SAFE;
CREATE FUNCTION decode_gzip_json(bytea) RETURNS json
  AS 'pgcompress', 'pgcompress_decode_gzip_text'
  LANGUAGE C IMMUTABLE STRICT PARALLEL SAFE;
--CREATE FUNCTION decode_gzip_jsonb(bytea) RETURNS jsonb
--  AS 'pgcompress', 'pgcompress_decode_gzip_jsonb'
--  LANGUAGE C IMMUTABLE STRICT PARALLEL SAFE;
CREATE FUNCTION decode_gzip_jsonb(in_compressed bytea) RETURNS jsonb AS $$
BEGIN
    RETURN decode_gzip_json(in_compressed)::jsonb;
END; $$
LANGUAGE PLPGSQL IMMUTABLE PARALLEL SAFE;



--Brotli functions
CREATE FUNCTION encode_br(text) RETURNS bytea
  AS 'pgcompress', 'pgcompress_encode_br_text'
  LANGUAGE C IMMUTABLE STRICT PARALLEL SAFE;
CREATE FUNCTION encode_br(text, int) RETURNS bytea
  AS 'pgcompress', 'pgcompress_encode_br_text'
  LANGUAGE C IMMUTABLE STRICT PARALLEL SAFE;

CREATE FUNCTION encode_br(bytea) RETURNS bytea
  AS 'pgcompress', 'pgcompress_encode_br_bytea'
  LANGUAGE C IMMUTABLE STRICT PARALLEL SAFE;
CREATE FUNCTION encode_br(bytea, int) RETURNS bytea
  AS 'pgcompress', 'pgcompress_encode_br_bytea'
  LANGUAGE C IMMUTABLE STRICT PARALLEL SAFE;

CREATE FUNCTION encode_br(jsonb) RETURNS bytea
  AS 'pgcompress', 'pgcompress_encode_br_jsonb'
  LANGUAGE C IMMUTABLE STRICT PARALLEL SAFE;
CREATE FUNCTION encode_br(jsonb, int) RETURNS bytea
  AS 'pgcompress', 'pgcompress_encode_br_jsonb'
  LANGUAGE C IMMUTABLE STRICT PARALLEL SAFE;

CREATE FUNCTION encode_br(json) RETURNS bytea
  AS 'pgcompress', 'pgcompress_encode_br_text'
  LANGUAGE C IMMUTABLE STRICT PARALLEL SAFE;
CREATE FUNCTION encode_br(json, int) RETURNS bytea
  AS 'pgcompress', 'pgcompress_encode_br_text'
  LANGUAGE C IMMUTABLE STRICT PARALLEL SAFE;


CREATE FUNCTION decode_br(bytea) RETURNS text
  AS 'pgcompress', 'pgcompress_decode_br_text'
  LANGUAGE C IMMUTABLE STRICT PARALLEL SAFE;
CREATE FUNCTION decode_br_bytea(bytea) RETURNS bytea
  AS 'pgcompress', 'pgcompress_decode_br_bytea'
  LANGUAGE C IMMUTABLE STRICT PARALLEL SAFE;
CREATE FUNCTION decode_br_json(bytea) RETURNS json
  AS 'pgcompress', 'pgcompress_decode_br_text'
  LANGUAGE C IMMUTABLE STRICT PARALLEL SAFE;
--CREATE FUNCTION decode_br_jsonb(bytea) RETURNS jsonb
--  AS 'pgcompress', 'pgcompress_decode_br_jsonb'
--  LANGUAGE C IMMUTABLE STRICT PARALLEL SAFE;
CREATE FUNCTION decode_br_jsonb(in_compressed bytea) RETURNS jsonb AS $$
BEGIN
    RETURN decode_br_json(in_compressed)::jsonb;
END; $$
LANGUAGE PLPGSQL IMMUTABLE PARALLEL SAFE;

