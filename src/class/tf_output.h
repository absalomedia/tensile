// // Represents a specific output of an operation.
// typedef struct TF_Output {
//   TF_Operation* oper;
//   int index;  // The index of the output within oper.
// } TF_Output;


// // Get the number of current consumers of a specific output of an
// // operation.  Note that this number can change when new operations
// // are added to the graph.
// extern int TF_OperationOutputNumConsumers(TF_Output oper_out);

// // Get list of all current consumers of a specific output of an
// // operation.  `consumers` must point to an array of length at least
// // `max_consumers` (ideally set to
// // TF_OperationOutputNumConsumers(oper_out)).  Beware that a concurrent
// // modification of the graph can increase the number of consumers of
// // an operation.  Returns the number of output consumers (should match
// // TF_OperationOutputNumConsumers(oper_out)).
// extern int TF_OperationOutputConsumers(TF_Output oper_out, TF_Input* consumers,
//                                        int max_consumers);

