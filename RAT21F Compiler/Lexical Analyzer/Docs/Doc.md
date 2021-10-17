
# Assignment 1 Lexical Analysis
## CS323 Due dates:    Softcopy   by  10/16   (Saturday),   11:59 pm

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

### Non-Lib Build yourself version
  
**Building:**

1) Ensure that all files are present in current working directory.
   1) ```LexicalAnalyzer.h```
   2) ```LexicalAnalyzer.cpp```
   3) ```main.cpp```
2) Open Microsoft Visual Studio Developer Command Prompt.
   1) ```I used Visual Studio 2019 Developer Command Prompt v16.10.0```
3) ```cd``` to the directory mentioned in step 1.
4) In CMD enter the following:
   1) note: cl is a command in the Visual Studio dev CMD prompt
>cl main.cpp LexicalAnalyzer.cpp
5) After the command is inputted press enter.
   1) You should now have a main.exe and possibly some other files in your CWD

**Running:**

1) Now you can run the program.
   1) You must supply a .txt file with the code you want analyzed.
   2) Output filename is optional and will create a text file in the CWD.
2) Run the program via:
>main.exe myText.txt output.txt(*optional*)
3) The resulting output file in your CWD should contain the tokenized printout of your "myText.txt" or what ever you may have named it.

---

### Statically Linked Version

**Running:**

1) Open windows command prompt.
2) navigate to the directory containing the static version of the main.exe file.
3) Ensure that you have a source file in the working directory or supply a full path for the program to find it.
4) Run the following command to produce the Analysis output file:
   >main.exe test.txt output.txt(*optional*)
   1) The output path is optional and if left blank, will default to a set filename.
5) You should now have a text file in your CWD contianing your tokenized source.

---

## **3)  Design of your program**
  
  ### **Note:** 
  >There is a folder in the project directory that is labelled graphs. This is all of the graphing and tables I made in order to solve this problem and make the Lexical Analyzer. I will label the ones that informed the design of the final build.

  ---

## The Design 

>This lexical analyzer is developed from a set of regular expressions at its core. Using regular expressions for Identifiers, integers and Reals, I created a Non-Deterministic Finite State Automoton. Then, using techniques like Thompson Conversiona nd Subset Method, I converted the NFSM to a set of e-closures then to a Deterministic finite state automoton. This state machine only recognized Identifiers, Integers, and reals as previously stated. I used this original machine and then expanded to recognize everything from operators, separators to compound operators. Keywords are derived from checking recognized identifiers against a map of keywords. I used a lot of techniques found in the textbook for my state table including the backup method of recognizing states.
>
>The main file and main function handle the file IO operations involved with loading and outputing files via CLI. Supplying a source file is required at point of command line execution. The output text file is optional and will be named as default value unless a file name is also supplied for the output text.

---

## User Interface

The Lexical Analysis logic is accessible via the class Lexical Analyzer. The client can access only 2 methods. 

- LexicalAnalyzer(std::string source) :: the Constructor
- bool Lexer(std::string& token, std::string lexeme); :: the function that returns lexical units when called

---

The source code is supplied to the Lexical Analyzer only at time of construction. The LA makes a copy of the source so it is not necessary for the source to persist during analysis. Lexical units are returned to the client in the form of std::string representation of the data found.

---

## Containers and algorithms used

#### The containers used primarily are:

- std::vector\<std::string\>
- std::string
- std::stack\<std::vector\<std::string\>\>

#### Algorithms from STL used but not limited to:

- std::reverse
- std::find
- std::string::iterator

#### and some primitives like:
- bool
- float
- int
- size_t (windows defined var)


---

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
| ; | , |   | ! |
|   |   |   |   |
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

---

## Integers
>*Regular Expression:* ```D+```

---

## Reals
>*Regular Expression:* ```D+.D+```

---

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

No limitations known at time of writing. However, limitations may exist depending on your hardware configuration as well as various architecture level factors possibly.

---

## **5) Shortcomings**

1) I was not sure how to classify the lexical charcter '#'
   1) it is currently ignored by the lexer
2) I thought double period instances were handled
   1) I had cases where the lexer could resolve to a set of valid tokens instead of a mass of unknown
   2) Recent runnings of the program with ".." in certain positions did cause problems.
3) The output table isn't formatted beautifully.
   1) that being said the output is for the sake of the assignment and the actual lexer would not output strings but pass tokens as classes or enums.


---
