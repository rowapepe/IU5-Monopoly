#include "Interface/Menu.hpp"
#include "Interface/Game.hpp"
#include <locale>

int main() {
    while (true) {
        Menu menu;
        auto menuAction = menu.run();

        if (menuAction == Menu::MenuAction::Play) {
            Game game(menu.getPlayersNumber());
            if (game.run() == Game::GameAction::WindowClosed);
        }
        else if (menuAction != Menu::MenuAction::Continue) break;
    }
    return 0;
}
