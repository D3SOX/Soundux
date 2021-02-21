#include "hotkeys.hpp"
#include "../global/globals.hpp"

namespace Soundux
{
    namespace Objects
    {
        void Hotkeys::init()
        {
            listener = std::thread([this] { listen(); });
        }
        void Hotkeys::stop()
        {
            kill = true;
            listener.join();
        }
        void Hotkeys::shouldNotify(bool status)
        {
            notify = status;
        }
        void Hotkeys::onKeyUp([[maybe_unused]] int key)
        {
            if (notify && !pressedKeys.empty())
            {
                Globals::gGui->onHotKeyReceived(pressedKeys);
            }
            pressedKeys.clear();
        }
        void Hotkeys::onKeyDown(int key)
        {
            pressedKeys.push_back(key);
        }
    } // namespace Objects
} // namespace Soundux