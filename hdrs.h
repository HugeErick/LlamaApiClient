#ifndef LLAMA_API_CLIENT_H
#define LLAMA_API_CLIENT_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>
#include <cjson/cJSON.h>
#include <time.h>

#define MAX_PROMPT_LENGTH 1000
#define API_URL "https://api.groq.com/openai/v1/chat/completions"
#define API_KEY_ENV "GROG_CLOUD_API_DEV_TOKEN"

// Struct definitions
typedef struct memoryStruct {
    char *memory;
    size_t size;
} memoryStruct;

// Function declarations
void saveResponseToJson(const char *response);
const char* getApiKey(void);
int justSendPrompt(const char *prompt);
int sendPromptAndSave(const char *prompt);
int menuInterface(void);
void set_environment_variable(void);

#endif // LLAMA_API_CLIENT_H
