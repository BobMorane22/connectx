# BACKLOG

List of all tasks which should eventually be documented in the project management tool.


## (28-10-2020) Add a way to enable/disable output stream disabling per tests via a fixture.

There is no way to enable or disable, for some fixture, the ouput streams. For example, for
a base fixture:

```
class Fixture { /* ... */ };
```
it would be helpful to have a related

```
class QuietFixture : public Fixture
{
    /* Ouptput streams captured. */
    std::string GetStdOutContents() const;
    std::string GetStdErrContents() const;
};
```
Both fixtures could be used exchangably for unit testing, except for the one that require
quieting (or interraction) with the output streams, where `QuietFixture` would be needed.
This would allow not capturing streams for all unit tests when only some require this
special treatment. Capturing all streams is dangerous since it may hide assertions from
showing in the unit test executable report.


## (XX-XX-XXXX) Title

Description...
