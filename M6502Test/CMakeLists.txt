#add_executable(M6502Test src/main_6502_test.cpp)
#
#target_link_libraries(M6502Test 
#    M6502Lib
#    gtest_main
#)

add_executable(M6502RefactoredTest
    src/m6502_cpu_test.cpp
)

target_link_libraries(M6502RefactoredTest
    M6502Lib
    gtest_main
)