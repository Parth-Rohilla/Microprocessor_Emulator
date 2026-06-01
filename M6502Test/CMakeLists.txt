add_executable(M6502Test src/main_6502_test.cpp)

target_link_libraries(M6502Test 
    M6502Lib
    gtest_main
)