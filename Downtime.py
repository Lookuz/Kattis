from sys import stdin
from collections import deque
import math

jobs = deque()
count, maxJobs = tuple(map(int, input().split()))
maxSize = 0

for i in range(0, count):
	nextJob = int(input())
	while jobs and (jobs[0] <= nextJob - 1000):
		jobs.popleft()
	jobs.append(nextJob)
	maxSize = len(jobs) if len(jobs) > maxSize else maxSize

maxSize = max(1, math.ceil(maxSize/maxJobs))
print(maxSize)
