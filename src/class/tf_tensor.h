#ifndef PHP_TENSILE_TENSOR_H
#define PHP_TENSILE_TENSOR_H

#include <php.h>
#include <php_ini.h>
#include <SAPI.h>
#include <ext/standard/info.h>
#include <Zend/zend_extensions.h>
#include <Zend/zend_exceptions.h>
#include <Zend/zend_interfaces.h>
#include <ext/spl/spl_exceptions.h>

#include "../utilties.h"
#include "tf_dtype.h"
#include <../include/tensorflow/c/c_api.h>// use this only

#define TF_TENSOR_P_ZO(zo) ((t_tf_tensor_object*)((char *)(zo) - XtOffsetOf(t_tf_tensor_object, std)))
#define TF_TENSOR_P_ZV(zv) TF_TENSOR_P_ZO(Z_OBJ_P(zv))

typedef struct _t_tf_tensor {
    TF_Tensor* src;
    char* str;
    int ref;
} t_tf_tensor;

typedef struct _t_tf_tensor_object {
    zend_object std;
    t_tf_tensor* ptr;
} t_tf_tensor_object;

void define_tf_tensor_class();

#endif  /* PHP_TENSILE_TENSOR_H */
