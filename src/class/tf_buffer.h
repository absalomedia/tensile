#ifndef PHP_TENSILE_BUFFER_H
#define PHP_TENSILE_BUFFER_H

#include <php.h>
#include <php_ini.h>
#include <SAPI.h>
#include <ext/standard/info.h>
#include <Zend/zend_extensions.h>
#include <Zend/zend_exceptions.h>
#include <Zend/zend_interfaces.h>

#include <../../includes/tensorflow/c/c_api.h>// use this only
#include "class_abstract.h"

#define TF_BUFFER_P_ZO(zo) ((t_tf_buffer_object*)((char *)(zo) - XtOffsetOf(t_tf_buffer_object, std)))
#define TF_BUFFER_P_ZV(zv) TF_BUFFER_P_ZO(Z_OBJ_P(zv))

extern zend_class_entry *ce_TF_Buffer;
extern zend_object_handlers oh_TF_Buffer;

typedef struct _t_tf_buffer {
	TF_Buffer* src;
	zend_string* str;
	int ref;
} t_tf_buffer;

typedef struct _t_tf_buffer_object {
	zend_object std;
	t_tf_buffer* ptr;
} t_tf_buffer_object;

void define_tf_buffer_class();

#endif	/* PHP_TENSILE_BUFFER_H */



// // Get the OpList of all OpDefs defined in this address space.
// // Returns a TF_Buffer, ownership of which is transferred to the caller
// // (and can be freed using TF_DeleteBuffer).
// //
// // The data in the buffer will be the serialized OpList proto for ops registered
// // in this address space.
// extern TF_Buffer* TF_GetAllOpList();

