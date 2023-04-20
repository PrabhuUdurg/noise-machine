from playsound import playsound
from pydub import AudioSegment
import random

track = []


def chop_sound(file):
    sound = AudioSegment.from_file(file)
    ten_seconds = random.randrange(1, 30) * 1000
    # begining_of_file = random.randrange(1, 30) * 1000
    sound = sound[:ten_seconds]
    # sound = sound[begining_of_file]
    sound.export('new_file', format="wav")
    playsound('new_file')


chop_sound('test1.wav')
