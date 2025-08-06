# Test configuration
set(TEST_SOURCE_FILE_LIST
    src/common.c
)

project(${VALID_EXPR_TEST_PROJECT} LANGUAGES C)
project(${INVALID_EXPR_TEST_PROJECT} LANGUAGES C)
project(${VALID_CTX_EXPR_TEST_PROJECT} LANGUAGES C)
project(${INVALID_CTX_EXPR_TEST_PROJECT} LANGUAGES C)

include_directories(include)

add_executable(${VALID_EXPR_TEST_PROJECT}
    ${TEST_SOURCE_FILE_LIST}
    src/valid_expressions.c
)

add_executable(${INVALID_EXPR_TEST_PROJECT}
    ${TEST_SOURCE_FILE_LIST}
    src/invalid_expressions.c
)

add_executable(${VALID_CTX_EXPR_TEST_PROJECT}
    ${TEST_SOURCE_FILE_LIST}
    src/valid_contextual_expressions.c
)

add_executable(${INVALID_CTX_EXPR_TEST_PROJECT}
    ${TEST_SOURCE_FILE_LIST}
    src/invalid_contextual_expressions.c
)


target_link_libraries(${VALID_EXPR_TEST_PROJECT} PRIVATE
    ${MAIN_PROJECT}
)

target_link_libraries(${INVALID_EXPR_TEST_PROJECT} PRIVATE
    ${MAIN_PROJECT}
)

target_link_libraries(${VALID_CTX_EXPR_TEST_PROJECT} PRIVATE
    ${MAIN_PROJECT}
)

target_link_libraries(${INVALID_CTX_EXPR_TEST_PROJECT} PRIVATE
    ${MAIN_PROJECT}
)
