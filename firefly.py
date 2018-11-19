from sys import stdin
import sys

numObs, height = tuple(map(int, input().split()))
high = [0 for i in range(0, height)]
low = [0 for i in range(0, height)]

for i in range(0, numObs):
	obsHeight = int(input())
	if i%2 == 0:
		high[obsHeight - 1] += 1
	else:
		low[height - obsHeight] += 1

total = 0
for i in range(height - 1, -1, -1):
	total += high[i]
	high[i] = total

total = 0
for i in range(0, height):
	total += low[i]
	low[i] = total

best = sys.maxsize
count = 0
for i in range(0, height):
	if (high[i] + low[i]) < best:
		best = high[i] + low[i]
		count = 1
	elif (high[i] + low[i]) == best:
		count += 1

print('{0} {1}'.format(best, count))
