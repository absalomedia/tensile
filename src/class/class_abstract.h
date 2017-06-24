#ifndef PHP_CLASS_ABSTRACT_H
#define PHP_CLASS_ABSTRACT_H

#define DEFINE_CLASS(Name, name, class_entry, object_handler) \
    zend_class_entry temp_ce; \
    INIT_NS_CLASS_ENTRY(temp_ce, "Tensile", #Name, tf_##name##_methods); \
    class_entry = zend_register_internal_class(&temp_ce); \
    class_entry->create_object = tf_##name##_object_create; \
    memcpy(&object_handler, zend_get_std_object_handlers(), sizeof(zend_object_handlers)); \
    object_handler.clone_obj = NULL; \
    object_handler.free_obj = tf_##name##_object_free; \
    object_handler.offset = XtOffsetOf(t_tf_##name##_object, std);

#define CA_OBJECT_CREATE(name, t_class, t_class_object, object_handler) \
    zend_object* tf_##name##_object_create(zend_class_entry *ce TSRMLS_DC) { \
        t_class_object* intern; \
        t_class *node = NULL; \
        intern = (t_class_object *)ecalloc(1, sizeof(t_class_object)); \
        node = (t_class *)ecalloc(1, sizeof(t_class)); \
        if (node != NULL) { \
            node->src = NULL; \
            node->str = NULL; \
            node->ref = 1; \
        } \
        intern->ptr = node; \
        zend_object_std_init(&intern->std, ce TSRMLS_CC); \
        object_properties_init(&intern->std, ce); \
        intern->std.handlers = &object_handler; \
        return &intern->std; \
    }

#define CA_OBJECT_FREE(name, t_class, t_class_object) \
    static void tf_##name##_object_free(zend_object *object TSRMLS_DC) { \
        t_class_object* intern = (t_class_object*)((char *)object - XtOffsetOf(t_class_object, std)); \
        t_class* node = intern->ptr; \
        node->ref--; \
        if (node->ref == 0) { \
            if (node->str != NULL) { \
                zend_string_release(node->str); \
            } \
            efree(node); \
        } \
        zend_object_std_dtor(&intern->std TSRMLS_CC); \
    }


#endif  /* PHP_CLASS_ABSTRACT_H */
