# BACKLOG

List of all tasks which should eventually be documented in the project management tool.

## (24-01-2021) Handle Github deprecation notice.

I recently have gotten some messages from GitHub asking me to update the way I access the
repository. The way I am working right now will no longer be working at GitHub soon:

  > Hi @BobMorane22,
  > 
  > You recently used a password to access the repository at
  > BobMorane22/connectx with git using git/2.17.1.
  > 
  > Basic authentication using a password to Git is deprecated and will soon no longer work.
  > Visit https://github.blog/2020-12-15-token-authentication-requirements-for-git-operations/
  > for more information around suggested workarounds and removal dates.
  > 
  > Thanks,
  > The GitHub Team

The removal date is August 13, 2021.


## (30-01-2021) Add unit tests for the NotImplementedException class.

Add unit tests for the `NotImplementedException` class.


## (30-01-2021) Progate the use of the ConfigurableMainWindowPresenterTestFixture class

Check if the following tests could benefit from the new
`ConfigurableMainWindowPresenterTestFixture` test fixture.

```
Update_CreateNewGame_NewGameInformationUpdated
Update_ChipDropped_BoardInformationUpdated
Update_GameReinitialized_BoardInformationUpdated
IsNewGamePossible_NoNotification_FalseReturned
IsNewGamePossible_CreateNewGameNotification_TrueReturned
IsNewGamePossible_ChipDroppedNotification_TrueReturned
IsNewGamePossible_GameReinitializedNotification_TrueReturned
IsNewGamePossible_AllOtherNotifications_FalseReturned
IsCurrentGameReinitializationPossible_NoNotification_FalseReturned
IsCurrentGameReinitializationPossible_ChipDroppedNotification_TrueReturned
IsCurrentGameReinitializationPossible_AllOtherNotifications_FalseReturned
```


## (XX-XX-XXXX) Title

Description...
