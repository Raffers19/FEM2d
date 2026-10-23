# Create the FEM library
add_library(fem2d STATIC
    mesh/mesh.cpp
    main.cpp
    #elements/p1_triangle.cpp
    #quadrature/triangle_quadrature.cpp
    #assembly/poisson.cpp
    #linalg/sparse_matrix.cpp
)

# Make public headers accessible
target_include_directories(fem2d PUBLIC
    ${PROJECT_SOURCE_DIR}/include
)

# Require C++20
target_compile_features(fem2d PUBLIC cxx_std_20)

# Enable compiler warnings
if(MSVC)
    target_compile_options(fem2d PRIVATE /W4)
else()
    target_compile_options(fem2d PRIVATE -Wall -Wextra -Wpedantic)
endif()