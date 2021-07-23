#
# @file cv_configure.bzl
# 
# @author ssugino / created on 2021/05/27
# 
#

#
# CV Framework List
#
CV_FRAMEWORK_LIST = [
    "calib3d",
    "core",
    "dnn",
    "features2d",
    "flann",
    "gapi",
    "highgui",
    "imgcodecs",
    "imgproc",
    "ml",
    "objdetect",
    "photo",
    "stitching",
    "video",
    "videoio",
]

#
# CV Lib Import Format for Windows
#
CV_IMPORT_FORMAT_FOR_WIN = '''
cc_import(
    name = "%s",
    hdrs = glob( [ "Headers/**" ] ),
    interface_library = "Lib/%s.lib",
    shared_library = "Bin/%s.dll",
)
'''

#
# CV DLL Format for Windows
#
CV_LIBRARY_FORMAT_FOR_WIN = '''
cc_library(
    name = "cv2",
    hdrs = glob( [ "Headers/**" ] ),
    includes = [ "Headers" ],
    deps = [
        %s
    ],
    visibility = [ "//visibility:public" ],
)
'''

#
# CV Framework Format for Mac
#
CV_LIBRARY_FORMAT_FOR_MAC = '''
cc_library(
    name = "cv2",
    srcs = [
        %s
    ],
    hdrs = glob( ["Headers/opencv4/**"] ),
    includes = [ "Headers/opencv4" ],
    visibility = [ "//visibility:public" ],
    linkstatic = 1,
)
'''

#
# CV Framework Format for Mac
#
CV_LIBRARY_FORMAT_FOR_LINUX = '''
cc_library(
    name = "cv2",
    srcs = [
        %s
    ],
    hdrs = glob( ["Headers/opencv4/**"] ),
    includes = [ "Headers/opencv4" ],
    visibility = [ "//visibility:public" ],
)
'''

#
# Generate Deploy Configure for Windows
#
def _gen_deploy_configure_win( repository_ctx, lib_path ):
    
    tpl_path = repository_ctx.path(
        Label( "//External/OpenCV:cv_deploy.bzl.tpl" )
    )

    repository_ctx.template(
        "cv_deploy.bzl",
        tpl_path,
        {
            "%{cv_lib_path}": lib_path,
            "%{commands}": "",
            "%{function}": "_cv_deploy_win",
        },
    )

#
# CV Repository Auto Configration for Windows
#
def _cv_autoconf_for_win( repository_ctx, lib_path, lib_version ):
    
    _gen_deploy_configure_win( repository_ctx, lib_path )

    bin_src_path = lib_path + "/bin"
    bin_dst_path = "./Bin"
    repository_ctx.symlink( bin_src_path, bin_dst_path )

    lib_src_path = lib_path + "/lib"
    lib_dst_path = "./Lib"
    repository_ctx.symlink( lib_src_path, lib_dst_path )

    hdr_src_path = lib_path + "/include"
    hdr_dst_path = "./Headers"
    repository_ctx.symlink( hdr_src_path, hdr_dst_path )

    import_contents = []
    import_list = []
    for lib_name in CV_FRAMEWORK_LIST:
        import_name = "opencv_%s" % ( lib_name )
        lib_name = "opencv_%s%s" % ( lib_name, lib_version )
        import_contents.append(
            CV_IMPORT_FORMAT_FOR_WIN % (
                import_name, lib_name, lib_name
            )
        )
        import_list.append( "\":%s\"" % ( import_name ) )

    build_contents = []
    build_contents.append( "".join( import_contents ) )
    build_contents.append(
        CV_LIBRARY_FORMAT_FOR_WIN % (
            ",".join( import_list )
        )
    )

    repository_ctx.file( "BUILD", "".join( build_contents ) )

#
# Generate Deploy Configure for Mac
#
def _gen_deploy_configure_mac( repository_ctx, lib_path, lib_version ):
    
    tpl_path = repository_ctx.path(
        Label( "//External/OpenCV:cv_deploy.bzl.tpl" )
    )

    cmd_list = []
    for lib_name in CV_FRAMEWORK_LIST:
        lib_name = "libopencv_%s.%s.dylib" % ( lib_name, lib_version )
        rpath = "@rpath/%s" % ( lib_name )
        lpath = "%s/lib/%s" % ( lib_path, lib_name )
        cmd   = "install_name_tool -change %s %s {binary};" % ( rpath, lpath )
        cmd_list.append( cmd )

    repository_ctx.template(
        "cv_deploy.bzl",
        tpl_path,
        {
            "%{cv_lib_path}": lib_path,
            "%{commands}": "\n".join( cmd_list ),
            "%{function}": "_cv_deploy_mac",
        }
    )

#
# CV Repository Auto Configuration for Mac
#
def _cv_autoconf_for_mac( repository_ctx, lib_path, lib_version ):
    
    _gen_deploy_configure_mac( repository_ctx, lib_path, lib_version )

    hdr_src_path = lib_path + "/include"
    hdr_dst_path = "./Headers"
    repository_ctx.symlink( hdr_src_path, hdr_dst_path )

    lib_src_path = lib_path + "/lib"
    lib_dst_path = "./Lib"
    repository_ctx.symlink( lib_src_path, lib_dst_path )

    lib_list = []
    for lib_name in CV_FRAMEWORK_LIST:
        lib_name = "\"Lib/libopencv_%s.%s.dylib\"" % ( lib_name, lib_version )
        lib_list.append( lib_name )

    contents = CV_LIBRARY_FORMAT_FOR_MAC % ( ",\n        ".join( lib_list ) )
    repository_ctx.file( "BUILD", contents )

#
# Generate Deploy Configure for Linux
#
def _gen_deploy_configure_linux( repository_ctx, lib_path, lib_version ):

    tpl_path = repository_ctx.path(
        Label( "//External/OpenCV:cv_deploy.bzl.tpl" )
    )
    repository_ctx.template(
        "cv_deploy.bzl",
        tpl_path,
        {
            "%{cv_lib_path}": lib_path,
            "%{commands}": "",
            "%{function}": "_cv_deploy_linux",
        }
    )

#
# CV Repository Auto Configuration for Linux
#
def _cv_autoconf_for_linux( repository_ctx, lib_path, lib_version ):

    _gen_deploy_configure_linux( repository_ctx, lib_path, lib_version )

    hdr_src_path = lib_path + "/include"
    hdr_dst_path = "./Headers"
    repository_ctx.symlink( hdr_src_path, hdr_dst_path )

    lib_src_path = lib_path + "/lib"
    lib_dst_path = "./Lib"
    repository_ctx.symlink( lib_src_path, lib_dst_path )

    lib_list = []
    for lib_name in CV_FRAMEWORK_LIST:
        lib_name = "\"Lib/libopencv_%s.so\"" % ( lib_name )
        lib_list.append( lib_name )

    contents = CV_LIBRARY_FORMAT_FOR_LINUX % ( ",\n        ".join( lib_list ) )
    repository_ctx.file( "BUILD", contents )

#
# CV Repository Auto Configuration
#
def _cv_autoconf_impl( repository_ctx ):
    
    os_name = repository_ctx.os.name.lower()
    lib_path = repository_ctx.os.environ[ "CV_LIB_PATH" ]
    lib_path = lib_path.replace( "\\", "/" )
    lib_version = repository_ctx.os.environ[ "CV_LIB_VERSION" ]

    if os_name.find( "windows" ) != -1:
        _cv_autoconf_for_win( repository_ctx, lib_path, lib_version )
    elif os_name.find( "mac" ) != -1:
        _cv_autoconf_for_mac( repository_ctx, lib_path, lib_version )
    else:
        _cv_autoconf_for_linux( repository_ctx, lib_path, lib_version )

#
# CV Repository Rule Decralation
#
cv_autoconf = repository_rule(
    implementation = _cv_autoconf_impl,
    local = True,
    configure = True,
)