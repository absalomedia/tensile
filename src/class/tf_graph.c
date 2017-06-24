
#include "tf_graph.h"

// predefine
zend_class_entry *ce_TF_Graph = NULL;
zend_object_handlers oh_TF_Graph;

// methods
static PHP_METHOD(TensorFlow_Graph, __construct);
static PHP_METHOD(TensorFlow_Graph, __destruct);

// argument info
// ZEND_BEGIN_ARG_INFO_EX(arginfo_tf_graph_setCode, 0, 0, 1)
//     ZEND_ARG_INFO(0, code)
//     ZEND_ARG_INFO(0, message)
// ZEND_END_ARG_INFO()

// methods
static zend_function_entry tf_graph_methods[] = {
    PHP_ME(TensorFlow_Graph, __construct, NULL,                      ZEND_ACC_PUBLIC)
    PHP_ME(TensorFlow_Graph, __destruct,  NULL,                      ZEND_ACC_PUBLIC)
    PHP_FE_END
};

CA_OBJECT_CREATE(graph, t_tf_graph, t_tf_graph_object, oh_TF_Graph)
CA_OBJECT_FREE(graph, t_tf_graph, t_tf_graph_object)

void define_tf_graph_class()
{
    DEFINE_CLASS(Graph, graph, ce_TF_Graph, oh_TF_Graph)
}

// extern TF_Graph* TF_NewGraph();
static PHP_METHOD(TensorFlow_Graph, __construct)
{
    t_tf_graph_object* intern = TF_GRAPH_P_ZV(getThis());
    t_tf_graph* node = intern->ptr;

    node->src = TF_NewGraph();
}

// extern void TF_DeleteGraph(TF_Graph*);
static PHP_METHOD(TensorFlow_Graph, __destruct)
{
    t_tf_graph_object* intern = TF_GRAPH_P_ZV(getThis());
    t_tf_graph* node = intern->ptr;

    TF_DeleteGraph(node->src);
}
