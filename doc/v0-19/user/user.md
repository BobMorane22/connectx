# Connect X v0.19 (November 8, 2020)

## New features

In this iteration:

1. assertion in the terminal when a warning dialog is popped removed.


## Fixed assertion message

When the user input is not valid in the _New game_ view, a warning dialog is shown. When that happened, the following message was displayed in the console:

```
Gtk-Message: GtkDialog mapped without a transient parent. This is discouraged.
```

It now no longer appears.