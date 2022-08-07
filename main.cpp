#include <iostream>
#include <fstream>
#include <tgbot/tgbot.h>

using namespace std;
using namespace TgBot;

const string your_user_name = "PUT YOUR USERNAME HERE";

int main() {
    Bot bot("PUT YOUR TOKEN HERE");

    bot.getEvents().onCommand("start", [&bot](TgBot::Message::Ptr message) {
        if (message->chat->username != your_user_name) {
            bot.getApi().sendMessage(message->chat->id, "YOU DONT HAVE PERMISSIONS TO USE THIS");

        } else {
            bot.getApi().sendMessage(message->chat->id, "Hi! ");
        }
    });


    bot.getEvents().onAnyMessage([&bot](TgBot::Message::Ptr message) {
        if (message->chat->username != your_user_name) {

            bot.getApi().sendMessage(message->chat->id, "YOU DONT HAVE PERMISSIONS TO USE THIS");

        } else {

            cout << message->chat->username << ": " << message->text << endl;
            string command = message->text + " > output.txt";
            const char *command_char = command.c_str();
            system(command_char);
            string output;
            ifstream output_file("output.txt");
            if (output_file.is_open()) {
                string line;
                while (getline(output_file, line)) {
                    output += line + "\n";
                }
                output_file.close();
            }
            if (output.empty()) {
                output = "empty output";
            }
            bot.getApi().sendMessage(message->chat->id, output);
        }
    });


    try {
        cout << "Bot username is: " << bot.

                        getApi()

                .getMe()->username.

                        c_str()

             <<
             endl;
        TgLongPoll longPoll(bot);
        while (true) {
            cout << "Long poll started" <<
                 endl;
            longPoll.

                    start();

        }
    } catch (
            TgBot::TgException &e
    ) {
        cout << "error: " << e.

                what()

             <<
             endl;
    }
    return 0;
}
