import io
import os
import os.path
import re
import csv
import time

filename = "log_" + time.strftime("%Y-%m-%d-%H") + "h.csv"
output = open("logs/" + filename, "w+")
if os.path.isfile("logs/current.csv"):
    os.unlink("logs/current.csv")
os.symlink(filename, "logs/current.csv")

output.write("time,temp,humidity,pressure,bmp180temp,si1132_visible,si1132_ir,si1132_uv,si7021_temp,si7021_humidity\n")

def write_line(fields):
    s = str(time.time())
    for key in ["temp", "humidity", "pressure", "bmp180temp", "si1132_visible", "si1132_ir", "si1132_uv", "si7021_temp", "si7021_humidity"]:
        s += "," + str(fields[key])
    output.write(s + "\n")
    output.flush()

with open("/dev/ttyUSB0") as tty:
    for line in tty:
        if re.search("^\s*$", line) == None:
            fields = dict()
            for field in line.split(","):
                name = field.split(":")[0].strip()
                value = float(field.split(":")[1])
                fields[name] = value
            write_line(fields)
