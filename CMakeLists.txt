cmake_minimum_required(VERSION 3.10)

set(MAIN_PROJECT expeval)
set(TEST_PROJECT ${MAIN_PROJECT}-test)
set(VALID_EXPR_TEST_PROJECT ${TEST_PROJECT}-valid-expressions)
set(INVALID_EXPR_TEST_PROJECT ${TEST_PROJECT}-invalid-expressions)
set(VALID_CTX_EXPR_TEST_PROJECT ${TEST_PROJECT}-valid-contextual-expressions)
set(INVALID_CTX_EXPR_TEST_PROJECT ${TEST_PROJECT}-invalid-contextual-expressions)

project(${MAIN_PROJECT} LANGUAGES C)

include_directories(include/${MAIN_PROJECT})

add_subdirectory(test)

set(SOURCE_FILE_LIST
    src/expeval.c
    src/result.c
    src/result_code.c
    src/math_operations.c
    src/expeval_ext.c
    src/internal/parser.c
    src/internal/number_parser.c
    src/internal/operand_actions.c
    src/internal/name_resolver.c
)

add_library(${MAIN_PROJECT} ${SOURCE_FILE_LIST})

target_link_libraries(${MAIN_PROJECT}
    m # math library
)

enable_testing()
add_test(NAME ${VALID_EXPR_TEST_PROJECT} COMMAND ${VALID_EXPR_TEST_PROJECT})
add_test(NAME ${INVALID_EXPR_TEST_PROJECT} COMMAND ${INVALID_EXPR_TEST_PROJECT})
add_test(NAME ${VALID_CTX_EXPR_TEST_PROJECT} COMMAND ${VALID_CTX_EXPR_TEST_PROJECT})
add_test(NAME ${INVALID_CTX_EXPR_TEST_PROJECT} COMMAND ${INVALID_CTX_EXPR_TEST_PROJECT})
