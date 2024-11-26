#include "../hdrs.h"

int menuInterface(){
	char prompt[MAX_PROMPT_LENGTH];
	int choice;

	while (1) {
		printf("\nLlama API Client\n");
		printf("1. Send prompt (save json & show)\n");
		printf("2. Send prompt (just show)\n");
		printf("3. Exit program\n");
		printf("Enter your choice: ");
		scanf("%d", &choice);
		getchar();  // Consume newline :o

		switch (choice) {
			case 1:
				printf("Enter your prompt: ");
				fgets(prompt, MAX_PROMPT_LENGTH, stdin);
				prompt[strcspn(prompt, "\n")] = 0;  // no le entiendo a esta linea
				sendPromptAndSave(prompt);
				break;
			case 2:
				printf("Enter your prompt: ");
				fgets(prompt, MAX_PROMPT_LENGTH, stdin);
				prompt[strcspn(prompt, "\n")] = 0;  // no le entiendo a esta linea
				justSendPrompt(prompt);
				break;
			case 3:
				printf("Exiting program. Goodbye!\n");
				return 0;
			default:
				printf("Invalid choice. I'm sorry\n exiting...\n");
				exit(1);
		}
	}

}

