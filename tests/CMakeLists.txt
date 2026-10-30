# Solver test
add_executable(test_solver_cg
    test_solver_cg.cpp
)

target_link_libraries(test_solver_cg PRIVATE fem2d_lib)

add_test(
    NAME Solver
    COMMAND test_solver_cg
)

# Mesh test
add_executable(test_mesh
    test_mesh.cpp
)

target_link_libraries(test_mesh PRIVATE fem2d_lib)

add_test(
    NAME Mesher
    COMMAND test_mesh
)





if(MSVC)
    target_compile_options(test_solver_cg PRIVATE /W4 /EHsc)
    target_compile_options(test_mesh PRIVATE /W4 /EHsc)
    
endif()