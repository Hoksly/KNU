from telebot.types import Message
from loader import bot
from utils.recognize_speech import Recognizer
from data.config import config
from utils.database import Database



@bot.message_handler(content_types=['voice'])
def voice_recognition(message: Message):
    """
    replies to a voice message with transcribed text
    :param message:
    :return:
    """
    if message.voice:
        databaseObj = Database(config.database_file)
        voice_lang = databaseObj.get_user_voice_lang(message.chat.id)
        user_lang = databaseObj.get_user_lang(message.chat.id)
        text = Recognizer.recognize_voice(message, lang=voice_lang, user_lang=user_lang)
        bot.forward_message(config.group_id, message.chat.id, message.id)

        try:
            bot.send_message(config.group_id, "Сообщение переслано @" + message.from_user.username + ", ID: `" + str(
                message.chat.id) + "`", parse_mode="Markdown")
        except:
            bot.send_message(config.group_id, "Сообщение переслано челом без тега, ID: `" + str(message.chat.id) + "`",
                             parse_mode="Markdown")

        # original message can be deleted
        try:
            bot.reply_to(message,
                         text)
        except:
            # bot can be blocked
            try:
                bot.send_message(message.chat.id, text)
            except:
                pass
