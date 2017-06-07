url-cpp
=======
![Status: Production](https://img.shields.io/badge/status-production-green.svg?style=flat)
![Team: Big Data](https://img.shields.io/badge/team-big_data-green.svg?style=flat)
![Scope: External](https://img.shields.io/badge/scope-external-green.svg?style=flat)
![Open Source: No](https://img.shields.io/badge/open_source-yes-green.svg?style=flat)
![Critical: Yes](https://img.shields.io/badge/critical-yes-red.svg?style=flat)

A C++ port of the URL parsing and sanitization provided by
[url-py](https://github.com/seomoz/url-py)

Goals
=====

1. __Performance__ -- to be faster than `url-py` for existing Python projects.
1. __Standardization__ -- of how we interpret and sanitize URLs across projects.
1. __Relaxed parsing__ -- to accept and work with the "URLs" we see in crawling, even when
    malformed.

RFC Compliance
==============
Rather than accept only RFC-compliant URLs, this library's parsing of URLs is based almost
exclusively on Python's own `urllib`. It is relatively permissive, but we've used it quite
extensively through `url-py` and have come to understand its interpretations.

Development
===========

Environment
-----------
To launch the `vagrant` image, we only need to
`vagrant up` (though you may have to provide a `--provider` flag):

```bash
vagrant up
```

With a running `vagrant` instance, you can log in and run tests:

```bash
vagrant ssh
cd /vagrant

make test
```

Running Tests
-------------
Tests are run with the top-level `Makefile`:

```bash
make test
```

PRs
===
These are not all hard-and-fast rules, but in general PRs have the following expectations:

- __pass Travis__ -- or more generally, whatever CI is used for the particular project
- __be a complete unit__ -- whether a bug fix or feature, it should appear as a complete
    unit before consideration.
- __maintain code coverage__ -- some projects may include code coverage requirements as
    part of the build as well
- __maintain the established style__ -- this means the existing style of established
    projects, the established conventions of the team for a given language on new
    projects, and the guidelines of the community of the relevant languages and
    frameworks.
- __include failing tests__ -- in the case of bugs, failing tests demonstrating the bug
    should be included as one commit, followed by a commit making the test succeed. This
    allows us to jump to a world with a bug included, and prove that our test in fact
    exercises the bug.
- __be reviewed by one or more developers__ -- not all feedback has to be accepted, but
    it should all be considered.
- __avoid 'addressed PR feedback' commits__ -- in general, PR feedback should be rebased
    back into the appropriate commits that introduced the change. In cases, where this
    is burdensome, PR feedback commits may be used but should still describe the changed
    contained therein.

PR reviews consider the design, organization, and functionality of the submitted code.

Commits
=======
Certain types of changes should be made in their own commits to improve readability. When
too many different types of changes happen simultaneous to a single commit, the purpose of
each change is muddled. By giving each commit a single logical purpose, it is implicitly
clear why changes in that commit took place.

- __updating / upgrading dependencies__ -- this is especially true for invocations like
    `bundle update` or `berks update`.
- __introducing a new dependency__ -- often preceeded by a commit updating existing
    dependencies, this should only include the changes for the new dependency.
- __refactoring__ -- these commits should preserve all the existing functionality and
    merely update how it's done.
- __utility components to be used by a new feature__ -- if introducing an auxiliary class
    in support of a subsequent commit, add this new class (and its tests) in its own
    commit.
- __config changes__ -- when adjusting configuration in isolation
- __formatting / whitespace commits__ -- when adjusting code only for stylistic purposes.

New Features
------------
Small new features (where small refers to the size and complexity of the change, not the
impact) are often introduced in a single commit. Larger features or components might be
built up piecewise, with each commit containing a single part of it (and its corresponding
tests).

Bug Fixes
---------
In general, bug fixes should come in two-commit pairs: a commit adding a failing test
demonstrating the bug, and a commit making that failing test pass.

Tagging and Versioning
======================
Whenever the version included in `setup.py` is changed (and it should be changed when
appropriate using [http://semver.org/](http://semver.org/)), a corresponding tag should
be created with the same version number (formatted `v<version>`).

```bash
git tag -a v0.1.0 -m 'Version 0.1.0

This release contains an initial working version of the `crawl` and `parse`
utilities.'

git push origin
```
