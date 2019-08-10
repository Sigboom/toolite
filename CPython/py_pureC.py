#!/usr/bin/env python
# coding=utf-8
import ctypes

libcaller = ctypes.cdll.LoadLibrary
caller = libcaller("libpureC.so")
caller.hello()
print("*****fiish*****")
