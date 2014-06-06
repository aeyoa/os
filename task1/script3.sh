#!/bin/bash

mkdir -p ccc
ls | grep ^c | while read file; do cp "$file" ccc/"$file"_new_name; done