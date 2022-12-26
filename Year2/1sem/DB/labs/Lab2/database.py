import sqlite3
from config import DBNAME

def createAdditionalTables():
    con = sqlite3.connect(DBNAME)
    cur = con.cursor()

    cur.execute(
        """
        CREATE TABLE IF NOT EXISTS
        IsAdmin
        (
            userTag text NOT NULL,
            channelTag text NOT NULL,

            FOREIGN KEY (userTag) REFERENCES User (tag),
            FOREIGN KEY (channelTag) REFERENCES Channel (tag)
        )
        """
    )

    cur.execute(
        """
        CREATE TABLE IF NOT EXISTS
        IsMember
        (
            id integer PRIMARY KEY
            userTag text NOT NULL,
            groupTag text NOT NULL,

            FOREIGN KEY (userTag) REFERENCES User (tag),
            FOREIGN KEY (groupTag) REFERENCES Group (tag)
        )
        """
    )
    con.commit()
    con.close()

def createMainTables():
    con = sqlite3.connect(DBNAME)
    cur = con.cursor()

    cur.execute(
        """
        CREATE TABLE IF NOT EXISTS
        User (
            firstName text,
            secondName text,
            tag text PRIMARY KEY

        )
        """
    )

    cur.execute(
        """
        CREATE TABLE IF NOT EXISTS
        GroupChat( 
            name text,
            tag text PRIMARY KEY,
            membersCount integer
        )
        """
    )

    cur.execute(
        """
        CREATE TABLE IF NOT EXISTS
        Channel(
            name text,
            tag text PRIMARY KEY

        )
        """
    )

    con.commit()
    con.close()


def recreateDB():
    createMainTables()

def getUser(userTag):

    with sqlite3.connect(DBNAME) as db:
        cur = db.cursor()
        cur.execute("SELECT * FROM User WHERE tag = ?", (userTag,))
        return cur.fetchone()


def addUser(firstName, secondName, tag):
    canAdd = True

    if canAdd:
        with sqlite3.connect(DBNAME) as db:
            cur = db.cursor()
            cur.execute("INSERT INTO User (firstName, secondName, tag) VALUES (?, ?, ?)", (firstName, secondName, tag))
            cur.close()
            db.commit()


def addGroupChat(name, tag, owner):
    canAdd = True

    if canAdd:
        with sqlite3.connect(DBNAME) as db:
            cur = db.cursor()
            cur.execute("INSERT INTO GroupChat (name, tag, membersCount) VALUES (?, ?, ?)", (name, tag, 0))
            cur.close()
            db.commit()


def addChannel(name, tag, owner):
    canAdd = True

    if canAdd:
        with sqlite3.connect(DBNAME) as db:
            cur = db.cursor()
            cur.execute("INSERT INTO GroupChat (name, tag, membersCount) VALUES (?, ?, ?)", (name, tag, 0))
            cur.close()
            db.commit()


def userJoinGroup():
    pass


def userLeftGroup():
    pass


def userSubscribeChannel():
    pass


def userUnsubscribeChannel():
    pass


def getUsersInGroup(groupName):
    with sqlite3.connect(DBNAME) as con:
        cur = con.cursor()
        cur.execute("""
            SELECT * FROM User (INNER JOIN IsMember ON User.tag = IsMember.userTag (INNER JOIN GroupChat ON GroupChat.tag = IsMember.groupTag))
            WHERE GroupChat.name = ?
        """, (groupName,))
        return cur.fetchall()


def getSubscribers(channelName):
    pass


def getChannelsUserOwn():
    pass


def getAllUsersWithSameChats(userFirstName):
    pass

def getAllGroupsWithSameSubscribers(groupTag):
    pass

def getChannelsWithSameSubscribers(channelTag):
    pass




if __name__ == '__main__':
