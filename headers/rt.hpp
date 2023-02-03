#ifndef RT_HPP
#define RT_HPP

#include <iostream>
#include <stdlib.h>

class Application {
public:
    void run();

private:
    void initSfml();
    void mainLoop();
    void cleanup();
};
#endif