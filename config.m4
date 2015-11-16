PHP_ARG_ENABLE(tensile, [whether to enable tensile extension],
[  --enable-tensile      Enable Tensile extension], yes, yes)

if test "$PHP_TENSILE" != "no"; then
  PHP_ADD_INCLUDE(lib/tensorflow)
  PHP_ADD_LIBRARY_WITH_PATH(tensile, lib/libexec, LIBTENSILE_SHARED_LIBADD)

  LDFLAGS="-lsass -L"`pwd`"/lib/tensorflow/core/ -lstdc++"

  # manually extract sass version as the non-autotool'ed
  # tensile_version.h that comes with libsass doesn't contain
  # the version
  tensile_version=$(cd lib/tensorflow && ./version.sh)

  if test "x$tensile_version" != "x" ; then
      # escape hell. This is what we need to pass to the
      #  compiler: -DLIBTENSILE_VERSION="\"'3.3.2\""
      CFLAGS="-DLIBTENSILE_VERSION=\"\\\"$tensile_version\\\"\" $CFLAGS"
      CXXFLAGS="-DLIBTENSILE_VERSION=\"\\\"$tensile_version\\\"\" $CXXFLAGS"
  fi

  PHP_NEW_EXTENSION(tensile, src/tensile.c src/utilities.c, $ext_shared)
fi
