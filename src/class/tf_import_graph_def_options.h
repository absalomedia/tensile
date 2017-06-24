// // TF_ImportGraphDefOptions holds options that can be passed to
// // TF_GraphImportGraphDef.
// typedef struct TF_ImportGraphDefOptions TF_ImportGraphDefOptions;

// extern TF_ImportGraphDefOptions* TF_NewImportGraphDefOptions();
// extern void TF_DeleteImportGraphDefOptions(TF_ImportGraphDefOptions* opts);

// // Set the prefix to be prepended to the names of nodes in `graph_def` that will
// // be imported into `graph`.
// extern void TF_ImportGraphDefOptionsSetPrefix(TF_ImportGraphDefOptions* opts,
//                                               const char* prefix);

// // Import the graph serialized in `graph_def` into `graph`.
// extern void TF_GraphImportGraphDef(TF_Graph* graph, const TF_Buffer* graph_def,
//                                    const TF_ImportGraphDefOptions* options,
//                                    TF_Status* status);

