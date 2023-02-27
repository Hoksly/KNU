# -*- coding: utf-8 -*-
import telebot

bot = telebot.TeleBot ("5061383269:AAG4N9TOHWmtskeA6Cpf1iscMEqZ0wqOXoE")

maincid = -1001444939502


def try_print (text):
    try:
        bot.send_message (maincid, '`' + text + '`', parse_mode = "Markdown")
    except Exception as e:
        print ("ERROR! COULDN'T SEND ERROR MESSAGE TO CHAT!")
        print ("Error message: " + text)
        print ("Current error: " + str (e))


def direct (tid, text):
    try:
        bot.send_message (tid, text)
    except Exception as e:
        try_print ("Failed to send directly: " + str (e))


def lastname (string):
    if string is None:
        return ""
    else:
        return " " + string


@bot.message_handler (commands = ['getcid'])
def cid (message):
    try:
        bot.send_message (message.chat.id, message.chat.id)
    except Exception as e:
        try_print ("Failed to get cid: " + str (e))


@bot.message_handler (commands = ['sendto'])
def sendto (message):
    try:
        if message.chat.id == maincid:
            message.text += ' '
            bt = False
            id = ''
            i = 0
            for i in range (len (message.text)):
                if message.text [i] == '>':
                    break
                if bt:
                    id += message.text [i]
                if message.text [i] == '<':
                    bt = True
                i = i + 1
            i = i + 1
            concid = int (id)
            direct (concid, message.text [i:-1])
    except Exception as e:
        try_print ("Failed to get stp data: " + str (e))


@bot.message_handler (commands = ['start'])
def cid (message):
    try:
        if message.chat.type == 'private':
            bot.send_message (message.chat.id, "Шо за /start , давай контент:)")
            try:
                bot.send_message (maincid, "С нами поздоровался " + message.from_user.first_name + lastname (message.from_user.last_name) + " (@" + message.from_user.username + "), ID: `" + str (message.from_user.id) + "`", parse_mode = "Markdown")
            except:
                bot.send_message (maincid, "С нами поздоровался " + message.from_user.first_name + lastname (message.from_user.last_name) + ", тега нет, ID: `" + str (message.from_user.id) + "`", parse_mode = "Markdown")
    except Exception as e:
        try_print ("Failed to greet:" + str (e))


@bot.message_handler (content_types = ['text', 'audio', 'document', 'photo', 'sticker', 'video', 'animation', 'video_note', 'voice', 'location', 'contact'])
def proceed (message):
    try:
        if message.chat.id == maincid:
            if message.reply_to_message is not None:
                try:
                    bot.copy_message (message.reply_to_message.forward_from.id, message.chat.id, message.id)
                except Exception as e1:
                    try_print ("Failed to send reply: " + str (e1))
        else:
            try:
                if message.chat.type == 'private':
                    if message.forward_from is not None or message.forward_from_chat is not None:
                        try:
                            bot.send_message (maincid, "Сообщение переслано вором " + message.from_user.first_name + lastname (message.from_user.last_name) + " (@" + message.from_user.username + "), ID: `" + str (message.chat.id) + "`", parse_mode = "Markdown")
                        except:
                            bot.send_message (maincid, "Сообщение переслано вором " + message.from_user.first_name + lastname (message.from_user.last_name) + " без тега, ID: `" + str (message.chat.id) + "`", parse_mode = "Markdown")
                    else: #
                        try:
                            bot.send_message (maincid, "Сообщение оригинальное, отправитель " + message.from_user.first_name + lastname (message.from_user.last_name) + " (@" + message.from_user.username + "), ID: `" + str (message.chat.id) + "`", parse_mode = "Markdown")
                        except:
                            bot.send_message (maincid, "Сообщение оригинальное, отправитель " + message.from_user.first_name + lastname (message.from_user.last_name) + " без тега, ID: `" + str (message.chat.id) + "`", parse_mode = "Markdown")
                    bot.forward_message (maincid, message.chat.id, message.id)
            except Exception as e2:
                try_print ("Failed to forward message: " + str (e2))
    except Exception as e0:
        try_print ("Failed in... if?..  :" + str (e0))


bot.infinity_polling ()
#bot.polling ()
