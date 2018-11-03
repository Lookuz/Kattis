from sys import stdin


numHouses, numRounds = tuple(map(int, input().split()))
parent = [i for i in range(0, numHouses)]

for i in range(0, numRounds):
	first, second = tuple(map(int, input().split()))
	first = first - 1
	second = second - 1

	while parent[first] != first:
		parent[first] = parent[parent[first]]
		first = parent[first]
	while parent[second] != second:
		parent[second] = parent[parent[second]]
		second = parent[second]

	if first != second:
		if first < second:
			parent[second] = first
		else:
			parent[first] = second

connected = True
for i in range(0, numHouses):
	root = i
	while root != parent[root]:
		root = parent[root]
	if root != 0:
		print(i + 1)
		connected = False

if connected:
	print('Connected')
