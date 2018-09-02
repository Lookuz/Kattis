import sys

def main():
	maxLen = 0
	itemList = [ [] for i in range(26)]

	for line in sys.stdin:
		if line == '\n':
			for i in range(26):
				itemList[i] = sorted(itemList[i])
				for x in itemList[i]:
					spaces = maxLen - len(x)
					print(' '* spaces + x[::-1])
			print()

			maxLen = 0
			itemList = [ [] for i in range(26)]
			continue
	
		else:
			item = str(line.strip())
			item = item[::-1]
			lastChar = item[0]
			itemList[ord(lastChar) - ord('a')].append(item)
			maxLen = len(item) if (len(item) > maxLen) else maxLen
	
	for i in range(26):
		itemList[i] = sorted(itemList[i])
		for x in itemList[i]:
			spaces = maxLen - len(x)
			print(' ' * spaces + x[::-1])

main()
