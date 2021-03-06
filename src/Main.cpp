#include "Game.hpp"
#include "spdlog/spdlog.h"

#include "PCG/ProceduralGenerator.hpp"
#include "yaml-cpp/yaml.h"

#include "Audio/SoundPlayer.hpp"

int main(int argc, char *argv[])
{   
    if(argc < 2){
        spdlog::error("No Game Directory Provided");
        spdlog::info("(provide it as a command line argument)");
        return EXIT_FAILURE;
    }
    
    SoundPlayer sp;

    Game game(argv[1]);
    game.run();

}
