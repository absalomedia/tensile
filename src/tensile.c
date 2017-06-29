/**
 * Tensile
 * PHP bindings to Tensorflow
 *
 * https://github.com/absalomedia/tensile
 * Copyright (c)2017 Lawrence Meckan <http://absalom.biz>
 *
 */

#include "php_tensile.h"

#include "class/tf_dtype.h"
#include "class/tf_status.h"
#include "class/tf_buffer.h"
#include "class/tf_tensor.h"
#include "class/tf_graph.h"
#include "class/tf_operation_description.h"
#include "class/tf_session_options.h"
#include "class/tf_session.h"



// functions
static zend_function_entry tf_functions[] = {
    ZEND_NS_FE("Tensile", NULL, NULL)
    PHP_FE_END
};

// the following code creates an entry for the module and registers it with Zend.
zend_module_entry tensile_module_entry = {
#if ZEND_MODULE_API_NO >= 20010901
    STANDARD_MODULE_HEADER,
#endif
    TENSILE_FLAVOR,
    tf_functions,
    PHP_MINIT(tensile),
    NULL, // name of the MSHUTDOWN function or NULL if not applicable
    NULL, // name of the RINIT function or NULL if not applicable
    NULL, // name of the RSHUTDOWN function or NULL if not applicable
    PHP_MINFO(tensile),
#if ZEND_MODULE_API_NO >= 20010901
    TENSILE_VERSION,
#endif
    STANDARD_MODULE_PROPERTIES
};

ZEND_GET_MODULE(tensile)

static PHP_MINFO_FUNCTION(tensile)
{
    
    php_info_print_table_start();
    php_info_print_table_row(2, "Tensorflow Support", "enabled");
    php_info_print_table_row(2, "Build", TENSILE_VERSION);
    php_info_print_table_row(2, "Release", TENSILE_FLAVOR);
    php_info_print_table_row(2, "Tensorflow version", TF_Version());
    php_info_print_table_end();    
    
    DISPLAY_INI_ENTRIES();
}    



static PHP_FUNCTION(debug)
{    
    #if PHP_MAJOR_VERSION < 7
    RETURN_STRING("Hello Dave",0);
    #else
    RETURN_STRING("Hello Dave");
    #endif
    
}
    
static PHP_MINIT_FUNCTION(tensile)
{
    REGISTER_NS_STRING_CONSTANT("Tensile", "VERSION", (char *)TF_Version(), CONST_PERSISTENT | CONST_CS);

    REGISTER_NS_LONG_CONSTANT("Tensile", "DTYPE_FLOAT", 1, CONST_PERSISTENT | CONST_CS);
    REGISTER_NS_LONG_CONSTANT("Tensile", "DTYPE_DOUBLE", 2, CONST_PERSISTENT | CONST_CS);
    REGISTER_NS_LONG_CONSTANT("Tensile", "DTYPE_INT32", 3, CONST_PERSISTENT | CONST_CS);
    REGISTER_NS_LONG_CONSTANT("Tensile", "DTYPE_UINT8", 4, CONST_PERSISTENT | CONST_CS);
    REGISTER_NS_LONG_CONSTANT("Tensile", "DTYPE_INT16", 5, CONST_PERSISTENT | CONST_CS);
    REGISTER_NS_LONG_CONSTANT("Tensile", "DTYPE_INT8", 6, CONST_PERSISTENT | CONST_CS);
    REGISTER_NS_LONG_CONSTANT("Tensile", "DTYPE_STRING", 7, CONST_PERSISTENT | CONST_CS);
    REGISTER_NS_LONG_CONSTANT("Tensile", "DTYPE_COMPLEX64", 8, CONST_PERSISTENT | CONST_CS);
    REGISTER_NS_LONG_CONSTANT("Tensile", "DTYPE_COMPLEX", 8, CONST_PERSISTENT | CONST_CS);
    REGISTER_NS_LONG_CONSTANT("Tensile", "DTYPE_INT64", 9, CONST_PERSISTENT | CONST_CS);
    REGISTER_NS_LONG_CONSTANT("Tensile", "DTYPE_BOOL", 10, CONST_PERSISTENT | CONST_CS);
    REGISTER_NS_LONG_CONSTANT("Tensile", "DTYPE_QINT8", 11, CONST_PERSISTENT | CONST_CS);
    REGISTER_NS_LONG_CONSTANT("Tensile", "DTYPE_QUINT8", 12, CONST_PERSISTENT | CONST_CS);
    REGISTER_NS_LONG_CONSTANT("Tensile", "DTYPE_QINT32", 13, CONST_PERSISTENT | CONST_CS);
    REGISTER_NS_LONG_CONSTANT("Tensile", "DTYPE_BFLOAT16", 14, CONST_PERSISTENT | CONST_CS);
    REGISTER_NS_LONG_CONSTANT("Tensile", "DTYPE_QINT16", 15, CONST_PERSISTENT | CONST_CS);
    REGISTER_NS_LONG_CONSTANT("Tensile", "DTYPE_QUINT16", 16, CONST_PERSISTENT | CONST_CS);
    REGISTER_NS_LONG_CONSTANT("Tensile", "DTYPE_UINT16", 17, CONST_PERSISTENT | CONST_CS);
    REGISTER_NS_LONG_CONSTANT("Tensile", "DTYPE_COMPLEX128", 18, CONST_PERSISTENT | CONST_CS);
    REGISTER_NS_LONG_CONSTANT("Tensile", "DTYPE_HALF", 19, CONST_PERSISTENT | CONST_CS);
    REGISTER_NS_LONG_CONSTANT("Tensile", "DTYPE_RESOURCE", 20, CONST_PERSISTENT | CONST_CS);

    define_tf_status_class();
    define_tf_buffer_class();
    define_tf_tensor_class();
    define_tf_graph_class();
    define_tf_operation_description_class();
    define_tf_session_options_class();
    define_tf_session_class();

    return SUCCESS;
}

