# ffmpeg.exe -f gdigrab -i title="ld32" -framerate 5 -vcodec libx264 -crf 18 output.mp4

from subprocess import call, Popen, DEVNULL
from time import time, sleep

command2 = "ffmpeg.exe -f gdigrab -i title=\"ld32\" -framerate 5 -vcodec libx264 -crf 18 ./timelapse/{}.mp4".format(int(time()))
command1 = "ld32.exe"

print(command1)
Popen([command1])
sleep(0.1)
print(command2)
Popen(command2, stdout=DEVNULL, stderr=DEVNULL)
