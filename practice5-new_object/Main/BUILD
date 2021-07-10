#
# @file BUILD
# 
# @author ssugino / created on 2021/06/30
# @copyright 2021 GlobalWalkers.inc. All rights reserved.
#
load( "@cv//:cv_deploy.bzl", "cv_deploy" )
load( "@gwrt//Main:gwrt.bzl", "gwrt_binary" )

BIN_NAME = "Sample"

gwrt_binary(
    name = BIN_NAME,
    srcs = [ "sample.cpp", ],
    copts = [],
    deps = [
        "//Main/VideoIO:VideoIO",
    ],
)

cv_deploy( 
    name="cv_deploy", 
    src=BIN_NAME, 
)

genrule(
    name = "run",
    srcs = [ "cv_deploy" ],
    outs = [ "run.sh" ],
    cmd  = "echo $(SRCS) | sed \'s/ /\\n/g\' > $@",
    executable = 1,
)
