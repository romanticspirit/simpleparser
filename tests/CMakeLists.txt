set(UNIT_TEST_LIST
        string_utils)

file(GLOB_RECURSE TEST_SOURCES ./*.cpp)


set(TARGET_NAME tests)

add_executable(${TARGET_NAME}
        main.cpp
        ${TEST_SOURCES})

target_link_libraries(${TARGET_NAME}
        PUBLIC intepreter)

include_directories(../externals/catch2/)

add_test(
        NAME ${TARGET_NAME}
        COMMAND ${TARGET_NAME} -o report.xml -r junit)


