#!/usr/bin/python
import os
env = Environment(
    ENV = os.environ,
    CC  = 'clang',
    CXX = 'clang++',
    CPPFLAGS = ['-Wall', '-Wextra', '-g'],
    CXXFLAGS = ['-std=c++0x']
)
env.Program(['rankdbench.cc', 'rankd.cc'])
env.Program(['test_rankd.cc', 'rankd.cc'])

