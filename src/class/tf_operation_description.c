
#include "tf_operation_description.h"

// predefine
zend_class_entry *ce_TF_OperationDescription = NULL;
zend_object_handlers oh_TF_OperationDescription;

// methods
static PHP_METHOD(TensorFlow_OperationDescription, __construct);
static PHP_METHOD(TensorFlow_OperationDescription, __destruct);
static PHP_METHOD(TensorFlow_OperationDescription, setDevice);

static PHP_METHOD(TensorFlow_OperationDescription, setAttrInt);
static PHP_METHOD(TensorFlow_OperationDescription, setAttrIntList);
static PHP_METHOD(TensorFlow_OperationDescription, setAttrFloat);
static PHP_METHOD(TensorFlow_OperationDescription, setAttrFloatList);
static PHP_METHOD(TensorFlow_OperationDescription, setAttrBool);
static PHP_METHOD(TensorFlow_OperationDescription, setAttrBoolList);
static PHP_METHOD(TensorFlow_OperationDescription, setAttrType);
static PHP_METHOD(TensorFlow_OperationDescription, setAttrTypeList);

// argument info
ZEND_BEGIN_ARG_INFO_EX(arginfo_tf_operation_description___construct, 0, 0, 3)
    ZEND_ARG_INFO(0, graph)
    ZEND_ARG_INFO(0, operatorType)
    ZEND_ARG_INFO(0, operatorName)
ZEND_END_ARG_INFO()
ZEND_BEGIN_ARG_INFO_EX(arginfo_tf_operation_description_setDevice, 0, 0, 1)
    ZEND_ARG_INFO(0, device)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_tf_operation_description_setAttrInt, 0, 0, 2)
    ZEND_ARG_INFO(0, name)
    ZEND_ARG_INFO(0, value)
ZEND_END_ARG_INFO()
ZEND_BEGIN_ARG_INFO_EX(arginfo_tf_operation_description_setAttrIntList, 0, 0, 2)
    ZEND_ARG_INFO(0, name)
    ZEND_ARG_ARRAY_INFO(0, values, 0)
ZEND_END_ARG_INFO()
ZEND_BEGIN_ARG_INFO_EX(arginfo_tf_operation_description_setAttrFloat, 0, 0, 2)
    ZEND_ARG_INFO(0, name)
    ZEND_ARG_INFO(0, value)
ZEND_END_ARG_INFO()
ZEND_BEGIN_ARG_INFO_EX(arginfo_tf_operation_description_setAttrFloatList, 0, 0, 2)
    ZEND_ARG_INFO(0, name)
    ZEND_ARG_ARRAY_INFO(0, values, 0)
ZEND_END_ARG_INFO()
ZEND_BEGIN_ARG_INFO_EX(arginfo_tf_operation_description_setAttrBool, 0, 0, 2)
    ZEND_ARG_INFO(0, name)
    ZEND_ARG_INFO(0, value)
ZEND_END_ARG_INFO()
ZEND_BEGIN_ARG_INFO_EX(arginfo_tf_operation_description_setAttrBoolList, 0, 0, 2)
    ZEND_ARG_INFO(0, name)
    ZEND_ARG_ARRAY_INFO(0, values, 0)
ZEND_END_ARG_INFO()
ZEND_BEGIN_ARG_INFO_EX(arginfo_tf_operation_description_setAttrType, 0, 0, 2)
    ZEND_ARG_INFO(0, name)
    ZEND_ARG_INFO(0, dtype)
ZEND_END_ARG_INFO()
ZEND_BEGIN_ARG_INFO_EX(arginfo_tf_operation_description_setAttrTypeList, 0, 0, 2)
    ZEND_ARG_INFO(0, name)
    ZEND_ARG_ARRAY_INFO(0, dtypes, 0)
ZEND_END_ARG_INFO()

// methods
static zend_function_entry tf_operation_description_methods[] = {
    PHP_ME(TensorFlow_OperationDescription, __construct,
                    arginfo_tf_operation_description___construct, ZEND_ACC_PUBLIC)
    PHP_ME(TensorFlow_OperationDescription, __destruct, NULL, ZEND_ACC_PUBLIC)
    PHP_ME(TensorFlow_OperationDescription, setDevice,
                    arginfo_tf_operation_description_setDevice, ZEND_ACC_PUBLIC)

    PHP_ME(TensorFlow_OperationDescription, setAttrInt,
                    arginfo_tf_operation_description_setAttrInt, ZEND_ACC_PUBLIC)
    PHP_ME(TensorFlow_OperationDescription, setAttrIntList,
                    arginfo_tf_operation_description_setAttrIntList, ZEND_ACC_PUBLIC)
    PHP_ME(TensorFlow_OperationDescription, setAttrFloat,
                    arginfo_tf_operation_description_setAttrFloat, ZEND_ACC_PUBLIC)
    PHP_ME(TensorFlow_OperationDescription, setAttrFloatList,
                    arginfo_tf_operation_description_setAttrFloatList, ZEND_ACC_PUBLIC)
    PHP_ME(TensorFlow_OperationDescription, setAttrBool,
                    arginfo_tf_operation_description_setAttrBool, ZEND_ACC_PUBLIC)
    PHP_ME(TensorFlow_OperationDescription, setAttrBoolList,
                    arginfo_tf_operation_description_setAttrBoolList, ZEND_ACC_PUBLIC)
    PHP_ME(TensorFlow_OperationDescription, setAttrType,
                    arginfo_tf_operation_description_setAttrType, ZEND_ACC_PUBLIC)
    PHP_ME(TensorFlow_OperationDescription, setAttrTypeList,
                    arginfo_tf_operation_description_setAttrTypeList, ZEND_ACC_PUBLIC)
    PHP_FE_END
};

CA_OBJECT_CREATE(operation_description, t_tf_operation_description, t_tf_operation_description_object, oh_TF_OperationDescription)
CA_OBJECT_FREE(operation_description, t_tf_operation_description, t_tf_operation_description_object)

void define_tf_operation_description_class()
{
    DEFINE_CLASS(OperationDescription, operation_description, ce_TF_OperationDescription, oh_TF_OperationDescription)
}

// extern TF_OperationDescription* TF_NewOperation(TF_Graph* graph,
//         const char* op_type, const char* oper_name);
static PHP_METHOD(TensorFlow_OperationDescription, __construct)
{
    zval *graph;
    zend_string *operatorType;
    zend_string *operatorName;

    ZEND_PARSE_PARAMETERS_START(3, 3)
        Z_PARAM_OBJECT_OF_CLASS_EX(graph, ce_TF_Graph, 0, 1) // last 1 is call by ref.
        Z_PARAM_STR(operatorType)
        Z_PARAM_STR(operatorName)
    ZEND_PARSE_PARAMETERS_END();

    // php_printf("optype : %s\n", operatorType->val);
    // php_printf("opname : %s\n", operatorName->val);

    t_tf_operation_description_object* intern = TF_OPERATION_DESCRIPTION_P_ZV(getThis());
    t_tf_operation_description* node = intern->ptr;

    node->src = TF_NewOperation(
        TF_GRAPH_P_ZV(graph)->ptr->src,
        operatorType->val,
        operatorName->val
    );
}

static PHP_METHOD(TensorFlow_OperationDescription, __destruct)
{
    t_tf_operation_description_object* intern = TF_OPERATION_DESCRIPTION_P_ZV(getThis());
    t_tf_operation_description* node = intern->ptr;
    // ? (node->src);
}

// extern void TF_SetDevice(TF_OperationDescription* desc, const char* device);
static PHP_METHOD(TensorFlow_OperationDescription, setDevice)
{
    zend_string *device;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_STR(device)
    ZEND_PARSE_PARAMETERS_END();

    // php_printf("device : %s\n", device->val);

    t_tf_operation_description_object* intern = TF_OPERATION_DESCRIPTION_P_ZV(getThis());
    t_tf_operation_description* node = intern->ptr;

    TF_SetDevice(node->src, device->val);
}

// extern void TF_SetAttrInt(TF_OperationDescription* desc, const char* attr_name,
//                           int64_t value);
static PHP_METHOD(TensorFlow_OperationDescription, setAttrInt)
{
    zend_string *name;
    zend_long value;

    ZEND_PARSE_PARAMETERS_START(2, 2)
        Z_PARAM_STR(name)
        Z_PARAM_LONG(value)
    ZEND_PARSE_PARAMETERS_END();

    // this
    t_tf_operation_description_object* intern = TF_OPERATION_DESCRIPTION_P_ZV(getThis());
    t_tf_operation_description* node = intern->ptr;

    TF_SetAttrInt(node->src, name->val, value);
}

// extern void TF_SetAttrIntList(TF_OperationDescription* desc,
//                               const char* attr_name, const int64_t* values,
//                               int num_values);
static PHP_METHOD(TensorFlow_OperationDescription, setAttrIntList)
{
    zend_string *name;
    zval* values;

    ZEND_PARSE_PARAMETERS_START(2, 2)
        Z_PARAM_STR(name)
        Z_PARAM_ARRAY(values)
    ZEND_PARSE_PARAMETERS_END();


    int64_t* tf_values = NULL;
    int tf_num_values = 0;

    HashTable *values_table = Z_ARRVAL_P(values);
    tf_num_values = zend_hash_num_elements(values_table); // count of array

    if (tf_num_values > 0) {
        tf_values = (int64_t*)emalloc(sizeof(int64_t) * tf_num_values);

        HashPosition pos;
        zval* element;
        int index = 0;

        zend_hash_internal_pointer_reset_ex(values_table, &pos);
        while (zend_hash_has_more_elements_ex(values_table, &pos) == SUCCESS) {
            if (!(element = zend_hash_get_current_data_ex(values_table, &pos))) {
                zend_throw_exception(spl_ce_InvalidArgumentException, "values something wrong", 0);
                return;
            }
            if (zval_get_type(element) != IS_LONG) {
                zend_throw_exception(spl_ce_InvalidArgumentException, "values must be array of integer", 0);
                return;
            }
            // insert tf_values
            tf_values[index] = Z_LVAL_P(element);
            // php_printf("%d \n", element->value.lval);
            zend_hash_move_forward_ex(values_table, &pos);

            index++;
        }
    }

    // int i;
    // for (i = 0; i < tf_num_values; i++) {
    //     php_printf("values[%d] ? %d\n", i, tf_values[i]);
    // }
    // php_printf("tf_num_values ? %d\n", tf_num_values);

    // this
    t_tf_operation_description_object* intern = TF_OPERATION_DESCRIPTION_P_ZV(getThis());
    t_tf_operation_description* node = intern->ptr;

    TF_SetAttrIntList(node->src, name->val, tf_values, tf_num_values);
}

// extern void TF_SetAttrFloat(TF_OperationDescription* desc,
//                             const char* attr_name, float value);
static PHP_METHOD(TensorFlow_OperationDescription, setAttrFloat)
{
    zend_string *name;
    double value;

    ZEND_PARSE_PARAMETERS_START(2, 2)
        Z_PARAM_STR(name)
        Z_PARAM_DOUBLE(value)
    ZEND_PARSE_PARAMETERS_END();

    // this
    t_tf_operation_description_object* intern = TF_OPERATION_DESCRIPTION_P_ZV(getThis());
    t_tf_operation_description* node = intern->ptr;

    TF_SetAttrFloat(node->src, name->val, value);
}

// extern void TF_SetAttrFloatList(TF_OperationDescription* desc,
//                                 const char* attr_name, const float* values,
//                                 int num_values);
static PHP_METHOD(TensorFlow_OperationDescription, setAttrFloatList)
{
    zend_string *name;
    zval* values;

    ZEND_PARSE_PARAMETERS_START(2, 2)
        Z_PARAM_STR(name)
        Z_PARAM_ARRAY(values)
    ZEND_PARSE_PARAMETERS_END();


    float* tf_values = NULL;
    int tf_num_values = 0;

    HashTable *values_table = Z_ARRVAL_P(values);
    tf_num_values = zend_hash_num_elements(values_table); // count of array

    if (tf_num_values > 0) {
        tf_values = (float*)emalloc(sizeof(float) * tf_num_values);

        HashPosition pos;
        zval* element;
        int index = 0;

        zend_hash_internal_pointer_reset_ex(values_table, &pos);
        while (zend_hash_has_more_elements_ex(values_table, &pos) == SUCCESS) {
            if (!(element = zend_hash_get_current_data_ex(values_table, &pos))) {
                zend_throw_exception(spl_ce_InvalidArgumentException, "values something wrong", 0);
                return;
            }
            if (zval_get_type(element) != IS_DOUBLE) {
                zend_throw_exception(spl_ce_InvalidArgumentException, "values must be array of float", 0);
                return;
            }
            // insert tf_values
            tf_values[index] = Z_DVAL_P(element);
            // php_printf("%d \n", element->value.lval);
            zend_hash_move_forward_ex(values_table, &pos);

            index++;
        }
    }

    // int i;
    // for (i = 0; i < tf_num_values; i++) {
    //     php_printf("values[%f] ? %d\n", i, tf_values[i]);
    // }
    // php_printf("tf_num_values ? %d\n", tf_num_values);

    // this
    t_tf_operation_description_object* intern = TF_OPERATION_DESCRIPTION_P_ZV(getThis());
    t_tf_operation_description* node = intern->ptr;

    TF_SetAttrFloatList(node->src, name->val, tf_values, tf_num_values);
}

// extern void TF_SetAttrBool(TF_OperationDescription* desc, const char* attr_name,
//                            unsigned char value);
static PHP_METHOD(TensorFlow_OperationDescription, setAttrBool)
{
    zend_string *name;
    zend_bool value;

    ZEND_PARSE_PARAMETERS_START(2, 2)
        Z_PARAM_STR(name)
        Z_PARAM_BOOL(value)
    ZEND_PARSE_PARAMETERS_END();

    // this
    t_tf_operation_description_object* intern = TF_OPERATION_DESCRIPTION_P_ZV(getThis());
    t_tf_operation_description* node = intern->ptr;

    TF_SetAttrBool(node->src, name->val, value);
}

// extern void TF_SetAttrBoolList(TF_OperationDescription* desc,
//                                const char* attr_name,
//                                const unsigned char* values, int num_values);
static PHP_METHOD(TensorFlow_OperationDescription, setAttrBoolList)
{
    zend_string *name;
    zval* values;

    ZEND_PARSE_PARAMETERS_START(2, 2)
        Z_PARAM_STR(name)
        Z_PARAM_ARRAY(values)
    ZEND_PARSE_PARAMETERS_END();


    unsigned char* tf_values = NULL;
    int tf_num_values = 0;

    HashTable *values_table = Z_ARRVAL_P(values);
    tf_num_values = zend_hash_num_elements(values_table); // count of array

    if (tf_num_values > 0) {
        tf_values = (unsigned char*)emalloc(sizeof(unsigned char) * tf_num_values);

        HashPosition pos;
        zval* element;
        int index = 0;

        zend_hash_internal_pointer_reset_ex(values_table, &pos);
        while (zend_hash_has_more_elements_ex(values_table, &pos) == SUCCESS) {
            if (!(element = zend_hash_get_current_data_ex(values_table, &pos))) {
                zend_throw_exception(spl_ce_InvalidArgumentException, "values something wrong", 0);
                return;
            }
            if (Z_TYPE_P(element) != IS_TRUE && Z_TYPE_P(element) != IS_FALSE) {
                zend_throw_exception(spl_ce_InvalidArgumentException, "values must be array of bool", 0);
                return;
            }
            // insert tf_values
            if (Z_TYPE_P(element) == IS_TRUE) {
                tf_values[index] = 1;
            } else {
                tf_values[index] = 0;
            }
            // php_printf("%d \n", element->value.lval);
            zend_hash_move_forward_ex(values_table, &pos);

            index++;
        }
    }

    // int i;
    // for (i = 0; i < tf_num_values; i++) {
    //     php_printf("values[%d] ? %d\n", i, tf_values[i]);
    // }
    // php_printf("tf_num_values ? %d\n", tf_num_values);

    // this
    t_tf_operation_description_object* intern = TF_OPERATION_DESCRIPTION_P_ZV(getThis());
    t_tf_operation_description* node = intern->ptr;

    TF_SetAttrBoolList(node->src, name->val, tf_values, tf_num_values);
}

// extern void TF_SetAttrType(TF_OperationDescription* desc, const char* attr_name,
//                            TF_DataType value);
static PHP_METHOD(TensorFlow_OperationDescription, setAttrType)
{
    zend_string *name;
    zend_long dtype;

    ZEND_PARSE_PARAMETERS_START(2, 2)
        Z_PARAM_STR(name)
        Z_PARAM_LONG(dtype)
    ZEND_PARSE_PARAMETERS_END();

    if (!valid_dtype(dtype)) {
        zend_throw_exception(spl_ce_InvalidArgumentException, "dtype must be from 1 to 20", 0);
        return;
    }

    // this
    t_tf_operation_description_object* intern = TF_OPERATION_DESCRIPTION_P_ZV(getThis());
    t_tf_operation_description* node = intern->ptr;

    TF_SetAttrType(node->src, name->val, dtype);
}

// extern void TF_SetAttrTypeList(TF_OperationDescription* desc,
//                                const char* attr_name, const TF_DataType* values,
//                                int num_values);
static PHP_METHOD(TensorFlow_OperationDescription, setAttrTypeList)
{
    zend_string *name;
    zval* dtypes;

    ZEND_PARSE_PARAMETERS_START(2, 2)
        Z_PARAM_STR(name)
        Z_PARAM_ARRAY(dtypes)
    ZEND_PARSE_PARAMETERS_END();


    TF_DataType* tf_values = NULL;
    int tf_num_values = 0;

    HashTable *values_table = Z_ARRVAL_P(dtypes);
    tf_num_values = zend_hash_num_elements(values_table); // count of array

    if (tf_num_values > 0) {
        tf_values = (TF_DataType*)emalloc(sizeof(TF_DataType) * tf_num_values);

        HashPosition pos;
        zval* element;
        int index = 0;

        zend_hash_internal_pointer_reset_ex(values_table, &pos);
        while (zend_hash_has_more_elements_ex(values_table, &pos) == SUCCESS) {
            if (!(element = zend_hash_get_current_data_ex(values_table, &pos))) {
                zend_throw_exception(spl_ce_InvalidArgumentException, "dtypes something wrong", 0);
                return;
            }
            if (zval_get_type(element) != IS_LONG) {
                zend_throw_exception(spl_ce_InvalidArgumentException, "dtypes must be array of integer", 0);
                return;
            }
            if (!valid_dtype(Z_LVAL_P(element))) {
                zend_throw_exception(spl_ce_InvalidArgumentException, "each dtype must be from 1 to 20", 0);
                return;
            }
            // insert tf_values
            tf_values[index] = Z_LVAL_P(element);
            // php_printf("%d \n", element->value.lval);
            zend_hash_move_forward_ex(values_table, &pos);

            index++;
        }
    }

    // int i;
    // for (i = 0; i < tf_num_values; i++) {
    //     php_printf("dtypes[%d] ? %d\n", i, tf_values[i]);
    // }
    // php_printf("tf_num_values ? %d\n", tf_num_values);

    // this
    t_tf_operation_description_object* intern = TF_OPERATION_DESCRIPTION_P_ZV(getThis());
    t_tf_operation_description* node = intern->ptr;

    TF_SetAttrTypeList(node->src, name->val, tf_values, tf_num_values);
}

