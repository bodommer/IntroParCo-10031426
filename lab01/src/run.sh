#!/bin/bash

gcc Array.c -o Array.run

gcc Scan.c -o Scan.run

./Array.run > ARRAY_RES.out
 
./Scan.run > SCAN_RES.out
