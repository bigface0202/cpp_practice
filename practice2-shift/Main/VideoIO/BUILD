#
# @file BUILD for VideoIO
# 
# @author ssugino / created on 2021/06/30
# @copyright 2021 GlobalWalkers.inc. All rights reserved.
#
load( "@gwrt//Main:gwrt.bzl", "gwrt_library" )

gwrt_library(
    name = "VideoIO",
    hdrs = [ 
        "VideoCapture.h",
        "VideoWriter.h",
    ],
    srcs = [
        "VideoCapture.cpp",
        "VideoWriter.cpp",
    ],
    copts = [],
    deps = [
        "@cv//:cv2",
    ],
)
