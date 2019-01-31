#ifndef PHP_TENSILE_STATUS_H
#define PHP_TENSILE_STATUS_H

#include <php.h>
#include <php_ini.h>
#include <SAPI.h>
#include <ext/standard/info.h>
#include <Zend/zend_extensions.h>
#include <Zend/zend_exceptions.h>
#include <Zend/zend_interfaces.h>

#include <../include/tensorflow/c/c_api.h>// use this only
#include "../utilties.h"

#define TF_STATUS_P_ZO(zo) ((t_tf_status_object*)((char *)(zo) - XtOffsetOf(t_tf_status_object, std)))
#define TF_STATUS_P_ZV(zv) TF_STATUS_P_ZO(Z_OBJ_P(zv))

extern zend_class_entry *ce_TF_Status;
extern zend_object_handlers oh_TF_Status;

typedef struct _t_tf_status {
	TF_Status* src;
	char* str;
	int ref;
} t_tf_status;

typedef struct _t_tf_status_object {
	zend_object std;
	t_tf_status* ptr;
} t_tf_status_object;

void define_tf_status_class();

t_tf_status_object* tf_status_object_fetch(zend_object *obj);

#endif	/* PHP_TENSILE_STATUS_H */
