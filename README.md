# UR5e robot module for [mc_rtc](https://jrl-umi3218.github.io/mc_rtc/)

This package contains a software representation, or a robot module, of [UR5e](https://www.universal-robots.com/products/ur5-robot/) robot platform. This robot module is used by [mc_rtc](https://jrl-umi3218.github.io/mc_rtc/) framework to realize control of Aliengo robot in simulation or in experiments with real platform.

## Required dependencies

 - [mc_rtc](https://jrl-umi3218.github.io/mc_rtc/)
 - [mc_ur5e_description](https://github.com/s-kidera/mc_rtc_project/tree/master/UR5e/mc_ur5e_description)

## Build instructions

```
$ cd src
$ git clone https://github.com/@MC_UR5E_REPOSITORY@
$ cd @MC_UR5E_PATH@
$ mkdir build
$ cd build
$ cmake ..
$ make
$ sudo make install
```
