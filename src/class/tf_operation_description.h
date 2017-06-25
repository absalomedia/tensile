#ifndef PHP_TENSILE_OPERATION_DESCRIPTION_H
#define PHP_TENSILE_OPERATION_DESCRIPTION_H

#include <php.h>
#include <php_ini.h>
#include <SAPI.h>
#include <ext/standard/info.h>
#include <Zend/zend_extensions.h>
#include <Zend/zend_exceptions.h>
#include <Zend/zend_interfaces.h>
#include <ext/spl/spl_exceptions.h>

#include <../includes/tensorflow/c/c_api.h>// use this only
#include "class_abstract.h"
#include "tf_dtype.h"
#include "tf_graph.h"

#define TF_OPERATION_DESCRIPTION_P_ZO(zo) (t_tf_operation_description_object*)((char *)(zo) - XtOffsetOf(t_tf_operation_description_object, std))
#define TF_OPERATION_DESCRIPTION_P_ZV(zv) TF_OPERATION_DESCRIPTION_P_ZO(Z_OBJ_P(zv))

extern zend_class_entry *ce_TF_OperationDescription;
extern zend_object_handlers oh_TF_OperationDescription;

typedef struct _t_tf_operation_description {
    TF_OperationDescription* src;
    zend_string* str;
    int ref;
} t_tf_operation_description;

typedef struct _t_tf_operation_description_object {
    zend_object std;
    t_tf_operation_description* ptr;
} t_tf_operation_description_object;

void define_tf_operation_description_class();

#endif  /* PHP_TENSILE_OPERATION_DESCRIPTION_H */
