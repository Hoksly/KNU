import os
import instabot
import json
import argparse
import requests  # to get image from the web
import shutil  # to save it locally

USERNAME = "_hoksly_"
PASSWORD = "AL041111"


class AddAccountPolicy:
    def __init__(self):
        self.max_followers = 370
        self.max_following = 370

    def check_counts(self, followers_count: int, following_count: int):
        return followers_count < self.max_followers and following_count < self.max_following


class User:
    def username(self):
        pass

    def user_id(self):
        pass

    def profile_pic(self):
        pass

    def data(self):
        pass


class UserGraph:
    def __init__(self, target_users: list, recursion_limit=0, bot=None, save_folder=None):
        self.all_users = {}
        self.policy = AddAccountPolicy()
        self.save_folder = save_folder

        if len(target_users) > 0:
            if not bot:
                self.bot = instabot.Bot()
                self.bot.login(username=USERNAME, password=PASSWORD)
            else:
                self.bot = bot
            for username in target_users:
                print("Working with:", username)
                self.get_user_data_from_username(username)


            for i in range(recursion_limit):
                self.go_deeper_into_connections()

    def get_user_from_user_id(self, user_id):

        user_data = self.bot.get_user_info(user_id)
        if not (user_data and self.policy.check_counts(user_data['follower_count'], user_data['following_count'])):
            return

        user_followers = self.bot.get_user_following(user_id)
        user_followings = self.bot.get_user_followers(user_id)

        if user_data:
            user_data.update({"followers": user_followers})
            user_data.update({"followings": user_followings})
            cleared_data = {k: user_data[k] for k in (
                'pk', 'username', 'full_name', 'is_private', 'followers', 'follower_count', 'following_count',
                'followings',
                'biography', 'hd_profile_pic_versions', 'profile_pic_url') if k in user_data}
            if 'hd_profile_pic_versions' in cleared_data and (len(cleared_data['hd_profile_pic_versions']) > 0):
                try:
                    link = cleared_data['hd_profile_pic_versions'][0]['url']
                    cleared_data['hd_profile_pic_versions'] = link
                except:
                    cleared_data['hd_profile_pic_versions'] = None


            self.all_users.update({str(user_id): cleared_data})


            if self.save_folder:
                self.save_user(self.save_folder, cleared_data)

    def get_user_data_from_username(self, username):
        user_id = self.bot.get_user_id_from_username(username)
        self.get_user_from_user_id(user_id)

    def check_and_add(self, user_id: int):
        # cheking if user is not a chanel
        self.get_user_from_user_id(user_id)

    def add_users_from_list(self, users: list):
        if not users:
            return

        for user_id in users:
            if user_id not in self.all_users:
                self.check_and_add(int(user_id))

    def add_all_followings(self, keys: list):
        for user_id in keys:
            try:  # if account is private, we cannot access its followings
                self.add_users_from_list(self.all_users[user_id]['followings'])
            except KeyError as err:
                print("KeyError with:", user_id, str(err))

    def add_all_followers(self, keys: list):
        for user_id in keys:
            try:
                self.add_users_from_list(self.all_users[user_id]['followers'])
            except KeyError as err:
                print("KeyError with:", user_id, str(err))

    def go_deeper_into_connections(self):
        self.add_all_followers(list(self.all_users.keys()))
        self.add_all_followings(list(self.all_users.keys()))

    @staticmethod
    def create_dir(folder_name):
        try:
            os.makedirs(folder_name)
        except:
            pass

    @staticmethod
    def download_user_pic(image_url, filename):
        if not (image_url and filename):
            return

        try:
            r = requests.get(image_url, stream=True)

            if r.status_code == 200:
                r.raw.decode_content = True

                with open(filename, 'wb') as f:
                    shutil.copyfileobj(r.raw, f)
        except:
            print("FUCKED with downlod:", image_url)

    def save_user(self, folder_name: str, user_data: dict):
        if not user_data:
            return
        print("SAVING")

        full_folder_name = folder_name + os.sep + str(user_data['pk'])
        self.create_dir(full_folder_name)

        with open(full_folder_name + os.sep + 'data.json', 'w') as file:
            json.dump(user_data, file)

        pic_url = user_data['profile_pic_url'] if ('profile_pic_url' in user_data) else None
        pic_url_hd = user_data['hd_profile_pic_versions']if ('hd_profile_pic_versions' in user_data) else None

        self.download_user_pic(pic_url, full_folder_name + os.sep + 'pic.jpg')
        self.download_user_pic(pic_url_hd, full_folder_name + os.sep + 'pic_hd.jpg')

    def save_to(self, folder_name: str):
        for user_id in self.all_users:
            self.save_user(folder_name, self.all_users[user_id])


def parse_cli(arg_str = None):
    parser = argparse.ArgumentParser("Parse inforamtion of user")
    parser.add_argument("-u", type=list, nargs="+",
                        help="target useror users")
    parser.add_argument("-r", type=int, nargs="+",
                        help="recursion limit")
    parser.add_argument("-s", type=str, nargs="+",
                        help="save folder")
    if not arg_str:
        args = parser.parse_args()
    else:
        args = parser.parse_args(arg_str)
    users = []

    if not args.u:
        print("Use -u to specify at least one user ")
        exit(1)

    for user_list in args.u:
        users.append(''.join(user_list))

    recursion_limit = 0
    if args.r and len(args.r) == 1:
        recursion_limit = args.r[0]

    save_folder = None
    if args.s:
        save_folder = args.s[0]

    return users, recursion_limit, save_folder


if __name__ == '__main__':
    try:
        shutil.rmtree('config')
    except:
        pass

    users, recursion_limit, save_folder = parse_cli()

    G = UserGraph(users, recursion_limit=recursion_limit, save_folder=save_folder)

