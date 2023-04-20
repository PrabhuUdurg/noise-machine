from playsound import playsound
from pydub import AudioSegment


def chop_sound(file):
    sound = AudioSegment.from_file(file)
    ten_seconds = 10 * 1000
    first_10_seconds = sound[:ten_seconds]
    # first_half.export("/nosie-machine/first_half.wav", format="wav")
    sound.export("mashup.mp3", format="mp3")
    playsound(sound)


chop_sound('test1.wav')
