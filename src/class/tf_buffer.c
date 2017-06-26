
#include "tf_buffer.h"

// predefine
zend_class_entry *ce_TF_Buffer = NULL;
zend_object_handlers oh_TF_Buffer;

// methods
static PHP_METHOD(Tensile_Buffer, __construct);
static PHP_METHOD(Tensile_Buffer, __destruct);
static PHP_METHOD(Tensile_Buffer, __toString);

// argument info
ZEND_BEGIN_ARG_INFO_EX(arginfo_tf_buffer___construct, 0, 0, 0)
    ZEND_ARG_INFO(0, buffer)
ZEND_END_ARG_INFO()

// methods
static zend_function_entry tf_buffer_methods[] = {
    PHP_ME(Tensile_Buffer, __construct, arginfo_tf_buffer___construct, ZEND_ACC_PUBLIC)
    PHP_ME(Tensile_Buffer, __destruct,  NULL,                          ZEND_ACC_PUBLIC)
    PHP_ME(Tensile_Buffer, __toString,  NULL,                          ZEND_ACC_PUBLIC)
    PHP_FE_END
};

CA_OBJECT_CREATE(buffer, t_tf_buffer, t_tf_buffer_object, oh_TF_Buffer)
CA_OBJECT_FREE(buffer, t_tf_buffer, t_tf_buffer_object)

void define_tf_buffer_class()
{
    DEFINE_CLASS(Buffer, buffer, ce_TF_Buffer, oh_TF_Buffer)
}

// extern TF_Buffer* TF_NewBufferFromString(const void* proto, size_t proto_len);
// extern TF_Buffer* TF_NewBuffer();
static PHP_METHOD(Tensile_Buffer, __construct)
{
    // arguments
    char* buffer;

    ZEND_PARSE_PARAMETERS_START(0, 1)
        Z_PARAM_OPTIONAL
        Z_PARAM_STR(buffer)
    ZEND_PARSE_PARAMETERS_END();

    // this
    t_tf_buffer_object* intern;
    t_tf_buffer* php_tf_buffer;

    intern = TF_BUFFER_P_ZV(getThis());
    php_tf_buffer = intern->ptr;

    if (ZEND_NUM_ARGS() == 1) {
        php_tf_buffer->src = TF_NewBufferFromString(ZSTR_VAL(buffer), ZSTR_LEN(buffer));
    } else {
        php_tf_buffer->src = TF_NewBuffer();
    }
}

// extern void TF_DeleteBuffer(TF_Buffer*);
static PHP_METHOD(Tensile_Buffer, __destruct)
{
    // this
    t_tf_buffer_object* intern;
    t_tf_buffer* node;

    intern = TF_BUFFER_P_ZV(getThis());
    node = intern->ptr;

    TF_DeleteBuffer(node->src);
}

// extern TF_Buffer TF_GetBuffer(TF_Buffer* buffer);
static PHP_METHOD(Tensile_Buffer, __toString)
{
    char* result;

    // this
    t_tf_buffer_object* intern;
    t_tf_buffer* node;
    TF_Buffer* tf_buffer;

    intern = TF_BUFFER_P_ZV(getThis());
    node = intern->ptr;
    tf_buffer = node->src;


    RETURN_STR(zend_string_init(tf_buffer->data, tf_buffer->length, 0));
}
