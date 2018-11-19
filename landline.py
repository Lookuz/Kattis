from sys import stdin
import sys
import heapq

safeEdges = []
unsafeEdges = []
totalCost = 0

def find(x):
	while x != parent[x]:
		parent[x] = parent[parent[x]]
		x = parent[x]
	
	return x

def merge(x, y):
	x = find(x)
	y = find(y)
	if x == y:
		return False
	else:
		parent[x] = y
		return True

numBuildings, numEdges, numUnsafe = tuple(map(int, input().split()))
parent = [i for i in range(0, numBuildings)]
isUnsafe = [False for i in range(0, numBuildings)]
if numEdges < numBuildings - 1:
	if numBuildings == 1:
		print(0)
	else:
		print('impossible')
		sys.exit()

if numUnsafe > 0:
	unsafe = map(int, input().split())
	for item in unsafe:
		isUnsafe[item - 1] = True

for i in range(0, numEdges):
	left, right, cost =tuple(map(int, input().split()))
	left = left - 1
	right = right- 1
	if isUnsafe[left] ^ isUnsafe[right]:
		heapq.heappush(unsafeEdges, (cost, left, right))
	elif ((not isUnsafe[left]) and (not isUnsafe[right])) or (numBuildings == numUnsafe):
		heapq.heappush(safeEdges, (cost, left, right))

while len(safeEdges) > 0:
	cost, left, right = heapq.heappop(safeEdges)
	if merge(left, right):
		totalCost += cost

firstSafe = -1
for i in range(0, numBuildings):
	if not isUnsafe[i]:
		firstSafe = i

if firstSafe != -1:
	for i in range(0, numBuildings):
		if (not isUnsafe[i]) and find(firstSafe) != find(i):
			print('impossible')
			sys.exit()

while len(unsafeEdges) > 0:
	cost, left, right = heapq.heappop(unsafeEdges)
	if merge(left, right):
		totalCost += cost

for i in range (0, numBuildings):
	if find(0) != find(i):
		print('impossible')
		break
	elif i == numBuildings - 1:
		print(totalCost)
