#!/bin/bash

dir=$(dirname "$0")

export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$dir/lib

# launching 
$dir/vdrpc-out
