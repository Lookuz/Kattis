import heapq

N = int(input())
cost = [int(input()) for _ in range(N)]
pq = []
visited = set()

heapq.heappush(pq, (0, 0, 0))

while pq:
    curr_cost, curr_pos, prev_jump = heapq.heappop(pq)
    if (curr_pos, prev_jump) in visited:
        continue
    visited.add((curr_pos, prev_jump))
    if curr_pos == N - 1:
        print(curr_cost)
        break
    back = curr_pos - prev_jump
    if back >= 0:
        heapq.heappush(pq, (curr_cost + cost[back], back, prev_jump))
    forward = curr_pos + prev_jump + 1
    if forward < N:
        heapq.heappush(pq, (curr_cost + cost[forward], forward, prev_jump + 1))
