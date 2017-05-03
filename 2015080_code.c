// Ronak Kumar (2015080)

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
char command[50];
char temp[50];
char byte_array[50];
struct Node
{
	int size;
	int* ptr_address;
	struct Node* next;
};
void initialize()
{
	for(int i = 0; i < 50; i++)
	{
		command[i] = 0;
		temp[i] = 0;
		byte_array[i] = 0;
	}
}
void handle_malloc_call(struct Node** head, int num_bytes)
{
	struct Node* temp = (struct Node*)malloc(sizeof(struct Node));
	int* address = (int*)malloc(num_bytes);
	temp->size = num_bytes;
	temp->ptr_address = address;
	temp->next = NULL;
	struct Node* last = *head;
	if(*head == NULL)
	{
		*head = temp;
		return;
	}
	while(last->next != NULL)
		last = last->next;
	last->next = temp;
	return;
}
void handle_free_call(struct Node** head, int index)
{
	if(*head == NULL)
		return;
	struct Node* temp = *head;
	if(index == 0)
	{
		*head = temp->next;
		free(temp);
		return;
	}	
	for(int i = 0; temp != NULL && i < index-1; i++)
		temp = temp->next;
	if(temp == NULL || temp->next == NULL)
		return;
	struct Node* next = temp->next->next;
	free(temp->next);
	temp->next = next;
	return;
}
void print_list(struct Node* head)
{
	struct Node* temp = head;
	printf("---------------------------------------------------------\n");
	while(temp != NULL)
	{
		printf("Size is : %d\t Address is : %p            |\n", temp->size, temp->ptr_address);
		temp = temp->next;
	}
	printf("---------------------------------------------------------\n");
	return;
}
int main(void)
{
	struct Node* head = NULL;
	while(1)
	{
		initialize();
		printf("$:> ");
		fgets(command, 50, stdin);
		int i = 0;
		int k = 0;
		if(command[0] == 'p')
			print_list(head);
		else if(command[0] == 'q')
			exit(0);
		else
		{
			for(i = 0; command[i] != ' '; i++)
				temp[i] = command[i];
			for(int j = i+1; j < strlen(command); j++)
				byte_array[k++] = command[j];
			int bytes_or_index = atoi(byte_array);
			if(!strcmp(temp, "malloc"))
				handle_malloc_call(&head, bytes_or_index);
			else if(!strcmp(temp, "free"))
				handle_free_call(&head, bytes_or_index-1);
			else
				printf("Wrong Command Error\n");
		}
	}
	return 0;
}