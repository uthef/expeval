# Test configuration
set(TEST_SOURCE_FILE_LIST
    common.c
)

project(${VALID_EXPR_TEST_PROJECT} LANGUAGES C)
project(${INVALID_EXPR_TEST_PROJECT} LANGUAGES C)

add_executable(${VALID_EXPR_TEST_PROJECT}
    ${TEST_SOURCE_FILE_LIST}
    valid_expressions.c
)

add_executable(${INVALID_EXPR_TEST_PROJECT}
    ${TEST_SOURCE_FILE_LIST}
    invalid_expressions.c
)

add_executable(${CTX_EXPR_TEST_PROJECT}
    ${TEST_SOURCE_FILE_LIST}
    contextual_expressions.c
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
