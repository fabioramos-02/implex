import matplotlib.pyplot as plt
import csv

# Criar programa que lê os dados do arquivo CSV e gera um gráfico
# Dados fornecidos pelo arquivo vetor_aleatorio.csv
# Dados: n, bubble, insertion

dados = []

# Ler os dados do arquivo CSV
with open('vetor_aleatorio.csv', 'r') as arquivo_csv:
    leitor_csv = csv.reader(arquivo_csv, delimiter=';')
    for linha in leitor_csv:
        dados.append([float(valor) for valor in linha])

# Separando os dados
n = [row[0] for row in dados]
bubble = [row[1] for row in dados]
insertion = [row[2] for row in dados]

# Criando o gráfico
plt.figure(figsize=(10, 6))
plt.plot(n, bubble, 'm-', marker='P', label='Bubble Sort')  # Usando a cor e marcador especificado
plt.plot(n, insertion, 'c-', marker='X', label='Insertion Sort')  # Usando a cor e marcador especificado

plt.xlabel('n (Tamanho do vetor)')
plt.ylabel('Tempo (segundos)')
plt.title('Comparação dos Tempos de Execução: Bubble Sort vs Insertion Sort no conjunto Aleatório')
plt.legend()
plt.grid(True)
plt.show()
