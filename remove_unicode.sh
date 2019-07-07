#!/bin/bash

tr '\240' ' ' < $1 > new.cpp
mv -f new.cpp $1
tr '\302' ' ' < $1 > new.cpp
mv -f new.cpp $1

