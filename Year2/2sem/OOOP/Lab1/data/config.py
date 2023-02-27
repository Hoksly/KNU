import environs

env = environs.Env()
env.read_env()

TOKEN = env.str("TOKEN")
ADMINS = env.list("ADMINS")

LANGUAGES = {
    'RU': 'ru',
    'UKR': 'uk-UA',
    'ENG': 'en-US'
}

VOICE_FOLDER = env.str("VOICE_FOLDER")
DATABASE_FILE = env.str('DATABASE_FILE')
GROUP_ID = env.int("GROUP_ID")