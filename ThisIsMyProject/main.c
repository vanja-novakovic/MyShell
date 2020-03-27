#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif
#pragma warning(disable: 6031)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <direct.h>

#define MAX_SIZE 200
int repeat_login(int value_login_command); //used for login or exit, no other options until user is logged in
int login(char* username, char* password); //looking for account in file and sending message about login
void current_directory(); //output is current directory
int execute_command(int value_login_command, char* username); // used for all commands after user is logged in, ex. where, logout, go, print, etc.
int prefix(const char* string, const char* prefix); // checks if second parameter is prefix of the first 
//char* input_command_std(); 
int contains(char* string, char ch); //checks if a string contains character
char* extract_string(char* longer_string, char* shorter_string); //moving shorter string from longer, but its its prefix
int check_format(char* command);  // checks if its txt for command find
char* get_text(char* command); //get text for command find
char* get_file_name(char* command); // get file name for command find
char* read_from_stdin(char* buffer);
void write_message(char* message, char* additional_parameter);
void where();
void go(char*);
void nop();

void write_message(char* message, char* additional_parameter)
{
	printf(message, additional_parameter);
	//getchar();
}

int prefix(const char* string, const char* prefix)
{
	return strncmp(prefix, string, strlen(prefix)) == 0;
}
char* read_from_stdin(char* buffer) {
	if (fgets(buffer, MAX_SIZE, stdin) != NULL)
	{
		size_t len = strlen(buffer);
		if (len > 0 && buffer[len - 1] == '\n')
			buffer[--len] = '\0';
		return strcmp(buffer, "") == NULL ? NULL : buffer;
	}
	return NULL;
}
char* extract_string(char* longer_string, char* shorter_string)
{
	int n = strlen(longer_string), m = strlen(shorter_string);
	int i, k = m;
	char new_string[MAX_SIZE] = { 0 };
    //char* new_string = malloc(sizeof(char) * (n - m));
	for (i = 0; i < n - m; i++)
		new_string[i] = longer_string[k++];
	new_string[i] = '\0';
	printf("%s", new_string);
	return new_string;
};
int contains(char* string, char ch)
{
	for (int i = 0; string[i] != '\0'; i++)
		if (string[i] == ch)
			return 1;
	return 0;
}
void current_directory()
{
	// User is now logged in, so the output should also be the current folder
	char* current_dir = malloc(sizeof(char) * MAX_SIZE);
	_getcwd(current_dir, MAX_SIZE);
	write_message("\nYour current directory: %s\n", current_dir);
	free(current_dir);
	return;
}
int login(char* username, char* password)
{
	FILE* user_data = fopen("user_data.txt", "r");
	char* tmp_username = malloc(sizeof(char) * MAX_SIZE);
	char* tmp_password = malloc(sizeof(char) * MAX_SIZE);

	if (user_data != NULL)
	{
		while (fscanf(user_data, "%s %s", tmp_username, tmp_password) != EOF)
			if (tmp_password != NULL && tmp_username != NULL && strcmp(tmp_username, username) == 0 && strcmp(tmp_password, password) == 0)
			{
				write_message("Successfull login!\n", "");
				current_directory();
				return 0;
			}
	}
	free(tmp_username);
	free(tmp_password);
	return -1;
}
int repeat_login(int value_login_command)
{
	char* input_command = malloc(sizeof(char) * MAX_SIZE);
	char* username = malloc(sizeof(char) * MAX_SIZE);
	char* password = malloc(sizeof(char) * MAX_SIZE);

	while (value_login_command == -1)
	{
		printf("Try again by entering 'login' to log in or 'exit' to exit the App.\n Your command: ");
		read_from_stdin(input_command);
		//scanf("%s", input_command);
		if (input_command != NULL)
			if (strcmp(input_command, "exit") == 0)
			{
				printf("Thank you for using this App! ");
				return 0; //closing app
			}

			else if (strcmp(input_command, "login") == 0)
			{
				printf("Username: ");
				read_from_stdin(username);
				printf("Password: ");
				read_from_stdin(password);
				value_login_command = login(username, password);
			}
	}
	free(input_command);
	free(username);
	free(password);
	return 1;
}
void where()
{
	current_directory();
}
void go(char* input_command)
{
	int i = 0;
	char path[MAX_SIZE];
	size_t path_len = strlen(input_command) - 3;
	if (path != NULL)
		for (i = 0; i < path_len; i++)
			path[i] = input_command[3 + i];
	path[i] = '\0';
	_chdir(path);
	current_directory();
}
void create(char* input_command)
{
		/*char* path = malloc(sizeof(char) * MAX_SIZE);
		if (prefix(input_command, "create [-d] ")) ///create directorium, folder
		{
			if (!contains(input_command, '\\'))///znaci da je navedena nova putanja
			{
				if (path != NULL)
				{
					strcpy(path, extract_string(input_command, "create [-d] "));
					_mkdir(path);
				}
			}
			else ///trebamo napraviti u ovom folderu
			{
				char* current_dir = malloc(sizeof(char) * MAX_SIZE);
				if (current_dir != NULL)
				{
					strcat(current_dir, extract_string(input_command, "create [-d] "));
					_mkdir(current_dir);
				}

			}
		}
		else if (prefix(input_command, "create "))///create file, datoteka
		{
			FILE* new_file;
			char* name = malloc(sizeof(char) * MAX_SIZE);
			if (!contains(input_command, '\\')) ///pravice se novi path
			{
				if (path != NULL && name!=NULL)
				{
					strcpy(path, extract_string(input_command, "create "));
					char* current_dir = malloc(sizeof(char) * MAX_SIZE);
					_getcwd(current_dir, MAX_SIZE);
					_chdir(path);
					strcpy(name, extract_string(input_command, "create "));
					new_file = fopen(name, "w");
					fclose(new_file);
					if(current_dir!=NULL)
					_chdir(current_dir);
				}
				
			}
			else
			{
				if (name != NULL)
				{
					strcpy(name, extract_string(input_command, "create "));
					new_file = fopen(name, "w");
				}
				
				fclose(new_file);
			}
		}
		else printf("Invalid command!");*/
}

void nop() 
{
	return;
}
void write_colored(char* username)
{
	printf("\033[0;35m#%s$", username);
	printf("\033[0m");
	return;
}
int execute_command(int is_logged_in, char* username)
{
	char input_command[MAX_SIZE];
	while (is_logged_in == 0)  // User is logged in and all of the commands are available
	{
		
		write_colored(username);
		if (read_from_stdin(input_command) != NULL)
		{
			// WHERE
			if (strcmp(input_command, "where") == 0)
				where();
			// GO
			else if (prefix(input_command, "go ") == 1)
				go(input_command);
			// CREATE
			else if (prefix(input_command, "create ") == 1)
				create(input_command);
			else if (strcmp(input_command, "") == 0)
				nop();
			else
				write_message("Invalid command.\n", "");
		}
	}
	return 1;
}

int main()
{
	char* input_command = malloc(sizeof(char) * MAX_SIZE);

	printf("Welcome to simple Shell App!\n Please start with your commands: ");
	read_from_stdin(input_command);
	if (input_command != NULL)
		while (strcmp(input_command, "login") != 0)
		{
			if (strcmp(input_command, "exit") == 0)
				return 0; // Exit the app
			printf("Sorry, you should log in using command 'login'!\n Try again: "); // wrong command
			read_from_stdin(input_command);
		}
	char* username = malloc(sizeof(char) * MAX_SIZE);
	char* password = malloc(sizeof(char) * MAX_SIZE);

	printf("Username: ");
	read_from_stdin(username);
	printf("Password: ");
	read_from_stdin(password);

	int login_result = login(username, password);
	if (login_result == -1) // Wrong login
	{
		printf("Unsuccessful login! ");
		repeat_login(login_result); // Repeat input until its exit or successful login
	}
	while (1)
		execute_command(login_result, username); // Now you can use all other possible commands because you are logged in
	free(input_command);
	free(username);
	free(password);
	return 0;
}