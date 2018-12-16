# Code-Editor

![Alt text](https://github.com/Binyamin-Brion/Code-Editor/blob/master/Editor%20Screenshot.PNG)

  This project was an experiment to learn more about how to design and create GUIs.

   A text editor that provides C and C++ syntax highlighting.

   It additionally lists common (ie. that I use) PDH counters and PDH commands and their associated special values beside the text. 
This allows me to quickly put in proper PDH commands without having to keep going to Microsoft's documentation. 

   PDH refers to utilities that Microsoft provides to get performance data about a program. It can be used from the command line (CMD.exe) 
to get data  of the entire program, but calls to those utilites can be placed within code to measure specific parts of a program.

   This program works using the following steps:
   
   1) A project containing code files is opened by selecting File->New Project or File->Open Project
      Note: New Project copies an exisiting project to a new location specified by the user- this new location are where saves are wirtten.
            Open Project opens an exisiting project and saves are written there.
   
   2) The now opened project will display files on the left in using a tree. Only files that are listed in a SOURCE_FILES variable in the
      CMake file can be openend. Boxes next to the selected file names can be clicked in order to open the file, and clicked again to close
      it. Opened files can be switched to by clicking the appropriate file tabs at the top of the text editing area.
      
   3) In the top right is a drop down menu that opens related counters to the resource that is to be measured in the scroll area below it. 
      The other two scroll area lists common PDH functions, and when their checkboxes are clicked, special values for that selected command
      are displayed in the bottom-most scroll area.
     
     Improvements can be made though:
     
     1) Improve Regex expressions to provide better syntax highlighting (sometimes there are mistakes)
     2) Use PIMPL idiom to reduce compile times
     
