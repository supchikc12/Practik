#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

//Структура для хранения данных о человеке
typedef struct{
	char surname [50];
	char name [50];
	char patronymic [50];
	int birthDay;	
} Person;

//Очистка старых символов
void removeNewLine(char *str){
	int len = strlen(str);
	if (len > 0 && str[len - 1] == '\n'){
		str[len-1] = '\0';
	}
}

//Чтение данных иp файла и запись в новый файл
int readPeopleFromFile(const char *fileName, const char *fileResult){
	
	FILE *file;
    FILE *result;
	
	char line[256];
	
	Person person;
	
	file = fopen(fileName,"r");
	
	
	if (file == NULL) {
        printf("Error open file!\n");
        return;
    }
    
    fileResult = fopen(fileResult,"w");
    if (fileResult == NULL) {
        printf("Error create file %s!\n", fileResult);
        fclose(file);
        return;
    }
	
	while (fgets(line, sizeof(line), file) != NULL) {
        
        // Удаляем символ новой строки
        line[strcspn(line, "\n")] = 0;
        
        char *token = strtok(line, " ");
        if (token != NULL)
        {
        	token = strcpy(person.surname, token);
        	
        	token = strtok(NULL, " ");
        	strcpy(person.name, token);
        	
        	token = strtok(NULL, " ");
			strcpy(person.patronymic, token);
        	
        	token = strtok(NULL, " ");
        	person.birthDay = atoi(token);
        	
        	if (person.birthDay > 1980)
        	{
        		fprintf(fileResult, "%s %s %s %d\n", 
                        person.surname, 
                        person.name, 
                        person.patronymic, 
                        person.birthDay);
			}        	
		}
    }
	
	
	fclose(file);
    fclose(fileResult); 
    return 1;
}

int main(int argc, char *argv[]) {
    
    const char *fileName = "C:\\Users\\Hp\\Desktop\\Test.txt"; 
    const char *fileResult = "C:\\Users\\Hp\\Desktop\\Result.txt";
    
    readPeopleFromFile(fileName, fileResult);
    
    getchar();
    
	return 0;
}