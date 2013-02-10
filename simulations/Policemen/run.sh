#!/bin/bash

MIXIM_DIR="../../../MiXiM"
PATH="${PATH}:${MIXIM_DIR}/src/base:${MIXIM_DIR}/src/modules:."

./Policemen.exe -r 0 -u Cmdenv -n ".;$MIXIM_DIR/src" -l "$MIXIM_DIR/src/base/miximbase" -l "$MIXIM_DIR/src/modules/miximmodules" omnetpp.ini boinc.ini default_indi.ini
scavetool scalar -p "name(*nbPacketsReceived*)" results/General-0.sca -O scavetool.out
cat scavetool.out
rm scavetool.out
