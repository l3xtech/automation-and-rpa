
import os
import random

def make_commits_for_day(day: str):
    num_commits = random.randint(1, 12)
    for _ in range(num_commits):
        with open('data.txt', 'a') as file:
            file.write(f'{day}\n')

        os.system('git add data.txt')
        os.system(f'git commit --date="{day}" -m "Commit for {day}"')

def make_c(days: int):
    for day in range(days, 0, -1):
        date_str = f'{day} days ago'
        make_commits_for_day(date_str)

    os.system('git push')

make_c(365)
