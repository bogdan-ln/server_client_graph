#include "libraries.h"

int main() {
    try {
        Server server(8080); 
        server.run();
        
    } catch (const std::exception& e) {
        std::cerr << "Ошибка: " << e.what() << std::endl;
        return 1;
    }
    return 0;
    // .gitignore 
}