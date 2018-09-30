import subprocess

# bad (mocking your code)
p = subprocess.Popen("echo 1 > output.txt", shell=True)
p.wait()

# better
fp = open("output.txt", "w")
p = subprocess.Popen(["echo", "1"], stdout=fp)

p.wait() # or do something else
fp.close() # remember to close file