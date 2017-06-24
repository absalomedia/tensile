
#include "tf_input.h"

// predefine
zend_class_entry *ce_TF_Input = NULL;
zend_object_handlers oh_TF_Input;

// methods
static PHP_METHOD(TensorFlow_Input, __construct);
static PHP_METHOD(TensorFlow_Input, __destruct);

// argument info
// ZEND_BEGIN_ARG_INFO_EX(arginfo_tf_input_setCode, 0, 0, 1)
//     ZEND_ARG_INFO(0, code)
//     ZEND_ARG_INFO(0, message)
// ZEND_END_ARG_INFO()

// methods
static zend_function_entry tf_input_methods[] = {
    PHP_ME(TensorFlow_Input, __construct, NULL,                      ZEND_ACC_PUBLIC)
    PHP_ME(TensorFlow_Input, __destruct,  NULL,                      ZEND_ACC_PUBLIC)
    PHP_FE_END
};

CA_OBJECT_CREATE(input, t_tf_input, t_tf_input_object, oh_TF_Input)
CA_OBJECT_FREE(input, t_tf_input, t_tf_input_object)

void define_tf_input_class()
{
    DEFINE_CLASS(Input, input, ce_TF_Input, oh_TF_Input)
}

// // Represents a specific input of an operation.
// typedef struct TF_Input {
//   TF_Operation* oper;
//   int index;  // The index of the input within oper.
// } TF_Input;

static PHP_METHOD(TensorFlow_Input, __construct)
{
    t_tf_input_object* intern = TF_INPUT_P_ZV(getThis());
    t_tf_input* node = intern->ptr;

    node->src = (TF_Input*)emalloc(sizeof(TF_Input));
    node->src->oper = NULL; // OPER;
    node->src->index = 0;
}

// // In this code:
// //   TF_Output producer = TF_OperationInput(consumer);
// // There is an edge from producer.oper's output (given by
// // producer.index) to consumer.oper's input (given by consumer.index).
// extern TF_Output TF_OperationInput(TF_Input oper_in);
static PHP_METHOD(TensorFlow_Input, __destruct)
{
    t_tf_input_object* intern = TF_INPUT_P_ZV(getThis());
    t_tf_input* node = intern->ptr;

    node->src; // ?
}
