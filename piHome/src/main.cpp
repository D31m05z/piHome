
#include "piHome.h"

int main(int argc, char** argv)
{
    PIHome piHome;
    while(piHome.isRunning()) {
        //piHome.update();
        piHome.draw();
    }

    return 0;
}
