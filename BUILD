cc_binary(
    name = "libtensorflow.so",
    linkshared = 1,
    linkopts=['-static'],
    deps = [
        "//tensorflow/core:kernels",
        "//tensorflow/core:tensorflow",
    ]
)