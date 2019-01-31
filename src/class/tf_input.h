#ifndef PHP_TENSILE_INPUT_H
#define PHP_TENSILE_INPUT_H

#include <php.h>
#include <php_ini.h>
#include <SAPI.h>
#include <ext/standard/info.h>
#include <Zend/zend_extensions.h>
#include <Zend/zend_exceptions.h>
#include <Zend/zend_interfaces.h>

#include <../include/tensorflow/c/c_api.h>// use this only
#include <../src/utilities.h>

#define TF_INPUT_P_ZO(zo) ((t_tf_input_object*)((char *)(zo) - XtOffsetOf(t_tf_input_object, std)))
#define TF_INPUT_P_ZV(zv) TF_INPUT_P_ZO(Z_OBJ_P(zv))

extern zend_class_entry *ce_TF_Input;
extern zend_object_handlers oh_TF_Input;

typedef struct _t_tf_input {
    TF_Input* src;
    char* str;
    int ref;
} t_tf_input;

typedef struct _t_tf_input_object {
    zend_object std;
    t_tf_input* ptr;
} t_tf_input_object;

void define_tf_input_class();

#endif  /* PHP_TENSILE_INPUT_H */
