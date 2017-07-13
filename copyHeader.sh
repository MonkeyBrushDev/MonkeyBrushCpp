#!/bin/bash

for i in `find -regex '.*/.*\.\(cpp\|hpp\)$'
`
do
  echo $i
  if ! grep -q Copyright $i
  then
    cat _license_.txt $i >$i.new && mv $i.new $i
  fi
done
