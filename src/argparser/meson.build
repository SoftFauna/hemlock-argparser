

libhemlock_argparser_public_includes = [
  './',
]

libhemlock_argparser = library(
  'hemlock_argparser',
  [ 'argparser.c', ],
  version : '0.1.0',
  soversion : '0',
  c_args: [
    '-DLIB_HEMARG_EXPORTS',
  ],
  install : true,
)

libhemlock_argparser_dep = declare_dependency(
  include_directories : libhemlock_argparser_public_includes,
  link_with : libhemlock_argparser,
)

install_headers(
  'argparser.h', 
  subdir : 'hemlock_argparser',
)

pkg = import('pkgconfig')
pkg.generate(
  libraries : libhemlock_argparser_dep,
  subdirs : [ '.', 'hemlock_argparser' ],
  version : '0.1.0',
  name : 'libhemlock_argparser',
  filebase : 'hemlock_argparser',
  description : 'Generic arguement parser.',

)


# end of file
