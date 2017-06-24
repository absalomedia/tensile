
#include "tf_tensor.h"

// predefine
zend_class_entry *ce_TF_Tensor = NULL;
zend_object_handlers oh_TF_Tensor;

// methods
static PHP_METHOD(TensorFlow_Tensor, __construct);
static PHP_METHOD(TensorFlow_Tensor, __destruct);
static PHP_METHOD(TensorFlow_Tensor, getDtype);

// argument info
ZEND_BEGIN_ARG_INFO_EX(arginfo_tf_tensor___construct, 0, 0, 1)
    ZEND_ARG_INFO(0, dtype)
    ZEND_ARG_ARRAY_INFO(0, dims, 1)
    ZEND_ARG_ARRAY_INFO(0, data, 1)
ZEND_END_ARG_INFO()

// methods
static zend_function_entry tf_tensor_methods[] = {
    PHP_ME(TensorFlow_Tensor, __construct, arginfo_tf_tensor___construct, ZEND_ACC_PUBLIC)
    PHP_ME(TensorFlow_Tensor, __destruct, NULL, ZEND_ACC_PUBLIC)
    PHP_ME(TensorFlow_Tensor, getDtype, NULL, ZEND_ACC_PUBLIC)
    PHP_FE_END
};

CA_OBJECT_CREATE(tensor, t_tf_tensor, t_tf_tensor_object, oh_TF_Tensor)
CA_OBJECT_FREE(tensor, t_tf_tensor, t_tf_tensor_object)

void define_tf_tensor_class()
{
    DEFINE_CLASS(Tensor, tensor, ce_TF_Tensor, oh_TF_Tensor)
}

// extern TF_Tensor* TF_AllocateTensor(TF_DataType, const int64_t* dims, int num_dims, size_t len);
static PHP_METHOD(TensorFlow_Tensor, __construct)
{
    zend_long dtype;
    zval* dims;
    zval* data;

    ZEND_PARSE_PARAMETERS_START(1, 3)
        Z_PARAM_LONG(dtype)
        Z_PARAM_OPTIONAL
        Z_PARAM_ARRAY_EX(dims, 1, 0)
        Z_PARAM_ARRAY_EX(data, 1, 0)
    ZEND_PARSE_PARAMETERS_END();

    if (!valid_dtype(dtype)) {
        zend_throw_exception(spl_ce_InvalidArgumentException, "dtype must be from 1 to 20", 0);
        return;
    }


    TF_DataType tf_dtype = (TF_DataType) dtype;

    int64_t* tf_dims = NULL;
    int tf_num_dims = 0;
    size_t tf_len = tf_dtype_sizeof(tf_dtype);

    if (dims != NULL) {
        HashTable *dims_table = Z_ARRVAL_P(dims);
        tf_num_dims = zend_hash_num_elements(dims_table); // count of array

        if (tf_num_dims > 0) {
            tf_dims = (int64_t*)emalloc(sizeof(int64_t) * tf_num_dims);

            HashPosition pos;
            zval* element;
            int index = 0;

            zend_hash_internal_pointer_reset_ex(dims_table, &pos);
            while (zend_hash_has_more_elements_ex(dims_table, &pos) == SUCCESS) {
                if (!(element = zend_hash_get_current_data_ex(dims_table, &pos))) {
                    zend_throw_exception(spl_ce_InvalidArgumentException, "dims something wrong", 0);
                    return;
                }
                if (zval_get_type(element) != IS_LONG) {
                    zend_throw_exception(spl_ce_InvalidArgumentException, "dims must be array of integer", 0);
                    return;
                }
                // multi equal tf_len and insert tf_dims
                tf_len *= tf_dims[index] = element->value.lval;
                // php_printf("%d \n", element->value.lval);
                zend_hash_move_forward_ex(dims_table, &pos);

                index++;
            }
        }
    }

    // php_printf("dtype ? %d\n", tf_dtype);
    // int i;
    // for (i = 0; i < tf_num_dims; i++) {
    //     php_printf("dims[%d] ? %d\n", i, tf_dims[i]);
    // }
    // php_printf("tf_num_dims ? %d\n", tf_num_dims);
    // php_printf("len ? %d\n", tf_len);

    // this
    t_tf_tensor_object* intern;
    t_tf_tensor* php_tf_tensor;
    int len = 0;

    intern = TF_TENSOR_P_ZV(getThis());
    php_tf_tensor = intern->ptr;
    php_tf_tensor->src = TF_AllocateTensor(tf_dtype, tf_dims, tf_num_dims, tf_len);
}

// extern void TF_DeleteTensor(TF_Tensor*);
static PHP_METHOD(TensorFlow_Tensor, __destruct)
{
    t_tf_tensor_object* intern = TF_TENSOR_P_ZV(getThis());
    t_tf_tensor* node = intern->ptr;

    TF_DeleteTensor(node->src);
}

// extern TF_DataType TF_TensorType(const TF_Tensor*);
static PHP_METHOD(TensorFlow_Tensor, getDtype)
{
    t_tf_tensor_object* intern = TF_TENSOR_P_ZV(getThis());
    t_tf_tensor* node = intern->ptr;

    RETURN_LONG(TF_TensorType(node->src));
}
