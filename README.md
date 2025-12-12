# Disk_Benchmark
Finding the write speed of my newly bought usb stick.

# Method1:
Uses the fread and fwrite functions in C to write a large file to the usb stick and read it back, measuring the time taken for each operation.

#Method2:
Uses the timeout command with a cat and find the size of the file to calculate the write speed.
