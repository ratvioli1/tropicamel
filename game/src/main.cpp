#include <string_view>

#include "Tropicamel.h"

Tropicamel gTropicamel;

int main(int argc, char* argv[]) {
    for (int i = 1; i < argc; ++i) {
        if (std::string_view(argv[i]) == "--sim")
            gTropicamel.setSim(true);
    }

    gTropicamel.start();
    gTropicamel.loop();

    return 0;
}
