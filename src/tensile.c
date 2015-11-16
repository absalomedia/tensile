/**
 * Tensile
 * PHP bindings to Tensorflow
 *
 * https://github.com/absalomedia/tensile
 * Copyright (c)2015 Lawrence Meckan <http://absalom.biz>
 *
 */

#include <stdio.h>
#if ZEND_MODULE_API_NO > 20131226
#include <stdlib.h>.
#endif

#include "php_tensile.h"
#include "utilities.h"

/* --------------------------------------------------------------
 * Tensile - Tensorflow
 * ------------------------------------------------------------ */

zend_object_handlers tensile_handlers;

typedef struct tensile_object {
    zend_object zo;
    int style;
    char* include_paths;
    bool comments;
    bool indent;
    long precision;
    char* map_path;
    bool omit_map_url;
    bool map_embed;
    bool map_contents;
    char* map_root;
} tensile_object;

zend_class_entry *tensile_ce;

void tensile_free_storage(void *object TSRMLS_DC)
{
    tensile_object *obj = (tensile_object *)object;
    if (obj->include_paths != NULL)
        efree(obj->include_paths);
    if (obj->map_path != NULL)
        efree(obj->map_path);
    if (obj->map_root != NULL)
        efree(obj->map_root);

    zend_hash_destroy(obj->zo.properties);
    FREE_HASHTABLE(obj->zo.properties);

    efree(obj);
}

#if ZEND_MODULE_API_NO <= 20131226
zend_object_value tensile_create_handler(zend_class_entry *type TSRMLS_DC) {
    zval *tmp;
    zend_object_value retval;

    tensile_object *obj = (tensile_object *)emalloc(sizeof(tensile_object));
    memset(obj, 0, sizeof(tensile_object));

    obj->zo.ce = type;

    ALLOC_HASHTABLE(obj->zo.properties);
    zend_hash_init(obj->zo.properties, 0, NULL, ZVAL_PTR_DTOR, 0);
#if PHP_VERSION_ID > 50399
    object_properties_init(&(obj->zo), type);
#endif

    retval.handle = zend_objects_store_put(obj, NULL,
        tensile_free_storage, NULL TSRMLS_CC);
    retval.handlers = &tensile_handlers;

    return retval;
 }
#endif

#if ZEND_MODULE_API_NO > 20131226
zend_object * tensile_create_handler(zend_class_entry *type TSRMLS_DC) {
    struct tensile_object *intern = ecalloc(1, 
         sizeof(struct tensile_object) + 
         zend_object_properties_size(type));

     zend_object_std_init(&intern->zo, type TSRMLS_CC);
     tensile_handlers.offset = XtOffsetOf(struct tensile_object, zo);
     tensile_handlers.free_obj = tensile_free_storage;
 
     intern->zo.handlers = &tensile_handlers;
 
     return &intern->zo;
}

static inline struct tensile_object * php_custom_object_fetch_object(zend_object *obj) {
      return (struct tensile_object *)((char *)obj - XtOffsetOf(struct tensile_object, zo));
}

#define Z_SASS_OBJ_P(zv) php_custom_object_fetch_object(Z_OBJ_P(zv));

#endif


PHP_METHOD(Tensile, __construct)
{
    zval *this = getThis();

    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "", NULL) == FAILURE) {
        RETURN_NULL();
    }
    #if ZEND_MODULE_API_NO > 20131226
    tensile_object *obj = Z_SASS_OBJ_P(this);
    #endif

    #if ZEND_MODULE_API_NO <= 20131226
    tensile_object *obj = (tensile_object *)zend_object_store_get_object(this TSRMLS_CC);
    #endif

    obj->style = SASS_STYLE_NESTED;
    obj->include_paths = NULL;
    obj->map_path = NULL;
    obj->map_root = NULL;
    obj->comments = false;
    obj->indent = false;
    obj->map_embed = false;
    obj->map_contents = false;
    obj->omit_map_url = true;
    obj->precision = 5;

}


void set_options(tensile_object *this, struct Tensile_Context *ctx)
{
    struct Tensile_Options* opts = tensile_context_get_options(ctx);

    tensile_option_set_precision(opts, this->precision);
    tensile_option_set_output_style(opts, this->style);
    tensile_option_set_is_indented_syntax_src(opts, this->indent);
    if (this->include_paths != NULL) {
    tensile_option_set_include_path(opts, this->include_paths);
    }
    tensile_option_set_source_comments(opts, this->comments);
    if (this->comments) {
    tensile_option_set_omit_source_map_url(opts, false);
    }
    tensile_option_set_source_map_embed(opts, this->map_embed);
    tensile_option_set_source_map_contents(opts, this->map_contents);
    if (this->map_path != NULL) {
    tensile_option_set_source_map_file(opts, this->map_path);
    tensile_option_set_omit_source_map_url(opts, false);
    tensile_option_set_source_map_contents(opts, true);
    }
    if (this->map_root != NULL) {
    tensile_option_set_source_map_root(opts, this->map_root);
    }

}

/**
 * $sass->parse(string $source, [  ]);
 *
 * Parse a string of Sass; a basic input -> output affair.
 */
PHP_METHOD(Tensile, compile)
{
    #if ZEND_MODULE_API_NO > 20131226
    tensile_object *this = Z_SASS_OBJ_P(getThis());
    #endif

    #if ZEND_MODULE_API_NO <= 20131226
    tensile_object *this = (tensile_object *)zend_object_store_get_object(getThis() TSRMLS_CC);
    #endif

    // We need a file name and a length
    #if ZEND_MODULE_API_NO <= 20131226
    // Define our parameters as local variables
    char *source;
    int source_len;

    // Use zend_parse_parameters() to grab our source from the function call
    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &source, &source_len) == FAILURE){
        RETURN_FALSE;
    }
    #endif

    // We need a file name and a length
    #if ZEND_MODULE_API_NO > 20131226
    // Define our parameters as local variables
    zend_string *source;

    // Use zend_parse_parameters() to grab our source from the function call
    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &source) == FAILURE){
        RETURN_FALSE;
    }
    #endif

    // Create a new tensile_context
    #if ZEND_MODULE_API_NO <= 20131226
    struct Tensile_Data_Context* data_context = tensile_make_data_context(strdup(source));
    #endif

    #if ZEND_MODULE_API_NO > 20131226
    struct Tensile_Data_Context* data_context = tensile_make_data_context(strdup(source->val));
    #endif

    struct Tensile_Context* ctx = tensile_data_context_get_context(data_context);

    set_options(this, ctx);

    int status = tensile_compile_data_context(data_context);

    // Check the context for any errors...
    if (status != 0)
    {
        zend_throw_exception(tensile_exception_ce, tensile_context_get_error_message(ctx), 0 TSRMLS_CC);
    }
    else
    {
        #if ZEND_MODULE_API_NO <= 20131226
        RETVAL_STRING(tensile_context_get_output_string(ctx), 1);
        #endif
        #if ZEND_MODULE_API_NO > 20131226
        RETVAL_STRING(tensile_context_get_output_string(ctx));
        #endif
    }

    tensile_delete_data_context(data_context);
}

/**
 * $sass->parse_file(string $file_name);
 *
 * Parse a whole file FULL of Sass and return the CSS output
 */
PHP_METHOD(Tensile, compileFile)
{
    array_init(return_value);

    #if ZEND_MODULE_API_NO > 20131226
    tensile_object *this = Z_SASS_OBJ_P(getThis());
    #endif

    #if ZEND_MODULE_API_NO <= 20131226
    tensile_object *this = (tensile_object *)zend_object_store_get_object(getThis() TSRMLS_CC);
    #endif

    // We need a file name and a length
    #if ZEND_MODULE_API_NO <= 20131226
    char *file;
    int file_len;

    // Grab the file name from the function
    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &file, &file_len) == FAILURE)
    {
        RETURN_FALSE;
    }
    #endif

    // We need a file name and a length
    #if ZEND_MODULE_API_NO > 20131226
    zend_string *file;

    // Grab the file name from the function
    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &file) == FAILURE)
    {
        RETURN_FALSE;
    }
    #endif

    // First, do a little checking of our own. Does the file exist?
    #if ZEND_MODULE_API_NO <= 20131226
    if( access( file, F_OK ) == -1 )
    {
        zend_throw_exception_ex(tensile_exception_ce, 0 TSRMLS_CC, "File %s could not be found", file);
        RETURN_FALSE;
    }
    #endif
     #if ZEND_MODULE_API_NO > 20131226
    if( access( file->val, F_OK ) == -1 )
    {
        zend_throw_exception_ex(tensile_exception_ce, 0 TSRMLS_CC, "File %s could not be found", file->val);
        RETURN_FALSE;
    }
    #endif    
    

    // Create a new tensile_file_context
    #if ZEND_MODULE_API_NO <= 20131226
    struct Tensile_File_Context* file_ctx = tensile_make_file_context(file);
    #endif
    #if ZEND_MODULE_API_NO > 20131226
    struct Tensile_File_Context* file_ctx = tensile_make_file_context(file->val);
    #endif

    struct Tensile_Context* ctx = tensile_file_context_get_context(file_ctx);

    set_options(this, ctx);

    int status = tensile_compile_file_context(file_ctx);

    // Check the context for any errors...
    if (status != 0)
    {
        zend_throw_exception(tensile_exception_ce, tensile_context_get_error_message(ctx), 0 TSRMLS_CC);
    }
    else
    {
        
        #if ZEND_MODULE_API_NO <= 20131226
        if (this->map_path != NULL ) {
        // Send it over to PHP.
        add_next_index_string(return_value, tensile_context_get_output_string(ctx), 1);
        } else {
        RETVAL_STRING(tensile_context_get_output_string(ctx), 1);
        }

         // Do we have source maps to go?
         if (this->map_path != NULL)
         {
         // Send it over to PHP.
         add_next_index_string(return_value, tensile_context_get_source_map_string(ctx), 1);
         }
         #endif

        #if ZEND_MODULE_API_NO > 20131226
        if (this->map_path != NULL ) {
        // Send it over to PHP.
        add_next_index_string(return_value, tensile_context_get_output_string(ctx));
        } else {
        RETVAL_STRING(tensile_context_get_output_string(ctx));
        }

         // Do we have source maps to go?
         if (this->map_path != NULL)
         {
         // Send it over to PHP.
         add_next_index_string(return_value, tensile_context_get_source_map_string(ctx));
         }
         #endif
    }

    tensile_delete_file_context(file_ctx);
}

PHP_METHOD(Tensile, getStyle)
{
    zval *this = getThis();

    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "", NULL) == FAILURE) {
        RETURN_FALSE;
    }

    #if ZEND_MODULE_API_NO > 20131226
    tensile_object *obj = Z_SASS_OBJ_P(this);
    #endif
    #if ZEND_MODULE_API_NO <= 20131226
    tensile_object *obj = (tensile_object *)zend_object_store_get_object(this TSRMLS_CC);
    #endif 

    RETURN_LONG(obj->style);
}

PHP_METHOD(Tensile, setStyle)
{
    zval *this = getThis();

    long new_style;

    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "l", &new_style) == FAILURE) {
        RETURN_FALSE;
    }

    #if ZEND_MODULE_API_NO > 20131226
    tensile_object *obj = Z_SASS_OBJ_P(this);
    #endif
    #if ZEND_MODULE_API_NO <= 20131226
    tensile_object *obj = (tensile_object *)zend_object_store_get_object(this TSRMLS_CC);
    #endif 
    obj->style = new_style;

    RETURN_NULL();
}

PHP_METHOD(Tensile, getIncludePath)
{
    zval *this = getThis();

    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "", NULL) == FAILURE) {
        RETURN_FALSE;
    }

    #if ZEND_MODULE_API_NO > 20131226
    tensile_object *obj = Z_SASS_OBJ_P(this);
    #endif
    #if ZEND_MODULE_API_NO <= 20131226
    tensile_object *obj = (tensile_object *)zend_object_store_get_object(this TSRMLS_CC);
    #endif  

    #if ZEND_MODULE_API_NO <= 20131226
    if (obj->include_paths == NULL) RETURN_STRING("", 1);
    RETURN_STRING(obj->include_paths, 1);
    #endif

    #if ZEND_MODULE_API_NO > 20131226
    if (obj->include_paths == NULL) RETURN_STRING("");
    RETURN_STRING(obj->include_paths);
    #endif
}

PHP_METHOD(Tensile, setIncludePath)
{
    zval *this = getThis();

    char *path;
    int path_len;

    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &path, &path_len) == FAILURE)
        RETURN_FALSE;

    #if ZEND_MODULE_API_NO > 20131226
    tensile_object *obj = Z_SASS_OBJ_P(this);
    #endif
    #if ZEND_MODULE_API_NO <= 20131226
    tensile_object *obj = (tensile_object *)zend_object_store_get_object(this TSRMLS_CC);
    #endif  

    if (obj->include_paths != NULL)
        efree(obj->include_paths);
    obj->include_paths = estrndup(path, path_len);

    RETURN_NULL();
}

PHP_METHOD(Tensile, getMapPath)
{
    zval *this = getThis();

    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "", NULL) == FAILURE) {
        RETURN_FALSE;
    }

    #if ZEND_MODULE_API_NO > 20131226
    tensile_object *obj = Z_SASS_OBJ_P(this);
    #endif
    #if ZEND_MODULE_API_NO <= 20131226
    tensile_object *obj = (tensile_object *)zend_object_store_get_object(this TSRMLS_CC);
    #endif  

    #if ZEND_MODULE_API_NO <= 20131226
    if (obj->map_path == NULL) RETURN_STRING("", 1);
    RETURN_STRING(obj->map_path, 1);
    #endif

    #if ZEND_MODULE_API_NO > 20131226
    if (obj->map_path == NULL) RETURN_STRING("");
    RETURN_STRING(obj->map_path);
    #endif
}

PHP_METHOD(Tensile, setMapPath)
{
    zval *this = getThis();

    char *path;
    int path_len;

    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &path, &path_len) == FAILURE)
        RETURN_FALSE;

    #if ZEND_MODULE_API_NO > 20131226
    tensile_object *obj = Z_SASS_OBJ_P(this);
    #endif
    #if ZEND_MODULE_API_NO <= 20131226
    tensile_object *obj = (tensile_object *)zend_object_store_get_object(this TSRMLS_CC);
    #endif  

    if (obj->map_path != NULL)
        efree(obj->map_path);
    obj->map_path = estrndup(path, path_len);

    RETURN_NULL();
}


PHP_METHOD(Tensile, getPrecision)
{
    zval *this = getThis();

    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "", NULL) == FAILURE) {
        RETURN_FALSE;
    }

    #if ZEND_MODULE_API_NO > 20131226
    tensile_object *obj = Z_SASS_OBJ_P(this);
    #endif
    #if ZEND_MODULE_API_NO <= 20131226
    tensile_object *obj = (tensile_object *)zend_object_store_get_object(this TSRMLS_CC);
    #endif  

    RETURN_LONG(obj->precision);
}

PHP_METHOD(Tensile, setPrecision)
{
    zval *this = getThis();

    long new_precision;

    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "l", &new_precision) == FAILURE) {
        RETURN_FALSE;
    }

    #if ZEND_MODULE_API_NO > 20131226
    tensile_object *obj = Z_SASS_OBJ_P(this);
    #endif
    #if ZEND_MODULE_API_NO <= 20131226
    tensile_object *obj = (tensile_object *)zend_object_store_get_object(this TSRMLS_CC);
    #endif 

    obj->precision = new_precision;

    RETURN_NULL();
}

PHP_METHOD(Tensile, getEmbed)
{
    zval *this = getThis();

    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "", NULL) == FAILURE) {
        RETURN_FALSE;
    }

    #if ZEND_MODULE_API_NO > 20131226
    tensile_object *obj = Z_SASS_OBJ_P(this);
    #endif
    #if ZEND_MODULE_API_NO <= 20131226
    tensile_object *obj = (tensile_object *)zend_object_store_get_object(this TSRMLS_CC);
    #endif  

    RETURN_LONG(obj->map_embed);
}

PHP_METHOD(Tensile, setEmbed)
{
    zval *this = getThis();

    bool new_map_embed;

    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "l", &new_map_embed) == FAILURE) {
        RETURN_FALSE;
    }

    #if ZEND_MODULE_API_NO > 20131226
    tensile_object *obj = Z_SASS_OBJ_P(this);
    #endif
    #if ZEND_MODULE_API_NO <= 20131226
    tensile_object *obj = (tensile_object *)zend_object_store_get_object(this TSRMLS_CC);
    #endif  

    obj->map_embed = new_map_embed;

    RETURN_NULL();
}


PHP_METHOD(Tensile, getComments)
{
    zval *this = getThis();

    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "", NULL) == FAILURE) {
        RETURN_FALSE;
    }

    #if ZEND_MODULE_API_NO > 20131226
    tensile_object *obj = Z_SASS_OBJ_P(this);
    #endif
    #if ZEND_MODULE_API_NO <= 20131226
    tensile_object *obj = (tensile_object *)zend_object_store_get_object(this TSRMLS_CC);
    #endif 

    RETURN_LONG(obj->comments);
}

PHP_METHOD(Tensile, setComments)
{
    zval *this = getThis();

    bool new_comments;

    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "l", &new_comments) == FAILURE) {
        RETURN_FALSE;
    }

    #if ZEND_MODULE_API_NO > 20131226
    tensile_object *obj = Z_SASS_OBJ_P(this);
    #endif
    #if ZEND_MODULE_API_NO <= 20131226
    tensile_object *obj = (tensile_object *)zend_object_store_get_object(this TSRMLS_CC);
    #endif  

    obj->comments = new_comments;

    RETURN_NULL();
}


PHP_METHOD(Tensile, getIndent)
{
    zval *this = getThis();

    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "", NULL) == FAILURE) {
        RETURN_FALSE;
    }

    #if ZEND_MODULE_API_NO > 20131226
    tensile_object *obj = Z_SASS_OBJ_P(this);
    #endif
    #if ZEND_MODULE_API_NO <= 20131226
    tensile_object *obj = (tensile_object *)zend_object_store_get_object(this TSRMLS_CC);
    #endif 

    RETURN_LONG(obj->indent);
}

PHP_METHOD(Tensile, setIndent)
{
    zval *this = getThis();

    bool new_indent;

    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "l", &new_indent) == FAILURE) {
        RETURN_FALSE;
    }

    #if ZEND_MODULE_API_NO > 20131226
    tensile_object *obj = Z_SASS_OBJ_P(this);
    #endif
    #if ZEND_MODULE_API_NO <= 20131226
    tensile_object *obj = (tensile_object *)zend_object_store_get_object(this TSRMLS_CC);
    #endif 

    obj->indent = new_indent;

    RETURN_NULL();
}


PHP_METHOD(Tensile, getLibraryVersion)
{
    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "", NULL) == FAILURE) {
        RETURN_FALSE;
    }

    #if ZEND_MODULE_API_NO <= 20131226
    RETURN_STRING(libtensile_version(), 1);
    #endif

    #if ZEND_MODULE_API_NO > 20131226
    RETURN_STRING(libtensile_version());
    #endif
    
}
/* --------------------------------------------------------------
 * EXCEPTION HANDLING
 * ------------------------------------------------------------ */

zend_class_entry *tensile_get_exception_base(TSRMLS_D)
{
    return zend_exception_get_default(TSRMLS_C);
}

/* --------------------------------------------------------------
 * PHP EXTENSION INFRASTRUCTURE
 * ------------------------------------------------------------ */

ZEND_BEGIN_ARG_INFO(arginfo_tensile_void, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_tensile_compile, 0, 0, 1)
    ZEND_ARG_INFO(0, tensile_string)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_tensile_compileFile, 0, 0, 1)
    ZEND_ARG_INFO(0, filename)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_tensile_setStyle, 0, 0, 1)
    ZEND_ARG_INFO(0, style)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_tensile_setIncludePath, 0, 0, 1)
    ZEND_ARG_INFO(0, include_path)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_tensile_setPrecision, 0, 0, 1)
    ZEND_ARG_INFO(0, precision)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_tensile_setComments, 0, 0, 1)
    ZEND_ARG_INFO(0, comments)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_tensile_setIndent, 0, 0, 1)
    ZEND_ARG_INFO(0, indent)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_tensile_setEmbed, 0, 0, 1)
    ZEND_ARG_INFO(0, map_embed)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_tensile_setMapPath, 0, 0, 1)
    ZEND_ARG_INFO(0, map_path)
ZEND_END_ARG_INFO()


zend_function_entry tensile_methods[] = {
    PHP_ME(Tensile,  __construct,       arginfo_tensile_void,           ZEND_ACC_PUBLIC | ZEND_ACC_CTOR)
    PHP_ME(Tensile,  compile,           arginfo_tensile_compile,        ZEND_ACC_PUBLIC)
    PHP_ME(Tensile,  compileFile,       arginfo_tensile_compileFile,    ZEND_ACC_PUBLIC)
    PHP_ME(Tensile,  getStyle,          arginfo_tensile_void,           ZEND_ACC_PUBLIC)
    PHP_ME(Tensile,  setStyle,          arginfo_tensile_setStyle,       ZEND_ACC_PUBLIC)
    PHP_ME(Tensile,  getIncludePath,    arginfo_tensile_void,           ZEND_ACC_PUBLIC)
    PHP_ME(Tensile,  setIncludePath,    arginfo_tensile_setIncludePath, ZEND_ACC_PUBLIC)
    PHP_ME(Tensile,  getPrecision,      arginfo_tensile_void,           ZEND_ACC_PUBLIC)
    PHP_ME(Tensile,  setPrecision,      arginfo_tensile_setPrecision,   ZEND_ACC_PUBLIC)
    PHP_ME(Tensile,  getComments,       arginfo_tensile_void,           ZEND_ACC_PUBLIC)
    PHP_ME(Tensile,  setComments,       arginfo_tensile_setComments,    ZEND_ACC_PUBLIC)
    PHP_ME(Tensile,  getIndent,         arginfo_tensile_void,           ZEND_ACC_PUBLIC)
    PHP_ME(Tensile,  setIndent,         arginfo_tensile_setIndent,      ZEND_ACC_PUBLIC)
    PHP_ME(Tensile,  getEmbed,          arginfo_tensile_void,           ZEND_ACC_PUBLIC)
    PHP_ME(Tensile,  setEmbed,          arginfo_tensile_setEmbed,       ZEND_ACC_PUBLIC)
    PHP_ME(Tensile,  getMapPath,        arginfo_tensile_void,           ZEND_ACC_PUBLIC)
    PHP_ME(Tensile,  setMapPath,        arginfo_tensile_setMapPath,     ZEND_ACC_PUBLIC)
    PHP_ME(Tensile,  getLibraryVersion, arginfo_tensile_void,           ZEND_ACC_PUBLIC | ZEND_ACC_STATIC)
    PHP_MALIAS(Tensile, compile_file, compileFile, NULL, ZEND_ACC_PUBLIC)
    {NULL, NULL, NULL}
};


static PHP_MINIT_FUNCTION(sass)
{
    zend_class_entry ce;
    zend_class_entry exception_ce;

    INIT_CLASS_ENTRY(ce, "Sass", tensile_methods);

    tensile_ce = zend_register_internal_class(&ce TSRMLS_CC);
    tensile_ce->create_object = tensile_create_handler;

    memcpy(&tensile_handlers, zend_get_std_object_handlers(), sizeof(zend_object_handlers));
    #if ZEND_MODULE_API_NO > 20131226
    tensile_handlers.offset = XtOffsetOf(tensile_object, zo);
    #endif
    tensile_handlers.clone_obj = NULL;

    INIT_CLASS_ENTRY(exception_ce, "SassException", NULL);

    #if ZEND_MODULE_API_NO > 20131226
    tensile_exception_ce = zend_register_internal_class_ex(&exception_ce, tensile_get_exception_base(TSRMLS_C));
    #endif

    #if ZEND_MODULE_API_NO <= 20131226
    tensile_exception_ce = zend_register_internal_class_ex(&exception_ce, tensile_get_exception_base(TSRMLS_C), NULL TSRMLS_CC);
    #endif

    #define REGISTER_SASS_CLASS_CONST_LONG(name, value) zend_declare_class_constant_long(tensile_ce, ZEND_STRS( #name ) - 1, value TSRMLS_CC)

    REGISTER_SASS_CLASS_CONST_LONG(STYLE_NESTED, SASS_STYLE_NESTED);
    REGISTER_SASS_CLASS_CONST_LONG(STYLE_EXPANDED, SASS_STYLE_EXPANDED);
    REGISTER_SASS_CLASS_CONST_LONG(STYLE_COMPACT, SASS_STYLE_COMPACT);
    REGISTER_SASS_CLASS_CONST_LONG(STYLE_COMPRESSED, SASS_STYLE_COMPRESSED);

    REGISTER_STRING_CONSTANT("SASS_FLAVOR", SASS_FLAVOR, CONST_CS | CONST_PERSISTENT);


    return SUCCESS;
}

static PHP_MINFO_FUNCTION(sass)
{
    php_info_print_table_start();
    php_info_print_table_row(2, "sass support", "enabled");
    php_info_print_table_row(2, "version", SASS_VERSION);
    php_info_print_table_row(2, "flavor", SASS_FLAVOR);
    php_info_print_table_row(2, "libsass version", libtensile_version());
    php_info_print_table_end();
}

static zend_module_entry tensile_module_entry = {
    STANDARD_MODULE_HEADER,
    "sass",
    NULL,
    PHP_MINIT(sass),
    NULL,
    NULL,
    NULL,
    PHP_MINFO(sass),
    SASS_VERSION,
    STANDARD_MODULE_PROPERTIES
};

#ifdef COMPILE_DL_SASS
ZEND_GET_MODULE(sass)
#endif
