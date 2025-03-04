

libhemlock_argparser_public_includes = [
  './',
]

libhemlock_argparser = library(
  'hemlock-argparser',
  [ 'argparser.c', ],
  version : '0.1.0',
  soversion : '0',
)

libhemlock_argparser_dep = declare_dependency(
  include_directories : libhemlock_argparser_public_includes,
  link_with : libhemlock_argparser,
)

# end of file
