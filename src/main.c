#include "../hdrs.h"

int main(void) {
    if (getenv("GROG_CLOUD_API_DEV_TOKEN") == NULL) {
        printf("GROG_CLOUD_API_DEV_TOKEN is not set. Let's set it up.\n");
        set_environment_variable();
    }
    return menuInterface();
}
