# CPSC323-Compiler
Project for CPSC323 Compilers at CSUF for James Choi's class

My general design at time of writing:   
![](https://github.com/TelloVisionGames/CPSC323-Compiler/blob/main/RAT21F%20Compiler/Lexical%20Analyzer/Docs/Assignment1Design.png)  

---
---
---
---

CS323 Documentation  
About 2-3 pages  
  
1.  Problem Statement<write the problem statement here. You can mostly get it from the assignment itself>  
2.  How to use your program <write detailed steps how to execute your program>  
3.  Design of your program< write major components of your program. Also, data structures you are utilizing, particular algorithms you have chosen etc. >  
4.  Any Limitation<All features are running according to the assignment but  you limit your program due to resource limitations, such asMaximum number of lines in the source code, size of the identifier, integer etc.      Say ‘None’ if there is no limitation>  
5.  Any shortcomings<Anything you could NOT implement although that is required by theAssignment. Say ‘None’ if there is no shortcoming> 

---
---
---
---

## Assignment 1       
### CS323 Due dates:    Softcopy   by  10/3   (Sunday),   11:59 pm

---

## Problem Statement

The first assignment is to write a lexical analyzer (lexer).You can build your entire lexer using a FSM, Or build using at least FSMs for identifier, integer and real (the rest can be written ad-hoc)  but YOU HAVE TO CONSTRUCT A FSM for this assignment otherwise, there will be a deduction of 2 points!  

---

### **Note:** 
>In your documentation (design section), YOU MUST write the REs for Identifiers, Real and Integer, and also show the NFSM using Thompson.

---

- The lexerA major component of your assignment will be to write a procedure (Function) – lexer (),  that returns a  token when it is needed.  
- Your lexer()  should return a record, one field for the token and another field the actual "value" of the token (lexeme), i.e. the instance of a token.
- Your main program should test the lexer i.e., your program should read a file containing the source code of Rat21F to generate tokens and write out the results to an output file.   
- Make sure that you print both, the tokens and lexemes. Basically, your main program should work as follows     
  ```while not finished (i.e. not end of the source file) do          call the lexer for a token          print the token and lexeme     endwhile```  
  
- Do at least 3 test cases and make sure that you turn in proper documentation using the documentation template. 

## A simple  test case                    


### **(Partial) Source code:**  

  
 ``` while  (fahr <= upper)   a = 23.00;  /* this is sample */ ```  
   
**Output:**

|token               |             lexeme  |
|----------------------|---------------------------|
|keyword|                            while| 
|separator|                           (      |
|identifier|                           fahr| 
|operator           |                  <=     | 
|identifier        |                   upper |   
|separator |                           )|   
|identifier|                           a   |
|operator|                             =    |
|real|                                23.00  | 
|Separator|                            ;|

---