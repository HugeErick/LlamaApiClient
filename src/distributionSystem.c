#include "../hdrs.h"

void set_environment_variable(void) {
#ifdef _WIN32
    system("set_env_windows.bat");
#elif __APPLE__
    system("bash set_env_mac.sh");
#elif __linux__
    system("bash set_env_unix.sh");
#else
    fprintf(stderr, "Unsupported operating system\n");
    exit(1);
#endif
}
