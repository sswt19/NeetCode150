from typing import List 
from collections import defaultdict 



# 8. https://leetcode.com/problems/valid-sudoku/description/
class CheckSudoku:
    # T:O(n*n) and S:O(n)
    def isValidSudoku(self, board: List[List[str]]) -> bool:
        def is_row_and_col_valid(pos):
            present_in_row, present_in_col=set(),set()
            for i in range(9):
                # check pos row
                if board[pos][i]!='.' and board[pos][i] in present_in_row:
                    return False
                # check pos col
                if board[i][pos]!='.' and board[i][pos] in present_in_col:
                    return False
                present_in_row.add(board[pos][i])
                present_in_col.add(board[i][pos])
            return True
        
        def is_matrix_valid(row,col):
            present=set()
            for i in range(row,row+3):
                for j in range(col,col+3):
                    if board[i][j]!='.' and board[i][j] in present:
                        return False
                    present.add(board[i][j])
            return True
        
        for i in range(9):
            if not is_row_and_col_valid(i):
                return False
        for i in range(3):
            for j in range(3):
                if not is_matrix_valid(i*3,j*3):
                    return False
        return True

# 9. https://leetcode.com/problems/longest-consecutive-sequence/description/
def longestConsecutive(self, nums: List[int]) -> int:
    # T:O(n) and S:O(n) for set
    present=set(nums)
    ans=0
    for n in present:
        if n-1 in present:
            continue
        end = n
        while end+1 in present:
            end+=1
        ans=max(ans,end-n+1)
    return ans
            
# 10. https://leetcode.com/problems/count-number-of-bad-pairs/description/
def countBadPairs(self, nums: List[int]) -> int:
    # T:O(n) and S:O(n) for defaultdict
    good_pairs=0
    count=defaultdict(int)
    for i, num in enumerate(nums):
        good_pairs+=count[num-i]
        count[num-i]+=1
    n=len(nums)
    #Wrong: I was using (n*(n+1))//2 for total pairs
    total_pairs=(n*(n-1))//2
    bad_pairs=total_pairs-good_pairs
    return bad_pairs

