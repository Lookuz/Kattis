from sys import stdin

start = True
while True:
	x, y = tuple(map(int, input().split()))

	if x == 0 and y == 0:
		break
	
	if start:
		start = False
	else:
		print('')

	stringList = []
	for i in range(0, x):
		stringList.append(str(input()))

	stringList = [*zip(*stringList)]
	for item in stringList:
		stringList = map(lambda s: ''.join(s), stringList)
	stringList = sorted(stringList, key= lambda s: s.lower())
	stringList = [*zip(*stringList)]
	for item in stringList:
		stringList = map(lambda s: ''.join(s), stringList)
	for string in stringList:
		print(string)
		
