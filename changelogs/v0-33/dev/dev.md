# Connect X v0.33 (January 2, 2022)

## New features

In this iteration:

1. The `tools/script/distribute.sh` script has been ported to CMake.


## How to distribute Connect X

The script works are before as far as calling on the command
prompt is concerned:

```bash
./tools/script/distribute.sh vX.Y
```

This will launch the distribution process. The archives will
now be located under `build/distribute/vX.Y`. The archived
builds are relocatable, so you can run them from anywhere.
If you want to access the documentation however, you will
have to update the `XDG_DATA_DIRS` environement variable, as
described [here](../user/user.md).
