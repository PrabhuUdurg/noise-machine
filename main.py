import os
import random
import tkinter as tk
from tkinter import filedialog
from pydub import AudioSegment
from PIL import Audio

def cut_randomly(audio, duration):
    start = random.randint(0, len(audio) - duration)
    return audio[start:start + duration]

def merge_audio_files(audio_files):
    merged_audio = AudioSegment.empty()
    for file in audio_files:
        audio = AudioSegment.from_file(file)
        merged_audio = merged_audio + audio
    return merged_audio

def process_audio():
    input_folder = input_file_var.get()
    output_file = output_file_var.get()

    sound_files = [file for file in os.listdir(input_folder) if file.endswith(".wav")]

    if len(sound_files) == 0:
        status_label.config(text="No sound files found in the input folder.")
        return

    random.shuffle(sound_files)

    duration = int(duration_var.get())
    num_segments = int(num_segments_var.get())

    cut_segments = [cut_randomly(AudioSegment.from_file(file), duration) for file in sound_files[:num_segments]]
    merged_audio = merge_audio_files(cut_segments)

    output_file_path = os.path.join(input_folder, output_file)
    merged_audio.export(output_file_path, format="wav")

    status_label.config(text=f"Output file '{output_file}' created with {num_segments} randomly cut and merged segments.")

def browse_input_folder():
    input_folder = filedialog.askopenfilename(initialdir="Documents/samples", title="Select file:", filetypes=(("wav files", "*.wav"),("all files","*.")))
    input_file_var.set(input_folder)

def browse_output_file():
    output_file = filedialog.asksaveasfilename(defaultextension=".wav", filetypes=[("Wav files", "*.wav")])
    file = 
    output_file_var.set(output_file)
    
    

# Create the main Tkinter window
window = tk.Tk()
window.title("Musical Application")

# Variables to hold user input
input_file_var = tk.StringVar()
output_file_var = tk.StringVar()
duration_var = tk.StringVar(value="10000")  # Default duration: 10 seconds
num_segments_var = tk.StringVar(value="10")  # Default number of segments: 10

# Input folder label and browse button
input_folder_label = tk.Label(window, text="Select Input file:")
input_folder_label.grid(row=0, column=0, padx=5, pady=5, sticky="e")
input_folder_entry = tk.Entry(window, textvariable=input_file_var)
input_folder_entry.grid(row=0, column=1, padx=5, pady=5)
input_folder_browse_btn = tk.Button(window, text="Browse", command=browse_input_folder)
input_folder_browse_btn.grid(row=0, column=2, padx=5, pady=5)

# Output file label and browse button
output_file_label = tk.Label(window, text="Select Output File:")
output_file_label.grid(row=1, column=0, padx=5, pady=5, sticky="e")
output_file_entry = tk.Entry(window, textvariable=output_file_var)
output_file_entry.grid(row=1, column=1, padx=5, pady=5)
output_file_browse_btn = tk.Button(window, text="Browse", command=browse_output_file)
output_file_browse_btn.grid(row=1, column=2, padx=5, pady=5)

# Duration label and entry
duration_label = tk.Label(window, text="Duration of each segment (ms):")
duration_label.grid(row=2, column=0, padx=5, pady=5, sticky="e")
duration_entry = tk.Entry(window, textvariable=duration_var)
duration_entry.grid(row=2, column=1, padx=5, pady=5)

# Number of segments label and entry
num_segments_label = tk.Label(window, text="Number of segments:")
num_segments_label.grid(row=3, column=0, padx=5, pady=5, sticky="e")
num_segments_entry = tk.Entry(window, textvariable=num_segments_var)
num_segments_entry.grid(row=3, column=1, padx=5, pady=5)

# Process button
process_btn = tk.Button(window, text="Process Audio", command=process_audio)
process_btn.grid(row=4, column=0, columnspan=3, padx=5, pady=10)

# Status label
status_label = tk.Label(window, text="")
status_label.grid(row=5, column=0, columnspan=3, padx=5, pady=5)

# Run the Tkinter event loop
window.mainloop()