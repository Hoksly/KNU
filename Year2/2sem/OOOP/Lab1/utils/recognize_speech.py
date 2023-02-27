import speech_recognition as sr
from utils.saver import save_voice_file
import os
from data.translations import LANGUAGE_KEYS, ERROR_MESSAGE


def recognize(filename, lang, user_lang):
    r = sr.Recognizer()

    recog = sr.Recognizer()
    sample_audio = sr.AudioFile(filename)
    with sample_audio as audio_file:
        audio_content = recog.record(audio_file)

    try:
        return recog.recognize_google(audio_content, language=LANGUAGE_KEYS[lang])
    except sr.UnknownValueError:
        return ERROR_MESSAGE[user_lang]


def recognize_voice(message, lang, user_lang):
    filename = save_voice_file(message)
    text = recognize(filename, lang=lang, user_lang=user_lang)
    os.remove(filename)
    return text