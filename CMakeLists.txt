cmake_minimum_required(VERSION 3.10)

set(MAIN_PROJECT expeval)

project(${MAIN_PROJECT} LANGUAGES C)

include_directories(include/${MAIN_PROJECT})

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

# Test configuration
set(TEST_SOURCE_FILE_LIST
    tests/common.c
)

set(TEST_PROJECT ${MAIN_PROJECT}-test)
set(VALID_EXPR_TEST_PROJECT ${TEST_PROJECT}-valid-expressions)
set(INVALID_EXPR_TEST_PROJECT ${TEST_PROJECT}-invalid-expressions)
set(CTX_EXPR_TEST_PROJECT ${TEST_PROJECT}-contextual-expressions)

project(${VALID_EXPR_TEST_PROJECT} LANGUAGES C)
project(${INVALID_EXPR_TEST_PROJECT} LANGUAGES C)

add_executable(${VALID_EXPR_TEST_PROJECT}
    ${TEST_SOURCE_FILE_LIST}
    tests/valid_expressions.c
)

add_executable(${INVALID_EXPR_TEST_PROJECT}
    ${TEST_SOURCE_FILE_LIST}
    tests/invalid_expressions.c
)

add_executable(${CTX_EXPR_TEST_PROJECT}
    ${TEST_SOURCE_FILE_LIST}
    tests/contextual_expressions.c
)

target_link_libraries(${VALID_EXPR_TEST_PROJECT} PRIVATE
    ${MAIN_PROJECT}
)

target_link_libraries(${INVALID_EXPR_TEST_PROJECT} PRIVATE
    ${MAIN_PROJECT}
)

target_link_libraries(${CTX_EXPR_TEST_PROJECT} PRIVATE
    ${MAIN_PROJECT}
)

enable_testing()
add_test(NAME ${VALID_EXPR_TEST_PROJECT} COMMAND ${VALID_EXPR_TEST_PROJECT})
add_test(NAME ${INVALID_EXPR_TEST_PROJECT} COMMAND ${INVALID_EXPR_TEST_PROJECT})
add_test(NAME ${CTX_EXPR_TEST_PROJECT} COMMAND ${CTX_EXPR_TEST_PROJECT})
