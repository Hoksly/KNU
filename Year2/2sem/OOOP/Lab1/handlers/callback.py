from loader import bot
from utils.database import Database
from data.translations import MESSAGE_EDITIONS, VOICE_LANGUAGES, LANGUAGES, LANGUAGES_NEW
from data.config import DATABASE_FILE


@bot.callback_query_handler(func=lambda call: True)
def call_handler(call):
    """
    It works, and I don't really care why
    call: call function
    """
    try:
        databaseObj = Database(DATABASE_FILE)
        call_data = int((call.data[1:]))
        call_mode = call.data[0]
        user_lang = databaseObj.get_user_lang(call.message.chat.id)
        if call_mode == 'V':
            databaseObj.update_user_voice_lang(call.message.chat.id, call_data)

            bot.edit_message_text(MESSAGE_EDITIONS[user_lang]['lang'] + VOICE_LANGUAGES[user_lang][call_data][0],
                                  call.message.chat.id, call.message.id)

        elif call_mode == 'L':
            databaseObj.update_user_lang(call.message.chat.id, call_data)
            print(call.message.chat.id, call_data)
            bot.edit_message_text(MESSAGE_EDITIONS[call_data]['language'] + LANGUAGES_NEW[call_data][call_data],
                                  call.message.chat.id, call.message.id)

    except Exception as e:
        print('\x1b[0;30;41m' +
              "Error in call_handler(): {} !".format(e) + '\x1b[0m')
