#!/bin/bash

# find /path/to/files -type f -exec sed -i 's/oldstring/new string/g' {} \;
find /home/bob/Programming/connectx/cxui/include/cxui -type f -exec sed -i 's/namespace cx::ui::cmn/namespace cx::ui/g' {} \;

find /home/bob/Programming/connectx -type f -exec sed -i 's/cx::ui::AboutWindowPresenter/cx::ui::AboutWindowPresenter/g' {} \;
find /home/bob/Programming/connectx -type f -exec sed -i 's/cx::ui::AnimatedBoardModel/cx::ui::AnimatedBoardModel/g' {} \;
find /home/bob/Programming/connectx -type f -exec sed -i 's/cx::ui::AnimatedBoardPresenter/cx::ui::AnimatedBoardPresenter/g' {} \;
find /home/bob/Programming/connectx -type f -exec sed -i 's/cx::ui::cmn::AnimationInformation/cx::ui::AnimationInformation/g' {} \;
find /home/bob/Programming/connectx -type f -exec sed -i 's/cx::ui::cmn::BoardAnimation/cx::ui::BoardAnimation/g' {} \;
find /home/bob/Programming/connectx -type f -exec sed -i 's/cx::ui::cmn::BoardAnimationNotificationContext/cx::ui::BoardAnimationNotificationContext/g' {} \;
find /home/bob/Programming/connectx -type f -exec sed -i 's/cx::ui::cmn::FrameAnimationStrategy/cx::ui::FrameAnimationStrategy/g' {} \;
find /home/bob/Programming/connectx -type f -exec sed -i 's/cx::ui::cmn::GameResolutionDialogController/cx::ui::GameResolutionDialogController/g' {} \;
find /home/bob/Programming/connectx -type f -exec sed -i 's/cx::ui::cmn::GameResolutionDialogPresenterFactory/cx::ui::GameResolutionDialogPresenterFactory/g' {} \;
find /home/bob/Programming/connectx -type f -exec sed -i 's/cx::ui::cmn::GameViewKeyHandlerStrategyFactory/cx::ui::GameViewKeyHandlerStrategyFactory/g' {} \;
find /home/bob/Programming/connectx -type f -exec sed -i 's/cx::ui::cmn::IAboutWindowPresenter/cx::ui::IAboutWindowPresenter/g' {} \;
find /home/bob/Programming/connectx -type f -exec sed -i 's/cx::ui::cmn::IAbstractConnectXWidgetsFactory/cx::ui::IAbstractConnectXWidgetsFactory/g' {} \;
find /home/bob/Programming/connectx -type f -exec sed -i 's/cx::ui::cmn::IAnimatedBoard/cx::ui::IAnimatedBoard/g' {} \;
find /home/bob/Programming/connectx -type f -exec sed -i 's/cx::ui::cmn::IAnimatedBoardModel/cx::ui::IAnimatedBoardModel/g' {} \;
find /home/bob/Programming/connectx -type f -exec sed -i 's/cx::ui::cmn::IAnimatedBoardPresenter/cx::ui::IAnimatedBoardPresenter/g' {} \;
find /home/bob/Programming/connectx -type f -exec sed -i 's/cx::ui::cmn::IGameResolutionDialogController/cx::ui::IGameResolutionDialogController/g' {} \;
find /home/bob/Programming/connectx -type f -exec sed -i 's/cx::ui::cmn::IGameResolutionDialogPresenter/cx::ui::IGameResolutionDialogPresenter/g' {} \;
find /home/bob/Programming/connectx -type f -exec sed -i 's/cx::ui::cmn::IGameViewController/cx::ui::IGameViewController/g' {} \;
find /home/bob/Programming/connectx -type f -exec sed -i 's/cx::ui::cmn::IGameViewKeyHandlerStrategy/cx::ui::IGameViewKeyHandlerStrategy/g' {} \;
find /home/bob/Programming/connectx -type f -exec sed -i 's/cx::ui::cmn::IGameViewPresenter/cx::ui::IGameViewPresenter/g' {} \;
find /home/bob/Programming/connectx -type f -exec sed -i 's/cx::ui::cmn::IMainWindowController/cx::ui::IMainWindowController/g' {} \;
find /home/bob/Programming/connectx -type f -exec sed -i 's/cx::ui::cmn::IMainWindowPresenter/cx::ui::IMainWindowPresenter/g' {} \;
find /home/bob/Programming/connectx -type f -exec sed -i 's/cx::ui::cmn::INewGameViewController/cx::ui::INewGameViewController/g' {} \;
find /home/bob/Programming/connectx -type f -exec sed -i 's/cx::ui::cmn::INewGameViewPresenter/cx::ui::INewGameViewPresenter/g' {} \;
find /home/bob/Programming/connectx -type f -exec sed -i 's/cx::ui::cmn::INewPlayersList/cx::ui::INewPlayersList/g' {} \;
find /home/bob/Programming/connectx -type f -exec sed -i 's/cx::ui::cmn::IView/cx::ui::IView/g' {} \;
find /home/bob/Programming/connectx -type f -exec sed -i 's/cx::ui::cmn::MainWindowController/cx::ui::MainWindowController/g' {} \;
find /home/bob/Programming/connectx -type f -exec sed -i 's/cx::ui::cmn::MainWindowPresenter/cx::ui::MainWindowPresenter/g' {} \;
find /home/bob/Programming/connectx -type f -exec sed -i 's/cx::ui::cmn::MenuItem/cx::ui::MenuItem/g' {} \;
find /home/bob/Programming/connectx -type f -exec sed -i 's/cx::ui::cmn::TieGameResolutionDialogPresenter/cx::ui::TieGameResolutionDialogPresenter/g' {} \;
find /home/bob/Programming/connectx -type f -exec sed -i 's/cx::ui::cmn::WidgetsFactories/cx::ui::WidgetsFactories/g' {} \;
find /home/bob/Programming/connectx -type f -exec sed -i 's/cx::ui::cmn::WinGameResolutionDialogPresenter/cx::ui::WinGameResolutionDialogPresenter/g' {} \;
