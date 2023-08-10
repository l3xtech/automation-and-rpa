import os
import sys
from wordcloud import WordCloud
import matplotlib.pyplot as plt
from nltk.corpus import stopwords
from collections import Counter
from nltk.tokenize import word_tokenize

# Verifica se os argumentos necessários foram fornecidos
if len(sys.argv) != 3:
    print("Uso: python3 word_cloud.py <-en|-pt> <caminho_para_o_arquivo.txt>")
    sys.exit()

# Atribui o idioma das stopwords e o caminho do arquivo para as variáveis
language_arg = sys.argv[1]
file_path = sys.argv[2]

# Define as stopwords de acordo com o idioma fornecido
if language_arg == "-pt":
    stopwords_set = set(stopwords.words('portuguese'))
elif language_arg == "-en":
    stopwords_set = set(stopwords.words('english'))
else:
    print("Idioma desconhecido. Use -en para inglês ou -pt para português.")
    sys.exit()

# Verifica se o arquivo existe
if not os.path.isfile(file_path):
    print("Arquivo não encontrado. Por favor, tente novamente.")
else:
    # Lê o arquivo
    with open(file_path, 'r') as file:
        text = file.read()

    # Tokeniza o texto e remove as stopwords e pontuações
    words = word_tokenize(text)

    words = [word for word in words if word.isalpha() and word not in stopwords_set]
    # Conta a frequência de cada palavra e imprime as 10 mais comuns
    word_freq = Counter(words)
    print("As 10 palavras mais comuns são:")
    for word, freq in word_freq.most_common(10):
        print(f"{word}: {freq}")

    # Cria a nuvem de palavras ignorando as stopwords
    wordcloud = WordCloud(stopwords=stopwords_set, width=1000, height=500).generate(text)
    # Mostra a nuvem de palavras
    plt.figure(figsize=(15,8))
    plt.imshow(wordcloud)
    plt.axis("off")
    plt.show()

