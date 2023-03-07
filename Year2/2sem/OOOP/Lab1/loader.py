from telebot import TeleBot
from data.config import config

bot = TeleBot(token=config.token)
