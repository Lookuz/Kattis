from sys import stdin

students = list(map(int, input().split()))
numStudents = students.pop(0)
students.sort()

total = 0
while len(students) > 0:
	if len(students) < 4:
		if len(students) < 3:
			total += students[-1]
			break
		else:
			while len(students) > 0:
				total += students.pop(0)
	
	else:
		first = (students[1] + students[0]) + (students[-1] + students[1])
		second = (students[0] + students[-1]) + (students[0] + students[-2])

		total += min(first, second)

		students.pop(-1)
		students.pop(-1)

print(total)
