"""SCons.Tool.gcc

Tool-specific initialization for G++

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

CXXSuffixes = ['.cpp', '.cc', '.c', '.cxx', '.c++', '.C++', '.mm']

def exists(env):
    return find(env)

# This is what we search for to find g++:
key_program = 'g++'

def find(env):
    return env.WhereIs(key_program) or SCons.Util.WhereIs(key_program)

def generate(env):
    """
    Add Builders and construction variables for Visual Age C++ compilers
    to an Environment.
    """
    import SCons.Tool
    import SCons.Tool.cc
    static_obj, shared_obj = SCons.Tool.createObjBuilders(env)

    for suffix in CXXSuffixes:
        static_obj.add_action(suffix, SCons.Defaults.CXXAction)
        shared_obj.add_action(suffix, SCons.Defaults.ShCXXAction)
        static_obj.add_emitter(suffix, SCons.Defaults.StaticObjectEmitter)
        shared_obj.add_emitter(suffix, SCons.Defaults.SharedObjectEmitter)

    SCons.Tool.cc.add_common_cc_variables(env)

    # retrieve the path to get the proper g++
    PATH= os.getenv('PATH')
    if PATH != 'none':
      env['ENV']['PATH']=PATH    
    
    
    
    # retrieve the parameters of the compilation
    env['GXXOPTIM'] = '${_concat("-O", OPTIM, "", __env__)}'

    env['CXX']        = 'g++'
    env['CXXFLAGS']   = SCons.Util.CLVar('')
    env['CXXCOM']     = '$CXX -c $GXXOPTIM $_CCCOMCOM $CXXFLAGS -o$TARGET $SOURCES'
    env['SHCXX']      = '$CXX'
    env['SHCXXFLAGS'] = SCons.Util.CLVar('$CXXFLAGS')
    env['SHCXXCOM']   = '$SHCXX -o $TARGET -c $SHCXXFLAGS $SHCCFLAGS $_CCCOMCOM $SOURCES'

    env['CPPDEFPREFIX']  = '-D'
    env['CPPDEFSUFFIX']  = ''
    env['INCPREFIX']  = '-I'
    env['INCSUFFIX']  = ''
    env['SHOBJSUFFIX'] = '.os'
    env['OBJSUFFIX'] = '.o'
    env['STATIC_AND_SHARED_OBJECTS_ARE_THE_SAME'] = 0

    env['CXXFILESUFFIX'] = '.cpp'

#    # Mostly it is the same as gcc and friends...
#    gnu_tools = ['gcc', 'gnulink', 'ar', 'gas']
#    for tool in gnu_tools:
#        SCons.Tool.Tool(tool)(env)
#
    # find where G++ binaries are hidden
    gpp_path = find(env)
    if gpp_path:
        dir = os.path.dirname(gpp_path)
        env.PrependENVPath('PATH', dir )
#     
#    # retrieve the parameters of the compilation
#    env['GXXOPTIM'] = '${_concat("-O", OPTIM, "", __env__)}'
#
#    # Rules for C++ compilation
#    env['CXX']        = 'g++'
#    env['CXXCOM']     = '$CXX -c $GPPOPTIM $_CCCOMCOM $CXXFLAGS -o$TARGET $SOURCES'
#    env['CXXFILESUFFIX'] = '.cpp'

    # Some setting from the platform also have to be overridden:
    env['OBJSUFFIX'] = '.o'
    env['LIBPREFIX'] = 'lib'
    env['LIBSUFFIX'] = '.a'
    

    # define G++ linker rules
    SCons.Tool.createProgBuilder(env)
    
    env['LINK'] = 'g++'
    # add the info file output in the link flags
    env['LINKINFO'] = '${_concat("-Wl,-Map,", LINKINFOFILE, "", __env__)}'
    env.Append(_LIBFLAGS = " $LINKINFO")
    
    env['LINKFLAGS'] = SCons.Util.CLVar('$LINKFLAGS -shared')
    env['LINKCOM']   = '$LINK $_LIBDIRFLAGS $GXXOPTIM $LINKFLAGS $_LIBFLAGS -o$TARGET $SOURCES $SYSTEMCLIB'
