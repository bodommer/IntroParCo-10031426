#!/bin/bash

gcc ../src/Array.c -o ../src/Array.run

gcc ../src/Scan.c -o ../src/Scan.run

../src/Array.run > ../experiments/ARRAY_RES.out
 
../src/Scan.run > ../experiments/SCAN_RES.out
