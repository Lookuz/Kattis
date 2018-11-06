from sys import stdin
from collections import deque

numCases = int(input())

for i in range(0, numCases):
	numFlakes = int(input())

	package = deque()
	currentSet = set()
	maxLen = 0
	for i in range(0, numFlakes):
		flakeNo = int(input())
		if flakeNo not in currentSet:
			currentSet.add(flakeNo)
			package.append(flakeNo)
		else:
			maxLen = len(package) if (len(package) > maxLen) else maxLen
			while True:
				left = package.popleft()
				if left != flakeNo:
					currentSet.remove(left)
				else:
					package.append(flakeNo)
					break
	
	maxLen = len(package) if (len(package) > maxLen) else maxLen
	print(maxLen)
