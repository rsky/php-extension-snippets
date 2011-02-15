PHP_ARG_ENABLE(snippets, [whether to enable snippets extension],
[  --enable-snippets        Enable snippets extension], yes, yes)

if test "$PHP_SNIPPETS" != "no"; then
  PHP_NEW_EXTENSION(snippets, snippets.c intarray.c, $ext_shared)
fi
