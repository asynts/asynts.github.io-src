import subprocess

# output: no such file or directory 'echo hello'
subprocess.run("echo hello")

# output: hello
subprocess.run(["echo", "hello"])

# output: hello
subprocess.run("echo hello", shell=True)

# don't take user input when using shell=True!
# output: \n malicious code
user_input = "; echo 'malicious code' #"
subprocess.run("echo " + user_input, shell=True)
