#!/bin/sh 
MIXIM_DIR="../../../MiXiM"
WSN_DIR="../.."

./BMacTest -r 0 -u Cmdenv -n "$WSN_DIR/src;$MIXIM_DIR/src" -l "$MIXIM_DIR/src/base/miximbase" -l "$MIXIM_DIR/src/modules/miximmodules" -l "$WSN_DIR/src/WSN" omnetpp.ini default_indi.ini
scavetool scalar -p "name(*nbPacketsReceived*) and module(**.node[250].*)" results/Test2-0.sca -O scavetool.out
cat scavetool.out
rm scavetool.out
