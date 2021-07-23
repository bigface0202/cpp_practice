#
# @file cv_deploy.bzl.tpl
# 
# @author y-ksst / created on 2021/05/27
# 
#

#
# CV Library Path
#
CV_LIB_PATH = '''%{cv_lib_path}'''

#
# RPATH Command Template
#
RPATH_COMMAND = '''
%{commands}
'''

#
# Exec Command for Bash
#
EXEC_COMMAND_BASH = '''
echo \\\"\\\"
echo \\\"***** Execute: %s *****\\\"
echo \\\"\\\"
./%s

echo \\\"\\\"
'''

#
# OpenCV deploy process for win
#
def _cv_deploy_win( ctx ):
    
    in_file = ctx.file.src

    deploy_bat = ctx.actions.declare_file( "cv_deploy.bat" )
    deploy_log = deploy_bat.path.replace( ".bat", ".log" )

    base_cmd = "@echo off\n"

    copy_cmd = "cp -rfp %s/bin/*.dll %s" % (
        CV_LIB_PATH, in_file.dirname
    )

    ctx.actions.write(
        output  = deploy_bat,
        content = base_cmd + copy_cmd,
        is_executable = True,
    )

    return [
        DefaultInfo( files = depset([ deploy_bat ]) )
    ]

#
# OpenCV deploy process for mac
#
def _cv_deploy_mac( ctx ):
    
    in_file = ctx.file.src
    deploy_sh = ctx.actions.declare_file( "cv_deploy.sh" )
    runner_sh = ctx.actions.declare_file( "runner.sh" )

    rpath_cmd = RPATH_COMMAND.replace(
        "{binary}", in_file.path
    )

    ctx.actions.run_shell(
        inputs  = [ in_file ],
        outputs = [ deploy_sh ],
        command = "echo \"%s\" > %s;" %
                  ( rpath_cmd, deploy_sh.path )
    )

    runner_cmd = EXEC_COMMAND_BASH % ( 
        in_file.basename, in_file.path 
    )
    ctx.actions.run_shell(
        inputs  = [ in_file ],
        outputs = [ runner_sh ],
        command = "echo \"%s\" > %s;" %
                  ( runner_cmd, runner_sh.path )
    )

    return [
        DefaultInfo( files = depset([ deploy_sh, runner_sh ]) )
    ]

#
# OpenCV deploy process for Linux
#
# @note runner only
#
def _cv_deploy_linux( ctx ):

    in_file = ctx.file.src
    runner_sh = ctx.actions.declare_file( "runner.sh" )

    runner_cmd = EXEC_COMMAND_BASH % ( 
        in_file.basename, in_file.path 
    )
    ctx.actions.run_shell(
        inputs  = [ in_file ],
        outputs = [ runner_sh ],
        command = "echo \"%s\" > %s;" %
                  ( runner_cmd, runner_sh.path )
    )

    return [
        DefaultInfo( files = depset([ runner_sh ]) )
    ]

#
# cv deploy decralation
#
cv_deploy = rule(
    implementation = %{function},
    attrs = {
        "src": attr.label(
            mandatory = True,
            allow_single_file = True,
        )
    }
)
