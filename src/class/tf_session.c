
#include "tf_session.h"

// predefine
zend_class_entry *ce_TF_Session = NULL;
zend_object_handlers oh_TF_Session;

// methods
static PHP_METHOD(TensorFlow_Session, __construct);
static PHP_METHOD(TensorFlow_Session, __destruct);
static PHP_METHOD(TensorFlow_Session, close);

// argument info
ZEND_BEGIN_ARG_INFO_EX(arginfo_tf_session___construct, 0, 0, 3)
    ZEND_ARG_INFO(0, graph)
    ZEND_ARG_INFO(0, sessionOptions)
    ZEND_ARG_INFO(0, status)
ZEND_END_ARG_INFO()
ZEND_BEGIN_ARG_INFO_EX(arginfo_tf_session_close, 0, 0, 1)
    ZEND_ARG_INFO(0, status)
ZEND_END_ARG_INFO()

// methods
static zend_function_entry tf_session_methods[] = {
    PHP_ME(TensorFlow_Session, __construct, arginfo_tf_session___construct, ZEND_ACC_PUBLIC)
    PHP_ME(TensorFlow_Session, __destruct, NULL, ZEND_ACC_PUBLIC)
    PHP_ME(TensorFlow_Session, close, arginfo_tf_session_close, ZEND_ACC_PUBLIC)
    PHP_FE_END
};

CA_OBJECT_CREATE(session, t_tf_session, t_tf_session_object, oh_TF_Session)
CA_OBJECT_FREE(session, t_tf_session, t_tf_session_object)

void define_tf_session_class()
{
    DEFINE_CLASS(Session, session, ce_TF_Session, oh_TF_Session)
}

// extern TF_Session* TF_NewSession(TF_Graph* graph, const TF_SessionOptions* opts,
//                                  TF_Status* status);
static PHP_METHOD(TensorFlow_Session, __construct)
{
    zval* graph;
    zval* sessionOptions;
    zval* status;

    ZEND_PARSE_PARAMETERS_START(3, 3)
        Z_PARAM_OBJECT_OF_CLASS_EX(graph, ce_TF_Graph, 0, 1)
        Z_PARAM_OBJECT_OF_CLASS_EX(sessionOptions, ce_TF_SessionOptions, 0, 1)
        Z_PARAM_OBJECT_OF_CLASS_EX(status, ce_TF_Status, 0, 1)
    ZEND_PARSE_PARAMETERS_END();

    t_tf_session_object* intern = TF_SESSION_P_ZV(getThis());
    t_tf_session* node = intern->ptr;

    node->src = TF_NewSession(
        TF_GRAPH_P_ZV(graph)->ptr->src,
        TF_SESSION_OPTIONS_P_ZV(sessionOptions)->ptr->src,
        TF_STATUS_P_ZV(status)->ptr->src
    );
}

// extern void TF_DeleteSession(TF_Session*);
static PHP_METHOD(TensorFlow_Session, __destruct)
{
    t_tf_session_object* intern = TF_SESSION_P_ZV(getThis());
    t_tf_session* node = intern->ptr;

    // TF_DeleteSession(node->src);
}

// extern void TF_CloseSession(TF_Session*, TF_Status* status);
static PHP_METHOD(TensorFlow_Session, close)
{
    zval* status;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_OBJECT_OF_CLASS_EX(status, ce_TF_Status, 0, 1)
    ZEND_PARSE_PARAMETERS_END();

    // php_printf("target : %s\n", target->val);

    t_tf_session_object* intern = TF_SESSION_P_ZV(getThis());
    t_tf_session* node = intern->ptr;

    TF_CloseSession(node->src, TF_STATUS_P_ZV(status)->ptr->src);
}

// // Destroy a session object.
// //
// // Even if error information is recorded in *status, this call discards all
// // local resources associated with the session.  The session may not be used
// // during or after this call (and the session drops its reference to the
// // corresponding graph).
// extern void TF_DeleteSession(TF_Session*, TF_Status* status);

// // Run the graph associated with the session starting with the supplied inputs
// // (inputs[0,ninputs-1] with corresponding values in input_values[0,ninputs-1]).
// //
// // Any NULL and non-NULL value combinations for (`run_options`,
// // `run_metadata`) are valid.
// //
// //    - `run_options` may be NULL, in which case it will be ignored; or
// //      non-NULL, in which case it must point to a `TF_Buffer` containing the
// //      serialized representation of a `RunOptions` protocol buffer.
// //    - `run_metadata` may be NULL, in which case it will be ignored; or
// //      non-NULL, in which case it must point to an empty, freshly allocated
// //      `TF_Buffer` that may be updated to contain the serialized representation
// //      of a `RunMetadata` protocol buffer.
// //
// // The caller retains ownership of `input_values` (which can be deleted using
// // TF_DeleteTensor). The caller also retains ownership of `run_options` and/or
// // `run_metadata` (when not NULL) and should manually call TF_DeleteBuffer on
// // them.
// //
// // On success, the tensors corresponding to outputs[0,noutputs-1] are placed in
// // output_values[]. Ownership of the elements of output_values[] is transferred
// // to the caller, which must eventually call TF_DeleteTensor on them.
// //
// // On failure, output_values[] contains NULLs.
// extern void TF_SessionRun(TF_Session* session,
//                           // RunOptions
//                           const TF_Buffer* run_options,
//                           // Input tensors
//                           const TF_Output* inputs,
//                           TF_Tensor* const* input_values, int ninputs,
//                           // Output tensors
//                           const TF_Output* outputs, TF_Tensor** output_values,
//                           int noutputs,
//                           // Target operations
//                           const TF_Operation* const* target_opers, int ntargets,
//                           // RunMetadata
//                           TF_Buffer* run_metadata,
//                           // Output status
//                           TF_Status*);

// // Set up the graph with the intended feeds (inputs) and fetches (outputs) for a
// // sequence of partial run calls.
// //
// // On success, returns a handle that is used for subsequent PRun calls.
// //
// // On failure, out_status contains a tensorflow::Status with an error
// // message.
// // NOTE: This is EXPERIMENTAL and subject to change.
// extern void TF_SessionPRunSetup(TF_Session*,
//                                 // Input names
//                                 const TF_Output* inputs, int ninputs,
//                                 // Output names
//                                 const TF_Output* outputs, int noutputs,
//                                 // Target operations
//                                 const TF_Operation* const* target_opers,
//                                 int ntargets,
//                                 // Output handle
//                                 const char** handle,
//                                 // Output status
//                                 TF_Status*);

// // Continue to run the graph with additional feeds and fetches. The
// // execution state is uniquely identified by the handle.
// // NOTE: This is EXPERIMENTAL and subject to change.
// extern void TF_SessionPRun(TF_Session*, const char* handle,
//                            // Input tensors
//                            const TF_Output* inputs,
//                            TF_Tensor* const* input_values, int ninputs,
//                            // Output tensors
//                            const TF_Output* outputs, TF_Tensor** output_values,
//                            int noutputs,
//                            // Target operations
//                            const TF_Operation* const* target_opers,
//                            int ntargets,
//                            // Output status
//                            TF_Status*);
