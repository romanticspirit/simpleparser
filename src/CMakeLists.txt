set(TARGET_NAME intepreter)

file(GLOB_RECURSE SOURCE ./*.cpp ./*.h)
add_library(${TARGET_NAME} STATIC ${SOURCE})

include_directories(include)
target_include_directories(${TARGET_NAME}
        INTERFACE include)

install(TARGETS ${TARGET_NAME}
        ARCHIVE DESTINATION lib
        LIBRARY DESTINATION lib)

