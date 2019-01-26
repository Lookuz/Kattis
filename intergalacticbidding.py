import sys

bidders = []
n = 0
s = 0

for line in sys.stdin:
	if n == 0 and s == 0:
		n, s = tuple(map(lambda x: int(x), line.split()))
	else:
		bidder, bid = tuple(line.split())
		bidders.append((bidder, int(bid)))
bidders.sort(key=lambda x: -x[1])

result = []
for bidder in bidders:
	if s - bidder[1] >= 0:
		s -= bidder[1]
		result.append(bidder[0])

if s == 0:
	print(len(result))
	for bidder in result:
		print(bidder)
else:
	print(0)
