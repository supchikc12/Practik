#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Объявление структуры human
struct human {
    char name[50];
    char surname[50];
    int birth_year;
};

// Функция для сравнения двух структур по году рождения
int compare_by_year(const void *a, const void *b) {
    struct human *human1 = (struct human *)a;
    struct human *human2 = (struct human *)b;
    return human1->birth_year - human2->birth_year;
}

// Функция для ввода данных из консоли
void input_from_console(struct human *arr, int size) {
    printf("Enter information about %d people:\n", size);
    for (int i = 0; i < size; i++) {
        printf("\nPerson %d:\n", i + 1);
        printf("Name: ");
        scanf("%s", arr[i].name);
        printf("Surname: ");
        scanf("%s", arr[i].surname);
        printf("Year of birth: ");
        scanf("%d", &arr[i].birth_year);
    }
}

// Функция для ввода данных из файла
int input_from_file(struct human *arr, int size, const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error opening the %s file\n", filename);
        return 0;
    }
    
    for (int i = 0; i < size; i++) {
        if (fscanf(file, "%s %s %d", arr[i].name, arr[i].surname, &arr[i].birth_year) != 3) {
            printf("Error reading data from the \n file");
            fclose(file);
            return 0;
        }
    }
    
    fclose(file);
    return 1;
}

// Функция для вывода массива
void print_array(struct human *arr, int size, const char *title) {
    printf("\n%s:\n", title);
    printf("------------------------------------------------\n");
    printf("%-15s %-15s %s\n", "Name", "Surname", "Year of birth");
    printf("------------------------------------------------\n");
    
    for (int i = 0; i < size; i++) {
        printf("%-15s %-15s %d\n", 
               arr[i].name, 
               arr[i].surname, 
               arr[i].birth_year);
    }
    printf("------------------------------------------------\n");
}

int main() {
    struct human first_array[4];   // Первый массив
    struct human second_array[4];  // Второй массив (упорядоченный)
    int choice;
    
    printf("Select the data entry method:\n");
    printf("1 - Input from the console\n");
    printf("2 - Input from a file\n");
    printf("Your choice: ");
    scanf("%d", &choice);
    
    // Ввод данных в первый массив
    if (choice == 1) {
        input_from_console(first_array, 4);
    } else if (choice == 2) {
        char filename[100];
        printf("Enter the file name: ");
        scanf("%s", filename);
        
        if (!input_from_file(first_array, 4, filename)) {
            printf("Data could not be read from the file. The program is completed.\n");
            return 1;
        }
    } else {
        printf("Wrong choice. The program is completed.\n");
        return 1;
    }
    
    // Вывод исходного массива
    print_array(first_array, 4, "The original array");
    
    // Копирование данных из первого массива во второй
    for (int i = 0; i < 4; i++) {
        strcpy(second_array[i].name, first_array[i].name);
        strcpy(second_array[i].surname, first_array[i].surname);
        second_array[i].birth_year = first_array[i].birth_year;
    }
    
    // Сортировка второго массива по году рождения
    qsort(second_array, 4, sizeof(struct human), compare_by_year);
    
    // Вывод упорядоченного массива
    print_array(second_array, 4, "Ordered array");
    
    return 0;
}