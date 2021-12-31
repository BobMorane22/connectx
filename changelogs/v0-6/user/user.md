# Connect X v0.6 (February 10, 2020)

## New features

In this release, a new logging facility has been introduced.

## Logging facility

When running the Connect X application, a new file appears next to the application executable: `connectx.log`. If you have the executable in a directory and you run `ls` before v0.6:
```
> connectx@doc: ~/connectx$ ./connectx
> ls
```
here is what you get:
```
connectx*
```
If you upgrade to v0.6 and you run Connect X again and then check the files, you now get:
```
connectx*  connectx.log
```
You will notice that a log file has been created. In this log file, you can read information about what actions you have performed with the application and when (as well as other stuff interesting to the developers of the application).

```
Timestamp, Verbosity level, File name, Function name, Line number, Message
2020-02-04T08:00:18.338, DEBUG, cxmodel/src/Model.cpp, Model, 44, Initializing model.
2020-02-04T08:00:21.310, DEBUG, cxmodel/src/Model.cpp, Increment, 71, Incremented value.
2020-02-04T08:00:21.580, DEBUG, cxmodel/src/Model.cpp, Increment, 71, Incremented value.
2020-02-04T08:00:21.860, DEBUG, cxmodel/src/Model.cpp, Increment, 71, Incremented value.
2020-02-04T08:00:22.202, DEBUG, cxmodel/src/Model.cpp, Increment, 71, Incremented value.
2020-02-04T08:00:22.836, DEBUG, cxmodel/src/Model.cpp, Reinitialize, 86, Reinitialized value.
2020-02-04T08:00:23.554, DEBUG, cxmodel/src/Model.cpp, Undo, 98, Last action undoed.
2020-02-04T08:00:24.408, DEBUG, cxmodel/src/Model.cpp, Redo, 110, Last action redoed.
2020-02-04T08:00:25.226, DEBUG, cxmodel/src/Model.cpp, Undo, 98, Last action undoed.
2020-02-04T08:00:26.290, DEBUG, cxmodel/src/Model.cpp, Increment, 71, Incremented value.
2020-02-04T08:00:26.524, DEBUG, cxmodel/src/Model.cpp, Increment, 71, Incremented value.
2020-02-04T08:00:26.763, DEBUG, cxmodel/src/Model.cpp, Increment, 71, Incremented value.
2020-02-04T08:00:27.679, DEBUG, cxmodel/src/Model.cpp, ~Model, 52, Uninitializing model.
```

In case of a bug, or a crash, you can use the contents of this file to better document your experience.

Notes:

1. On every run of Connect X, the previous log file is lost.
2. The file contents follows the CSV format, which means it can be opened in most spreadsheet application.
3. The log file is local to your machine.