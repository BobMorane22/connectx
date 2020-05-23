# Wishlist for Connect X

## Wishes

These ideas are not ready yet to become official story in Taiga. For now, they are kept here as wishes that might, some day, become a reality:

- Add the possibility to create a classic Connect 4 in a simplified way (no grid dimensions,
  no adding of players, etc).
- Add a save feature: users can save the current game state and come back to it later.
- Add a crash handler (report with log, message to user, machine/OS information, etc.)
- Add a playback feature: users can check a replay of passed games.
- Add a game export feature: users can export a finished game in a report. They can trace
  back their moves for a game.
- Create a OS library (paths, I/O, file handling, threads, etc).
- Add user configurations to save some parameters (i.e. window positioning, scaling, etc).
- Add a sound player.
- Add utf8 support inside the model.
- Add portable help system (one that can be maintained only once, but displayed offline,
  inside the application and also online).
- Add animations for the Grid widget. Discs should fall smoothly (gravity feel).
- In `cxgui`, add global GUI settings that can be reused across windows and widgets
  (spacing between widgets, fonts, etc).


## Planned wishes

These wishes have made their way in Taiga:

| Task | Wish |
| :----| :--- |
| TG-93 | Migrate the Connect X documentation center to the new project. |
| TG-95 | Have a commit message template to format messages accordingly. |
| TG-94 | Create a unit test utilities library (general fixtures, helper, etc).|
| TG-96 | Disable unreachable code analysis by LCOV for `cxmodel`, `cxgui`, `cxexec` and `connectx`. |
| TG-97 | Activate the "Start" button (New Game view) only when valid and complete game information is detected. |
| TG-98 | Add the possibility to come back on a new game creation, for games that have not yet been started. |


## Handled wishes

These wishes have become a reality:

| Task | Wish |
| :--- | :--- |
| TG-87 | Have 'make' always builds the necessary without having to 'make clean' first. |
| TG-86 | Have the `cxinv::HandleAssert` returns a boolean so that calls such as `if(ASSERT(...))` |
