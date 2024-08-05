#!/bin/bash

# find /path/to/files -type f -exec sed -i 's/oldstring/new string/g' {} \;

# find /home/bob/Programming/connectx/cxui/include/cxui -type f -exec sed -i 's/namespace cx::ui::cmn/namespace cx::ui/g' {} \;
# 
# find /home/bob/Programming/connectx -type f -exec sed -i 's/cx::ui::AboutWindowPresenter/cx::ui::AboutWindowPresenter/g' {} \;
# find /home/bob/Programming/connectx -type f -exec sed -i 's/cx::ui::AnimatedBoardModel/cx::ui::AnimatedBoardModel/g' {} \;
# find /home/bob/Programming/connectx -type f -exec sed -i 's/cx::ui::AnimatedBoardPresenter/cx::ui::AnimatedBoardPresenter/g' {} \;
# find /home/bob/Programming/connectx -type f -exec sed -i 's/cx::ui::AnimationInformation/cx::ui::AnimationInformation/g' {} \;
# find /home/bob/Programming/connectx -type f -exec sed -i 's/cx::ui::BoardAnimation/cx::ui::BoardAnimation/g' {} \;
# find /home/bob/Programming/connectx -type f -exec sed -i 's/cx::ui::BoardAnimationNotificationContext/cx::ui::BoardAnimationNotificationContext/g' {} \;
# find /home/bob/Programming/connectx -type f -exec sed -i 's/cx::ui::FrameAnimationStrategy/cx::ui::FrameAnimationStrategy/g' {} \;
# find /home/bob/Programming/connectx -type f -exec sed -i 's/cx::ui::GameResolutionDialogController/cx::ui::GameResolutionDialogController/g' {} \;
# find /home/bob/Programming/connectx -type f -exec sed -i 's/cx::ui::GameResolutionDialogPresenterFactory/cx::ui::GameResolutionDialogPresenterFactory/g' {} \;
# find /home/bob/Programming/connectx -type f -exec sed -i 's/cx::ui::GameViewKeyHandlerStrategyFactory/cx::ui::GameViewKeyHandlerStrategyFactory/g' {} \;
# find /home/bob/Programming/connectx -type f -exec sed -i 's/cx::ui::IAboutWindowPresenter/cx::ui::IAboutWindowPresenter/g' {} \;
# find /home/bob/Programming/connectx -type f -exec sed -i 's/cx::ui::IAbstractConnectXWidgetsFactory/cx::ui::IAbstractConnectXWidgetsFactory/g' {} \;
# find /home/bob/Programming/connectx -type f -exec sed -i 's/cx::ui::IAnimatedBoard/cx::ui::IAnimatedBoard/g' {} \;
# find /home/bob/Programming/connectx -type f -exec sed -i 's/cx::ui::IAnimatedBoardModel/cx::ui::IAnimatedBoardModel/g' {} \;
# find /home/bob/Programming/connectx -type f -exec sed -i 's/cx::ui::IAnimatedBoardPresenter/cx::ui::IAnimatedBoardPresenter/g' {} \;
# find /home/bob/Programming/connectx -type f -exec sed -i 's/cx::ui::IGameResolutionDialogController/cx::ui::IGameResolutionDialogController/g' {} \;
# find /home/bob/Programming/connectx -type f -exec sed -i 's/cx::ui::IGameResolutionDialogPresenter/cx::ui::IGameResolutionDialogPresenter/g' {} \;
# find /home/bob/Programming/connectx -type f -exec sed -i 's/cx::ui::IGameViewController/cx::ui::IGameViewController/g' {} \;
# find /home/bob/Programming/connectx -type f -exec sed -i 's/cx::ui::IGameViewKeyHandlerStrategy/cx::ui::IGameViewKeyHandlerStrategy/g' {} \;
# find /home/bob/Programming/connectx -type f -exec sed -i 's/cx::ui::IGameViewPresenter/cx::ui::IGameViewPresenter/g' {} \;
# find /home/bob/Programming/connectx -type f -exec sed -i 's/cx::ui::IMainWindowController/cx::ui::IMainWindowController/g' {} \;
# find /home/bob/Programming/connectx -type f -exec sed -i 's/cx::ui::IMainWindowPresenter/cx::ui::IMainWindowPresenter/g' {} \;
# find /home/bob/Programming/connectx -type f -exec sed -i 's/cx::ui::INewGameViewController/cx::ui::INewGameViewController/g' {} \;
# find /home/bob/Programming/connectx -type f -exec sed -i 's/cx::ui::INewGameViewPresenter/cx::ui::INewGameViewPresenter/g' {} \;
# find /home/bob/Programming/connectx -type f -exec sed -i 's/cx::ui::INewPlayersList/cx::ui::INewPlayersList/g' {} \;
# find /home/bob/Programming/connectx -type f -exec sed -i 's/cx::ui::IView/cx::ui::IView/g' {} \;
# find /home/bob/Programming/connectx -type f -exec sed -i 's/cx::ui::MainWindowController/cx::ui::MainWindowController/g' {} \;
# find /home/bob/Programming/connectx -type f -exec sed -i 's/cx::ui::MainWindowPresenter/cx::ui::MainWindowPresenter/g' {} \;
# find /home/bob/Programming/connectx -type f -exec sed -i 's/cx::ui::MenuItem/cx::ui::MenuItem/g' {} \;
# find /home/bob/Programming/connectx -type f -exec sed -i 's/cx::ui::TieGameResolutionDialogPresenter/cx::ui::TieGameResolutionDialogPresenter/g' {} \;
# find /home/bob/Programming/connectx -type f -exec sed -i 's/cx::ui::WidgetsFactories/cx::ui::WidgetsFactories/g' {} \;
# find /home/bob/Programming/connectx -type f -exec sed -i 's/cx::ui::WinGameResolutionDialogPresenter/cx::ui::WinGameResolutionDialogPresenter/g' {} \;
# find /home/bob/Programming/connectx -type f -exec sed -i 's/cx::ui::CreateFrameAnimationStrategy/cx::ui::CreateFrameAnimationStrategy/g' {} \;
# find /home/bob/Programming/connectx -type f -exec sed -i 's/cx::ui::MakeLabel/cx::ui::MakeLabel/g' {} \;
# find /home/bob/Programming/connectx -type f -exec sed -i 's/cx::ui::ComputeColumnFromPosition/cx::ui::ComputeColumnFromPosition/g' {} \;
# find /home/bob/Programming/connectx -type f -exec sed -i 's/cx::ui::ComputeChipPositionFromColumn/cx::ui::ComputeChipPositionFromColumn/g' {} \;
# find /home/bob/Programming/connectx -type f -exec sed -i 's/cx::ui::AnimationSpeed/cx::ui::AnimationSpeed/g' {} \;
# find /home/bob/Programming/connectx -type f -exec sed -i 's/cx::ui::FPS/cx::ui::FPS/g' {} \;
# find /home/bob/Programming/connectx -type f -exec sed -i 's/cx::ui::IColorPicker/cx::ui::IColorPicker/g' {} \;
find /home/bob/Programming/connectx -type f -exec sed -i 's/cx::ui::Feature/cx::ui::Feature/g' {} \;
