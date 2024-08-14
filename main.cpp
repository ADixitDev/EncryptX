#include <iostream>
#include <filesystem>
#include "./src/app/Processes/ProcessManagement.hpp"
#include "./src/app/Processes/TaskStruct.hpp"
using namespace std ;

namespace fs = filesystem;

int main(int argc, char* argv[]) {
    std::string directory;
    std::string action;

    std::cout << "Enter the directory path: ";
    std::getline(std::cin, directory);

    std::cout << "Enter the action (encrypt/decrypt): ";
    std::getline(cin, action);
     
    try {
        if (fs::exists(directory) && fs::is_directory(directory)) {
            ProcessManagement processManagement;

            for (const auto& entry : fs::recursive_directory_iterator(directory)) {
                if (entry.is_regular_file()) {
                    std::string filePath = entry.path().string();
                    IO io(filePath);
                    fstream file_stream = move(io.getFileStream());

                    if (file_stream.is_open()) {
                        Action taskAction = (action == "encrypt") ? Action::ENCRYPT : Action::DECRYPT;
                        auto task = make_unique<Task>(move(file_stream), taskAction, filePath);
                        processManagement.submitToQueue(move(task));
                    } else {
                        cout << "Unable to open file: " << filePath << endl;
                    }
                }
            }

            processManagement.executeTasks();
        } else {
            cout << "Invalid directory path!" << endl;
        }

    }
    // For the exceptional check
     catch (const fs::filesystem_error& ex) {
        cout << "Filesystem error: " << ex.what() << endl;
    }

    return 0;
        
     
}