# The Abstract Widgets Toolkit

@brief
     Abstract UI toolkit used by Connect X to instantiate and configure common widgets, such
     as button, labels, windows, and more.

## Contents
1. [Introduction](#introduction)
2. [Motivation](#motivation)
3. [Architecture](#architecture)
4. [Specific framework elements](#specific-framework-elements)
5. [Hello World](#hello-world)
6. [References](#references)
7. [TODOs](#todos)


<a name="introduction"></a>
## 1. Introduction
In this document, the Abstract Widgets Toolkit (AWT) is presented in details. This toolkit
is used by Connect X for implementing user interfaces (UI).


<a name="motivation"></a>
## 2. Motivation
While Gtkmm is a GUI library which is fun to work with, its API is pretty unstable. From
one version to another, majors API changes frequently occur and make maintenance a pain.
Much effort is put into the UI code, which is later broken by Gtkmm updates. The major
issue is that the UI code depends directly on Gtkmm. When its API changes, UI code maintenance 
across the whole codebase is needed to restore functionnalities were broken by API changes.
This can result in new bugs that can creep in, unnoticed.

Since Gtkmm 3 is now deprecated and that Gtkmm 4 will soon be the new standard on Ubuntu LTS
distros (and many others), a migration is needed.[[1]](#gtkorg) I have decided to take
advantage of this. The migration will not happen by simple "call replacements", but rather
I will add an indirection layer between the views and the Gtkmm related code, freeing myself
from it at the same time. With this approach, UI code code changes should be limited to a
minimum when migrating to a new Gtkmm version and much less risky. Finally, moving to another
framework should be easier, if that ever becomes a need.


<a name="architecture"></a>
## 3. Architecture

### 3.1. Description
To achieve this, the *Abstract Factory* design pattern is going to be used. From the book
*Design Patterns : elements of reusable object-oriented software*:

> Provide an interface for creating familities of related or dependant
> objects without specifying their concrete class.[[2]](#gof)

The root idea is that basic UI elements (widgets mostly), are first going to be abstracted away
such that no Gtkmm code leaks into the Connect X code. Logic related to Gtkmm should be completely
contained behind the widget abstractions. A factory will then be made available to create
these abstractions so that the Connect X code can still use the widgets, but only through the
abstractions. Since the factory is abstract and only deals with abstractions, it can be made
into several concrete instances, each providing a different backend through the same widget
abstractions. For example, one instance could use Gtkmm 3 as the backend while another instance
could use Gtkmm 4 (or any other toolkit, like Qt for instance). This will have no effect on the
Connect X code. This is illustrated in [Figure 1](#arch-high-level).

With this approach, migrating from one widget toolkit to another will come down to adding new
widget implementations using this toolkit and creating a new instance of the abstract factory
supporting these implementations. As far as Connect X is concerned, nothing will have changed.
In my case, this will greatly simplify the Gtkmm 4 porting.

<a name="arch-high-level">**Figure 1 :**</a> The abstract factory architecture (high level).
```plantuml
skinparam linetype ortho

object "Connect X" as cx

package "cx::cmn::ui" as abstraction {

    rectangle " " as abstractions {
        interface "IWidget" as iWidget
        interface "IButton" as iBtn
        interface "ILabel"  as iLbl

        interface "IAbstractWidgetsFactory" as iFty
    }

package "gtkmm3" as implementation {

    class "Button"                 as gtkmm3Btn
    class "Label"                  as gtkmm3Lbl
    class "AbstractWidgetsFactory" as gtkmm3Fty

} /' gtkmm3 '/

} /' cx::cmn::ui '/

iWidget <|-down- iBtn
iWidget <|-down- iLbl
iBtn    <|-down- gtkmm3Btn
iLbl    <|-down- gtkmm3Lbl

iFty    <|-down- gtkmm3Fty

gtkmm3Fty -[#blue]-> gtkmm3Btn : "<color:blue>creates"
gtkmm3Fty -[#blue]-> gtkmm3Lbl : "<color:blue>creates"

cx -[#blue]right-> abstractions : "<color:blue>depends on"
cx -[#blue]down-> iFty : "<color:blue>uses"
```

In [Figure 1](#arch-high-level), a first class hierarchy is created for the individual widgets.
All widgets implement the `cx::cmn::ui::IWidget` interface and specialize it to their own needs.
Only the final implementation is GUI toolkit specific. This final implementation is hidden behind
an interface (for example: `cx::cmn::ui::IButton` for buttons) which will be what Connect X is
going to be using, as a client of the abstract factory.

As mentionned before, creating the concrete widgets will be the responsibility of the abstract
factory, which will have an implementation for all supported toolkits. The abstracty factory
will select the needed implementation at construction time and from there, will create the
widgets using the appropriate implementation, while only making the abstract interfaces
available to Connect X.


### 3.2. Layering

[Figure 2](#arch-layering) illustrates the general layering allowing any application using
the AWT to decouple itself from the underlying GUI toolkit.

<a name="arch-layering">**Figure 2 :**</a> Generic layering using the `cxcmnui` library
```plantuml
component "Application"      as app
component "cxcmnui"          as cxcmnui
component "implementation A" as impla
component "implementation B" as implb
component "GUI toolkit A"    as toolkita
component "GUI toolkit B"    as toolkitb

app -d-> cxcmnui : "depends on"

impla -u-> cxcmnui
impla -d-> toolkita

implb -u-> cxcmnui
implb -d-> toolkitb
```

The dependance on the toolkit is inverted by the `cxcmnui` component, which only exposes
abstractions and on which both the client application and the toolkit implementation depend.


<a name="specific-framework-elements"></a>
## 4. Specific framework elements
The main goal of the AWT is not to expose a complete GUI toolkit API, but rather to free ourselves
from the GUI toolkits. Only the necessary elements are exposed and simplicity of use is the main
criterion.


### 4.1. Widgets
The AWT exposes all of its widgets through inferfaces. For example, the call for creating a
button is:

\snippet{trimleft} doxygen/awt/helloworld.cpp AWT - Create button

where the type `cx::cmn::ui::IButton` is UI toolkit agnostic, as shown in
[Figure 1](#arch-high-level). It should only know about `std` and Connect X types, nothing
more. Like in most GUI toolkits, the widgets get more and more specialized through inheritance.

For reasons that will become clear in the next section, all specific widget implementations
should also publicly inherit from the toolkit's interface for that widget. For example,
the button implementation for the Gtkmm toolkit would look something like:

```cpp
class Button : public cx::cmn::ui::IButton,
               public Gtk::Button                                    
```

but only the `cx::cmn::ui::IButton` interface is exposed through the factory and hence is available
in the calling code. In short, this is because for some applications (such as layouts), casting
to the toolkit's specific type is necessary in the implementation. More on this later.

Notice that in [Figure 1](#arch-high-level), the `cx::cmn::ui::IButton` interface inherits from
the `cx::cmn::ui::IWidget` interface. Both of these are interfaces, which means there is no code
inheritance between both interfaces. This is the price to pay to provide abstractions.  Still,
repeating the widget implementation code in every child class is not a good choice: it is pure
code duplication.

To avoid this issue (partially), a technique called *delegation* will be used:

> Delegation is an extreme example of object composition. It shows that you
> can always replace inheritance with object composition as a mechanism for
> code reuse.[[2]](#gof)

More concretely:

> In delegation, *two* objects are involved in handling a request: a receiving
> object delegates operations to its **delegate**. This is analogous to
> subclasses deferring requests to parent classes.[[2]](#gof)

In the case of a button instance (i.e. implementing the `cx::cmn::ui::IButton` interface), all
`cx::cmn::ui::IWidget` calls will be handled by a widget delegate, which will be injected at
construction, as shown in [Figure 3](#widget-delegation).

<a name="widget-delegation">**Figure 3 :**</a> Delegation of the widget implementation.
```plantuml
skinparam linetype ortho

package Gtk
{
    abstract "Widget" as gtkwidget 
    class    "Button" as gtkbutton

    gtkwidget <|- gtkbutton
}

package "cx::cmn::ui" as ui
{
    interface "IWidget" as iwidget
    interface "IButton" as ibutton
    
    iwidget <|- ibutton
    
    package gtkmm3
    {
        class "WidgetDelegate" as gdelegate
        class "Button"         as gbutton
    
        ibutton    <|-   gbutton
        gbutton    *-    gdelegate
        iwidget    <|-d- gdelegate
        gdelegate  *-d-  gtkwidget
        gtkbutton <|-u-  gbutton
    }
}
```

The widget delegate implements the `cx::cmn::ui::IWidget` interface (which will be used for
delegation) and has a reference to the underlying Gtkmm widget, so that it can operate on it.

This solution is not as ideal as standard inheritance: it requires lots of repetitive boiler plate
code and complexifies the design. However, I think users of the abstract factory will benefit
from it since only pure, stable abstractions will be available to them. From their point of
view, this will hide a lot of complexity.


### 4.2. Layouts
Layouts are a type of UI element that is not directly visible by the user of the software. Their
task is to spatially arrange widgets inside a window. In Gtkmm, they are known as containers,
in Qt, they are known as layouts. In this abstract factory, they will be known as layouts, since
I think the word "layout" better represent their responsibility.

One important detail about layout is that they *are* widgets. In other words, they implement the
`cx::cmn::ui::IWidget` interface. Another important detail is that their implementation needs to
know about the underlying UI toolkit for the widgets they are manipulating.

Indeed, the `cx::cmn::ui::ILayout::Register` implementations cannot add the button because all they
know about is the `cx::cmn::ui::IWidget` interface, which is Gtkmm agnostic. This is where we, as
implementers of the abstract factory, will use our private knowledge that in this case, the widget
to register in the layout also inherits from `Gtk::Widget` (see previous section). Because of this,
we can use casting to solve the problem. Sadly, there is now way around this casting. If everything
is built through the factory, however, it will always be safe.


### 4.3. Windows
Windows also inherit from the `cx::cmn::ui::IWidget` interface. Windows can do two things:

 1. register a layout;
 2. show themselves (i.e. become visible to the user).

In the case of windows, only one layout can be registered. It holds all the window's child widgets.
Note that this layout, however, can register sublayouts.


### 4.4. Connecting to signals
Signal handling is an important part of widget interactions. It is through these that user can
interact with the system. Because the Gtkmm signaling technology is so nice, it is the design
which will be used by the AWT as well. What I like about the Gtkmm signaling system:

 1. It is strong typed: If you fail to provide the right slot signature for your signal,
    you will know at compile time.
 2. It is pure C++. There is no "meta" process involved at compile time to make it work, as is
    the case with Qt.

Two interfaces drive the signaling process: `cx::cmn::ui::IConnection` and `cx::cmn::ui::ISignal`.
The `cx::cmn::ui::IConnection` interface is basically a handle on a connection between a slot and
a signal. The `cx::cmn::ui::IConnection` instance is used to connect and disconnect a signal to
a slot.

The `cx::cmn::ui::ISignal::Connect` method is provided a slot which has `ReturnType` as its
return type and `Arguments...` as its arguments' types. The parameter pack makes it possible for
a slot to have any given number of arguments of any desired type. This method is the core of the
strong typing.

For any signal you want to expose, you must implement the `cx::cmn::ui::ISignal` interface and
provide the return and argument types for the corresponding slot. The
`cx::cmn::ui::ISignal::Connect` method returns a connection instance, which you can reference
for later (in case you need to disconnect the slot, at some later point in time).

This is very close to what Gtkmm does. In [this example](#hello-world), the
`cx::cmn::ui::IButton::OnClicked` method returns the signal, on which
`cx::cmn::ui::ISignal::Connect` is immediately called. The provided slot shows that the signal
returns nothing and takes no parameter. This is indeed what is exposed in the
`cx::cmn::ui::IButton` interface.

Even though the signaling process is very similar to what Gtkmm offers, care should be taken when
exposing a new signal. Other toolkit should be looked at to make sure the slot return and
arguments type are generic enough to be implementable in other toolkits.


<a name="hello-world"></a>
## 5. Hello World

Here is a complete example using the AWT. The program shows a button witht the "Hello World!"
label. When clicked, the button writes "Hello World!" and a newline to the console. The underlying
GUI toolkit used is Gtkmm3.

\snippet doxygen/awt/helloworld.cpp AWT - Hello World


<a name="references"></a>
## 6. References

<a name="gtkorg">[1]</a>
  “Gtk: Migrating from GTK 3.x to GTK 4” Gtk.org, 2024.
  https://docs.gtk.org/gtk4/migrating-3to4.html#title (accessed Aug. 18, 2024).

<a name="gof">[2]</a>
  E. Gamma, R. Helm, R. Johnson, and J. Vlissides, *Design Patterns : elements
  of reusable object-oriented software*. Boston: Addison-Wesley, 1994.


<a name="todos"></a>
## 7. TODOs

\todo Privatise all comments in implementations.
\todo Fix all Doxygen errors.
