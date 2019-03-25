#!/bin/sh

# grabs timestamp and TSS column from tss.log, strips the first header line,
# writes to temp file, runs gg on temp file to produce heatmap, deletes temp
# file.

awk '{print $1, $6}' ../silvercheetah/tss.log | sed 1d > temp
./gg temp
rm temp
