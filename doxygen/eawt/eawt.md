# The Extenting the Abstract Widgets Toolkit

@brief
     Guide for extending the Abstract Widgets Toolkit (AWT).

## Contents
1. [Introduction](#introduction)
2. [Motivation](#motivation)
3. [Extending Common Widgets](#extending)
4. [Architecture](#architecture)


<a name="introduction"></a>
## 1. Introduction
This document explains how the [Abstract Widgets Toolkit](../awt/awt.md) (AWT) can be extended
to meet application specific needs.


<a name="motivation"></a>
## 2. Motivation
The AWT is nice for using common widgets, such as buttons, labels and windows (to name a few).
When applications get more involved, they sometimes need widgets that are more specialized.
At this point, the AWT no longer does the job.

The AWT philosophy is to decouple these very different usages:

 1. Using common widgets.
 2. Using application specific widgets.

The AWT takes care of the common widgets, while application developpers take care the their
application specific widgets. This is no different than any other GUI toolkit. What is different,
however, is how this specialization is achieved. The Connect X specific extension of the AWT
is known as the Extended Abstract Widget Toolkit (EAWT).


<a name="extending"></a>
## 3. Extending Common Widgets

There are three ways in which GUI toolkits typically let us create specialized widgets:

 1. **Composition:** Common widgets (buttons, labels, etc) are bundled together
    in a layout. The way the widgets are arranged inside the layout makes sense
    for the specific application.
 2. **Inheritance:** Common widgets are specialized through inheritance. This
    is usually the most common form of widget extension.
 3. **Custom widgets:** Sometimes, the type of widget needed by the application
    simply does not exist in the toolkit, not even in a primitive and extensible
    form. GUI tookits often offer a mechanism to draw custom widgets from scratch.
    In Connect X, this is the case with the game board.

In the AWT, all specialization forms are available, except for inheritance. While this
specialization form is usually very popular, we have decided to stay away from it in
the relation between the AWT and the EAWT. This is because inheritance needs to
know too much about the internal details of its parent. Remember that the AWT is
only usable through pure interfaces, so publishing anything more is counter productive,
especially for an abstraction that aims at being GUI toolkit independant. Moreover,
in practice, direct inheritance to the AWT toolkit was never really a need.


<a name="architecture"></a>
## 4. Architecture
As illustrated in [Figure 1](#arch-high-level), the EAWT is a client of the AWT. The
`cx::ui::gtkmm3::AbstractConnectXWidgetsFactory` class has a reference to the
`cx::cmn::ui::IAbstractWidgetsFactory` interface. This makes it possible to use this factory
to create common widgets. Because of this, composition of common widgets to create new,
application specific ones, is easy. Furthermore, the `cx::ui::gtkmm3::AbstractConnectXWidgetsFactory`
class automatically benefits from any maintenance done on the AWT, with minimal change. This is
because the only dependence it has is on the AWT interfaces.  One example of a composed widget
is the `cx::ui::gtkmm3::MainWindow`.

<a name="arch-high-level">**Figure 1 :**</a> The extended abstract factory architecture (high level).
```plantuml
skinparam linetype ortho

package cx::cmn::ui {

    interface "IAbstractWidgetsFactory" as iFty
    interface "IWidget"                 as iWidget
    interface "IWindow"                 as iWindow

    iWidget <|-- iWindow

    iFty -[hidden]d-> iWidget
    iFty -[hidden]d-> iWindow

} /' cx::cmn::ui '/

package cx::ui {

    interface "IAbstractConnectXWidgetsFactory" as iEfty
    interface "IAnimatedBoard"                  as iBoard

    iWidget  <|-- iBoard

package gtkmm3 as implementation {

    class "AbstractConnectXWidgetsFactory" as fty
    class "MainWindow"                     as mainWindow
    class "AnimatedBoard"                  as board

    iEfty   <|-- fty
    iBoard  <|-- board
    iWindow <|-- mainWindow

    fty *-- iFty

    fty --> board      : "Creates"
    fty --> mainWindow : "Creates"

} /' gtkmm3 '/

    iEfty -[hidden]d-> iBoard
    iEfty -[hidden]d-> implementation

} /' cx::ui '/

cx::cmn::ui --[hidden]u-> cx::ui

```

The abstract factory associated with the EAWT also has access to Gtkmm. This makes it possible
for the factory to create its own custom widgets using `Gtk::DrawingArea`. One example of this
in Connect X is the game board (`cx::ui::gtkmm3::AnimatedBoard`). There was no such widget
in the Gtkmm library and it was too closely related to Connect X to land in the AWT. This is
why it is made available in the EAWT.
