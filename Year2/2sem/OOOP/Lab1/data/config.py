import environs


class ConfigClass:
    def __init__(self):
        env = environs.Env()
        env.read_env()

        self._token = env.str("TOKEN")
        self._admins = env.list("ADMINS")
        self._languages = {
            'ru': 'ru',
            'ukr': 'uk-UA',
            'eng': 'en-US'
        }
        self._voice_folder = env.str("VOICE_FOLDER")
        self._database_file = env.str('DATABASE_FILE')
        self._group_id = env.int("GROUP_ID")

    @property
    def token(self):
        return self._token

    @token.setter
    def token(self, value):
        self._token = value

    @property
    def admins(self):
        return self._admins

    @admins.setter
    def admins(self, value):
        self._admins = value

    @property
    def languages(self):
        return self._languages

    @languages.setter
    def languages(self, value):
        self._languages = value

    @property
    def voice_folder(self):
        return self._voice_folder

    @voice_folder.setter
    def voice_folder(self, value):
        self._voice_folder = value

    @property
    def database_file(self):
        return self._database_file

    @database_file.setter
    def database_file(self, value):
        self._database_file = value

    # Setter and Getter for GROUP_ID
    @property
    def group_id(self):
        return self._group_id

    @group_id.setter
    def group_id(self, value):
        self._group_id = value


config = ConfigClass()
