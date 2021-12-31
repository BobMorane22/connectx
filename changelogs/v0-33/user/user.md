# Connect X v0.33 (January 2, 2022)

## New features

In this iteration:

1. Buiding Connect X is now possible with CMake.
2. Installing Connect X is now possible with CMake.


## How to build and run Connect X:

### Default installation location

The most basic way to build is to use the default install location.
Assuming we start at the top of the project's source directory.

1. Create a build directory, move to it:

        cd ..
        mkdir build
        cd build

2. Generate the CMake project (using the defaults):

        cmake -DCMAKE_BUILD_TYPE=Release \
              ../connectx

3. Build the software:

        make -j8

4. Finally, install it (default location is: `/usr/local/`). Note that
   this operation may require root privileges:

        make install

5. You can now run Connect X normally:

        connectx


### Installing at a custom location

If you want to install Connect X somewhere else, you
can pass a custom `CMAKE_INSTALL_PREFIX` value. In this
next example, we will assume you want to install the
software under `/home/bob/`:

1. Create a build directory, move to it:

        cd ..
        mkdir build
        cd build

2. Generate the CMake project (using a custom install location):

        cmake -DCMAKE_BUILD_TYPE=Release \
              -DCMAKE_INSTALL_PREFIX=/home/bob/ \
              ../connectx

3. Build the software:

        make -j8

4. Finally, install it. Note that this operation may require root
   privileges depending on the location:

        make install

5. You can now move to `/home/bob` and run the software like so:

        cd /home/bob/
        ./bin/connectx

6. To complete the installation and be able to access user help
   files using `yelp`, you will need to update the `XDG_DATA_DIRS`
   environement variable so that `yelp` is aware of your custom
   install location:

        export XDG_DATA_DIRS=/home/bob/share:$XDG_DATA_DIRS

    At this point, if you call `yelp`, the user help should
    be available. Note that this only works if `yelp` is called
    from the same terminal from which the environement variable
    was updated.
