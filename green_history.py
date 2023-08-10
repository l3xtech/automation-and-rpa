import os
import random
import sys

sys.setrecursionlimit(10000)

def make_commits_for_day(day: str):
    num_commits = random.randint(1, 12)
    for _ in range(num_commits):
        with open('data.txt', 'a') as file:
            file.write(f'{day}\n')

        os.system('git add data.txt')
        os.system(f'git commit --date="{day}" -m "Commit for {day}"')

def make_c(days: int):
    if days < 1:
        return os.system('git push')
    else:
        date_str = f'{days} days ago'
        make_commits_for_day(date_str)
        return make_c(days-1)

make_c(368)
