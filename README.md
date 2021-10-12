# CPSC323-Compiler
Project for CPSC323 Compilers at CSUF for James Choi's class

---

# Assignment 1 
## CS323 Due dates:    Softcopy   by  10/3   (Sunday),   11:59 pm

[Cover Page Document](https://github.com/TelloVisionGames/CPSC323-Compiler/blob/main/RAT21F%20Compiler/Lexical%20Analyzer/Docs/Project1_CoverPage.md)
---

## **1) Problem Statement**

>The first assignment is to write a lexical analyzer (lexer).You can build your entire lexer using a FSM, Or build using at least FSMs for identifier, integer and real (the rest can be written ad-hoc)  but YOU HAVE TO CONSTRUCT A FSM for this assignment otherwise, there will be a deduction of 2 points!  

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


---

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

## **2) How to use your program**

---

## **3)  Design of your program**
  
![](https://github.com/TelloVisionGames/CPSC323-Compiler/blob/main/RAT21F%20Compiler/Lexical%20Analyzer/Docs/Assignment1Design.png)  

## Keywords

|        |       |       |        |        |
|--------|-------|-------|--------|--------|
|if      | put   |integer|function|        |
|endif   | get   |boolean|return  |        |
|else    | true  |real   | while  |  false |
|        |       |       |        |        |

---

## Simple Operators

|   |   |   |   |
|---|---|---|---|
| + | - | * | / |
| = | . | > | < |
| { | } | ( | ) |
| ; | , |   |   |
---

## Compound Operators
|    |    |    |    |
|----|----|----|----|
| == | != | <= | => |
|    |    |    |    |

---

## Identifiers
>*Regular Expression:* ```L(L|D|_)*```

*Including but not limited to:* 
- abc
- ABC
- abc7
- a_b_c7
- a7349__3

*Examples of invalid identifiers:*
- 7abc
- _abc
- _7abc
- 7_abc
- 77
- __
- 7_

## Integers
>*Regular Expression:* ```D+```

## Reals
>*Regular Expression:* ```D+.D+```

## Grammar

```R1. <Rat21F>                    ::=  <Opt Function Definitions>   #  <Opt Declaration List>  <Statement List>  #  ```  

```R2. <Opt Function Definitions>  ::=  <Function Definitions>     |  <Empty>  ```  

```R3. <Function Definitions>      ::=  <Function> | <Function> <Function Definitions>  ```  

```R4. <Function>                  ::=  function  <Identifier>   ( <Opt Parameter List> )  <Opt Declaration List>  <Body>  ```  

```R5. <Opt Parameter List>        ::=  <Parameter List>    |     <Empty>  ```  

```R6. <Parameter List>            ::=  <Parameter>    |     <Parameter> , <Parameter List>  ```  

```R7. <Parameter>                 ::=  <IDs >  <Qualifier>    ```  

```R8. <Qualifier>                 ::=  integer    |    boolean    |  real   ```  

```R9. <Body>                      ::=  {  < Statement List>  }  ```  

```R10. <Opt Declaration List>     ::=  <Declaration List>   |    <Empty>  ```  

```R11. <Declaration List>         ::=  <Declaration> ;     |      <Declaration> ; <Declaration List>  ```  

```R12. <Declaration>              ::=  <Qualifier > <IDs>                     ```  

```R13. <IDs>                      ::=  <Identifier>    | <Identifier>, <IDs>  ```  

```R14. <Statement List>           ::=  <Statement>   | <Statement> <Statement List>  ```  

```R15. <Statement>                ::=  <Compound>  |  <Assign>  |   <If>  |  <Return>   | <Print>   |   <Scan>   |  <While>   ```  

```R16. <Compound>                 ::=  {  <Statement List>  }   ```  

```R17. <Assign>                   ::=  <Identifier> = <Expression> ;  ```  

```R18. <If>                       ::=  if  ( <Condition>  ) <Statement>   endif   |  if  ( <Condition>  ) <Statement>   else    <Statement>  endif   ```  

```R19. <Return>                   ::=  return ; |  return <Expression> ;  ```  

```R21. <Print>                    ::=  put ( <Expression>);  ```  

```R21. <Scan>                     ::=  get ( <IDs> );  ```  

```R22. <While>                    ::=  while ( <Condition>  )  <Statement>    ```  

```R23. <Condition>                ::=  <Expression>  <Relop>   <Expression>  ```  

```R24. <Relop>                    ::=  ==   |   !=    |   >     |   <    |  <=   |    =>          ```  

```R25. <Expression>               ::=  <Expression> + <Term>    | <Expression>  - <Term>    |    <Term>  ```  

```R26. <Term>                     ::=  <Term>  *  <Factor>     |   <Term>  /  <Factor>     |     <Factor>  ```  

```R27. <Factor>                   ::=  -  <Primary>    |    <Primary>  ```  

```R28. <Primary>                  ::=  <Identifier>  |  <Integer>  |   <Identifier>  ( <IDs> )   |   ( <Expression> )   |   <Real>  |   true   |    false                          ```

```R29. <Empty>                    ::=  Epsilon ```   

---

## **4) Limitations**

---

## **5) Shortcomings**


---
