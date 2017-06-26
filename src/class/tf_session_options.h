#ifndef PHP_TENSILE_SESSION_OPTIONS_H
#define PHP_TENSILE_SESSION_OPTIONS_H

#include <php.h>
#include <php_ini.h>
#include <SAPI.h>
#include <ext/standard/info.h>
#include <Zend/zend_extensions.h>
#include <Zend/zend_exceptions.h>
#include <Zend/zend_interfaces.h>

#include <../include/tensorflow/c/c_api.h>// use this only
#include "class_abstract.h"

#define TF_SESSION_OPTIONS_P_ZO(zo) ((t_tf_session_options_object*)((char *)(zo) - XtOffsetOf(t_tf_session_options_object, std)))
#define TF_SESSION_OPTIONS_P_ZV(zv) TF_SESSION_OPTIONS_P_ZO(Z_OBJ_P(zv))

extern zend_class_entry *ce_TF_SessionOptions;
extern zend_object_handlers oh_TF_SessionOptions;

typedef struct _t_tf_session_options {
    TF_SessionOptions* src;
    char* str;
    int ref;
} t_tf_session_options;

typedef struct _t_tf_session_options_object {
    zend_object std;
    t_tf_session_options* ptr;
} t_tf_session_options_object;

void define_tf_session_options_class();

#endif  /* PHP_TENSILE_SESSION_OPTIONS_H */
