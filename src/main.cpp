#include "common/system.hpp"
#include "common/window.hpp"
#include "render/render.hpp"
#include "game/game.hpp"
#include <memory>

int main()
{
    using namespace tgame;

    System s;

    if (!s.init())
        return -1;

    auto wnd = std::make_shared<Window>(640, 640);

    auto game = std::make_shared<Game>(*wnd);
    s.subscribeToInput(game->getInputSubscriber());
    game->prepare();

    auto render = std::make_shared<Render>(wnd, game->getBoard());


    while (!s.isQuitRequested())
    {
        s.handleEvents();
        render->draw(game->getBoard());
        render->present();
    }

    return 0;
}