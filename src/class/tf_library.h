// // TF_Library holds information about dynamically loaded TensorFlow plugins.
// typedef struct TF_Library TF_Library;

// // Load the library specified by library_filename and register the ops and
// // kernels present in that library.
// //
// // Pass "library_filename" to a platform-specific mechanism for dynamically
// // loading a library. The rules for determining the exact location of the
// // library are platform-specific and are not documented here.
// //
// // On success, place OK in status and return the newly created library handle.
// // The caller owns the library handle.
// //
// // On failure, place an error status in status and return NULL.
// extern TF_Library* TF_LoadLibrary(const char* library_filename,
//                                   TF_Status* status);

// // Get the OpList of OpDefs defined in the library pointed by lib_handle.
// //
// // Returns a TF_Buffer. The memory pointed to by the result is owned by
// // lib_handle. The data in the buffer will be the serialized OpList proto for
// // ops defined in the library.
// extern TF_Buffer TF_GetOpList(TF_Library* lib_handle);

// // Frees the memory associated with the library handle.
// // Does NOT unload the library.
// extern void TF_DeleteLibraryHandle(TF_Library* lib_handle);
