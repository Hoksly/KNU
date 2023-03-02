from loader import bot
from telebot.types import Message
from data.translations import COMMANDS_DESCRIPTION
from utils.database import Database
from data.config import DATABASE_FILE
import telebot
from data.translations import VOICE_LANGUAGES, COMMANDS_DESCRIPTION, LANGUAGES


@bot.message_handler(commands=['start'])
def start(message: Message) -> None:
    """
    sends message when /start command sends, adds user to database if not added yet
    :param message: telegram message
    :return None:
    """
    databaseObj = Database(DATABASE_FILE)
    databaseObj.add_user(message.chat.id)
    user_lang = 0
    bot.send_message(message.chat.id, COMMANDS_DESCRIPTION['start'][user_lang])


@bot.message_handler(commands=['help'])
def helpp(message: Message):
    """
    sends help message when /help command sends
    :param message: telegram message
    :return None:
    """
    databaseObj = Database(DATABASE_FILE)

    user_lang = databaseObj.get_user_lang(message.chat.id)
    bot.send_message(message.chat.id, COMMANDS_DESCRIPTION['help'][user_lang])


@bot.message_handler(commands=['voicelang'])
def lang(message: Message):
    """
    Sends message that allow change language of voice message
    :param message:
    :return:
    """
    try:
        databaseObj = Database(DATABASE_FILE)
        user_lang = databaseObj.get_user_lang(message.chat.id)

        markup = telebot.types.InlineKeyboardMarkup()

        for i in range(len(VOICE_LANGUAGES[user_lang])):
            markup.add(telebot.types.InlineKeyboardButton(VOICE_LANGUAGES[user_lang][i][0], callback_data='V' + str(i)))
        bot.send_message(message.chat.id, COMMANDS_DESCRIPTION['lang'][user_lang], reply_markup=markup)

    except Exception as e:
        print('\x1b[0;30;41m' + "Error in lang(): {} !".format(e) + '\x1b[0m')


@bot.message_handler(commands=['botlang'])
def language(message: Message):
    """
    Sends message that allows change language of bot
    :param message:
    :return:
    """
    databaseObj = Database(DATABASE_FILE)
    user_lang = databaseObj.get_user_lang(message.chat.id)

    markup = telebot.types.InlineKeyboardMarkup()
    for i in range(len(LANGUAGES[user_lang])):
        markup.add(telebot.types.InlineKeyboardButton(LANGUAGES[user_lang][i], callback_data='L' + str(i)))
    bot.send_message(message.chat.id, COMMANDS_DESCRIPTION['language'][user_lang], reply_markup=markup)


@bot.message_handler(content_types=['text'])
def text(message: Message):
    helpp(message)
