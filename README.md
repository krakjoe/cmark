cmark
=====
*CommonMark API*

[![Build Status](https://travis-ci.org/krakjoe/cmark.svg?branch=develop)](https://travis-ci.org/krakjoe/cmark)
[![Build status](https://ci.appveyor.com/api/projects/status/sv9fcm89cxss38cw/branch/develop?svg=true)](https://ci.appveyor.com/project/krakjoe/cmark/branch/develop)
[![Coverage Status](https://coveralls.io/repos/github/krakjoe/cmark/badge.svg)](https://coveralls.io/github/krakjoe/cmark)

Requires
========

  * libcmark version >= 0.28

Installation
============

## From PECL

To install latest stable version

```
pecl install cmark
```

## From sources

Use `release` branch for stable version or `develop` branch.

```
phpize
./configure --with-cmark[=DIR] [ --with-cmark-coverage ]
make
make test

```

**Notice**: without the DIR argument, the `configure` script rely on `pkg-config` output  to locate the libcmark library.

## Binary packages

### Microsoft Windows

Download DLL from the [pecl page](https://pecl.php.net/package/cmark).

### Fedora / CentOS / RHEL

RPM are available in [Remi's repository](https://rpms.remirepo.net/).


Documentation
=============

Documentation can be found in the [PHP Manual](http://docs.php.net/cmark)
