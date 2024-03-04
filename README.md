# test_torch
## 0. Introduction

This is a generic **ROS package** designed to test the functionality of **LibTorch**. [https://pytorch.org/get-started/locally/](https://pytorch.org/get-started/locally/)

Please download **cxx11 ABI** version, otherwise it may cause **ROS library error**.

**Reference:**

- [Libtorch with ROS](https://discuss.pytorch.org/t/libtorch-with-ros/51313)
- [Using Libtorch and ROS together causes library error, issue #60178](https://github.com/pytorch/pytorch/issues/60178)

## 1. Installation

- Move this package to the directory of your **ROS workspace** (e.g., `catkin_ws/src/`).

  - Create a workspace: `cd $HOME && mkdir -p catkin_ws/src`

  - Clone the repo into the workspace:

    ```
    cd $HOME/catkin_ws/src
    git clone https://github.com/KafuuChikai/test_torch.git
    ```

- Change the **Torch_DIR** variable in the **CMakeLists.txt** file to point to your **LibTorch installation directory**.

  ```cmake
  # set package directories
  set(Torch_DIR {Your_libtorch_path})
  ```

- Navigate to the `catkin_ws/` directory and then build:

  ```cmake
  catkin_make
  ```

Possible make **ERROR**:

  ```bash
  CMake Error at test_torch/CMakeLists.txt:1 (cmake_minimum_required):
    CMake 3.18 or higher is required.  You are running version 3.xx.x
  ```

**Resolution: update Cmake：**

1. Download from https://cmake.org/files/ and

   ```bash
   tar -xvzf cmake-3.xx.tar.gz
   ```

2. Make and install

   ```
   cd cmake-3.xx.tar.gz
   ./configure
   make
   sudo make install
   ```

## 2. getting started

To get started, open a terminal and start `roscore`.

```ros
roscore
```

Then, in another terminal, run ROS node.

```ros
rosrun test_torch test_torch
```