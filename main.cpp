#include <iostream>
#include <fstream>
#include <tgbot/tgbot.h>
#include <string>

using namespace std;
using namespace TgBot;

void help() {
    cout << "--token <token> - to specify bot token" << endl << endl;
    cout << "--username <username> - to specify user, which can use bot" << endl << endl;
    cout << "--help - to get help" << endl;
}

int main(int argc, char *argv[]) {

    string your_user_name;

    string token;

    for (int i = 0; i < argc; i++) {

        if (strcmp(argv[i], "--username") == 0) {
            your_user_name = argv[i + 1];
        }

        if (strcmp(argv[i], "--token") == 0) {
            token = argv[i + 1];
        }

        if (strcmp(argv[i], "--help") == 0) {
            help();
            return 0;
        }

    }

    cout << "Only " << your_user_name << " can use your bot" << endl;
    cout << "Token: " << token << endl;

    Bot bot(token);

    bot.getEvents().onCommand("start", [&bot, &your_user_name](const TgBot::Message::Ptr message) {


        if (message->chat->username != your_user_name) {
            bot.getApi().sendMessage(message->chat->id, "FUCK YOU");

        } else {
            bot.getApi().sendMessage(message->chat->id, "Hi! ");
        }
    });


    bot.getEvents().onAnyMessage([&bot, &your_user_name](const TgBot::Message::Ptr &message) {
        if (message->chat->username != your_user_name) {

            bot.getApi().sendMessage(message->chat->id, "FUCK YOU");

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
        cout << "Bot username is: " << bot.getApi().getMe()->username.c_str() << endl;

        TgLongPoll longPoll(bot);

        while (true) {
            cout << "Long poll started" << endl;
            longPoll.start();

        }
    } catch (
            TgBot::TgException &e
    ) {
        cout << "error: " << e.what() << endl;
    }
    return 0;
}
