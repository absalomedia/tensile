
#include "tf_status.h"

// predefine
zend_class_entry *ce_TF_Status = NULL;
zend_object_handlers oh_TF_Status;

// methods
static PHP_METHOD(TensorFlow_Status, __construct);
static PHP_METHOD(TensorFlow_Status, __destruct);
static PHP_METHOD(TensorFlow_Status, setCode);
static PHP_METHOD(TensorFlow_Status, getCode);
static PHP_METHOD(TensorFlow_Status, getMessage);

// argument info
ZEND_BEGIN_ARG_INFO_EX(arginfo_tf_status_setCode, 0, 0, 1)
    ZEND_ARG_INFO(0, code)
    ZEND_ARG_INFO(0, message)
ZEND_END_ARG_INFO()


// methods
static zend_function_entry tf_status_methods[] = {
    PHP_ME(TensorFlow_Status, __construct, NULL,                      ZEND_ACC_PUBLIC)
    PHP_ME(TensorFlow_Status, __destruct,  NULL,                      ZEND_ACC_PUBLIC)
    PHP_ME(TensorFlow_Status, setCode,     arginfo_tf_status_setCode, ZEND_ACC_PUBLIC)
    PHP_ME(TensorFlow_Status, getCode,     NULL,                      ZEND_ACC_PUBLIC)
    PHP_ME(TensorFlow_Status, getMessage,  NULL,                      ZEND_ACC_PUBLIC)
    PHP_FE_END
};

CA_OBJECT_CREATE(status, t_tf_status, t_tf_status_object, oh_TF_Status)
CA_OBJECT_FREE(status, t_tf_status, t_tf_status_object)

void define_tf_status_class()
{
    DEFINE_CLASS(Status, status, ce_TF_Status, oh_TF_Status)

    #define TF_STATUS_CLASS_CONST(name, value) zend_declare_class_constant_long(ce_TF_Status, name, sizeof(name) - 1, value);
 
    TF_STATUS_CLASS_CONST("CODE_OK", 0);
    TF_STATUS_CLASS_CONST("CODE_CANCELLED", 1);
    TF_STATUS_CLASS_CONST("CODE_UNKNOWN", 2);
    TF_STATUS_CLASS_CONST("CODE_INVALID_ARGUMENT", 3);
    TF_STATUS_CLASS_CONST("CODE_DEADLINE_EXCEEDED", 4);
    TF_STATUS_CLASS_CONST("CODE_NOT_FOUND", 5);
    TF_STATUS_CLASS_CONST("CODE_ALREADY_EXISTS", 6);
    TF_STATUS_CLASS_CONST("CODE_PERMISSION_DENIED", 7);
    TF_STATUS_CLASS_CONST("CODE_RESOURCE_EXHAUSTED", 8);
    TF_STATUS_CLASS_CONST("CODE_FAILED_PRECONDITION", 9);
    TF_STATUS_CLASS_CONST("CODE_ABORTED", 10);
    TF_STATUS_CLASS_CONST("CODE_OUT_OF_RANGE", 11);
    TF_STATUS_CLASS_CONST("CODE_UNIMPLEMENTED", 12);
    TF_STATUS_CLASS_CONST("CODE_INTERNAL", 13);
    TF_STATUS_CLASS_CONST("CODE_UNAVAILABLE", 14);
    TF_STATUS_CLASS_CONST("CODE_DATA_LOSS", 15);
    TF_STATUS_CLASS_CONST("CODE_UNAUTHENTICATED", 16);
}

static PHP_METHOD(TensorFlow_Status, __construct)
{
    t_tf_status_object* intern = TF_STATUS_P_ZV(getThis());
    t_tf_status* node = intern->ptr;

    node->src = TF_NewStatus();
}

static PHP_METHOD(TensorFlow_Status, __destruct)
{
    t_tf_status_object* intern = TF_STATUS_P_ZV(getThis());
    t_tf_status* node = intern->ptr;

    TF_DeleteStatus(node->src);
}

// void TF_SetStatus(TF_Status* s, TF_Code code, const char* message);
static PHP_METHOD(TensorFlow_Status, setCode)
{
    // arguments
    int code;
    char* message = NULL;
    size_t message_len;
    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "l|s", &code, &message, &message_len) == FAILURE) {
        RETURN_NULL();
        return;
    }
    // ZEND_PARSE_PARAMETERS_START(1, 2)
    //     Z_PARAM_LONG(code)
    //     Z_PARAM_OPTIONAL
    //     Z_PARAM_STR(message)
    // ZEND_PARSE_PARAMETERS_END();

    t_tf_status_object* intern = TF_STATUS_P_ZV(getThis());
    t_tf_status* node = intern->ptr;
    TF_Status* tf_status = node->src;

    if (message == NULL) {
        TF_SetStatus(tf_status, code, "");
    } else {
        TF_SetStatus(tf_status, code, message);
    }
}

// extern TF_Code TF_GetCode(const TF_Status* s);
static PHP_METHOD(TensorFlow_Status, getCode)
{
    if (ZEND_NUM_ARGS() != 0) {
        WRONG_PARAM_COUNT;
    }

    // this
    t_tf_status_object* intern = TF_STATUS_P_ZV(getThis());
    t_tf_status* node = intern->ptr;
    TF_Status* tf_status = node->src;

    RETURN_LONG(TF_GetCode(tf_status));
}


// extern const char* TF_Message(const TF_Status* s);
static PHP_METHOD(TensorFlow_Status, getMessage)
{
    if (ZEND_NUM_ARGS() != 0) {
        WRONG_PARAM_COUNT;
    }

    // this
    t_tf_status_object* intern = TF_STATUS_P_ZV(getThis());
    t_tf_status* node = intern->ptr;
    TF_Status* tf_status = node->src;

    RETURN_STRING(TF_Message(tf_status));
}
