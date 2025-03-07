
cc = meson.get_compiler('c')
m_dep = cc.find_library('m', required : false)

libhemlock_argparser_public_includes = [
  './',
]

libhemlock_argparser = library(
  'hemlock_argparser',
  files([ 
    'argparser.c',
    'finish.c',
    'genhelp.c',
    'log.c',
    'parser.c',
    'pretty.c',
    'tokenizer.c',
    'validate.c',
  ]),
  version : '0.2.0',
  soversion : '0',
  c_args: [
    '-DLIB_HEMARG_EXPORTS',
    #'-DWE_TRACIN',
  ],
  dependencies : [
    m_dep,
  ],
  include_directories : [
    cprintf_inc,
  ],
  install : true,
)

libhemlock_argparser_dep = declare_dependency(
  include_directories : libhemlock_argparser_public_includes,
  link_with : libhemlock_argparser,
)

install_headers(
  [ 'argparser.h', 'option.h' ], 
  subdir : 'hemlock_argparser',
)

pkg = import('pkgconfig')
pkg.generate(
  libraries : libhemlock_argparser_dep,
  subdirs : [ '.', 'hemlock_argparser' ],
  version : '0.2.0',
  name : 'libhemlock_argparser',
  filebase : 'hemlock_argparser',
  description : 'Generic arguement parser.',

)


# end of file
