// // TF_AttrType describes the type of the value of an attribute on an operation.
// typedef enum {
//   TF_ATTR_STRING = 0,
//   TF_ATTR_INT = 1,
//   TF_ATTR_FLOAT = 2,
//   TF_ATTR_BOOL = 3,
//   TF_ATTR_TYPE = 4,
//   TF_ATTR_SHAPE = 5,
//   TF_ATTR_TENSOR = 6,
//   TF_ATTR_PLACEHOLDER = 7,
//   TF_ATTR_FUNC = 8,
// } TF_AttrType;


// // TF_AttrMetadata describes the value of an attribute on an operation.
// typedef struct {
//   // A boolean: 1 if the attribute value is a list, 0 otherwise.
//   unsigned char is_list;

//   // Length of the list if is_list is true. Undefined otherwise.
//   int64_t list_size;

//   // Type of elements of the list if is_list != 0.
//   // Type of the single value stored in the attribute if is_list == 0.
//   TF_AttrType type;

//   // Total size the attribute value.
//   // The units of total_size depend on is_list and type.
//   // (1) If type == TF_ATTR_STRING and is_list == 0
//   //     then total_size is the byte size of the string
//   //     valued attribute.
//   // (2) If type == TF_ATTR_STRING and is_list == 1
//   //     then total_size is the cumulative byte size
//   //     of all the strings in the list.
//   // (3) If type == TF_ATTR_SHAPE and is_list == 0
//   //     then total_size is the number of dimensions
//   //     of the shape valued attribute, or -1
//   //     if its rank is unknown.
//   // (4) If type == TF_ATTR_SHAPE and is_list == 1
//   //     then total_size is the cumulative number
//   //     of dimensions of all shapes in the list.
//   // (5) Otherwise, total_size is undefined.
//   int64_t total_size;
// } TF_AttrMetadata;

// // Returns metadata about the value of the attribute `attr_name` of `oper`.
// extern TF_AttrMetadata TF_OperationGetAttrMetadata(TF_Operation* oper,
//                                                    const char* attr_name,
//                                                    TF_Status* status);
