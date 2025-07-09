cmake_minimum_required(VERSION 3.20)

set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 20)

set(tName sodium)
set(tNameRand ${tName}_random)
set(tNameTest ${tName}_test)
set(tNameProj ${tName}_project)

project(${tNameProj})

include(CTest)

# sodium 部分。
set(${tName}_src_path ${CMAKE_CURRENT_LIST_DIR}/libsodium/src/libsodium)
set(${tName}_src
    # sources
    ${CMAKE_CURRENT_LIST_DIR}/empty_implementation.c
    ${${tName}_src_path}/sodium/core.c
    ${${tName}_src_path}/sodium/runtime.c
    ${${tName}_src_path}/sodium/utils.c
    ${${tName}_src_path}/randombytes/randombytes.c
    ${${tName}_src_path}/randombytes/sysrandom/randombytes_sysrandom.c
    ${${tName}_src_path}/randombytes/internal/randombytes_internal_random.c

    # headers
    ${${tName}_src_path}/include/sodium.h
    ${${tName}_src_path}/include/sodium/core.h
    ${${tName}_src_path}/include/sodium/runtime.h
    ${${tName}_src_path}/include/sodium/utils.h
    ${${tName}_src_path}/include/sodium/randombytes.h
    ${${tName}_src_path}/include/sodium/randombytes_internal_random.h
    ${${tName}_src_path}/include/sodium/randombytes_sysrandom.h
)

add_library(${tName} STATIC ${${tName}_src})
add_library(sodium::${tName} ALIAS ${tName})
target_compile_definitions(${tName} PUBLIC USE_SODIUM SODIUM_STATIC)
target_include_directories(${tName} PUBLIC ${${tName}_src_path}/include ${${tName}_src_path}/include/sodium)
if (MSVC)
    target_compile_options(${tName} PRIVATE /utf-8)
endif()


# sodium_random 部分，用于包装sodium随机算法部分，以便在外部更方便使用。
set(${tNameRand}_src
    # sources
    ${CMAKE_CURRENT_LIST_DIR}/sodium_random.cpp

    # headers
    ${CMAKE_CURRENT_LIST_DIR}/sodium_random.hpp
)

add_library(${tNameRand} STATIC ${${tNameRand}_src})
add_library(sodium::${tNameRand} ALIAS ${tNameRand})
target_include_directories(${tNameRand} PUBLIC ${CMAKE_CURRENT_LIST_DIR})
if (MSVC)
    target_compile_options(${tNameRand} PRIVATE /utf-8)
endif()
target_link_libraries(${tNameRand} PUBLIC ${tName})

if (${PROJECT_IS_TOP_LEVEL})
    # sodium_test 部分。

    set(${tNameTest}_src
        # sources
        ${CMAKE_CURRENT_LIST_DIR}/test/main.cpp
    )

    add_executable(${tNameTest} ${${tNameTest}_src})

    enable_testing()
    add_test(
        NAME ${tNameTest}
        COMMAND $<TARGET_FILE:${tNameTest}>
        WORKING_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}
    )

    if (MSVC)
        target_compile_options(${tNameTest} PRIVATE /utf-8)
    endif()
    target_link_libraries(${tNameTest} PUBLIC ${tNameRand})
endif()