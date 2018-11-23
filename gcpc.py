from sys import stdin

numTeams, numEvents = tuple(map(int, input().split()))
solved = [0 for i in range(0, numTeams)]
penalty = [0 for i in range(0, numTeams)]
better = set()

for i in range(0, numEvents):
	teamNo, teamPenalty = tuple(map(int, input().split()))

	solved[teamNo - 1] += 1
	penalty[teamNo - 1] += teamPenalty

	if teamNo == 1:
		for team in list(better):
			if solved[team] < solved[0] or (solved[team] == solved[0] and penalty[team] >= penalty[0]):
				better.remove(team)
	else:
		if teamNo - 1 not in better:
			if solved[teamNo - 1] > solved[0] or (solved[teamNo - 1] == solved[0] and penalty[teamNo - 1] < penalty[0]):
				better.add(teamNo - 1)
	print(len(better) + 1)
