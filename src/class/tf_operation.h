// // Operation that has been added to the graph. Valid until the graph is
// // deleted -- in particular adding a new operation to the graph does not
// // invalidate old TF_Operation* pointers.
// typedef struct TF_Operation TF_Operation;

// // TF_Operation functions.  Operations are immutable once created, so
// // these are all query functions.

// extern const char* TF_OperationName(TF_Operation* oper);
// extern const char* TF_OperationOpType(TF_Operation* oper);
// extern const char* TF_OperationDevice(TF_Operation* oper);

// extern int TF_OperationNumOutputs(TF_Operation* oper);
// extern TF_DataType TF_OperationOutputType(TF_Output oper_out);
// extern int TF_OperationOutputListLength(TF_Operation* oper,
//                                         const char* arg_name,
//                                         TF_Status* status);

// extern int TF_OperationNumInputs(TF_Operation* oper);
// extern TF_DataType TF_OperationInputType(TF_Input oper_in);
// extern int TF_OperationInputListLength(TF_Operation* oper, const char* arg_name,
//                                        TF_Status* status);


// // Get the number of control inputs to an operation.
// extern int TF_OperationNumControlInputs(TF_Operation* oper);

// // Get list of all control inputs to an operation.  `control_inputs` must
// // point to an array of length `max_control_inputs` (ideally set to
// // TF_OperationNumControlInputs(oper)).  Returns the number of control
// // inputs (should match TF_OperationNumControlInputs(oper)).
// extern int TF_OperationGetControlInputs(TF_Operation* oper,
//                                         TF_Operation** control_inputs,
//                                         int max_control_inputs);

// // Get the number of operations that have `*oper` as a control input.
// // Note that this number can change when new operations are added to
// // the graph.
// extern int TF_OperationNumControlOutputs(TF_Operation* oper);

// // Get the list of operations that have `*oper` as a control input.
// // `control_outputs` must point to an array of length at least
// // `max_control_outputs` (ideally set to
// // TF_OperationNumControlOutputs(oper)). Beware that a concurrent
// // modification of the graph can increase the number of control
// // outputs.  Returns the number of control outputs (should match
// // TF_OperationNumControlOutputs(oper)).
// extern int TF_OperationGetControlOutputs(TF_Operation* oper,
//                                          TF_Operation** control_outputs,
//                                          int max_control_outputs);

// // Fills in `value` with the value of the attribute `attr_name`.  `value` must
// // point to an array of length at least `max_length` (ideally set to
// // TF_AttrMetadata.total_size from TF_OperationGetAttrMetadata(oper,
// // attr_name)).
// extern void TF_OperationGetAttrString(TF_Operation* oper, const char* attr_name,
//                                       void* value, size_t max_length,
//                                       TF_Status* status);

// // Get the list of strings in the value of the attribute `attr_name`.  Fills in
// // `values` and `lengths`, each of which must point to an array of length at
// // least `max_values`.
// //
// // The elements of values will point to addresses in `storage` which must be at
// // least `storage_size` bytes in length.  Ideally, max_values would be set to
// // TF_AttrMetadata.list_size and `storage` would be at least
// // TF_AttrMetadata.total_size, obtained from TF_OperationGetAttrMetadata(oper,
// // attr_name).
// //
// // Fails if storage_size is too small to hold the requested number of strings.
// extern void TF_OperationGetAttrStringList(TF_Operation* oper,
//                                           const char* attr_name, void** values,
//                                           size_t* lengths, int max_values,
//                                           void* storage, size_t storage_size,
//                                           TF_Status* status);

// extern void TF_OperationGetAttrInt(TF_Operation* oper, const char* attr_name,
//                                    int64_t* value, TF_Status* status);

// // Fills in `values` with the value of the attribute `attr_name` of `oper`.
// // `values` must point to an array of length at least `max_values` (ideally set
// // TF_AttrMetadata.list_size from TF_OperationGetAttrMetadata(oper,
// // attr_name)).
// extern void TF_OperationGetAttrIntList(TF_Operation* oper,
//                                        const char* attr_name, int64_t* values,
//                                        int max_values, TF_Status* status);

// extern void TF_OperationGetAttrFloat(TF_Operation* oper, const char* attr_name,
//                                      float* value, TF_Status* status);

// // Fills in `values` with the value of the attribute `attr_name` of `oper`.
// // `values` must point to an array of length at least `max_values` (ideally set
// // to TF_AttrMetadata.list_size from TF_OperationGetAttrMetadata(oper,
// // attr_name)).
// extern void TF_OperationGetAttrFloatList(TF_Operation* oper,
//                                          const char* attr_name, float* values,
//                                          int max_values, TF_Status* status);

// extern void TF_OperationGetAttrBool(TF_Operation* oper, const char* attr_name,
//                                     unsigned char* value, TF_Status* status);

// // Fills in `values` with the value of the attribute `attr_name` of `oper`.
// // `values` must point to an array of length at least `max_values` (ideally set
// // to TF_AttrMetadata.list_size from TF_OperationGetAttrMetadata(oper,
// // attr_name)).
// extern void TF_OperationGetAttrBoolList(TF_Operation* oper,
//                                         const char* attr_name,
//                                         unsigned char* values, int max_values,
//                                         TF_Status* status);

// extern void TF_OperationGetAttrType(TF_Operation* oper, const char* attr_name,
//                                     TF_DataType* value, TF_Status* status);

// // Fills in `values` with the value of the attribute `attr_name` of `oper`.
// // `values` must point to an array of length at least `max_values` (ideally set
// // to TF_AttrMetadata.list_size from TF_OperationGetAttrMetadata(oper,
// // attr_name)).
// extern void TF_OperationGetAttrTypeList(TF_Operation* oper,
//                                         const char* attr_name,
//                                         TF_DataType* values, int max_values,
//                                         TF_Status* status);

// // Fills in `value` with the value of the attribute `attr_name` of `oper`.
// // `values` must point to an array of length at least `num_dims` (ideally set to
// // TF_Attr_Meta.size from TF_OperationGetAttrMetadata(oper, attr_name)).
// extern void TF_OperationGetAttrShape(TF_Operation* oper, const char* attr_name,
//                                      int64_t* value, int num_dims,
//                                      TF_Status* status);

// // Fills in `dims` with the list of shapes in the attribute `attr_name` of
// // `oper` and `num_dims` with the corresponding number of dimensions. On return,
// // for every i where `num_dims[i]` > 0, `dims[i]` will be an array of
// // `num_dims[i]` elements. A value of -1 for `num_dims[i]` indicates that the
// // i-th shape in the list is unknown.
// //
// // The elements of `dims` will point to addresses in `storage` which must be
// // large enough to hold at least `storage_size` int64_ts.  Ideally, `num_shapes`
// // would be set to TF_AttrMetadata.list_size and `storage_size` would be set to
// // TF_AttrMetadata.total_size from TF_OperationGetAttrMetadata(oper,
// // attr_name).
// //
// // Fails if storage_size is insufficient to hold the requested shapes.
// extern void TF_OperationGetAttrShapeList(TF_Operation* oper,
//                                          const char* attr_name, int64_t** dims,
//                                          int* num_dims, int num_shapes,
//                                          int64_t* storage, int storage_size,
//                                          TF_Status* status);

// // Sets `value` to the binary-serialized TensorShapeProto of the value of
// // `attr_name` attribute of `oper`'.
// extern void TF_OperationGetAttrTensorShapeProto(TF_Operation* oper,
//                                                 const char* attr_name,
//                                                 TF_Buffer* value,
//                                                 TF_Status* status);

// // Fills in `values` with binary-serialized TensorShapeProto values of the
// // attribute `attr_name` of `oper`. `values` must point to an array of length at
// // least `num_values` (ideally set to TF_AttrMetadata.list_size from
// // TF_OperationGetAttrMetadata(oper, attr_name)).
// extern void TF_OperationGetAttrTensorShapeProtoList(TF_Operation* oper,
//                                                     const char* attr_name,
//                                                     TF_Buffer** values,
//                                                     int max_values,
//                                                     TF_Status* status);

// // Gets the TF_Tensor valued attribute of `attr_name` of `oper`.
// //
// // Allocates a new TF_Tensor which the caller is expected to take
// // ownership of (and can deallocate using TF_DeleteTensor).
// extern void TF_OperationGetAttrTensor(TF_Operation* oper, const char* attr_name,
//                                       TF_Tensor** value, TF_Status* status);

// // Fills in `values` with the TF_Tensor values of the attribute `attr_name` of
// // `oper`. `values` must point to an array of TF_Tensor* of length at least
// // `max_values` (ideally set to TF_AttrMetadata.list_size from
// // TF_OperationGetAttrMetadata(oper, attr_name)).
// //
// // The caller takes ownership of all the non-null TF_Tensor* entries in `values`
// // (which can be deleted using TF_DeleteTensor(values[i])).
// extern void TF_OperationGetAttrTensorList(TF_Operation* oper,
//                                           const char* attr_name,
//                                           TF_Tensor** values, int max_values,
//                                           TF_Status* status);

// // Sets `output_attr_value` to the binary-serialized AttrValue proto
// // representation of the value of the `attr_name` attr of `oper`.
// extern void TF_OperationGetAttrValueProto(TF_Operation* oper,
//                                           const char* attr_name,
//                                           TF_Buffer* output_attr_value,
//                                           TF_Status* status);

// // Returns the operation in the graph with `oper_name`. Returns nullptr if
// // no operation found.
// extern TF_Operation* TF_GraphOperationByName(TF_Graph* graph,
//                                              const char* oper_name);


// // Note: The following function may fail on very large protos in the future.

// extern void TF_OperationToNodeDef(TF_Operation* oper,
//                                   TF_Buffer* output_node_def,
//                                   TF_Status* status);


