#
# @file gwrt.bzl
# 
# @author y-ksst / created on 2021/06/30
# 
#
load( "@rules_cc//cc:defs.bzl", "cc_library" )
load( "@rules_cc//cc:defs.bzl", "cc_binary" )

#
# Common Comiple options
#
COMMON_COPTS = {
    "@platforms//os:windows": [
    ],
    "@platforms//os:macos": [
    ],
    "@platforms//os:linux": [
    ],
}

#
# Main Normal Code Compile
#
def gwrt_library( name, srcs, hdrs, copts=None, deps=None, **kwargs ):
    cc_library(
        name = name,
        srcs = srcs,
        hdrs = hdrs,
        copts = copts + select( COMMON_COPTS ),
        deps = deps,
        visibility = [ "//visibility:public" ],
        **kwargs
    )

#
# Main Binary Compile
#
def gwrt_binary( name, srcs, copts, deps=None, **kwargs ):
    cc_binary(
        name = name,
        srcs = srcs,
        copts = copts + select( COMMON_COPTS ),
        deps = deps,
        **kwargs
    )
