# DFA-Converter

### Description ###   
You can use this program to  
    1-  See visualization to your DFA or DFA 1,s compliment  
    2- Check input against your dfa to see if it accepted or not  
          
### input format ###
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

### output format ###
* dead state will appear in gray  
* final state will appear in red  
* normal state will appear in blue  
* initial state will appear surrounded by ()  
         



