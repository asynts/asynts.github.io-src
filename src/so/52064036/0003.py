import subprocess
from multiprocessing.pool import Pool

# mocking your code
modules = ["mod1.onnx", "mod2.onnx"]

def run(args):
  # pool.map will call run() with a tuple, deconstruct it
  idx, mod = args

  with open("output.txt", "w") as fp:
    subprocess.run(["./SOME_PROGRAM", str(idx)], stdout=fp)
    print("module", mod, "has finished")

# use the maximum number of threads by default
with Pool() as pool:
  pool.map(run, enumerate(modules))
