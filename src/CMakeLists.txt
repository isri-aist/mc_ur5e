# Here we find a typical ROS description package, this set the MC_UR5E_DESCRIPTION_PATH CMake variable
find_description_package(mc_ur5e_description)

# Generate the robot module C++ code using this value
configure_file(ur5e.in.cpp "${CMAKE_CURRENT_BINARY_DIR}/ur5e.cpp")

set(ur5e_SRC
  "${CMAKE_CURRENT_BINARY_DIR}/ur5e.cpp"
)
set(ur5e_HDR
  ur5e.h
)

add_robot(ur5e ${ur5e_SRC} ${ur5e_HDR})
target_include_directories(ur5e PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}")
