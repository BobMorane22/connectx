# Connect X

## Building and installing

### Dependencies

To build Connect X, the following dependencies are needed:

* A C++17 compatible compiler.
* Gtkmm 3.24.


### Installation guide

1. Create a build directory, move to it:

        cd ..
        mkdir build
        cd build

2. Generate the CMake project:

        cmake -DCMAKE_BUILD_TYPE=Release \
              ../connectx

3. Build:

        make -j8

4. Install. Note that this operation may require root privileges:

        make install

Installing at a custom location is also possible by supplying a custom
value for the `CMAKE_INSTALL_PREFIX` variable when generating the CMake
project.


## Latest stable

The latest stable version is 0.34.


## Changelogs

Available [here](./changelogs/changes.md).
