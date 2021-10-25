#!/bin/bash
cat $1 | awk '{str=$1;for(j=NF; j>1;j--) {str=$j" "str};print str}' 
