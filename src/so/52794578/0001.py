import os

target = "./target/"
trans = str.maketrans("", "", "0123456789")

for name in os.listdir(target):
  os.renames(
      os.path.join(target, name),
      os.path.join(target, name.translate(trans)) )

