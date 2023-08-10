
import os
import random

def make_c(days: int):
    if days < 1:
        return os.system('git push')
    else:
        dates = f'{days} days ago'

        # Quantidade aleatória de vezes para escrever no arquivo
        num_loops = random.randint(1, 12)
        for _ in range(num_loops):
            with open('data.txt', 'a') as file:
                file.write(f'{dates}\n')

            os.system('git add data.txt')
            os.system(f'git commit --date="{dates}" -m "Commit for {dates}"')

        return days * make_c(days-1)

make_c(368)
