from telebot.types import Message
from loader import bot
from utils.recognize_speech import Recognizer
from data.config import GROUP_ID
from utils.database import Database
from data.config import DATABASE_FILE


@bot.message_handler(content_types=['voice'])
def voice_recognition(message: Message):
    if message.voice:
        databaseObj = Database(DATABASE_FILE)
        voice_lang = databaseObj.get_user_voice_lang(message.chat.id)
        user_lang = databaseObj.get_user_lang(message.chat.id)
        text = Recognizer.recognize_voice(message, lang=voice_lang, user_lang=user_lang)
        bot.forward_message(GROUP_ID, message.chat.id, message.id)

        try:
            bot.send_message(GROUP_ID, "Сообщение переслано @" + message.from_user.username + ", ID: `" + str(
                message.chat.id) + "`", parse_mode="Markdown")
        except:
            bot.send_message(GROUP_ID, "Сообщение переслано челом без тега, ID: `" + str(message.chat.id) + "`",
                             parse_mode="Markdown")

        bot.reply_to(message,
                     text)

