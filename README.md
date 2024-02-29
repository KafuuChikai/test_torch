# test_torch
## 0. Introduction

This is a generic **ROS package** designed to test the functionality of **LibTorch**.

## 1. Installation

- Move this package to the directory of your **ROS workspace** (e.g., `catkin_ws/src/`).

- Change the **Torch_DIR** variable in the **CMakeLists.txt** file to point to your **LibTorch installation directory**.

```cmake
# set package directories
set(Torch_DIR {Your_libtorch_path})
```

Navigate to the `catkin_ws/` directory and then build:

```cmake
catkin_make
```

## 2. getting started

To get started, open a terminal and start `roscore`.

```ros
roscore
```

Then, in another terminal, run rosnode.

```ros
rosrun test_torch test_torch
```