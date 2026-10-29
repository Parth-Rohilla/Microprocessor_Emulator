add_executable(
    M6502Test 
    src/6502LoadInstructionsTests.cpp
    src/6502StoreInstructionsTests.cpp
    )

target_link_libraries(
    M6502Test 
    M6502Lib
    gtest_main
)

# backup test file
#
#add_executable(M6502RefactoredTest
#   src/m6502_cpu_test.cpp
#)
#
#target_link_libraries(M6502RefactoredTest
#  M6502Lib
#    gtest_main
#)