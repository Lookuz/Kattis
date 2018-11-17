from sys import stdin

users = set()
words = {}
count = {}

numLines = int(input())

for i in range(0, numLines):
	inputs = input().split()
	user = inputs.pop(0)
	if user not in users:
		users.add(user)
	for word in inputs:
		if word not in words:
			words[word] = {user}
			count[word] = 0
		elif user not in words[word]:
			words[word].add(user)
		count[word] += 1

words = {k : v for k, v in words.items() if len(v) >= len(users)}
wordList = list(words.keys())
wordList.sort(key=lambda x : (-count[x], x))

if len(wordList) == 0:
	print('ALL CLEAR')
else:
	for word in wordList:
		print(word)
