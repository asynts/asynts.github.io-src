target = [8, 9, 8, 9, 8, 9, 8]

print(target, "---")

solution = []
for j in range(1, len(target)):
  result = []
  while len(result) < len(target):
    # extend does the thing you are trying to achieve
    result.extend(target[:j])

  if result[:len(target)] == target:
    solution = target[:j]
    # find the shortest solution
    break

print(solution)

