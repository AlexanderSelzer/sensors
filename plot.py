import matplotlib
matplotlib.use('Agg')

import matplotlib.pyplot as plt
import re
import datetime
import numpy as np
import csv
import sys

if len(sys.argv) < 2:
	print("usage: plot.py file column")
	exit(0)

filename = sys.argv[1]
column = sys.argv[2]

x = []
y = []

with open(filename, "r") as csvfile:
	reader = csv.DictReader(csvfile)
	for row in reader:
		x.append(datetime.datetime.fromtimestamp(float(row["time"])))
		y.append(float(row[column]))
		

plt.plot(x, y, label=column)
plt.legend()
plt.savefig("graphs/" + column + ".png")
