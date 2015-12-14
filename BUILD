cc_binary(
    name = "libtensorflow.so",
    linkshared = 1,
    copts = tf_copts(),
    deps = [
        ":cc_ops",
        "//tensorflow/core:kernels",
        "//tensorflow/core:tensorflow",
    ]
)