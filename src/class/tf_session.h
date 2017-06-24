#ifndef PHP_TENSILE_SESSION_H
#define PHP_TENSILE_SESSION_H

#include <php.h>
#include <php_ini.h>
#include <SAPI.h>
#include <ext/standard/info.h>
#include <Zend/zend_extensions.h>
#include <Zend/zend_exceptions.h>
#include <Zend/zend_interfaces.h>

#include <../../includes/tensorflow/c/c_api.h>// use this only
#include "class_abstract.h"

#include "tf_graph.h"
#include "tf_status.h"
#include "tf_session_options.h"


#define TF_SESSION_P_ZO(zo) ((t_tf_session_object*)((char *)(zo) - XtOffsetOf(t_tf_session_object, std)))
#define TF_SESSION_P_ZV(zv) TF_SESSION_P_ZO(Z_OBJ_P(zv))

extern zend_class_entry *ce_TF_Session;
extern zend_object_handlers oh_TF_Session;

typedef struct _t_tf_session {
    TF_Session* src;
    zend_string* str;
    int ref;
} t_tf_session;

typedef struct _t_tf_session_object {
    zend_object std;
    t_tf_session* ptr;
} t_tf_session_object;

void define_tf_session_class();

#endif  /* PHP_TENSILE_SESSION_H */
