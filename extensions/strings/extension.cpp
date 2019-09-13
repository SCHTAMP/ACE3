#include <string>
#include "shared.hpp"

#include "ace_break_line.hpp"
#include "ace_parse_imagepath.hpp"

extern "C" {
    __declspec(dllexport) void __stdcall RVExtension(char* output, int outputSize, const char* function);
    __declspec(dllexport) int __stdcall RVExtensionArgs(char* output, int outputSize, const char* function, const char** argv, int argc);
    __declspec(dllexport) void __stdcall RVExtensionVersion(char* output, int outputSize);
}

void __stdcall RVExtensionVersion(char* output, int outputSize) {
    strncpy(output, ACE_FULL_VERSION_STR, outputSize);
}

void __stdcall RVExtension(char* output, int outputSize, const char* function) {
    if (!strcmp(function, "version")) {
        RVExtensionVersion(output, outputSize);
        return;
    }
    strncpy(output, "error", outputSize);
}

int __stdcall RVExtensionArgs(char* output, int outputSize, const char* function, const char** args, int argsCnt) {
    if (!strcmp(function, "breakLine")) {
        if (argsCnt != 1) { return -1002; } // Error: wrong arg count
        const char* input = args[0];
        std::string outputStr = addLineBreaks(splitString(input));
        strncpy(output, outputStr.c_str(), outputSize);
        return 0;
    };
    if (!strcmp(function, "getImagePath")) {
        if (argsCnt != 1) { return -1002; } // Error: wrong arg count
        const char* input = args[0];
        std::string outputStr = getImagePathFromStructuredText(input);
        strncpy(output, outputStr.c_str(), outputSize);
        return 0;
    };
    if (!strcmp(function, "version")) {
        RVExtensionVersion(output, outputSize);
        return 0;
    }
    strncpy(output, "invalid function", outputSize);
    return -1001; // bad function
};
