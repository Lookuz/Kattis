from sys import stdin


class Node:
	def __init__(self, id, name):
		self.id = id
		self.name = name
		self.size = 1

	def join(self, other):
		self.size += other.size


numRounds = int(input())

for i in range(0, numRounds):
	count = int(input())
	nextId = 0

	predecessor = list(range(count * 2))
	sizes = [1] * (count * 2)
	indexMap = {}

	for j in range(count):
		first, second = tuple(input().split())

		if first not in indexMap:
			indexMap[first] = nextId
			nextId += 1
		if second not in indexMap:
			indexMap[second] = nextId
			nextId += 1

		firstParent = predecessor[indexMap.get(first)]
		secondParent = predecessor[indexMap.get(second)]

		while firstParent != predecessor[firstParent]:
			predecessor[firstParent] = predecessor[predecessor[firstParent]]
			firstParent = predecessor[firstParent]
		while secondParent != predecessor[secondParent]:
			predecessor[secondParent] = predecessor[predecessor[secondParent]]
			secondParent = predecessor[secondParent]

		if firstParent != secondParent:
			if sizes[firstParent] > sizes[secondParent]:
				sizes[firstParent] += sizes[secondParent]
				predecessor[secondParent] = firstParent
				print(sizes[firstParent])
			else:
				sizes[secondParent] += sizes[firstParent]
				predecessor[firstParent] = secondParent
				print(sizes[secondParent])
		else:
			print(sizes[firstParent])
