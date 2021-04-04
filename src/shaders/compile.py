import os

class color:
    HEADER = '\033[95m'
    OKBLUE = '\033[94m'
    OKCYAN = '\033[96m'
    OKGREEN = '\033[92m'
    WARNING = '\033[93m'
    FAIL = '\033[91m'
    ENDC = '\033[0m'
    BOLD = '\033[1m'
    UNDERLINE = '\033[4m'

path = "/home/brfh/Fractal_engine_Course_project/src/shaders/src/"
dir = os.listdir(path)
for file in dir:
	output = os.popen("glslangValidator " + path + file).read()
	# output = os.system("glslangValidator ./src/"+file)
	if output:
		print(color.WARNING + "in shader file ERROR :" + file + color.ENDC)
		print(color.FAIL +output+ color.ENDC)