#!/bin/sh 
DIRECTORY="build"
if [ -d "$DIRECTORY" ]
then
    echo "$DIRECTORY exists on your filesystem."
else
  mkdir $DIRECTORY
fi
cd $DIRECTORY
cmake ../
make VERBOSE=1
