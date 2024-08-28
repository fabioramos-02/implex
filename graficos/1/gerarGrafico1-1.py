import matplotlib.pyplot as plt
import csv

# Ler os dados do arquivo CSV
dados = []
with open('../../vetor_aleatorio.csv', 'r') as arquivo_csv:
    leitor_csv = csv.reader(arquivo_csv, delimiter=';')
    for linha in leitor_csv:
        dados.append([float(valor) for valor in linha])

# Separando os dados
n = [row[0] for row in dados]
bubble = [row[1] for row in dados]
insertion = [row[2] for row in dados]

# Criando o gráfico
plt.figure(figsize=(10, 6))

# Definindo cores explícitas para cada algoritmo
plt.plot(n, bubble, color='black', marker='v', label='Bubble Sort')
plt.plot(n, insertion, color='red', marker='o', label='Insertion Sort')


# Configurando os eixos
plt.xlabel('n (Tamanho do vetor)', fontsize=12)
plt.ylabel('Tempo (s)', fontsize=12)

# Ajustando o título
plt.title('Tempos de Execução dos Algoritmos de Ordenação no Conjunto Aleatório', fontsize=14, weight='bold')

# Ajustando os ticks do eixo x
#variar conforme o parametro int inc = 2000, fim = 30000, stp = 2000, rpt = 10;
plt.xticks([2000, 4000, 6000, 8000, 10000, 12000, 14000, 16000, 18000, 20000, 22000, 24000, 26000, 28000, 30000])

# Exibindo a grade
plt.grid(True)

# Exibindo a legenda
plt.legend()

# Mostrar o gráfico
plt.show()
