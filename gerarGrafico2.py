import matplotlib.pyplot as plt
import csv

# Ler os dados do arquivo CSV
dados = []
with open('vetor_reverso.csv', 'r') as arquivo_csv:
    leitor_csv = csv.reader(arquivo_csv, delimiter=';')
    for linha in leitor_csv:
        dados.append([float(valor) for valor in linha])

# Separando os dados
n = [row[0] for row in dados]
bubble = [row[1] for row in dados]
insertion = [row[2] for row in dados]
merge = [row[3] for row in dados]
heap = [row[4] for row in dados]
quick = [row[5] for row in dados]
counting = [row[6] for row in dados]

# Criando o gráfico
plt.figure(figsize=(10, 6))

# Definindo cores explícitas para cada algoritmo
plt.plot(n, bubble, color='black', marker='v', label='Bubble Sort')
plt.plot(n, insertion, color='red', marker='o', label='Insertion Sort')
plt.plot(n, merge, color='purple', marker='P', label='Merge Sort')
plt.plot(n, heap, color='green', marker='X', label='Heap Sort')
plt.plot(n, quick, color='blue', marker='*', label='Quick Sort')
plt.plot(n, counting, color='orange', marker='s', label='Counting Sort')

# Configurando os eixos
plt.xlabel('n (Tamanho do vetor)', fontsize=12)
plt.ylabel('Tempo (s)', fontsize=12)

# Ajustando o título
plt.title('Tempos de Execução dos Algoritmos de Ordenação no Conjunto Reverso', fontsize=14, weight='bold')

plt.xticks([2000, 4000, 6000, 8000, 10000, 12000, 14000, 16000, 18000, 20000])

# Exibindo a grade
plt.grid(True)

# Exibindo a legenda
plt.legend()

# Mostrar o gráfico
plt.show()
