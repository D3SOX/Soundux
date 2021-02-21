#include "config.hpp"
#include "../../helper/json/bindings.hpp"
#include "fancy.hpp"
#include "lib/json/single_include/nlohmann/json.hpp"
#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>
#include <utility>
namespace Soundux::Objects
{
    const std::string Config::path = []() -> std::string {
#if defined(__linux__)
        const auto *configPath = std::getenv("XDG_CONFIG_HOME"); // NOLINT
        if (configPath)
        {
            return std::string(configPath) + "/Soundux/config.json";
        }
        return std::string(std::getenv("HOME")) + "/.config/Soundux/config.json"; // NOLINT
#elif defined(_WIN32)
        char *buffer;
        std::size_t size;
        _dupenv_s(&buffer, &size, "APPDATA");
        auto rtn = std::string(buffer) + "\\Soundux\\config.json";
        free(buffer);

        return rtn;
#endif
    }();

    void Config::save()
    {
        try
        {
            if (!std::filesystem::exists(path))
            {
                std::filesystem::path configFile(path);
                std::filesystem::create_directories(configFile.parent_path());
            }
            std::ofstream configFile(path);
            configFile << nlohmann::json(*this).dump();
            configFile.close();
        }
        catch (const std::exception &e)
        {
            Fancy::fancy.logTime().failure() << "Failed to write config: " << e.what() << std::endl;
        }
        catch (...)
        {
            Fancy::fancy.logTime().failure() << "Failed to write config" << std::endl;
        }
    }
    void Config::load()
    {
        try
        {
            if (!std::filesystem::exists(path))
            {
                Fancy::fancy.logTime().warning() << "Config not found" << std::endl;
                return;
            }

            std::fstream configFile(path);
            std::string content((std::istreambuf_iterator<char>(configFile)), std::istreambuf_iterator<char>());
            auto json = nlohmann::json::parse(content, nullptr, false);
            if (json.is_discarded())
            {
                Fancy::fancy.logTime().failure() << "Config seems corrupted" << std::endl;
            }
            else
            {
                try
                {
                    auto conf = json.get<Config>();
                    data = conf.data;
                    settings = conf.settings;
                }
                catch (...)
                {
                    Fancy::fancy.logTime().warning()
                        << "Found possibly old config format, moving old config..." << std::endl;

                    std::filesystem::path configFile(path);
                    std::filesystem::rename(path, configFile.parent_path() / "soundux_config_old.json");
                }
            }
            configFile.close();
        }
        catch (const std::exception &e)
        {
            Fancy::fancy.logTime().warning() << "Failed to read config: " << e.what() << std::endl;
        }
        catch (...)
        {
            Fancy::fancy.logTime().warning() << "Failed to read config" << std::endl;
        }
    }
} // namespace Soundux::Objects