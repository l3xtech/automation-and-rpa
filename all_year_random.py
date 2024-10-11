import os
import random

def make_c(days: int):
    if days < 1:
        return os.system('git push')
    else:
        dates = f'{days} days ago'

        with open('data.txt', 'a') as file:
            file.write(f'{dates}\n')

        os.system('git add data.txt')
        os.system('git commit --date="'+dates+'" -m "First Commit"')

        jump = random.randint(1, 6) #  year_range = random.randint(120, 368)
        return days * make_c(days-jump)

for i in range(20):
    make_c(76)
