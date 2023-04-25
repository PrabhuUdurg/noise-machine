from playsound import playsound
from pydub import AudioSegment
import random

track = []


def chop_sound(file):
    sound = AudioSegment.from_file(file)

# Assign range of cut
    first_seconds = random.randrange(1, 30) * 1000
    last_seconds = random.radrange(1, 10) * 1000 

# Chop beginning and ending  
    beginning = sound[:ten_seconds]
    end = sound[-last_seconds:]

# Editing main sound
    whole_sound = sound - beginning - end 
    
    
    whole_sound.export('new_file', format="wav")
    playsound('new_file')


chop_sound('test1.wav')
