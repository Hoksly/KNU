COMMANDS = {
    'help': ['Show help', 'RUS', 'UKR'],
    'lang': ['Change default language of voice messages', 'RUS', 'UKR'],
    'language': ['Change language of bot', 'RUS', 'UKR'],

}

COMMANDS_DESCRIPTION = {
    'help': [
        '/help - show this message again \n/voicelang - change voice messages language \n/botlang - change language of bot',
        '/help - show this message again \n/voicelang - change voice messages language \n/botlang - change language of bot',
        '/help - show this message again \n/voicelang - change voice messages language \n/botlang - change language of bot'],
    'lang': ['Choose language of voice messages:',
             'Выберете язык голосовых сообщений:', 'Оберіть мову голосових повідомлень:'],
    'language': ['Choose one of the languages below:',
                 'Выберите язык бота:', 'Оберіть мову бота:'],
    'start': [
        'Hello, I am bot, who helps you transform voice messages into text.\nJust send me any voice message and I wll repily with a text.'
        'To change language of voice message use /lang (default id english)\n To change language of bot use /language',
        'Russian Greetings', 'Ukrainian Greetings']
}

VOICE_LANGUAGES = [[['English', 'en-US'],
                    ['Ukrainian', 'uk-UA'],
                    ['Russian', 'ru'],
                    ['German', 'de-DE']],
                   [['Английский', 'en-US'],
                    ['Украинский', 'uk-UA'],
                    ['Русский', 'ru'],
                    ['Немецкий', 'de-DE']],
                   [['Англійська', 'en-US'],
                    ['Українська', 'uk-UA'],
                    ['Російська', 'ru'],
                    ['Німецька', 'de-DE']],
                   ]

MESSAGE_EDITIONS = [{'lang': 'Voice messages language changed to ',
                     'language': 'Bot language changed to '},
                    {'lang': 'Язык голосовых сообщений изменён на ',
                     'language': 'Язык бота изменён на '},
                    {'lang': 'Мову голосових повідомлень змінено на ',
                     'language': 'Мову бота змінено на '}]

LANGUAGES = [['English', 'Russian', 'Ukrainian'],
             ['Английский', 'Русский', 'Украинский'],
             ['Англійська', 'Російська', 'Українська'],]

LANGUAGE_KEYS = ['en-US', 'uk-UA', 'ru', 'de-DE']

ERROR_MESSAGE = ['Could not recognize any word in this voice message, please check /lang', 'Ошибка при обработке голосового сообщения: невозможно распознать ни одного слова, проверь /lang',
                 'Неможу нічого розібрати, перевір /lang']


LANGUAGES_NEW = [['English', 'Russian', 'Ukrainian'],
             ['английский', 'русский', 'украинский'],
             ['англійську', 'російську', 'українську'],]