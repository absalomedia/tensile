/**
 * Tensile
 * PHP bindings to Tensorflow
 *
 * https://github.com/absalomedia/tensile
 * Copyright (c) 2017-2019 Lawrence Meckan <http://absalom.biz>
 *
 *
 */


#ifndef PHP_TENSILE_H
#define PHP_TENSILE_H

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <php.h>

#include <php_ini.h>
#include <SAPI.h>
#include <ext/standard/info.h>
#include <Zend/zend_extensions.h>
#include <Zend/zend_exceptions.h>
#include <Zend/zend_interfaces.h>

#include <include/tensorflow/c/c_api.h>
#include "utilities.h"

zend_class_entry *tensile_ce;
zend_class_entry *tensile_exception_ce;

zend_class_entry *tensile_get_exception_base();

#define TENSILE_VERSION "0.9.0"
#define TENSILE_FLAVOR "Tonewood"

#define TENSILE_NS "Tensile"

#define TF_BUFFER_P_ZO(zo) ((t_tf_buffer_object*)((char *)(zo) - XtOffsetOf(t_tf_buffer_object, std)))
#define TF_BUFFER_P_ZV(zv) TF_BUFFER_P_ZO(Z_OBJ_P(zv))

extern zend_class_entry *ce_TF_Buffer;
extern zend_object_handlers oh_TF_Buffer;

typedef struct _t_tf_buffer {
	TF_Buffer* src;
	char* str;
	int ref;
} t_tf_buffer;

typedef struct _t_tf_buffer_object {
	zend_object std;
	t_tf_buffer* ptr;
} t_tf_buffer_object;

void define_tf_buffer_class();

size_t tf_dtype_sizeof(TF_DataType type);

char valid_dtype(int64_t dtype);


static PHP_MINFO_FUNCTION(tensile);
static PHP_MINIT_FUNCTION(tensile);

extern zend_module_entry tensile_module_entry;

#endif