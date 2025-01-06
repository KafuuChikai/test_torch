cmake_minimum_required(VERSION 3.18 FATAL_ERROR)
set(CMAKE_CXX_STANDARD 11)
project(test_torch)

# set package directories
set(Torch_DIR "$ENV{HOME}/libtorch/share/cmake/Torch")

## Find catkin macros and libraries
find_package(catkin REQUIRED COMPONENTS
  roscpp
  rospy
  std_msgs
)
find_package(Eigen3 REQUIRED)
find_package(Torch REQUIRED)

catkin_package(
  INCLUDE_DIRS include
#  LIBRARIES test_torch
#  CATKIN_DEPENDS roscpp rospy std_msgs
#  DEPENDS system_lib
)

###########
## Build ##
###########

## Specify additional locations of header files
include_directories(
  include
  ${catkin_INCLUDE_DIRS}
  ${EIGEN3_INCLUDE_DIRS}
)

# torch
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${TORCH_CXX_FLAGS}")

# test_torch
add_executable(${PROJECT_NAME}
              src/test_torch.cpp
              )
target_link_libraries(${PROJECT_NAME}
                      ${catkin_LIBRARIES}
                      ${TORCH_LIBRARIES}
                      )
set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 17)