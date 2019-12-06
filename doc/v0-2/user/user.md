# Connect X v0.2 (December 15, 2019)

## New features

Two standard command line arguments are now supported: `--help` and `--version`.


## The `--help` argument

With the command

```
connectx --help
```

some help about how to run the software is printed to the console. Note that the program immediately closes afterwards. The printed help looks like this:

```
Usage: connectx [OPTION]...

Possible arguments:
--help        display this help and exit
--version     output version information and exit

Exit status:
 0 if OK,
 1 if problems.

Connect X available at: <https://github.com/BobMorane22/connectx/>

```


## The `--version` argument

With the command

```
connectx --version
```

some basic versionning information is printed to the console. The information includes version number as well as licensing information. For example:

```
Connect X v0.2

Copyright (C) 2019 Eric Poirier.
License GPLv3+: GNU GPL version 3 or later <gnu.org/licenses/gpl.html>.
This is free software: you are free to change and redistribute it.
There is NO WARRANTY, to the extent permitted by law.

Written by Eric Poirier.
```


## Argument call order and unsupported arguments

If an unsupported command line argument is used, an error message is printed to the error stream (still on the console). For example:

```
connectx --invalid
```

results in

```
Connect X: invalid option '--invalid'
```

If more than one _valid_ argument is given, only the first is handled and the program closes. If more than one argument is given and one or more argument is not valid, then the first invalid argument is treated and the program closes.