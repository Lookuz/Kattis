from sys import stdin

def lose(player, maxStars):
	player[2] = 0
	if player[0] >= 20:
		if player[0] == 20 and player[1] > 0:
			player[1] -= 1
		return
	else:
		if player[1] <= 0:
			player[0] += 1
			player[1] = maxStars[(player[0] - 1)//5] - 1
		else:
			player[1] -= 1

def win(player, maxStars):
	player[2] += 1
	player[1] += 1
	if player[2] >= 3 and player[0] >= 6:
		player[1] += 1
	
	if player[1] > maxStars[(player[0] - 1)//5]:
		player[1] = player[1] - maxStars[(player[0] - 1)//5]
		player[0] -= 1


maxStars = {4: 2, 3: 3, 2: 4, 1: 5, 0: 5}

record = input()
player = [25, 0, 0]
for char in record:
	if char == 'W':
		win(player, maxStars)
	else:
		lose(player, maxStars)
	
	if player[0] == 0:
		break

if player[0] == 0:
	print('Legend')
else:
	print(player[0])
