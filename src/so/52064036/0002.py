from multiprocessing.pool import Pool

# mocking your code
modules = ["mod1.onnx", "mod2.onnx"]

def run(module):
  print("running", module)

# use the maximum number of threads by default
with Pool() as pool:
  pool.map(run, modules)