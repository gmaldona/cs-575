cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

project(knapsack)

add_compile_options(-Wall -Wextra -O2 -Wunused-parameter)

set(COMMON_SRC
    src/knapsack.cc
    src/KnapsackFileReader.cc
    src/KnapsackFormattedFileWriter.cc)

add_executable(createkn01
               ${COMMON_SRC}
               src/impl/CreateRandomKnapsack.cc)

target_include_directories(createkn01 PUBLIC
               ${CMAKE_CURRENT_SOURCE_DIR}/include/)

add_executable(bruteforce
               ${COMMON_SRC}
               src/impl/BruteforceKnapsack.cc)

target_include_directories(bruteforce PUBLIC
               ${CMAKE_CURRENT_SOURCE_DIR}/include/)

add_executable(dynpro
               ${COMMON_SRC}
               src/impl/DPKnapsack.cc)

target_include_directories(dynpro PUBLIC
               ${CMAKE_CURRENT_SOURCE_DIR}/include/)

add_executable(igreedy
               ${COMMON_SRC}
               src/impl/GreedyKnapsack.cc)               

target_include_directories(igreedy PUBLIC
               ${CMAKE_CURRENT_SOURCE_DIR}/include/)
