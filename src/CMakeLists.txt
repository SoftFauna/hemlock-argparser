
# build the static lib
add_library(hemlock-argparser STATIC 
        argparser/argparser.c
        argparser/finish.c
        argparser/genhelp.c
        argparser/log.c
        argparser/parser.c
        argparser/pretty.c
        argparser/tokenizer.c
        argparser/validate.c
)
target_compile_definitions(hemlock-argparser PRIVATE LIB_HEMARG_EXPORTS)
target_link_libraries(hemlock-argparser m)

# build the example executable
add_executable(argparser_ex example/main.c)
target_include_directories(argparser_ex PRIVATE "./argparser")
target_link_libraries(argparser_ex hemlock-argparser)

# end of file
