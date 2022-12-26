from config import FORBIDDEN_SYMBOLS_IN_NAME

class Check:
    forbiddenInName = ["@", "$"]

    @staticmethod
    def checkName(name):
        res = True
        for sym in FORBIDDEN_SYMBOLS_IN_NAME:
            res = res and sym not in name

        return res

    @staticmethod
    def checkTag(tag):
        res = len(tag) > 5
        for sym in FORBIDDEN_SYMBOLS_IN_NAME:
            res = res and sym not in FORBIDDEN_SYMBOLS_IN_NAME

        return res
