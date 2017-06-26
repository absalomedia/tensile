#ifndef PHP_TENSILE_GRAPH_H
#define PHP_TENSILE_GRAPH_H

#include <php.h>
#include <php_ini.h>
#include <SAPI.h>
#include <ext/standard/info.h>
#include <Zend/zend_extensions.h>
#include <Zend/zend_exceptions.h>
#include <Zend/zend_interfaces.h>

#include <../../include/tensorflow/c/c_api.h>// use this only
#include "class_abstract.h"

#define TF_GRAPH_P_ZO(zo) (t_tf_graph_object*)((char *)(zo) - XtOffsetOf(t_tf_graph_object, std))
#define TF_GRAPH_P_ZV(zv) TF_GRAPH_P_ZO(Z_OBJ_P(zv))

extern zend_class_entry *ce_TF_Graph;
extern zend_object_handlers oh_TF_Graph;

typedef struct _t_tf_graph {
    TF_Graph* src;
    char* str;
    int ref;
} t_tf_graph;

typedef struct _t_tf_graph_object {
    zend_object std;
    t_tf_graph* ptr;
} t_tf_graph_object;

void define_tf_graph_class();

#endif  /* PHP_TENSILE_GRAPH_H */
