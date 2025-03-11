
# build the static lib
add_library(hemlock_argparser SHARED
        hemlock_argparser/argparser.c
        hemlock_argparser/finish.c
        hemlock_argparser/genhelp.c
        hemlock_argparser/log.c
        hemlock_argparser/parser.c
        hemlock_argparser/pretty.c
        hemlock_argparser/tokenizer.c
        hemlock_argparser/validate.c
)
target_compile_definitions(hemlock_argparser PRIVATE LIB_HEMARG_EXPORTS)
target_include_directories(hemlock_argparser PRIVATE "${CMAKE_SOURCE_DIR}/external/cprintf")
if(MATH_LIBRARY)
    target_link_libraries(hemlock_argparser ${MATH_LIBRARY})
endif()
set_target_properties(hemlock_argparser PROPERTIES VERSION ${PROJECT_VERSION})
set_target_properties(hemlock_argparser PROPERTIES SOVERSION ${PROJECT_VERSION_MAJOR})
set_target_properties(hemlock_argparser PROPERTIES PUBLIC_HEADER hemlock_argparser/argparser.h)
set_target_properties(hemlock_argparser PROPERTIES PUBLIC_HEADER hemlock_argparser/option.h)

# build the example executable
add_executable(hemlock_argparser_ex 
        example/main.c
        example/cli.c
)
target_include_directories(hemlock_argparser_ex PRIVATE 
        "."
        "./example"
)
target_link_libraries(hemlock_argparser_ex hemlock_argparser)

# end of file
