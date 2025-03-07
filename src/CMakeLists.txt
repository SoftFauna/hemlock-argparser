
# build the static lib
add_library(hemlock_argparser STATIC 
        argparser/argparser.c
        argparser/finish.c
        argparser/genhelp.c
        argparser/log.c
        argparser/parser.c
        argparser/pretty.c
        argparser/tokenizer.c
        argparser/validate.c
)
target_compile_definitions(hemlock_argparser PRIVATE LIB_HEMARG_EXPORTS)
target_link_libraries(hemlock_argparser m)

# build the example executable
add_executable(hemlock_argparser_ex example/main.c)
target_include_directories(hemlock_argparser_ex PRIVATE "./argparser")
target_link_libraries(hemlock_argparser_ex hemlock_argparser)

# end of file
