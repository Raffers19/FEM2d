# Conjugate Gradient solver test
add_executable(test_solver_cg
    test_solver_cg.cpp
)

target_link_libraries(test_solver_cg PRIVATE fem2d_lib)

add_test(
    NAME SolverConjugateGradients
    COMMAND test_solver_cg
)

if(MSVC)
    target_compile_options(test_solver_cg PRIVATE /W4 /EHsc)
    
endif()