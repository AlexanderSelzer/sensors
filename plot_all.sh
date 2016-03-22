#!/bin/sh

python plot.py logs/current.csv temp &
python plot.py logs/current.csv humidity &
python plot.py logs/current.csv pressure &
python plot.py logs/current.csv si7021_humidity &
python plot.py logs/current.csv si1132_visible &
python plot.py logs/current.csv si1132_ir &
wait
