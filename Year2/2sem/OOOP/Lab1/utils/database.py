from data.config import DATABASE_FILE
import sqlite3


class Database:
    def __init__(self, databaseFile):
        self.databaseFile = databaseFile

    def recreate_db(self):
        """
        Creates database on local machine if it doesn't exist
        :return: None
        """
        db = sqlite3.connect(self.databaseFile)
        cur = db.cursor()
        cur.execute("""CREATE TABLE IF NOT EXISTS User(
                ID INT PRIMARY KEY,
                VOICE_LANG INT,
                LANGUAGE INT
        )""")

        db.commit()
        db.close()

    def get_user_lang(self, user_id) -> int:
        """
        Gets user lang from database. If information about user doesn't exist in database, defaults it to English
        :param user_id: int
        :return: user_lang_code: int
        """
        db = sqlite3.connect(self.databaseFile)
        cur = db.cursor()
        cur.execute("""SELECT LANGUAGE FROM User WHERE ID = ?""", (user_id,))
        user_lang = cur.fetchone()
        db.close()
        if user_lang:
            return user_lang[0]
        else:
            self.add_user(user_id)
            return 0

    def get_user_voice_lang(self, user_id):
        """
        Gets users language of voice messages from database.
        If information about user doesn't exist in database, defaults it to English
        :param user_id:
        :return: voice_message_code: int
        """
        db = sqlite3.connect(DATABASE_FILE)
        cur = db.cursor()

        cur.execute("""SELECT VOICE_LANG FROM User WHERE ID = ?""", (user_id,))
        voice_lang = cur.fetchone()
        db.close()
        if voice_lang:
            return voice_lang[0]
        else:
            self.add_user(user_id)
            return 0

    def add_user(self, user_id, default_lang=0, default_voice=2):
        """
        Adds user to a database
        :param user_id: user id in Telegram
        :param default_lang: default language of bot (English)
        :param default_voice: default language of bot (Ukrainian)
        :return: None
        """
        db = sqlite3.connect(DATABASE_FILE)
        cur = db.cursor()
        cur.execute('SELECT LANGUAGE FROM User WHERE ID = ?', (user_id,))
        if not cur.fetchone():
            cur.execute("""INSERT INTO User(ID, VOICE_LANG, LANGUAGE) VALUES (?, ?, ?)""",
                        (user_id, default_voice, default_lang))
            db.commit()
        db.close()

    def update_user_lang(self, user_id, lang):
        """
        Updates user's language code in database

        :param user_id: user id in Telegram
        :param lang: language code
        :return: None
        """
        db = sqlite3.connect(DATABASE_FILE)
        cur = db.cursor()
        cur.execute('SELECT LANGUAGE FROM User WHERE ID = ?', (user_id,))
        if cur.fetchone():
            cur.execute(
                """UPDATE User SET LANGUAGE = ? WHERE ID = ?""", (lang, user_id))
        else:
            self.add_user(user_id)
            return 0
        db.commit()
        db.close()

    def update_user_voice_lang(self, user_id, lang: str):
        """
        Updates user's language of voice messages code in database

        :param user_id: user id in Telegram
        :param lang: language code
        :return: None
        """
        db = sqlite3.connect(DATABASE_FILE)
        cur = db.cursor()
        # exception if user is not in database
        cur.execute('SELECT LANGUAGE FROM User WHERE ID = ?', (user_id,))
        if cur.fetchone():
            cur.execute(
                """UPDATE User SET VOICE_LANG = ? WHERE ID = ?""", (lang, user_id))
            db.commit()
        else:
            self.add_user(user_id)
            return 0

        db.close()


if __name__ == '__main__':
    pass
