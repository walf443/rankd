#!/usr/bin/python
import os
env = Environment(
    ENV = os.environ,
    CC  = 'clang',
    CXX = 'clang++',
    CPPFLAGS = ['-Wall', '-Wextra', '-g', '-O2']
)
env.Program(['rankdbench.cc', 'rankd.cc'])
