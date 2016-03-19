import io
import re
import csv
import time

output = open("logs/log_" + time.strftime("%Y-%m-%d-%H") + "h.csv", "w+")

output.write("time,temp,humidity,pressure,bmp180temp,si1132_visible,si1132_ir,si1132_uv,si7021_temp,si7021_humidity\n")

def write_line(fields):
	s = str(time.time())
	for key in ["temp", "humidity", "pressure", "bmp180temp", "si1132_visible", "si1132_ir", "si1132_uv", "si7021_temp", "si7021_humidity"]:
		s += "," + str(fields[key])
	output.write(s + "\n")


with open("/dev/ttyUSB0") as tty:
	for line in tty:
		if re.search("^\s*$", line) == None:
			fields = dict()
			for field in line.split(","):
				name = field.split(":")[0].strip()
				value = float(field.split(":")[1])
				fields[name] = value
			write_line(fields)
