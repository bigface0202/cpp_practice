#
# @file BUILD
# 
# @author y-ksst / created on 2021/07/23
#
# load( "@cv//:cv_deploy.bzl", "cv_deploy" )
load( "@gwrt//Main:gwrt.bzl", "gwrt_binary" )

BIN_NAME = "Answer"

gwrt_binary(
    name = BIN_NAME,
    srcs = [ "answer.cpp"],
    copts = ["-std=c++17", "-lstdc++fs"], # C++17を使う
    deps = [],
)

# ans_deploy( 
#     name="ans_deploy", 
#     src=BIN_NAME, 
# )

# genrule(
#     name = "run",
#     srcs = [ "ans_deploy" ],
#     outs = [ "run.sh" ],
#     cmd  = "echo $(SRCS) | sed \'s/ /\\n/g\' > $@",
#     executable = 1,
# )

# cc_binary(
#   name = BIN_NAME,
#   srcs = ["answer.cpp"],
# )