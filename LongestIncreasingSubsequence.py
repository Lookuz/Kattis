def ceilSearch(numArr, temp, length, key):
	low = 1
	high = length

	while low <= high:
		mid = (low + high)//2
		if numArr[temp[mid]] < numArr[key]:
			low = mid + 1
		else:
			high = mid - 1

	return low

def longestLis():
	while True:
		try:
			numItems = int(input())
			numArr = list(map(int, input().split()))
			tempArr = [0] * (numItems + 1)
			predecessorArr = [-1] * numItems
			length = 0

			for i in range(0, len(numArr)):
				newLength = ceilSearch(numArr, tempArr, length, i)

				"""Value of numArr[i] becomes the new end element of list of size newLength"""
				tempArr[newLength] = i
				"""New end element tempArr[newLength] comes from the end element of list before it"""
				predecessorArr[i] = tempArr[newLength - 1]

				length = newLength if (newLength > length) else length

			longestSubsequence = []
			index = tempArr[length]

			for i in range(length - 1, -1, -1):
				longestSubsequence.append(index)
				index = predecessorArr[index]

			print(length)
			print(" ".join(list(map(str, longestSubsequence[::-1]))))

		except EOFError:
			break

longestLis()
