# Lenscraft an Open Source Photobooth

## Code status
[![codecov](https://codecov.io/gh/farzonl/lenscraft/branch/master/graph/badge.svg)](https://codecov.io/gh/farzonl/lenscraft)
[![Build Status](https://travis-ci.com/farzonl/lenscraft.svg?branch=master)](https://travis-ci.com/farzonl/lenscraft)
[![Total alerts](https://img.shields.io/lgtm/alerts/g/farzonl/lenscraft.svg?logo=lgtm&logoWidth=18)](https://lgtm.com/projects/g/farzonl/lenscraft/alerts/)
[![Language grade: C/C++](https://img.shields.io/lgtm/grade/cpp/g/farzonl/lenscraft.svg?logo=lgtm&logoWidth=18)](https://lgtm.com/projects/g/farzonl/lenscraft/context:cpp)

## Demo
[![Photo booth](https://raw.githubusercontent.com/farzonl/lenscraft/master/lenscraftLoop.gif)](https://youtu.be/sWvmMe_b8Ss)

## Dependencies
- opencv2
- opengl 2.1
- glfw 2.x
- glm
- glew
- pkg-config

### Setup For Mac & Linux 
pkg-config & glew are required before running make. The makefile will trigger a script
to pull down all required dependencies.

## how to build?
```
make
```