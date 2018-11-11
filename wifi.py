from sys import stdin

def checkDist(dist, numAccessPoints, houses):
	currAccessNum = 1
	## dist *= 2
	position = houses[0] + dist

	for house in houses:
		if house > position:
			currAccessNum += 1
			position = house + dist
	
	return currAccessNum


numCase = int(input())

for n in range(0, numCase):
	numAccessPoints, numHouse = tuple(map(int, input().split()))
	houses = []

	for i in range(0, numHouse):
		houses.append(int(input()))

	houses.sort()

	low = 0
	high = houses[-1] - houses[0]

	while low < high:
		mid = (low + high)//2
		currAccessNum = checkDist(mid, numAccessPoints, houses)
		if (currAccessNum > numAccessPoints):
			low = mid + 1
		else:
			high = mid

	print('%.1f' % (high/2))
