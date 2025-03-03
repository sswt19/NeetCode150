
from typing import List

# 5. https://leetcode.com/problems/daily-temperatures/
def dailyTemperatures(self, temperatures: List[int]) -> List[int]:
    # T:O(n) and S:O(n) for stack
    # monotonic decreasing stack, and store index in stack
    # next greater element to the right
    n=len(temperatures)
    stack=[]
    ans=[0]*n
    for i in range(n-1,-1,-1):
        # Mistake: temperatures[stack[-1]]<temperatures[i]
        while stack and temperatures[stack[-1]]<=temperatures[i]:
            stack.pop()
        ans[i]=stack[-1]-i if stack else 0
        stack.append(i)
    return ans

# 6. https://leetcode.com/problems/car-fleet/
def carFleet(self, target: int, position: List[int], speed: List[int]) -> int:
    # T:O(nlogn) and S:O(n)
    # Sort the cars based on their position, and calculate the time required to reach target,from end and not from the start.
    # first car might not reach second carbut third car can block second car, so first can reach the second and third car
    car_pos_speed=[[x,v] for x,v in zip(position,speed)]
    car_pos_speed.sort(key=lambda x: x[0],reverse=True)
    time_queue=[]

    for car in car_pos_speed:
        time_required=(target-car[0])/car[1]
        if not time_queue or time_queue[-1]<time_required:
            time_queue.append(time_required)
    
    return len(time_queue)