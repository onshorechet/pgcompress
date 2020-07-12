CREATE FUNCTION geodistancec(alat double precision, alng double precision, blat double precision, blng double precision) RETURNS double precision
  AS 'pgos', 'pgos_geodistance_double'
  LANGUAGE C STRICT;


CREATE FUNCTION geodistancec(alat real, alng real, blat real, blng real) RETURNS real
  AS 'pgos', 'pgos_geodistance_real'
  LANGUAGE C STRICT;


CREATE FUNCTION deflate(bytea) RETURNS bytea
  AS 'pgos', 'pgos_deflate_bytea'
  LANGUAGE C STRICT;


CREATE FUNCTION deflate(text) RETURNS bytea
  AS 'pgos', 'pgos_deflate_text'
  LANGUAGE C STRICT;


CREATE FUNCTION gzip(bytea) RETURNS bytea
  AS 'pgos', 'pgos_deflate_bytea'
  LANGUAGE C STRICT;


CREATE FUNCTION gzip(text) RETURNS bytea
  AS 'pgos', 'pgos_deflate_text'
  LANGUAGE C STRICT;


CREATE FUNCTION inflate(bytea) RETURNS text
  AS 'pgos', 'pgos_inflate_text'
  LANGUAGE C STRICT;


CREATE FUNCTION inflate_bytea(bytea) RETURNS bytea
  AS 'pgos', 'pgos_inflate_bytea'
  LANGUAGE C STRICT;
