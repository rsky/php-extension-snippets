PHP_ARG_ENABLE(snippets, [whether to enable snippets extension],
[  --enable-snippets     Enable snippets extension], yes, yes)

if test "$PHP_SNIPPETS" != "no"; then
  SOURCES="snippets.c hash.c intarray.c"
  PHP_NEW_EXTENSION(snippets, $SOURCES, $ext_shared)
fi
