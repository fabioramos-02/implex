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
merge = [row[3] for row in dados]
heap = [row[4] for row in dados]
quick = [row[5] for row in dados]
counting = [row[6] for row in dados]

# Criando o gráfico
plt.figure(figsize=(10, 6))
plt.plot(n, merge, 'm-', marker='P', label='Merge Sort')  # Usando a cor e marcador especificado
plt.plot(n, heap, 'c-', marker='X', label='Heap Sort')  # Usando a cor e marcador especificado
plt.plot(n, quick, 'y-', marker='D', label='Quick Sort')  # Usando a cor e marcador especificado
plt.plot(n, counting, 'g-', marker='o', label='Counting Sort')  # Usando a cor e marcador especificado

plt.xlabel('n (Tamanho do vetor)')
plt.ylabel('Tempo (segundos)')
plt.title('Comparação dos Tempos de Execução: Conjunto Aleatório')
plt.legend()
plt.grid(True)
plt.show()
