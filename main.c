#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void selectionSort(int array[], int tamanho)
{
    for (int i = 0; i < tamanho - 1; i++)
    {
        int minIndex = i;
        for (int j = i + 1; j < tamanho; j++)
        {
            if (array[j] < array[minIndex])
            {
                minIndex = j;
            }
        }
        // Troca o menor elemento com o elemento da posição atual
        int temp = array[minIndex];
        array[minIndex] = array[i];
        array[i] = temp;
    }
}

void insertionSort(int array[], int tamanho)
{
    for (int i = 1; i < tamanho; i++)
    {
        int key = array[i];
        int j = i - 1;
        while (j >= 0 && array[j] > key)
        {
            array[j + 1] = array[j];
            j--;
        }
        array[j + 1] = key;
    }
}

void bubbleSort(int array[], int tamanho)
{
    for (int i = 0; i < tamanho - 1; i++)
    {
        for (int j = 0; j < tamanho - i - 1; j++)
        {
            if (array[j] > array[j + 1])
            {
                int temp = array[j];
                array[j] = array[j + 1];
                array[j + 1] = temp;
            }
        }
    }
}

void merge(int array[], int inicio, int meio, int fim)
{
    int n1 = meio - inicio + 1;
    int n2 = fim - meio;

    int esquerda[n1], direita[n2];

    for (int i = 0; i < n1; i++)
        esquerda[i] = array[inicio + i];
    for (int j = 0; j < n2; j++)
        direita[j] = array[meio + 1 + j];

    int i = 0, j = 0, k = inicio;
    while (i < n1 && j < n2)
    {
        if (esquerda[i] <= direita[j])
        {
            array[k] = esquerda[i];
            i++;
        }
        else
        {
            array[k] = direita[j];
            j++;
        }
        k++;
    }

    while (i < n1)
    {
        array[k] = esquerda[i];
        i++;
        k++;
    }
    while (j < n2)
    {
        array[k] = direita[j];
        j++;
        k++;
    }
}

void mergeSort(int array[], int inicio, int fim)
{
    if (inicio < fim)
    {
        int meio = inicio + (fim - inicio) / 2;
        mergeSort(array, inicio, meio);
        mergeSort(array, meio + 1, fim);
        merge(array, inicio, meio, fim);
    }
}

int partition(int array[], int inicio, int fim)
{
    int pivot = array[fim];
    int i = inicio - 1;

    for (int j = inicio; j < fim; j++)
    {
        if (array[j] <= pivot)
        {
            i++;
            int temp = array[i];
            array[i] = array[j];
            array[j] = temp;
        }
    }

    int temp = array[i + 1];
    array[i + 1] = array[fim];
    array[fim] = temp;
    return i + 1;
}

void quickSort(int array[], int inicio, int fim)
{
    if (inicio < fim)
    {
        int pi = partition(array, inicio, fim);
        quickSort(array, inicio, pi - 1);
        quickSort(array, pi + 1, fim);
    }
}

void heapify(int array[], int tamanho, int i)
{
    int maior = i;
    int esquerda = 2 * i + 1;
    int direita = 2 * i + 2;

    if (esquerda < tamanho && array[esquerda] > array[maior])
        maior = esquerda;

    if (direita < tamanho && array[direita] > array[maior])
        maior = direita;

    if (maior != i)
    {
        int temp = array[i];
        array[i] = array[maior];
        array[maior] = temp;
        heapify(array, tamanho, maior);
    }
}

void heapSort(int array[], int tamanho)
{
    for (int i = tamanho / 2 - 1; i >= 0; i--)
        heapify(array, tamanho, i);

    for (int i = tamanho - 1; i > 0; i--)
    {
        int temp = array[0];
        array[0] = array[i];
        array[i] = temp;
        heapify(array, i, 0);
    }
}

// Função para copiar o array
void copiaArray(int origem[], int destino[], int tamanho)
{
    for (int i = 0; i < tamanho; i++)
    {
        destino[i] = origem[i];
    }
}

// Função para medir o tempo de execução de cada algoritmo
void medeTempoExecucao(void (*algoritmo)(int[], int), int arr[], int tamanho, const char *nome)
{
    int arr_copia[tamanho];
    copiaArray(arr, arr_copia, tamanho); // Copia o array original para não alterar o original

    clock_t inicio = clock();
    algoritmo(arr_copia, tamanho); // Chama o algoritmo de ordenação
    clock_t fim = clock();

    double tempo_cpu = ((double)(fim - inicio)) / CLOCKS_PER_SEC;
    printf("%s para %d elementos: %f segundos\n", nome, tamanho, tempo_cpu);
}

// Função para preencher o array com valores aleatórios
void preencheArrayAleatorio(int arr[], int tamanho)
{
    for (int i = 0; i < tamanho; i++)
    {
        arr[i] = rand();
    }
}

int main()
{
    int tamanhos[] = {100, 1000, 10000, 50000, 100000};
    int num_tamanhos = sizeof(tamanhos) / sizeof(tamanhos[0]);

    srand(time(NULL)); // Inicializa o gerador de números aleatórios

    // Preenche o array com números aleatórios
    for (int i = 0; i < num_tamanhos; i++)
    {
        int tamanho = tamanhos[i];
        int arr[tamanho];
        preencheArrayAleatorio(arr, tamanho); // Preenche o array com números aleatórios

        printf("Testes de desempenho para arrays de tamanho %d:\n", tamanho);

        // Realiza os testes de desempenho para cada algoritmo
        medeTempoExecucao(selectionSort, arr, tamanho, "Selection Sort");
        medeTempoExecucao(insertionSort, arr, tamanho, "Insertion Sort");
        medeTempoExecucao(bubbleSort, arr, tamanho, "Bubble Sort");

        // Para Merge Sort e Quick Sort, que precisam de índices adicionais
        int arr_copia[tamanho];
        copiaArray(arr, arr_copia, tamanho);
        clock_t inicio = clock();
        mergeSort(arr_copia, 0, tamanho - 1);
        clock_t fim = clock();
        printf("Merge Sort para %d elementos: %f segundos\n", tamanho, ((double)(fim - inicio)) / CLOCKS_PER_SEC);

        copiaArray(arr, arr_copia, tamanho);
        inicio = clock();
        quickSort(arr_copia, 0, tamanho - 1);
        fim = clock();
        printf("Quick Sort para %d elementos: %f segundos\n", tamanho, ((double)(fim - inicio)) / CLOCKS_PER_SEC);

        medeTempoExecucao(heapSort, arr, tamanho, "Heap Sort");

        printf("\n");
    }

    return 0;
}