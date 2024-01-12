add_library( test_base INTERFACE )
target_include_directories( test_base
    INTERFACE
    
    )
target_link_libraries( test_base
    INTERFACE
    doctest::doctest
    example_static
    )

# add tests
TEST_TARGET(test_example test_example.cc test_base)
