from loader import bot
from aiogram.types import Message
import os
from time import sleep
from data.config import VOICE_FOLDER


class Saver:
    @staticmethod
    def save_voice_file(message: Message) -> str:
        """
        Saves telegram voice message on local machine, returns file name

        :param message: telegram voice message
        :return: str

        """
        file_info = bot.get_file(message.voice.file_id)
        downloaded_file = bot.download_file(file_info.file_path)
        ogg_file = VOICE_FOLDER + '{}.ogg'.format(message.voice.file_id)
        wav_file = VOICE_FOLDER + '{}.wav'.format(message.voice.file_id)

        with open(ogg_file, 'wb') as new_file:
            new_file.write(downloaded_file)

        sleep(1)
        os.system(f'ffmpeg -i {ogg_file} {wav_file}')  # not the best way to do it, but now it is working....
        sleep(2)

        os.remove(ogg_file)
        return wav_file
