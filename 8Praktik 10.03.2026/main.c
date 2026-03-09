#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_NAME 100
#define MAX_RECORDS 100
#define MAX_PATH 260
#define FILE_PATH "C:\\Users\\Hp\\Desktop\\people.txt"
#define SORTED_FILE_PATH "C:\\Users\\Hp\\Desktop\\sorted_people.txt"

typedef struct {
    char name[MAX_NAME];
    int birth_year;
    char gender;  // 'M' или 'F'
    float height; // в метрах
} Person;

// Прототипы функций
void clear_input_buffer();
void add_person(Person people[], int *count);
void save_to_file(Person people[], int count, char *filepath);
int read_from_file(Person people[], char *filepath);
void print_people(Person people[], int count);
int compare_people(Person a, Person b, int fields[], int orders[], int num_fields);
void parse_sort_criteria(char *input, int fields[], int orders[], int *num_fields);
void sort_people(Person people[], int count, int fields[], int orders[], int num_fields);
int input_from_console(Person people[]);
int input_from_file(Person people[]);

int main() {
    Person people[MAX_RECORDS];
    int count = 0;
    int choice;
    char input[100];
    int sort_fields[10] = {0};
    int sort_orders[10] = {0};
    int num_fields = 0;
    
    printf("=== Program for working with people data ===\n\n");
    
    // Выбор способа ввода
    printf("Select input method:\n");
    printf("1. Input from console\n");
    printf("2. Input from file\n");
    printf("Your choice: ");
    scanf("%d", &choice);
    clear_input_buffer();
    
    switch(choice) {
        case 1:
            count = input_from_console(people);
            break;
        case 2:
            count = input_from_file(people);
            break;
        default:
            printf("Invalid choice. Using console input by default.\n");
            count = input_from_console(people);
    }
    
    if (count == 0) {
        printf("No data to process. Program terminated.\n");
        return 0;
    }
    
    printf("\nLoaded data:\n");
    print_people(people, count);
    
    // Запрашиваем критерии сортировки
    printf("\n=== Sorting settings ===\n");
    printf("Enter fields for sorting (space-separated):\n");
    printf("1 - Birth year\n");
    printf("2 - First/Last name\n");
    printf("3 - Gender\n");
    printf("4 - Height\n");
    printf("After each field specify direction (0 - ascending, 1 - descending)\n");
    printf("Example: 1 0 2 1 3 0\n");
    printf("Your input: ");
    
    fgets(input, sizeof(input), stdin);
    
    // Парсим введенные критерии
    parse_sort_criteria(input, sort_fields, sort_orders, &num_fields);
    
    if (num_fields == 0) {
        printf("Could not recognize sorting criteria. Using sorting by birth year.\n");
        sort_fields[0] = 1;
        sort_orders[0] = 0;
        num_fields = 1;
    }
    
    // Сортируем данные
    sort_people(people, count, sort_fields, sort_orders, num_fields);
    
    // Выводим результат
    printf("\n=== Sorted data ===\n");
    print_people(people, count);
    
    // Сохраняем отсортированные данные
    save_to_file(people, count, SORTED_FILE_PATH);
    printf("\nSorted data saved to file: %s\n", SORTED_FILE_PATH);
    
    return 0;
}

// Ввод данных с консоли
int input_from_console(Person people[]) {
    int count = 0;
    char choice;
    
    printf("\n=== Console Input ===\n");
    do {
        printf("\n--- Adding a new person ---\n");
        add_person(people, &count);
        
        printf("\nDo you want to add another person? (y/n): ");
        scanf(" %c", &choice);
        clear_input_buffer();
        
    } while (tolower(choice) == 'y' && count < MAX_RECORDS);
    
    if (count > 0) {
        // Сохраняем в файл на рабочем столе
        save_to_file(people, count, FILE_PATH);
        printf("\nData saved to file: %s\n", FILE_PATH);
    }
    
    return count;
}

// Ввод данных из файла
int input_from_file(Person people[]) {
    char filename[MAX_NAME];
    char full_path[MAX_PATH];
    int count;
    
    printf("\n=== File Input ===\n");
    printf("Enter filename (e.g., people.txt): ");
    fgets(filename, sizeof(filename), stdin);
    filename[strcspn(filename, "\n")] = 0; // Удаляем символ новой строки
    
    // Формируем полный путь к файлу на рабочем столе
    snprintf(full_path, sizeof(full_path), "C:\\Users\\Hp\\Desktop\\%s", filename);
    
    // Пытаемся прочитать файл
    count = read_from_file(people, full_path);
    
    if (count > 0) {
        printf("\nSuccessfully loaded %d records from %s\n", count, full_path);
        return count;
    } else {
        printf("\nFailed to load file. Make sure the file exists and is in correct format.\n");
        return 0;
    }
}

// Очистка буфера ввода
void clear_input_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// Добавление нового человека
void add_person(Person people[], int *count) {
    Person new_person;
    char temp[MAX_NAME];
    
    printf("Enter first name: ");
    fgets(new_person.name, MAX_NAME, stdin);
    new_person.name[strcspn(new_person.name, "\n")] = 0;
    
    printf("Enter last name: ");
    fgets(temp, MAX_NAME, stdin);
    temp[strcspn(temp, "\n")] = 0;
    
    // Объединяем имя и фамилию
    strcat(new_person.name, " ");
    strcat(new_person.name, temp);
    
    printf("Enter birth year: ");
    while (scanf("%d", &new_person.birth_year) != 1 || new_person.birth_year < 1900 || new_person.birth_year > 2024) {
        printf("Error! Enter a valid year (1900-2024): ");
        clear_input_buffer();
    }
    clear_input_buffer();
    
    printf("Enter gender (M/F): ");
    scanf(" %c", &new_person.gender);
    new_person.gender = toupper(new_person.gender);
    while (new_person.gender != 'M' && new_person.gender != 'F') {
        printf("Error! Enter M or F: ");
        scanf(" %c", &new_person.gender);
        new_person.gender = toupper(new_person.gender);
    }
    clear_input_buffer();
    
    printf("Enter height in meters (e.g., 1.75): ");
    while (scanf("%f", &new_person.height) != 1 || new_person.height < 0.5 || new_person.height > 2.5) {
        printf("Error! Enter a valid height (0.5-2.5): ");
        clear_input_buffer();
    }
    clear_input_buffer();
    
    people[*count] = new_person;
    (*count)++;
    printf("Person successfully added!\n");
}

// Сохранение в файл по указанному пути
void save_to_file(Person people[], int count, char *filepath) {
    FILE *file = fopen(filepath, "w");
    if (file == NULL) {
        printf("Error creating file %s!\n", filepath);
        printf("Please check if the path exists and you have write permissions.\n");
        return;
    }
    
    for (int i = 0; i < count; i++) {
        fprintf(file, "%s %d %c %.2f\n", 
                people[i].name, 
                people[i].birth_year, 
                people[i].gender, 
                people[i].height);
    }
    
    fclose(file);
}

// Чтение из файла
int read_from_file(Person people[], char *filepath) {
    FILE *file = fopen(filepath, "r");
    if (file == NULL) {
        return 0;
    }
    
    int count = 0;
    char line[200];
    
    while (fgets(line, sizeof(line), file) && count < MAX_RECORDS) {
        char *token;
        
        // Удаляем символ новой строки
        line[strcspn(line, "\n")] = 0;
        
        // Парсим строку (формат: "Имя Фамилия Год Пол Рост")
        token = strtok(line, " ");
        if (token == NULL) continue;
        
        // Копируем имя
        strcpy(people[count].name, token);
        
        // Добавляем фамилию
        token = strtok(NULL, " ");
        if (token == NULL) continue;
        strcat(people[count].name, " ");
        strcat(people[count].name, token);
        
        // Читаем год
        token = strtok(NULL, " ");
        if (token == NULL) continue;
        people[count].birth_year = atoi(token);
        
        // Читаем пол
        token = strtok(NULL, " ");
        if (token == NULL) continue;
        people[count].gender = token[0];
        
        // Читаем рост
        token = strtok(NULL, " ");
        if (token == NULL) continue;
        people[count].height = atof(token);
        
        count++;
    }
    
    fclose(file);
    return count;
}

// Вывод данных
void print_people(Person people[], int count) {
    if (count == 0) {
        printf("No data to display.\n");
        return;
    }
    
    printf("\n%-30s %-12s %-6s %-8s\n", "Full Name", "Birth Year", "Gender", "Height(m)");
    printf("--------------------------------------------------------\n");
    
    for (int i = 0; i < count; i++) {
        printf("%-30s %-12d %-6c %-8.2f\n", 
               people[i].name, 
               people[i].birth_year, 
               people[i].gender, 
               people[i].height);
    }
}

// Функция сравнения для сортировки
int compare_people(Person a, Person b, int fields[], int orders[], int num_fields) {
    for (int i = 0; i < num_fields; i++) {
        int result = 0;
        
        switch (fields[i]) {
            case 1: // Год рождения
                result = a.birth_year - b.birth_year;
                break;
            case 2: // Имя/Фамилия
                result = strcmp(a.name, b.name);
                break;
            case 3: // Пол
                result = a.gender - b.gender;
                break;
            case 4: // Рост
                if (a.height < b.height) result = -1;
                else if (a.height > b.height) result = 1;
                else result = 0;
                break;
        }
        
        if (result != 0) {
            return orders[i] ? -result : result;
        }
    }
    
    return 0;
}

// Парсинг критериев сортировки
void parse_sort_criteria(char *input, int fields[], int orders[], int *num_fields) {
    char *token;
    int count = 0;
    int temp[20];
    
    token = strtok(input, " \n");
    while (token != NULL && count < 20) {
        temp[count] = atoi(token);
        count++;
        token = strtok(NULL, " \n");
    }
    
    *num_fields = count / 2;
    for (int i = 0; i < *num_fields; i++) {
        fields[i] = temp[i*2];
        orders[i] = temp[i*2 + 1];
    }
}

// Сортировка данных (пузырьковая сортировка)
void sort_people(Person people[], int count, int fields[], int orders[], int num_fields) {
    for (int i = 0; i < count - 1; i++) {
        for (int j = 0; j < count - i - 1; j++) {
            if (compare_people(people[j], people[j + 1], fields, orders, num_fields) > 0) {
                // Меняем элементы местами
                Person temp = people[j];
                people[j] = people[j + 1];
                people[j + 1] = temp;
            }
        }
    }
}