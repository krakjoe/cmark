#!/bin/sh

for i in src/*.c src/*.h
do
  k=$(basename $i)
  grep -q $k package.xml || echo missing $k
done
for i in $(find tests -type f)
do
  k=${i#tests/}
  grep -q $k package.xml || echo missing $k
done

