import heapq
from sys import stdin

class MedianHeap:
	def __init__(self):
		self.maxHeap = []
		self.minHeap = []
		self.median = None

	def heapInsert(self, value):
		if self.median is None:
			self.median = value

		elif value < self.median:
			heapq.heappush(self.minHeap, -value)

		else:
			heapq.heappush(self.maxHeap, value)

		while len(self.minHeap) - len(self.maxHeap) >= 2:
			heapq.heappush(self.maxHeap, self.median)
			self.median = -heapq.heappop(self.minHeap)

		while len(self.maxHeap) - len(self.minHeap) >= 1:
			heapq.heappush(self.minHeap, -self.median)
			self.median = heapq.heappop(self.maxHeap)

	def getMedian(self):
		result = self.median
		if len(self.minHeap) == len(self.maxHeap):
			if len(self.maxHeap) >= 1:
				self.median = heapq.heappop(self.maxHeap)
			else:
				self.median = None
		else:
			if len(self.maxHeap) > len(self.minHeap):
				self.median = heapq.heappop(self.maxHeap)
			else:
				self.median = -heapq.heappop(self.minHeap)

		return result


medianHeap = MedianHeap()

for line in stdin:
	if str(line) == '#\n':
		print(medianHeap.getMedian())

	else:
		medianHeap.heapInsert(int(line))
