currMax = 0
totalMax = 0
numArr = []

numItems, price = tuple(map(int, input().split()))

numArr = list(map(int, input().split()))

for i in numArr:

	currMax += (i - price)

	if currMax < 0:
		currMax = 0

	if currMax > totalMax:
		totalMax = currMax

print(totalMax)
