PHP_ARG_ENABLE(tensile, [whether to enable tensile extension],
[  --enable-tensile      Enable Tensile extension], yes, yes)

if test "$PHP_TENSILE" != "no"; then
  PHP_ADD_INCLUDE(tensorflow/lib)
  PHP_ADD_LIBRARY_WITH_PATH(tensile, lib/libexec, LIBTENSILE_SHARED_LIBADD)

  LDFLAGS="-lsass -L"`pwd`"/tensorflow/include/tensorflow/c/ -lstdc++"


  PHP_NEW_EXTENSION(tensile, src/tensile.c src/utilities.c, $ext_shared)
fi
