cc_library(
    name = "thirdparty",
    srcs = [
      # "src/tz.cpp"
    ],
    hdrs = glob(
      [
        "include/date/*.h",
      ]
    ),
    includes = ["include"],
    linkstatic = 1,
    linkopts = [
      "-pthread",
      '-ldl',
      '-lm',
      '-lcurl',
      '-l /media/yusuke/Moon/FromGitHub/date/build/libdate-tz.a'
      ],
    visibility = ["//visibility:public"],
)