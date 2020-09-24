# BACKLOG

List of all tasks which should eventually be documented in the project management tool.

## (18-09-2020) Remove useless cxgui::IMainWindowPresenter interface

This interface only inherits other interfaces. It is therefore useless...


## (24-09-2020) Migrate the contents of cxgui::NewGameView::OnStart() into the presenter

Right now, this method handles a lot of housekeeping that should not be the reponsibility
of the view. It should rather be the presenter which handles all the logic, and the view
only displaying errors (if any) and eventually calling the controller.

This migration could have significant importance on coverage because everything that
is migrated can then be unit tested.


## (24-09-2020) When creating big boards, the mainwindow size does not it in the screen

For example, on my big screen, when creating a 64x64 board, the window is so big it is not
entirely visible on my screen. Clicking maximize does not help, and it can't be minimized.
