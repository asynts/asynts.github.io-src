pos = {
  "x": 0, 
  "y": 0
}

while True:
  n = input()
  if not n:
    break

  direction,steps=n.split()
  if direction == "UP":
    pos["y"] += int(steps)
  elif direction == "DOWN":
    pos["y"] -= int(steps)
  elif direction == "LEFT":
    pos["x"] -= int(steps)
  elif direction == "RIGHT":
    pos["x"] += int(steps)

print (int(round((pos["x"]**2 + pos["y"]**2)**0.5)))
