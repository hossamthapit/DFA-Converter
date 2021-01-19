# DFA-Converter

## Table of Contents
<a name="general-info"></a>
1. [General Info](#general-info)
<a name="technologies"></a>
2. [Tools-&-Technologies](#technologies)
<a name="installation"></a>
3. [Installation](#installation)

## General Info
***
1. You can use this program to visualize your DFA or DFA compliment , or test input against your DFA


### Input format ###

```
Number_Of_States: 5  
Number_Of_Transitions: 10    
Number_Of_Final_States: 3    
Make_1_To_Show_DFA_Complment_or_0_To_Show_DFA: 0  
Initial_State:  q2  
Final_States:  q0 q2 q1  
Transitions:  
q0 a q2  
q0 b q4  
q1 a q1  
q1 b q0  
q2 a q3  
q2 b q4  
q3 a q4  
q3 b q0  
q4 a q3  
q4 b q4  

Enter_String_To_Determine_if_it_belong_to_this_DFA  
babbbab   
```


### Output format ###
* dead state will appear in ![#808080](https://via.placeholder.com/15/808080/000000?text=+)  
* final state will appear in ![#f03c15](https://via.placeholder.com/15/f03c15/000000?text=+)  
* normal state will appear in ![#0000ff](https://via.placeholder.com/15/0000ff/000000?text=+)  
* initial state will appear surrounded by ()  
         


### Screenshot
![Image text](/outputDfa.png)


## Tools & Technologies 
***
A list of tools & technologies used within the project:
* [OpenGL]
* [Visual Studio 2019]
* [C++]


## Installation
***
1. Follow the instructions to download OpenGL <a href='https://www.absingh.com/opengl/?fbclid=IwAR2xf5aTrp2fcqd0MSfkgOC5UHih77r5FRBJ4lLc2BZxVawnbeIYYWU86Jg'>from here</a>
2. Now , you can modify the input file in the directory DFA-Converter\Debug\  with your DFA info
3. Run the program from DFA-Converter\Debug\DFA_Complment_Converter.exe
4. You can skip step 3 and use visual studio to run the program



