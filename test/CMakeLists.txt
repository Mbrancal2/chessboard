#not in use right now but willbe when I fix cmake file and impliment Cach2 tests.
include(AddCatch2)

add_executable(
    unit_tests
    test.cpp
)

target_link_libraries(
    unit_tests PRIVATE chessgame Catch2::Catch2WithMain
)

include(CTest)
include(Catch)
catch_discover_tests(unit_tests)