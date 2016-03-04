import os
import ycm_core
from clang_helpers import PrepareClangFlags

# Set this to the absolute path to the folder (NOT the file!) containing the
# compile_commands.json file to use that instead of 'flags'. See here for
# more details: http://clang.llvm.org/docs/JSONCompilationDatabase.html
# Most projects will NOT need to set this to anything; you can just change the
# 'flags' list of compilation flags. Notice that YCM itself uses that approach.
compilation_database_folder = ''

# These are the compilation flags that will be used in case there's no
# compilation database set.
flags = [
# THIS IS IMPORTANT! Without a "-std=<something>" flag, clang won't know which
# language to use when compiling headers. So it will guess. Badly. So C++
# headers will be compiled as C headers. You don't want that so ALWAYS specify
# a "-std=<something>".
# For a C project, you would set this to something like 'c99' instead of
# 'c++11'.
'-std=c++11',
# ...and the same thing goes for the magic -x option which specifies the
# language that the files to be compiled are written in. This is mostly
# relevant for c++ headers.
# For a C project, you would set this to 'c' instead of 'c++'.
'-x',
'c++',

'-I', '/home/mhoggan/Devel/SDL2-2.0.4/include',
'-I', '/home/mhoggan/Devel/SDL2-2.0.4/src/joystick/linux',
'-I', '/home/mhoggan/Devel/SDL2-2.0.4/src/joystick/windows',
'-I', '/home/mhoggan/Devel/SDL2-2.0.4/src/libm',
'-I', '/home/mhoggan/Devel/SDL2-2.0.4/src/main/haiku',
'-I', '/home/mhoggan/Devel/SDL2-2.0.4/src/power/uikit',
'-I', '/home/mhoggan/Devel/SDL2-2.0.4/src/render',
'-I', '/home/mhoggan/Devel/SDL2-2.0.4/src/render/direct3d11',
'-I', '/home/mhoggan/Devel/SDL2-2.0.4/src/render/opengl',
'-I', '/home/mhoggan/Devel/SDL2-2.0.4/src/render/opengles',
'-I', '/home/mhoggan/Devel/SDL2-2.0.4/src/render/opengles2',
'-I', '/home/mhoggan/Devel/SDL2-2.0.4/src/render/software',
'-I', '/home/mhoggan/Devel/SDL2-2.0.4/src/thread',
'-I', '/home/mhoggan/Devel/SDL2-2.0.4/src/thread/generic',
'-I', '/home/mhoggan/Devel/SDL2-2.0.4/src/thread/psp',
'-I', '/home/mhoggan/Devel/SDL2-2.0.4/src/thread/pthread',
'-I', '/home/mhoggan/Devel/SDL2-2.0.4/src/thread/stdcpp',
'-I', '/home/mhoggan/Devel/SDL2-2.0.4/src/thread/windows',
'-I', '/home/mhoggan/Devel/SDL2-2.0.4/src/timer',
'-I', '/home/mhoggan/Devel/SDL2-2.0.4/src/video',
'-I', '/home/mhoggan/Devel/SDL2-2.0.4/src/video/android',
'-I', '/home/mhoggan/Devel/SDL2-2.0.4/src/video/cocoa',
'-I', '/home/mhoggan/Devel/SDL2-2.0.4/src/video/directfb',
'-I', '/home/mhoggan/Devel/SDL2-2.0.4/src/video/dummy',
'-I', '/home/mhoggan/Devel/SDL2-2.0.4/src/video/emscripten',
'-I', '/home/mhoggan/Devel/SDL2-2.0.4/src/video/haiku',
'-I', '/home/mhoggan/Devel/SDL2-2.0.4/src/video/mir',
'-I', '/home/mhoggan/Devel/SDL2-2.0.4/src/video/nacl',
'-I', '/home/mhoggan/Devel/SDL2-2.0.4/src/video/pandora',
'-I', '/home/mhoggan/Devel/SDL2-2.0.4/src/video/psp',
'-I', '/home/mhoggan/Devel/SDL2-2.0.4/src/video/raspberry',
'-I', '/home/mhoggan/Devel/SDL2-2.0.4/src/video/uikit',
'-I', '/home/mhoggan/Devel/SDL2-2.0.4/src/video/vivante',
'-I', '/home/mhoggan/Devel/SDL2-2.0.4/src/video/wayland',
'-I', '/home/mhoggan/Devel/SDL2-2.0.4/src/video/windows',
'-I', '/home/mhoggan/Devel/SDL2-2.0.4/src/video/winrt',
'-I', '/home/mhoggan/Devel/SDL2-2.0.4/src/video/x11',
'-I', '/home/mhoggan/Devel/SDL2-2.0.4/src/',
'-I', '/home/mhoggan/Devel/SDL2-2.0.4/src/libm/',
'-I', '/home/mhoggan/Devel/SDL2-2.0.4/src/power/',
'-I', '/home/mhoggan/Devel/SDL2-2.0.4/src/cpuinfo/',
'-I', '/home/mhoggan/Devel/SDL2-2.0.4/src/core/',
'-I', '/home/mhoggan/Devel/SDL2-2.0.4/src/haptic/',
'-I', '/home/mhoggan/Devel/SDL2-2.0.4/src/events/',
'-I', '/home/mhoggan/Devel/SDL2-2.0.4/src/timer/',
'-I', '/home/mhoggan/Devel/SDL2-2.0.4/src/stdlib/',
'-I', '/home/mhoggan/Devel/SDL2-2.0.4/src/atomic/',
'-I', '/home/mhoggan/Devel/SDL2-2.0.4/src/joystick/',
'-I', '/home/mhoggan/Devel/SDL2-2.0.4/src/dynapi/',
'-I', '/home/mhoggan/Devel/SDL2-2.0.4/src/video/',
'-I', '/home/mhoggan/Devel/SDL2-2.0.4/src/filesystem/',
'-I', '/home/mhoggan/Devel/SDL2-2.0.4/src/audio/',
'-I', '/home/mhoggan/Devel/SDL2-2.0.4/src/loadso/',
'-I', '/usr/local/include/',
'-I', './',
'-I', '/usr/lib/qt/mkspecs/linux-clang',
]

if compilation_database_folder:
  database = ycm_core.CompilationDatabase( compilation_database_folder )
else:
  database = None


def DirectoryOfThisScript():
  return os.path.dirname( os.path.abspath( __file__ ) )


def MakeRelativePathsInFlagsAbsolute( flags, working_directory ):
  if not working_directory:
    return flags
  new_flags = []
  make_next_absolute = False
  path_flags = [ '-isystem', '-I', '-iquote', '--sysroot=' ]
  for flag in flags:
    new_flag = flag

    if make_next_absolute:
      make_next_absolute = False
      if not flag.startswith( '/' ):
        new_flag = os.path.join( working_directory, flag )

    for path_flag in path_flags:
      if flag == path_flag:
        make_next_absolute = True
        break

      if flag.startswith( path_flag ):
        path = flag[ len( path_flag ): ]
        new_flag = path_flag + os.path.join( working_directory, path )
        break

    if new_flag:
      new_flags.append( new_flag )
  return new_flags


def FlagsForFile( filename ):
  if database:
    # Bear in mind that compilation_info.compiler_flags_ does NOT return a
    # python list, but a "list-like" StringVec object
    compilation_info = database.GetCompilationInfoForFile( filename )
    final_flags = PrepareClangFlags(
        MakeRelativePathsInFlagsAbsolute(
            compilation_info.compiler_flags_,
            compilation_info.compiler_working_dir_ ),
        filename )
  else:
    relative_to = DirectoryOfThisScript()
    final_flags = MakeRelativePathsInFlagsAbsolute( flags, relative_to )

  return {
    'flags': final_flags,
    'do_cache': True
  }
