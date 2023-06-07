import asyncio
import os
import random
import re
import hashlib
import environs

import pygame
from aiogram import Bot, types
from aiogram.dispatcher import Dispatcher
from aiogram.utils import executor
from aiogram.types import InlineKeyboardButton, InlineKeyboardMarkup
from aiogram.utils.callback_data import CallbackData

# Initialize pygame
pygame.init()
env = environs.Env()
env.read_env()
API_TOKEN = env.str("TOKEN")
bot = Bot(token=API_TOKEN)
dp = Dispatcher(bot)

# Store the current directory path
rhcp_dir = "/home/hoksly/Music/Classic"
current_directory = "/home/hoksly/Music/Official"


# Function to retrieve the files in the current directory

def get_files_in_directory(directory):
    files = []
    for filename in os.listdir(directory):
        if filename and filename[0] == '.':
            continue

        path = os.path.join(directory, filename)
        if os.path.isfile(path) and is_music_file(filename):
            files.append(filename)
        elif os.path.isdir(path):
            files.append(filename)
    return files


def is_music_file(filename):
    # Add your logic to determine if a file is a music file based on its extension
    # For example, you can check if the file has a .mp3 or .wav extension
    music_extensions = ['.mp3', '.wav']
    return any(filename.lower().endswith(ext) for ext in music_extensions)


# Function to create the inline keyboard markup
# Command handler for the /choose command
@dp.message_handler(commands=['choose'])
async def choose_command_handler(message: types.Message):
    directory = current_directory
    files = get_files_in_directory(directory)
    keyboard = get_keyboard(files, directory)  # Generate the keyboard
    print(keyboard)

    await message.answer("Choose a file or directory:", reply_markup=keyboard)


# Create a dictionary to store the mapping between identifiers and file paths
file_mapping = {}

# Define the CallbackData objects
file_callback = CallbackData("file", "identifier")
directory_callback = CallbackData("directory", "path")


def get_path_without_emojis(path_with_emojis):
    return re.sub(r"[\U0001F3B5\U0001F4C1]", "", path_with_emojis)


# Function to generate the keyboard with files and directories
def get_keyboard(files, directory):
    keyboard = []
    for item in files:
        if os.path.isdir(os.path.join(directory, item)):
            callback_data = directory_callback.new(path=os.path.join(directory, item))
            button = InlineKeyboardButton(text="📁 " + item, callback_data=callback_data)
        else:
            file_path = os.path.join(directory, item)
            file_identifier = hashlib.sha1(file_path.encode()).hexdigest()  # Generate a unique identifier for the file
            file_mapping[file_identifier] = get_path_without_emojis(file_path)

            if ('.' in item):
                sanitized_filename = item[:item.rindex('.')]
                sanitized_filename = re.sub(r'\W+', '', sanitized_filename)  # Remove non-alphanumeric characters
            else:
                sanitized_filename = re.sub(r'\W+', '', item)  # Remove non-alphanumeric characters
            truncated_filename = sanitized_filename[:32] + '...' if len(sanitized_filename) > 32 else sanitized_filename
            callback_data = file_callback.new(identifier=file_identifier)
            button = InlineKeyboardButton(text="🎵 " + truncated_filename, callback_data=callback_data)
        keyboard.append([button])

    # Add a button to go back to the previous directory if not in the root directory

    parent_directory = os.path.dirname(directory)
    if not parent_directory:
        parent_directory = "/"
    callback_data = directory_callback.new(path=parent_directory)
    back_button = InlineKeyboardButton(text="⬅ Back", callback_data=callback_data)
    keyboard.append([back_button])

    return InlineKeyboardMarkup(inline_keyboard=keyboard)


@dp.callback_query_handler(file_callback.filter())
async def file_callback_handler(query: types.CallbackQuery, callback_data: dict):
    print(callback_data)
    path = callback_data["identifier"]
    file = file_mapping[path]
    pygame.mixer.music.stop()  # Stop the currently playing music
    pygame.mixer.music.load(file)  # Load the music file

    pygame.mixer.music.play()  # Start playing the music


# Callback handler for directory selection
@dp.callback_query_handler(directory_callback.filter())
async def directory_callback_handler(query: types.CallbackQuery, callback_data: dict):
    path = callback_data["path"]
    print("here")
    await query.answer(f"You selected the directory: {path}")

    keyboard = get_keyboard(get_files_in_directory(path), path)  # Generate the keyboard
    if  query.message.reply_markup != keyboard:
        await bot.edit_message_text(
        chat_id=query.message.chat.id,
        message_id=query.message.message_id,
        text="Choose a file or directory:",
        reply_markup=keyboard
    )


autoplay_running = False


# Command handler for the /autoplay command
@dp.message_handler(commands=['autoplay'])
async def autoplay_command_handler(message: types.Message):
    global autoplay_running
    if autoplay_running:
        await message.answer("Autoplay is already running.")
        return

    autoplay_running = True

    directory = rhcp_dir
    files = get_files_in_directory(directory)
    random.shuffle(files)  # Shuffle the list of files

    for filename in files:
        file_path = os.path.join(directory, filename)
        if os.path.isfile(file_path):
            pygame.mixer.music.stop()  # Stop the currently playing music
            pygame.mixer.music.load(file_path)  # Load the music file
            pygame.mixer.music.play()  # Start playing the music

            # Wait for the music to finish playing
            while pygame.mixer.music.get_busy():
                await asyncio.sleep(1)  # Pause for 1 second before checking again

            # Check if the autoplay was stopped
            if not autoplay_running:
                break

    autoplay_running = False


# Command handler for the /stopplay command
@dp.message_handler(commands=['stopplay'])
async def stopplay_command_handler(message: types.Message):
    global autoplay_running
    pygame.mixer.music.stop()
    autoplay_running = False


@dp.message_handler(commands=['volume'])
async def volume_command_handler(message: types.Message):
    # Create the inline keyboard
    keyboard = types.InlineKeyboardMarkup(row_width=5)

    # Add volume options to the keyboard
    for volume in range(0, 11, 1):
        volume_value = volume / 10  # Convert volume value to a float between 0.0 and 1.0
        volume_text = str(volume_value)
        callback_data = f"volume:{volume_value}"
        keyboard.insert(types.InlineKeyboardButton(volume_text, callback_data=callback_data))

    await message.answer("Choose the volume:", reply_markup=keyboard)


# Callback handler for volume selection
@dp.callback_query_handler(lambda query: query.data.startswith('volume:'))
async def volume_callback_handler(query: types.CallbackQuery):
    volume = float(query.data.split(':')[1])

    # Set the volume
    pygame.mixer.music.set_volume(volume)

    await query.answer(f"Volume set to {volume}")


@dp.message_handler(commands=['menu'])
async def menu_command_handler(message: types.Message):
    # Create the inline keyboard
    keyboard = types.InlineKeyboardMarkup(row_width=2)

    # Add menu options to the keyboard
    keyboard.add(types.InlineKeyboardButton("Play", callback_data="play"))
    keyboard.add(types.InlineKeyboardButton("Pause", callback_data="pause"))
    keyboard.add(types.InlineKeyboardButton("Stop", callback_data="stop"))
    keyboard.add(types.InlineKeyboardButton("Volume", callback_data="volume"))

    await message.answer("Menu options:", reply_markup=keyboard)


if __name__ == '__main__':
    executor.start_polling(dp, skip_updates=True)
