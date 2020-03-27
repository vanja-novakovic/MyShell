#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif
#pragma warning(disable: 6031)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <direct.h>

#define MAX_SIZE 200
int repeated_login_or_exit(int value_login_command); //used for login or exit, no other options until user is logged in
int login_command(char* username, char* password); //looking for account in file and sending message about login
void current_directory(); //output is current directory
int repeated_commands(int value_login_command); // used for all commands after user is logged in, ex. where, logout, go, print, etc.
int prefix(const char* string, const char* prefix); // checks if second parameter is prefix of the first 
//char* input_command_std(); 
int contains(char* string, char ch); //checks if a string contains character
char* extract_string(char* longer_string, char* shorter_string); //moving shorter string from longer, but its its prefix
int check_format(char* command);  // checks if its txt for command find
char* get_text(char* command); //get text for command find
char* get_file_name(char* command); // get file name for command find

int prefix(const char* string, const char* prefix)
{
    return strncmp(prefix, string, strlen(prefix)) == 0;
}

void current_directory()
{
    ///user is now logged in, so the output should also be current folder
    char* current_dir = malloc(sizeof(char) * MAX_SIZE);
    _getcwd(current_dir, MAX_SIZE);
    printf("\nYour current directory: %s\n", current_dir);
    return;
}
int login_command(char* username, char* password)
{
    FILE* user_data = fopen("user_data.txt", "r");
    char* tmp_username = malloc(sizeof(char) * MAX_SIZE);
    char* tmp_password = malloc(sizeof(char) * MAX_SIZE);

    if (user_data != NULL)
    {
        while (fscanf(user_data, "%s %s", tmp_username, tmp_password) != EOF)
            if (tmp_password != NULL && tmp_username != NULL && strcmp(tmp_username, username) == 0 && strcmp(tmp_password, password) == 0)
            {
                printf("Successfull login!");
                current_directory();
                return 0;
            }
    }
    return -1;
}
int repeated_login_or_exit(int value_login_command)
{
    char* input_command = malloc(sizeof(char) * MAX_SIZE);
    char* username = malloc(sizeof(char) * MAX_SIZE);
    char* password = malloc(sizeof(char) * MAX_SIZE);

    while (value_login_command == -1)
    {
        printf("Try again by entering 'login' to log in or 'exit' to exit the App.\n Your command: ");
        scanf("%s", input_command);
        if (input_command != NULL)
            if (strcmp(input_command, "exit") == 0)
            {
                printf("Thank you for using this App! ");
                return 0; //closing app
            }

            else if (strcmp(input_command, "login") == 0)
            {
                printf("Username: ");
                scanf("%s", username);
                printf("Password: ");
                scanf("%s", password);
                value_login_command = login_command(username, password);
            }
    }
    return 1;
}

int repeated_commands(int value_login_command)
{
    char input_command[MAX_SIZE];
    while (value_login_command == 0)  ///user is logged in and all commands are available
    {
        if (fgets(input_command, MAX_SIZE, stdin) != NULL)
        {
            ///WHERE
            if (strcmp(input_command, "where") == 0)
            {
                current_directory();
            }
            ///GO
            else if (prefix(input_command, "go ") == 1)
            {
                int i = 0;
                char path[MAX_SIZE];
                int path_len = strlen(input_command) - 3;
                if (path != NULL)
                    for (i = 0; i < path_len; i++)
                        path[i] = input_command[3 + i];
                path[i] = '\0';
                printf("%s", path);
                printf("\n%s\n", input_command);
                _chdir(path);
                current_directory();
                value_login_command = -1;
            }
            else
            {
                printf("Invalid command.");
                value_login_command = -1;
            }
        }
    }
}

int main()
{
    char* input_command = malloc(sizeof(char) * MAX_SIZE);

    printf("Welcome to simple Shell App!\n Please start with your commands: ");
    scanf("%s", input_command);
    if (input_command != NULL)
        while (strcmp(input_command, "login") != 0)
        {
            if (strcmp(input_command, "exit") == 0)
                return 0; // exit the app
            printf("Sorry, you should log in using command 'login'!\n Try again: "); // wrong command
            scanf("%s", input_command);
        }
    char* username = malloc(sizeof(char) * MAX_SIZE);
    char* password = malloc(sizeof(char) * MAX_SIZE);

    printf("Username: ");
    scanf("%s", username);
    printf("Password: ");
    scanf("%s", password);

    int value_login_command = login_command(username, password);
    if (value_login_command == -1) // wrong login
    {
        printf("Unsuccessful login! ");
        repeated_login_or_exit(value_login_command); //repeat input until its exit or successful login
    }

    repeated_commands(value_login_command); // now you can use all other possible commands because you are logged in

    return 0;
}