import os

def make_c(days: int):
    if days < 1:
        return os.system('git push')
    else:
        dates = f'{days} days ago'

        with open('data.txt', 'a') as file:
            file.write(f'{dates}\n')

        os.system('git add data.txt')
        os.system('git commit --date="'+dates+'" -m "First Commit"')

        return days * make_c(days-1)

make_c(368)
