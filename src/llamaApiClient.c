#include "../hdrs.h"

static size_t writeMemoryCallback(void *contents, size_t size, size_t nmemb, void *userp) {
	size_t realsize = size * nmemb;
	memoryStruct *mem = (memoryStruct *)userp;

	char *ptr = realloc(mem->memory, mem->size + realsize + 1);
	if (!ptr) {
		printf("Not enough memory (realloc returned NULL)\n");
		return 0;
	}

	mem->memory = ptr;
	memcpy(&(mem->memory[mem->size]), contents, realsize);
	mem->size += realsize;
	mem->memory[mem->size] = 0;

	return realsize;
}

void saveResponseToJson(const char *response) {
	cJSON *json = cJSON_Parse(response);
	if (json == NULL) {
		const char *errorPtr = cJSON_GetErrorPtr();
		if (errorPtr != NULL) {
			fprintf(stderr, "Error parsing JSON: %s\n", errorPtr);
		}
		return;
	}

	char filename[64];
	snprintf(filename, sizeof(filename), "response_%ld.json", time(NULL));

	FILE *file = fopen(filename, "w");
	if (file == NULL) {
		fprintf(stderr, "Error opening file for writing\n");
		cJSON_Delete(json);
		return;
	}

	char *printedJson = cJSON_Print(json);
	fprintf(file, "%s", printedJson);
	fclose(file);

	printf("Response saved to %s\n", filename);

	free(printedJson);
	cJSON_Delete(json);
}

const char* getApiKey() {
	const char* apiKey = getenv(API_KEY_ENV);
	if (apiKey == NULL) {
		fprintf(stderr, "Error: LLAMA_API_KEY environment variable not set.\n");
		exit(1);
	}
	return apiKey;
}

int justSendPrompt(const char *prompt){
	CURL *curl;
	CURLcode res;
	memoryStruct chunk;

	chunk.memory = malloc(1);
	chunk.size = 0;

	curl_global_init(CURL_GLOBAL_ALL);
	curl = curl_easy_init();

	if (curl) {
		struct curl_slist *headers = NULL;
		headers = curl_slist_append(headers, "Content-Type: application/json");
		char authHeader[256];
		snprintf(authHeader, sizeof(authHeader), "Authorization: Bearer %s", getApiKey());
		headers = curl_slist_append(headers, authHeader);

		cJSON *root = cJSON_CreateObject();
		cJSON_AddStringToObject(root, "model", "llama3-8b-8192");
		cJSON *messages = cJSON_AddArrayToObject(root, "messages");
		cJSON *message = cJSON_CreateObject();
		cJSON_AddStringToObject(message, "role", "user");
		cJSON_AddStringToObject(message, "content", prompt);
		cJSON_AddItemToArray(messages, message);

		char *jsonStr = cJSON_Print(root);

		curl_easy_setopt(curl, CURLOPT_URL, API_URL);
		curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
		curl_easy_setopt(curl, CURLOPT_POSTFIELDS, jsonStr);
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeMemoryCallback);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)&chunk);

		res = curl_easy_perform(curl);

		if (res != CURLE_OK) {
			fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
		} else {
			printf("Response from API:\n%s\n", chunk.memory);
			//saveResponseToJson(chunk.memory);
		}

		curl_easy_cleanup(curl);
		curl_slist_free_all(headers);
		free(jsonStr);
		cJSON_Delete(root);
	}

	free(chunk.memory);
	curl_global_cleanup();


	return 0;
}

int sendPromptAndSave(const char *prompt) {
	CURL *curl;
	CURLcode res;
	memoryStruct chunk;

	chunk.memory = malloc(1);
	chunk.size = 0;

	curl_global_init(CURL_GLOBAL_ALL);
	curl = curl_easy_init();

	if (curl) {
		struct curl_slist *headers = NULL;
		headers = curl_slist_append(headers, "Content-Type: application/json");
		char authHeader[256];
		snprintf(authHeader, sizeof(authHeader), "Authorization: Bearer %s", getApiKey());
		headers = curl_slist_append(headers, authHeader);

		cJSON *root = cJSON_CreateObject();
		cJSON_AddStringToObject(root, "model", "llama3-8b-8192");
		cJSON *messages = cJSON_AddArrayToObject(root, "messages");
		cJSON *message = cJSON_CreateObject();
		cJSON_AddStringToObject(message, "role", "user");
		cJSON_AddStringToObject(message, "content", prompt);
		cJSON_AddItemToArray(messages, message);

		char *jsonStr = cJSON_Print(root);

		curl_easy_setopt(curl, CURLOPT_URL, API_URL);
		curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
		curl_easy_setopt(curl, CURLOPT_POSTFIELDS, jsonStr);
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeMemoryCallback);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)&chunk);

		res = curl_easy_perform(curl);

		if (res != CURLE_OK) {
			fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
		} else {
			printf("Response from API:\n%s\n", chunk.memory);
			saveResponseToJson(chunk.memory);
		}

		curl_easy_cleanup(curl);
		curl_slist_free_all(headers);
		free(jsonStr);
		cJSON_Delete(root);
	}

	free(chunk.memory);
	curl_global_cleanup();

	return 0;
}

