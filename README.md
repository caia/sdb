<h1 align="center">SDB: Simple Database</h1>

This repository contains the code made upon the guidance of the [Let's Build a
Simple Database][simple-db-tuto] tutorial. The project aims to be a
overly-simplified version of [SQLite][sqlite], to illustrate the basics of a
[database engine][db-eng].

[simple-db-tuto]: https://cstack.github.io/db_tutorial
[sqlite]: https://www.sqlite.org/index.html
[db-eng]: https://en.wikipedia.org/wiki/Database_engine


## Why?

- Databases are such an important topic, but we (computer science students, IT
  professionals etc) often doesn't understand what happens under the hood (like
  in most everyday technologies). This is an attempt to learn and understand a
  bit more.

- C is a wonderful language which I unfortunately  do not exercise that much,
  since much of my work at college and work uses high level languages like
  Python, Java and JavaScript. This is a way to keep some knowledge fresh in my
  head.


## Build

To compile it, use `make`:

```sh
$ cd simple-db && make
```


## Usage

Just execute the binary builded by `make`. You should see the REPL:

```
sdb >
```
