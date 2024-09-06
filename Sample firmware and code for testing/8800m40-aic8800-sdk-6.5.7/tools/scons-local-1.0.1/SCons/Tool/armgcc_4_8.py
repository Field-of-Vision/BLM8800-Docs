"""SCons.Tool.gcc

Tool-specific initialization for GNUARM

There normally shouldn't be any need to import this module directly.
It will usually be imported through the generic SCons.Tool.Tool()
selection method.

"""

#
# Copyright (c) 2001, 2002, 2003, 2004, 2005, 2006, 2007, 2008 The SCons Foundation
#
# Permission is hereby granted, free of charge, to any person obtaining
# a copy of this software and associated documentation files (the
# "Software"), to deal in the Software without restriction, including
# without limitation the rights to use, copy, modify, merge, publish,
# distribute, sublicense, and/or sell copies of the Software, and to
# permit persons to whom the Software is furnished to do so, subject to
# the following conditions:
#
# The above copyright notice and this permission notice shall be included
# in all copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY
# KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
# WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
# NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE
# LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
# OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
# WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
#

__revision__ = ""

import os
import os.path
import string

import SCons.Action
import SCons.Builder
import SCons.Defaults
import SCons.Tool
import SCons.Util

def exists(env):
    return find(env)

def find(env):
    try:
        gnuarm_path = os.environ['GNUARM_4_8_LIB']
    except KeyError:
        print "GNU ARM install error: please set GNUARM_4_8_LIB)"
        raise
    # First search in the SCons path and then the OS path:
    return gnuarm_path

def generate(env):

    # Mostly it is the same as gcc and friends...
#    gnu_tools = ['gcc', 'g++', 'gnulink', 'ar', 'gas']
    gnu_tools = ['gcc', 'gnulink', 'ar', 'gas']
    for tool in gnu_tools:
        SCons.Tool.Tool(tool)(env)

    # retrieve the gnuarm install directory, and add it to bin and lib paths
    gnuarm_path = find(env)
    print 'gnuarm_path:', gnuarm_path
    env.PrependENVPath('PATH', os.path.normpath(os.path.join(gnuarm_path, '../../../../bin')))
    #env.Append(LIBPATH = [ gnuarm_path, os.path.join(gnuarm_path, '../../../../arm-none-eabi/lib') ])

    # retrieve the parameters of the compilation
    env['ARMCPU'] = '${_concat("-mcpu=", CPU, "", __env__)}'
    env['ARMOPTIM'] = '${_concat("-O", OPTIM, "", __env__)}'

    #... but a few things differ:
    env['CC'] = 'arm-none-eabi-gcc'
    #env['AS'] = 'arm-none-eabi-as'
    env['AS'] = 'arm-none-eabi-gcc'
    #env['LINK'] = 'arm-none-eabi-ld'
    env['LINK'] = 'arm-none-eabi-gcc'
    env['AR'] = 'arm-none-eabi-ar'

    # add some flags common to C and C++ and to assembly
    env['CCCOM']     = "${TEMPFILE('$CC -o $TARGET -c $ARMCPU $ARMOPTIM $CCFLAGS $_CCCOMCOM $SOURCES')}"
    env['ASCOM']     = '$AS $ARMCPU $ASFLAGS $_ASMDEFFLAGS -o $TARGET $SOURCES'
    env['ASPPCOM']   = '$CC $ARMCPU $ASPPFLAGS $_ASMDEFFLAGS -o $TARGET $SOURCES'
    env['ARCOM']     = "${TEMPFILE('" + env['ARCOM'] + "')}"

    # add libs
    env['LIBS'] = ['libm', 'libgcc', 'libc']

    # add the info file output in the link flags
    #env['LINKINFO'] = '${_concat("-Map ", LINKINFOFILE, "", __env__)}'
    env['LINKINFO'] = '${_concat("-Wl,-Map=", LINKINFOFILE, "", __env__)}'
    # add the linker script at the end of the link command line
    env['LINKMAP'] = '${_concat("-T", LINKMAPFILE, "", __env__)}'
    env.Append(_LIBFLAGS = " $LINKINFO $LINKMAP")

    # Some setting from the platform also have to be overridden:
    env['OBJSUFFIX'] = '.o'
    env['LIBPREFIX'] = 'lib'
    env['LIBSUFFIX'] = '.a'
    env['PROGSUFFIX'] = '.elf'

