#include <SDL2/SDL.h>
#include <iostream>
#include <ctime>
#include <iomanip>
#include <algorithm> // for std::swap
using namespace std;

const int WIDTH = 1000;
const int HEIGHT = 600;
const int SIZE = 500;
SDL_Window* window = NULL;
SDL_Renderer* renderer;
SDL_Event event;
bool quit = false;

// Function declarations
void GenerateArray(int* arr);
void PrintArray(int* arr);
void draw(int* arr, int i, int j);

// Sorting algorithms
void SelectionSort(int* arr);
void BubbleSort(int* arr);
void InsertionSort(int* arr);
void MergeSort(int* arr, int l, int r);
void Merge(int* arr, int l, int m, int r);
int Partition(int* arr, int low, int high);
void QuickSort(int* arr, int low, int high);
void HeapSort(int* arr);
void CountingSort(int* arr);
void EvenOddSort(int* arr);
void RadixSort(int* arr);

// Utility functions
void Swap(int* arr, int i, int j);
bool processEvent();
void setup();
void performSorting(int* arr, int choice);

int main(int argc, char* args[])
{
    time_t start, end;
    int arr[SIZE];

    GenerateArray(arr);

    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        cout << "SDL could not initialize! SDL_Error" << endl << SDL_GetError();
    }
    else
    {
        setup();
    }

    cout << "Choose a sorting algorithm:" << endl;
    cout << "1. Selection Sort" << endl;
    cout << "2. Bubble Sort" << endl;
    cout << "3. Insertion Sort" << endl;
    cout << "4. Merge Sort" << endl;
    cout << "5. Quick Sort" << endl;
    cout << "6. Heap Sort" << endl;
    cout << "7. Counting Sort" << endl;
    cout << "8. Even Odd Sort" << endl;
    cout << "9. Radix Sort" << endl;

    int choice;
    cout << "Enter your choice (1-9): ";
    cin >> choice;

    if (choice < 1 || choice > 9)
    {
        cout << "Invalid choice. Exiting program." << endl;
        return 1;
    }

    SDL_SetRenderDrawColor(renderer, 255, 165, 0, 255);
    for (int i = 0; i < SIZE; i++)
    {
        SDL_Rect rect = { i * WIDTH / SIZE, HEIGHT - arr[i], WIDTH / SIZE, HEIGHT };
        SDL_RenderFillRect(renderer, &rect);
        SDL_RenderPresent(renderer);
    }

    time(&start);

    // Call the appropriate sorting function based on user choice
    switch (choice)
    {
    case 1:
        SelectionSort(arr);
        break;
    case 2:
        BubbleSort(arr);
        break;
    case 3:
        InsertionSort(arr);
        break;
    case 4:
        MergeSort(arr, 0, SIZE - 1);
        break;
    case 5:
        QuickSort(arr, 0, SIZE - 1);
        break;
    case 6:
        HeapSort(arr);
        break;
    case 7:
        CountingSort(arr);
        break;
    case 8:
        EvenOddSort(arr);
        break;
    case 9:
        RadixSort(arr);
        break;
    default:
        cout << "Invalid choice." << endl;
    }

    time(&end);

    double time_taken = double(end - start);
    cout << "Array size: " << SIZE << endl;
    cout << "Time taken by program is: " << fixed << time_taken << setprecision(5) << " sec " << endl;

    while (!quit)
    {
        quit = processEvent();
    }

    // Destroy renderer
    SDL_DestroyRenderer(renderer);
    // Destroy window
    SDL_DestroyWindow(window);
    // Quit SDL subsystems
    SDL_Quit();

    return 0;
}

void GenerateArray(int* arr)
{
    srand(time(NULL));
    for (int i = 0; i < SIZE; i++)
    {
        arr[i] = 1 + rand() % HEIGHT;
    }
}

void PrintArray(int* arr)
{
    for (int i = 0; i < SIZE; i++)
    {
        cout << arr[i] << ' ';
    }
}

void draw(int* arr, int i, int j)
{
    SDL_Rect rect;

    SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
    rect = { j * WIDTH / SIZE, HEIGHT - arr[j], WIDTH / SIZE, HEIGHT };
    SDL_RenderFillRect(renderer, &rect);
    SDL_RenderPresent(renderer);

    SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
    rect = { i * WIDTH / SIZE, HEIGHT - arr[i], WIDTH / SIZE, HEIGHT };
    SDL_RenderFillRect(renderer, &rect);
    SDL_RenderPresent(renderer);

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    rect = { j * WIDTH / SIZE, HEIGHT - arr[j], WIDTH / SIZE, HEIGHT };
    SDL_RenderFillRect(renderer, &rect);

    SDL_SetRenderDrawColor(renderer, 255, 165, 0, 255);
    rect = { j * WIDTH / SIZE, HEIGHT - arr[i], WIDTH / SIZE, HEIGHT };
    SDL_RenderFillRect(renderer, &rect);
    SDL_RenderPresent(renderer);

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    rect = { i * WIDTH / SIZE, HEIGHT - arr[i], WIDTH / SIZE, HEIGHT };
    SDL_RenderFillRect(renderer, &rect);

    SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
    rect = { i * WIDTH / SIZE, HEIGHT - arr[j], WIDTH / SIZE, HEIGHT };
    SDL_RenderFillRect(renderer, &rect);
    SDL_RenderPresent(renderer);
}

void SelectionSort(int* arr)
{
    int i, j, index;
    for (i = 0; i < SIZE - 1; i++)
    {
        index = i;
        for (j = i + 1; j < SIZE; j++)
        {
            if (arr[j] < arr[index]) {
                index = j;
            }
        }
        draw(arr, i, index);
        Swap(arr, i, index);
        SDL_Delay(5);
    }
    SDL_Rect rect;
    SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
    rect = { (SIZE - 1) * (WIDTH / SIZE), HEIGHT - arr[SIZE - 1], WIDTH / SIZE, HEIGHT };
    SDL_RenderFillRect(renderer, &rect);
    SDL_RenderPresent(renderer);
}

void BubbleSort(int* arr)
{
    for (int i = 0; i < SIZE - 1; i++)
    {
        for (int j = 0; j < SIZE - i - 1; j++)
        {
            if (arr[j] > arr[j + 1])
            {
                draw(arr, j, j + 1);
                Swap(arr, j, j + 1);
                SDL_Delay(5);
            }
        }
    }
}

void InsertionSort(int* arr)
{
    int i, key, j;
    for (i = 1; i < SIZE; i++)
    {
        key = arr[i];
        j = i - 1;

        while (j >= 0 && arr[j] > key)
        {
            draw(arr, j, j + 1);
            arr[j + 1] = arr[j];
            j = j - 1;
            SDL_Delay(5);
        }
        arr[j + 1] = key;
    }
}

void MergeSort(int* arr, int l, int r)
{
    if (l < r)
    {
        int m = l + (r - l) / 2;
        MergeSort(arr, l, m);
        MergeSort(arr, m + 1, r);
        Merge(arr, l, m, r);
    }
}
// ... (Your existing includes and constants)

void Merge(int* arr, int l, int m, int r)
{
    int n1 = m - l + 1;
    int n2 = r - m;

    int L[n1], R[n2];

    for (int i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];

    int i = 0;
    int j = 0;
    int k = l;

    while (i < n1 && j < n2)
    {
        if (L[i] <= R[j])
        {
            arr[k] = L[i];
            i++;
        }
        else
        {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1)
    {
        arr[k] = L[i];
        i++;
        k++;
    }

    while (j < n2)
    {
        arr[k] = R[j];
        j++;
        k++;
    }
}

void QuickSort(int* arr, int low, int high)
{
    if (low < high)
    {
        int pi = Partition(arr, low, high);

        QuickSort(arr, low, pi - 1);
        QuickSort(arr, pi + 1, high);
    }
}
void Heapify(int* arr, int n, int i)
{
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && arr[left] > arr[largest])
        largest = left;

    if (right < n && arr[right] > arr[largest])
        largest = right;

    if (largest != i)
    {
        draw(arr, i, largest);
        Swap(arr, i, largest);
        SDL_Delay(5);

        Heapify(arr, n, largest);
    }
}

void HeapSort(int* arr)
{
    for (int i = SIZE / 2 - 1; i >= 0; i--)
        Heapify(arr, SIZE, i);

    for (int i = SIZE - 1; i > 0; i--)
    {
        draw(arr, 0, i);
        Swap(arr, 0, i);
        SDL_Delay(5);

        Heapify(arr, i, 0);
    }
}

void CountingSort(int* arr)
{
    int maxVal = *max_element(arr, arr + SIZE);
    int minVal = *min_element(arr, arr + SIZE);
    int range = maxVal - minVal + 1;

    int* count = new int[range]();
    int* output = new int[SIZE];

    for (int i = 0; i < SIZE; i++)
        count[arr[i] - minVal]++;

    for (int i = 1; i < range; i++)
        count[i] += count[i - 1];

    for (int i = SIZE - 1; i >= 0; i--) {
        draw(arr, count[arr[i] - minVal] - 1, i);
        output[count[arr[i] - minVal] - 1] = arr[i];
        count[arr[i] - minVal]--;
        SDL_Delay(5);
    }

    for (int i = 0; i < SIZE; i++) {
        arr[i] = output[i];
        draw(arr, i, i);
        SDL_Delay(5);
    }

    delete[] count;
    delete[] output;
}

void EvenOddSort(int* arr)
{
    bool sorted = false;
    while (!sorted)
    {
        sorted = true;
        for (int i = 1; i < SIZE - 1; i += 2)
        {
            if (arr[i] > arr[i + 1])
            {
                draw(arr, i, i + 1);
                Swap(arr, i, i + 1);
                SDL_Delay(5);
                sorted = false;
            }
        }

        for (int i = 0; i < SIZE - 1; i += 2)
        {
            if (arr[i] > arr[i + 1])
            {
                draw(arr, i, i + 1);
                Swap(arr, i, i + 1);
                SDL_Delay(5);
                sorted = false;
            }
        }
    }
}

void RadixSort(int* arr)
{
    int maxVal = *max_element(arr, arr + SIZE);
    for (int exp = 1; maxVal / exp > 0; exp *= 10)
    {
        int output[SIZE];
        int count[10] = { 0 };

        for (int i = 0; i < SIZE; i++)
            count[(arr[i] / exp) % 10]++;

        for (int i = 1; i < 10; i++)
            count[i] += count[i - 1];

        for (int i = SIZE - 1; i >= 0; i--)
        {
            draw(arr, count[(arr[i] / exp) % 10] - 1, i);
            output[count[(arr[i] / exp) % 10] - 1] = arr[i];
            count[(arr[i] / exp) % 10]--;
            SDL_Delay(5);
        }

        for (int i = 0; i < SIZE; i++)
        {
            arr[i] = output[i];
            draw(arr, i, i);
            SDL_Delay(5);
        }
    }
}

int Partition(int* arr, int low, int high)
{
    int pivot = arr[high];
    int i = (low - 1);

    for (int j = low; j <= high - 1; j++)
    {
        if (arr[j] < pivot)
        {
            i++;
            Swap(arr, i, j);
            draw(arr, i, j);
            SDL_Delay(5);
        }
    }
    Swap(arr, i + 1, high);
    draw(arr, i + 1, high);
    SDL_Delay(5);
    return (i + 1);
}
void Swap(int* arr, int i, int j)
{
    int temp = arr[i];
    arr[i] = arr[j];
    arr[j] = temp;
}

bool processEvent()
{
    while (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
        case SDL_WINDOWEVENT_CLOSE:
            if (window)
            {
                SDL_DestroyWindow(window);
                window = NULL;
                quit = true;
            }
            break;
        case SDL_KEYDOWN:
            switch (event.key.keysym.sym)
            {
            case SDLK_ESCAPE:
                quit = true;
                break;
            }
            break;
        case SDL_QUIT:
            quit = true;
            break;
        }
    }
    return quit;
}

void setup()
{
    window = SDL_CreateWindow("Sorting Visualizer", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, 0);
    if (window == NULL)
    {
        cout << "Window could not be created! SDL_Error" << endl << SDL_GetError();
    }
    else
    {
        renderer = SDL_CreateRenderer(window, -1, 0);

        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

        SDL_RenderClear(renderer);

        SDL_UpdateWindowSurface(window);
    }
}

void performSorting(int* arr, int choice)
{
    switch (choice)
    {
    case 1:
        SelectionSort(arr);
        break;
    case 2:
        BubbleSort(arr);
        break;
    case 3:
        InsertionSort(arr);
        break;
    case 4:
        MergeSort(arr, 0, SIZE - 1);
        break;
    case 5:
        QuickSort(arr, 0, SIZE - 1);
        break;
    default:
        cout << "Invalid choice." << endl;
    }
}

