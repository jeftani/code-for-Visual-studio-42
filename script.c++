#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <sys/stat.h>
#include <fstream>
#include <iostream>
#include <chrono>
#include <thread>

// ANSI escape codes for text color
#define RESET_COLOR "\033[0m"
#define RED_TEXT "\033[31m"
#define GREEN_TEXT "\033[32m"
#define YELLOW_TEXT "\033[33m"
#define BLUE_TEXT "\033[34m"

#define print(x,y) std::cout << x << y <<std::endl;

#ifdef _WIN32
#include <direct.h>
#include <io.h>
#define mkdir(dir, mode) _mkdir(dir)
#define access _access
#define PATH_SEPARATOR ";"
#else
#include <unistd.h>
#define PATH_SEPARATOR ":"
#endif



void printYellowLink(const std::string& text, const std::string& url) {
    // ANSI escape code for yellow text
    const std::string yellowColor = "\033[33m";

    // ANSI escape code for resetting text color
    const std::string resetColor = "\033[0m";

    // Print the clickable link with yellow text
    std::cout << yellowColor << "[" << text << "](" << url << ")" << resetColor << std::endl;
}

void loadingAnimation(int durationSeconds) {
    int totalFrames = durationSeconds * 10; // Adjust for the desired animation speed
    for (int frame = 0; frame < totalFrames; ++frame) {
        int barWidth = 20;
        int position = frame % (2 * barWidth - 1);

        // Print the loading bar
        std::cout << "[";
        for (int i = 0; i < barWidth; ++i) {
            if (i <= position && i + barWidth > position) {
                std::cout << "=";
            } else {
                std::cout << " ";
            }
        }
        std::cout << "] " << (frame * 103) / totalFrames << "%";
        std::cout << std::flush;  // Ensure immediate output

        // Pause for a short duration to create the animation effect
        std::this_thread::sleep_for(std::chrono::milliseconds(100));

        // Move the cursor back to the beginning of the line
        std::cout << "\r";
    }

    // Print a newline after the animation is complete
    std::cout << std::endl;
}




bool directoryExists(const std::string& directory) {
    struct stat info;
    return stat(directory.c_str(), &info) == 0 && S_ISDIR(info.st_mode);
}

bool fileExists(const std::string& filename) {
    return access(filename.c_str(), F_OK) == 0;
}

bool moveFile(const std::string& source, const std::string& destination) {
    if (rename(source.c_str(), destination.c_str()) == 0) {
        print("File moved successfully.",GREEN_TEXT);
        //std::cout << "File moved successfully." << std::endl;
        return true;
    } else {
        print("Failed to move the file.",RED_TEXT);
        //std::cerr << "Failed to move the file." << std::endl;
        return false;
    }
}

bool addToShellConfig(const std::string& shell, const std::string& binPath) {
    // Get the home directory
    const char* homeDirectory = getenv("HOME");

    if (homeDirectory == nullptr) {
        std::cerr << "Unable to determine home directory..." << RED_TEXT << std::endl;
        return false;
    }

    // Construct the path to the shell configuration file
    std::string configFilePath;
    if (shell == "zsh") {
        configFilePath = std::string(homeDirectory) + "/.zshrc";
    } else if (shell == "bash") {
        configFilePath = std::string(homeDirectory) + "/.bashrc";
    } else {
        // Add support for other shells as needed
        std::cerr << "Unsupported shell. Please add support for your shell." << RED_TEXT << std::endl;
        return false;
    }

    // Check if the shell configuration file exists
    if (!fileExists(configFilePath)) {
        std::cerr << "Shell configuration file not found: " << RED_TEXT <<configFilePath << std::endl;
        return false;
    }

    // Open the shell configuration file in append mode
    std::ofstream configFileStream(configFilePath, std::ios::app);

    if (!configFileStream.is_open()) {
        std::cerr << "Failed to open shell configuration file: " << RED_TEXT << configFilePath << std::endl;
        return false;
    }

    // Add the export command to the shell configuration file
    configFileStream << "\nexport PATH=\"" << binPath << ":$PATH\"\n";

    // Close the file stream
    configFileStream.close();

    std::cout << "Export command added to " << GREEN_TEXT << configFilePath << std::endl;

    return true;
}

int main() {

std::cout <<  '\n' ; 
std::cout <<  '\n' ;  
std::cout <<  '\n' ;  
std::cout <<  '\n' ;  
std::cout << "   /$$$$$$   /$$$$$$  /$$$$$$$  /$$$$$$$$       /$$   /$$  /$$$$$$"  << std::endl ;  
std::cout << "  /$$__  $$ /$$__  $$| $$__  $$| $$_____/      | $$  | $$ /$$__  $$"   << std::endl ;  
std::cout << " | $$  \\__/| $$  \\ $$| $$  \\ $$| $$            | $$  | $$|__/  \\ $$ "    << std::endl ;
std::cout << " | $$      | $$  | $$| $$  | $$| $$$$$         | $$$$$$$$  /$$$$$$/ "     << std::endl;
std::cout << " | $$      | $$  | $$| $$  | $$| $$__/         |_____  $$ /$$____/ "      << std::endl;
std::cout << " | $$    $$| $$  | $$| $$  | $$| $$                  | $$| $$  "          << std::endl;
std::cout << " |  $$$$$$/|  $$$$$$/| $$$$$$$/| $$$$$$$$            | $$| $$$$$$$$ "     << std::endl;
std::cout << "  \\______/  \\______/ |_______/ |________/            |__/|________/  "    << std::endl;
std::cout <<  '\n' ;  
std::cout <<  '\n' ;  
std::cout <<  '\n' ; 
std::string linkText = "ajeftani";
std::string linkUrl = "https://github.com/jeftani";

    printYellowLink(linkText, linkUrl);

    std::cout << "Loading: ";
    loadingAnimation(5);

    // Get the home directory
    const char* homeDirectory = getenv("HOME");

    if (homeDirectory == nullptr) {
        std::cerr << "Unable to determine home directory." << std::endl;
        return 1;
    }

    // Create the path for the "bin" directory in the home directory
    std::string binPath = std::string(homeDirectory) + "/bin";

    // Check if the "bin" directory already exists
    if (directoryExists(binPath)) {
        std::cout << "The 'bin' directory already exists." << std::endl;
    } else {
        // Attempt to create the "bin" directory
        if (mkdir(binPath.c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH) == 0) {
            std::cout << "The 'bin' directory has been created successfully." << std::endl;
        } else {
            std::cerr << "Failed to create the 'bin' directory." << std::endl;
            return 1;
        }
    }

    std::cout << "Loading: ";
    loadingAnimation(5);

    // Path to the executable file named "code"
    std::string codeExecutable = "./code "; // Update this with the actual path if necessary

    // Check if the "code" executable file exists
    if (!fileExists(codeExecutable)) {
        std::cerr << "The 'code' executable file does not exist." << std::endl;
        return 1;
    }

    // Move the "code" executable to the "bin" directory
    std::string destinationPath = binPath + "/code";

    if (moveFile(codeExecutable, destinationPath)) {
        std::cout << "The 'code' executable has been moved to the 'bin' directory." << RESET_COLOR << std::endl;
    }

    std::cout << "Loading: ";
    loadingAnimation(5);

    // Ask the user to choose a shell
    std::cout << "Choose your shell : \n";
    std::cout << "1: zsh \n";
    std::cout << "2: bash \n";
    int choice;
    std::cin >> choice;

    std::string userShell;
    switch (choice) {
        case 1:
            userShell = "zsh";
            break;
        case 2:
            userShell = "bash";
            break;
        default:
            std::cerr << "Invalid choice. Exiting." << std::endl;
            return 1;
    }

    // Add the "bin" directory to the shell configuration file
    addToShellConfig(userShell, binPath);
    std::cout << "Loading: ";
    loadingAnimation(5);
    std::cout << "code installed successfully ";

    // Add your welcome message or additional code here

    return 0;
}