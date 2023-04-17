from playsound import playsound
from pydub import AudioSegment
playsound('test1.wav')


def chop_sound(file):
    sound = AudioSegment.from_file(file)
    halfway_point = len(sound) // 2
    first_half = sound[:halfway_point]

    first_half.export("/nosie-machine/first_half.mp3", format="wav")
