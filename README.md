# MyBusybox

## Introduction



This project is a simaple version busybox, so far the supported commands include, ls, cp, and ln.

## Build

Just type ``make all`` the execuable file lazybox will be generated and create the commands in ``bin/`` with symbolic link.

```
make all
```

## Usage

### ls

```ls [--option] file```

options
- -l --list,    use a long listing format
- -a --all,    do not ignore entries starting with

### cp
```cp SOURCE DIRECTORY```

### ln
```ln [OPTION] TARGET LINK_NAME```
options
- s --symbolic  make symbolic links instead of hard links

