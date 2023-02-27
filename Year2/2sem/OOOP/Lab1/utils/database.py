from data.config import DATABASE_FILE
import sqlite3


class Database:
    def __init__(self, databaseFile):
        self.databaseFile = databaseFile

    def recreate_db(self):
        db = sqlite3.connect(self.databaseFile)
        cur = db.cursor()
        cur.execute("""CREATE TABLE IF NOT EXISTS User(
                ID INT PRIMARY KEY,
                VOICE_LANG INT,
                LANGUAGE INT
        )""")

        db.commit()
        db.close()

    def get_user_lang(self, user_id):
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
        db = sqlite3.connect(DATABASE_FILE)
        cur = db.cursor()
        cur.execute('SELECT LANGUAGE FROM User WHERE ID = ?', (user_id,))
        if not cur.fetchone():
            cur.execute("""INSERT INTO User(ID, VOICE_LANG, LANGUAGE) VALUES (?, ?, ?)""",
                        (user_id, default_voice, default_lang))
            db.commit()
        db.close()

    def update_user_lang(self, user_id, lang):
        db = sqlite3.connect(DATABASE_FILE)
        cur = db.cursor()
        cur.execute('SELECT LANGUAGE FROM User WHERE ID = ?', (user_id,))
        if cur.fetchone():
            cur.execute("""UPDATE User SET LANGUAGE = ? WHERE ID = ?""", (lang, user_id))
        else:
            self.add_user(user_id)
            return 0
        db.commit()
        db.close()

    def update_user_voice_lang(self, user_id, lang: str):
        db = sqlite3.connect(DATABASE_FILE)
        cur = db.cursor()
        # exception if user is not in database
        cur.execute('SELECT LANGUAGE FROM User WHERE ID = ?', (user_id,))
        if cur.fetchone():
            cur.execute("""UPDATE User SET VOICE_LANG = ? WHERE ID = ?""", (lang, user_id))
            db.commit()
        else:
            self.add_user(user_id)
            return 0

        db.close()


if __name__ == '__main__':
    pass
