#!/usr/bin/env python
# coding=utf-8
import ctypes

libcaller = ctypes.cdll.LoadLibrary
lib = libcaller("./libpycall.so")
lib.hello()
print("****finish****")
