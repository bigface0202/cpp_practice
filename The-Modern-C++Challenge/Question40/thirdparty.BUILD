cc_library(
    name = "thirdparty",
    srcs = [],
    hdrs = glob(
      [
        "include/date/date.h",
      ]
    ),
    includes = ["include"],
    linkstatic = 1,
    linkopts = [
      "-pthread",
      '-ldl',
      '-lm',
      ],
    visibility = ["//visibility:public"],
)