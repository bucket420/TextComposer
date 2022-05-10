# TextComposer
## Description
**TextComposer** is an application that plays chord progressions and melodies based on your input text. It allows you to quickly test musical ideas with a simple GUI and syntax. It's especially useful when you want to experiment with chord progressions.

The output sound does not come from prerecorded audio files, but is generated directly by the soundcard using wavetable synthesis, with the help of [PortAudio library](http://portaudio.com/). The GUI is made with HTML, CSS, and Javascript using [Sciter.JS](https://github.com/c-smile/sciter-js-sdk).

![uipreview](https://user-images.githubusercontent.com/72154050/167323113-0533ac90-51f3-4e14-ada8-f505fe08dd11.png)
## Installation
You can download the compiled application [here](https://github.com/bucket420/TextComposer/releases) (the *.rar* file).  

If you want to compile it yourself, just clone this repo, open ***TextComposer.sln*** with **VisualStudio**, and click **Build Solution**. All external libraries and necessary configurations are already included. 
## Syntax
### I. Duration:
- '**-**' means an eighth note; '**.**' means a sixty-fourth note. Chain them together to create other durations. 

- Examples: '**--**' (fourth note), '**--.**', '**..**' (thirty-second note).

- The real duration (in seconds) will be calculated based on your inputs in '**Time signature**' and '**BPM**'.
### II. Chords and notes:
There are currently two modes available: 
1. Chord Progression:
	- For this mode you'd choose a scale and use Roman numerals - from one to seven - to represent chords. Upper case letters indicate major chords, while lowercase letters signify minor chords. '**b**' and '**#**' imply flat and sharp, respectively. Add '**d**' and '**a**' at the end for diminished and augmented chords. Currently only triads and major/minor scales are supported.
	- Add duration symbols at the end of each chord and chain the chords together to complete a chord progression.
	- Examples: **E Major I--V--vi--IV--**, **A Minor i----VI----III----VII----**

2. Melody:  
	- For this mode you'd use the musical alphabet - '**A**', '**B**', '**C**', '**D**', '**E**', '**F**', '**G**' - to represent notes. '**b**' and '**#**' imply flat and sharp, respectively. Put an integer (>=0) at 	the end to indicate which octave the note is in. E.g., '**A4**', '**C3**', '**F#4**', '**Db5**'. 
	- Add duration symbols at the end of each note and chain the notes together to complete a melody.
	- Examples: **C#5-E5-C#5-F#5---A5---G#5------.C#5-E5-C#5-A5---G#5---E5------** (Linkin Park - Numb).
	
