import sqlite3


class Database:
    def __init__(self, database_file):
        self.database_file = database_file
        self.connection = sqlite3.connect(database_file)
        self.cursor = self.connection.cursor()
        self.recreate_db()

    def __del__(self):
        self.connection.close()

    def recreate_db(self):
        """
        Creates database on local machine if it doesn't exist
        """

        self.cursor.execute(
            """CREATE TABLE IF NOT EXISTS User(
                ID INTEGER PRIMARY KEY,
                VOICE_LANG INTEGER,
                LANGUAGE INTEGER
            )"""
        )
        self.connection.commit()

    def get_user_lang(self, user_id):
        """
        Gets user lang from database. If information about user doesn't exist in database, defaults it to English
        """
        self.cursor.execute(
            """SELECT LANGUAGE FROM User WHERE ID = ?""", (user_id,)
        )
        user_lang = self.cursor.fetchone()
        if user_lang:
            return user_lang[0]
        else:
            self.add_user(user_id)
            return 0

    def get_user_voice_lang(self, user_id):
        """
        Gets users language of voice messages from database.
        If information about user doesn't exist in database, defaults it to English
        """
        self.cursor.execute(
            """SELECT VOICE_LANG FROM User WHERE ID = ?""", (user_id,)
        )
        voice_lang = self.cursor.fetchone()
        if voice_lang:
            return voice_lang[0]
        else:
            self.add_user(user_id)
            return 0

    def add_user(self, user_id, default_lang=0, default_voice=2):
        """
        Adds user to a database
        """
        self.cursor.execute(
            "INSERT INTO User(ID, VOICE_LANG, LANGUAGE) VALUES (?, ?, ?)",
            (user_id, default_voice, default_lang),
        )
        self.connection.commit()

    def update_user_lang(self, user_id, lang):
        """
        Updates user's language code in database
        """
        self.cursor.execute(
            """UPDATE User SET LANGUAGE = ? WHERE ID = ?""", (lang, user_id)
        )
        self.connection.commit()

    def update_user_voice_lang(self, user_id, lang):
        """
        Updates user's language of voice messages code in database
        """
        self.cursor.execute(
            """UPDATE User SET VOICE_LANG = ? WHERE ID = ?""", (lang, user_id)
        )
        self.connection.commit()
