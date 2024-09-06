"""SCons.Tool.armcc_5

Tool-specific initialization for ARM Compiler 5

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
import cc

# define the suffixes that are supported
CSuffixes = ['.c', '.C']
CXXSuffixes = ['.cpp', '.cc', '.cxx', '.c++', '.C++']
ASSuffixes = ['.s', '.S', '.asm', '.ASM']

# This is what we search for to find armcc_5:
key_program = 'armcc'

def find(env):
    # First search in the SCons path and then the OS path:
    return env.WhereIs(key_program) or SCons.Util.WhereIs(key_program)

def generate(env):

    # define C compilation rules
    static_obj, shared_obj = SCons.Tool.createObjBuilders(env)

    for suffix in CSuffixes:
        static_obj.add_action(suffix, SCons.Defaults.CAction)
        shared_obj.add_action(suffix, SCons.Defaults.ShCAction)
        static_obj.add_emitter(suffix, SCons.Defaults.StaticObjectEmitter)
        shared_obj.add_emitter(suffix, SCons.Defaults.SharedObjectEmitter)

    # use the common cc variables in $_CCOMCOM
    cc.add_common_cc_variables(env)

    # flags common to C and C++
    env['CC']        = 'armcc'

    env['ARMCPU'] = '${_concat("--cpu=", CPU, "", __env__)}'
    env['ARMOPTIM'] = '${_concat("-O", OPTIM, "", __env__)}'

    env['CCCOM']     = '$CC -o $TARGET -c $ARMCPU $ARMOPTIM $CCFLAGS $_CCCOMCOM $SOURCES'

    env['CPPDEFPREFIX']  = '-D'
    env['CPPDEFSUFFIX']  = ''
    env['INCPREFIX']  = '-I'
    env['INCSUFFIX']  = ''
    env['STATIC_AND_SHARED_OBJECTS_ARE_THE_SAME'] = 0

    env['CFILESUFFIX'] = '.c'

    # define C++ compilation rules
    static_obj, shared_obj = SCons.Tool.createObjBuilders(env)

    for suffix in CXXSuffixes:
        static_obj.add_action(suffix, SCons.Defaults.CXXAction)
        static_obj.add_emitter(suffix, SCons.Defaults.StaticObjectEmitter)

    env['CXX']        = 'armcc'
    #env['CXXFLAGS']   = SCons.Util.CLVar('')
    env['CXXCOM']     = '$CXX -o $TARGET -c $ARMCPU $ARMOPTIM $CXXFLAGS $CCFLAGS $_CCCOMCOM $SOURCES'
    env['CXXFILESUFFIX'] = '.cpp'

    # define assembly compilation rules
    static_obj, shared_obj = SCons.Tool.createObjBuilders(env)

    for suffix in ASSuffixes:
        static_obj.add_action(suffix, SCons.Defaults.ASAction)
        shared_obj.add_action(suffix, SCons.Defaults.ASAction)
        static_obj.add_emitter(suffix, SCons.Defaults.StaticObjectEmitter)
        shared_obj.add_emitter(suffix, SCons.Defaults.SharedObjectEmitter)

    env['AS']        = 'armasm'
    #env['ASCOM']     = '$AS $ARMCPU $ARMOPTIM $ASFLAGS -o $TARGET $SOURCES'
    env['ASCOM']     = '$AS $ARMCPU $ASFLAGS $_ASMDEFFLAGS -o $TARGET $SOURCES'
    env['ASMDEFPREFIX'] = '--pd '
    env['ASMDEFSUFFIX'] = ''

    # define armcc_5 linker rules
    SCons.Tool.createProgBuilder(env)

    env['LINK']        = "armlink"
    env['LINKINFO']    = '${_concat("--list=", LINKINFOFILE, "", __env__)}'
    env['LINKMAP']     = '${_concat("--scatter=", LINKMAPFILE, "", __env__)}'

    env['TEMPFILEOPT'] = '--via ${TEMPFILENAME}'      # arm tool chain

    #env['LINKCOM']     = '$LINK $LINKMAP $LINKINFO $ARMCPU --output $TARGET $LINKFLAGS $SOURCES $_LIBDIRFLAGS $_LIBFLAGS'
    env['LINKCOM']     = "${TEMPFILE('$LINK $ARMCPU $LINKFLAGS $_LIBDIRFLAGS $LINKMAP $LINKINFO --output $TARGET $SOURCES $_LIBFLAGS')}"
    env['LIBDIRPREFIX']='--libpath '
    env['LIBDIRSUFFIX']=''
    env['_LIBFLAGS']='${_stripixes(LIBLINKPREFIX, LIBS, LIBLINKSUFFIX, LIBPREFIXES, LIBSUFFIXES, __env__)}'
    env['LIBLINKPREFIX']='-l'
    env['LIBLINKSUFFIX']=''

    # Some setting from the platform also have to be overridden:
    env['OBJSUFFIX'] = '.o'
    env['LIBPREFIX'] = ''
    env['LIBSUFFIX'] = '.a'
    env['PROGSUFFIX'] = '.axf'

    # find where armcc_5 binaries are hidden
    armcc_5 = find(env)
    if armcc_5:
        dir = os.path.dirname(armcc_5)
        env.PrependENVPath('PATH', dir )

    # Add the enviroment variables required by armcc_5
    #env['ENV']['ARMLMD_LICENSE_FILE'] = os.environ['ARMLMD_LICENSE_FILE']
    #env['ENV']['ARMCC41BIN'] = os.environ['ARMCC41BIN']
    #env['ENV']['ARMCC41INC'] = os.environ['ARMCC41INC']
    #env['ENV']['ARMCC41LIB'] = os.environ['ARMCC41LIB']
    env['ENV']['ARMCC5LIB'] = os.environ['ARMCC5LIB']
    #env['LIBPATH']          = os.environ['ARMCC41LIB']

def exists(env):
    return find(env)
