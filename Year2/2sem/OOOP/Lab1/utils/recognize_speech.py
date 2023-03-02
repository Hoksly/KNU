import speech_recognition as sr
from utils.saver import Saver
from aiogram.types import Message
import os
from data.translations import LANGUAGE_KEYS, ERROR_MESSAGE


class Recognizer:
    @staticmethod
    def recognize(filename: str, lang: int, user_lang: int) -> str:
        """

        :param filename: voice file location
        :param lang: code of voice message language
        :param user_lang: code of user's language
        :return: transcribed voice message
        """
        r = sr.Recognizer()

        recog = sr.Recognizer()
        sample_audio = sr.AudioFile(filename)
        with sample_audio as audio_file:
            audio_content = recog.record(audio_file)

        try:
            return recog.recognize_google(audio_content, language=LANGUAGE_KEYS[lang])
        except sr.UnknownValueError:
            return ERROR_MESSAGE[user_lang]

    @staticmethod
    def recognize_voice(message: Message, lang: int, user_lang: int) -> str:
        """
        Transcribe telegram voice message into text

        :param message: telegram voice message
        :param lang: code of voice message language
        :param user_lang: code of user's language
        :return: transcribed voice message
        """
        filename = Saver.save_voice_file(message)
        text = Recognizer.recognize(filename, lang=lang, user_lang=user_lang)
        os.remove(filename)
        return text
