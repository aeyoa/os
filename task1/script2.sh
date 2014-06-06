#!/bin/bash

mkdir -p bbb
ls | grep ^b | while read file; do mv "$file" bbb; done
