
#include "tf_dtype.h"

/**
 * @ref https://github.com/tensorflow/tensorflow/blob/287db3a9b0701021f302e7bb58af5cf89fdcd424/tensorflow/java/src/main/native/tensor_jni.cc
 */
size_t tf_dtype_sizeof(TF_DataType type)
{
    switch (type) {
        case TF_INT8 :
        case TF_UINT8 :
        case TF_QINT8 :
        case TF_QUINT8 :
        case TF_BOOL :
            return 1;
        case TF_INT16 :
        case TF_BFLOAT16 :
        case TF_QINT16 :
        case TF_QUINT16 :
        case TF_UINT16 :
            return 2;
        case TF_FLOAT :
        case TF_INT32 :
        case TF_QINT32 :
            return 4;
        case TF_DOUBLE :
        case TF_INT64 :
        case TF_COMPLEX64 : // equal TF_COMPLEX
            return 8;
        case TF_COMPLEX128 :
            return 16;
        default:
            break;
        // @todo
        // case TF_STRING : nbytes = uintptr(nflattened*8) + byteSizeOfEncodedStrings(value)
        // case TF_HALF :
        // case TF_RESOURCE :
    }
    return 0; // unknown;
}

char valid_dtype(int64_t dtype)
{
    return dtype > 0 && dtype < 21;
}
