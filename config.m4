PHP_ARG_ENABLE(tensile, [whether to enable tensile extension],
[  --enable-tensile      Enable Tensile extension], yes, yes)

if test "$PHP_TENSILE" != "no"; then
  PHP_ADD_INCLUDE(include)
  PHP_ADD_LIBRARY_WITH_PATH(tensorflow, lib, LIBTENSORFLOW_SHARED_LIBADD)
  
  LDFLAGS="-ltensorflow -L"`pwd`"/lib/ -lstdc++"

  PHP_NEW_EXTENSION(tensile, src/tensile.c src/utilities.c src/class/tf_buffer.c src/class/tf_dtype.c src/class/tf_graph.c src/class/tf_input.c src/class/tf_operation_description.c src/class/tf_session.c src/class/tf_status.c src/class/tf_tensor.c, $ext_shared)
fi
