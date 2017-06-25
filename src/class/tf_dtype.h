#ifndef PHP_TENSILE_DTYPE_H
#define PHP_TENSILE_DTYPE_H

#include <../../include/tensorflow/c/c_api.h>// use this only

size_t tf_dtype_sizeof(TF_DataType type);

char valid_dtype(int64_t dtype);

#endif  /* PHP_TENSILE_DTYPE_H */
