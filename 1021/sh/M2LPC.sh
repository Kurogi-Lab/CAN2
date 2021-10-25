#!/bin/bash
cat $1 | awk '{str=$NF;for(j=1; j<NF;j++) {str=str" "$j};print str}' 
#M=[M1,M2,...,Mk,M0],LPC=[M0,M1,...,Mk]
