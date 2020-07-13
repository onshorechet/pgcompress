CREATE FUNCTION deflate(bytea) RETURNS bytea
  AS 'pgcompress', 'pgcompress_deflate_bytea'
  LANGUAGE C STRICT;


CREATE FUNCTION deflate(text) RETURNS bytea
  AS 'pgcompress', 'pgcompress_deflate_text'
  LANGUAGE C STRICT;


CREATE FUNCTION gzip(bytea) RETURNS bytea
  AS 'pgcompress', 'pgcompress_gzip_bytea'
  LANGUAGE C STRICT;


CREATE FUNCTION gzip(text) RETURNS bytea
  AS 'pgcompress', 'pgcompress_gzip_text'
  LANGUAGE C STRICT;


CREATE FUNCTION inflate(bytea) RETURNS text
  AS 'pgcompress', 'pgcompress_inflate_text'
  LANGUAGE C STRICT;


CREATE FUNCTION inflate_bytea(bytea) RETURNS bytea
  AS 'pgcompress', 'pgcompress_inflate_bytea'
  LANGUAGE C STRICT;
