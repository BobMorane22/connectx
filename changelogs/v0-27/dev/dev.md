# Connect X v0.27 (February 28, 2021)

## New features

In this iteration:

1. a script to generate changelogs has been added.


## New changelog generation script

Whenever a new version of Connect X comes out, new changes are documented
in changelog files. For example, for Connect X version A.B, these files
are:

```
doc
├──... (other changelogs)
└──vA-B
   ├── user
   │   └── user.md
   └── dev
       └── dev.md
```
where `user.md` corresponds to the changelog for users, and `dev.md` the
changelog for developpers. Before v0.27, all these directories and files
(and hence their contents) had to be created by hand. This meant copying
and pasting previous contents and trimming it down to retain a somewhat
consistent style as well as manual version updating.

Useless to say this was painful and error prone. With v0.27, a new script
is introduced (under `tools/script`) to automatically generate the
documentation as templated files. For example, to produce the above
changelogs, one can now call:

```
> ./tools/script/generateChangelog.sh vA.B
```
