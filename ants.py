from sys import stdin

numRounds = int(input())

for i in range(0, numRounds):
	l, n = tuple(map(int, input().split()))
	ants = []
	while len(ants) < n:
		ants += map(int, input().split())

	mid = round(l/2)
	worst = 0
	best = l
	bestAnt = None
	for ant in ants:
		if abs(ant - mid) < best:
			best = abs(ant - mid)
			bestAnt = ant
		longer = max(abs(l - ant), ant)
		if longer > worst:
			worst = longer

	if n > 0:
		best = min(abs(l - bestAnt), bestAnt)
		print('{0} {1}'.format(best, worst))

