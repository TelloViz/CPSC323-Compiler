# Lexer()

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

>```R1. <Rat21F>                    ::=  <Opt Function Definitions>   #  <Opt Declaration List>  <Statement List>  #  ```  

>```R2. <Opt Function Definitions>  ::=  <Function Definitions>     |  <Empty>  ```  

>```R3. <Function Definitions>      ::=  <Function> | <Function> <Function Definitions>  ```  

>```R4. <Function>                  ::=  function  <Identifier>   ( <Opt Parameter List> )  <Opt Declaration List>  <Body>  ```  

>```R5. <Opt Parameter List>        ::=  <Parameter List>    |     <Empty>  ```  

>```R6. <Parameter List>            ::=  <Parameter>    |     <Parameter> , <Parameter List>  ```  

>```R7. <Parameter>                 ::=  <IDs >  <Qualifier>    ```  

>```R8. <Qualifier>                 ::=  integer    |    boolean    |  real   ```  

>```R9. <Body>                      ::=  {  < Statement List>  }  ```  

>```R10. <Opt Declaration List>     ::=  <Declaration List>   |    <Empty>  ```  

>```R11. <Declaration List>         ::=  <Declaration> ;     |      <Declaration> ; <Declaration List>  ```  

>```R12. <Declaration>              ::=  <Qualifier > <IDs>                     ```  

>```R13. <IDs>                      ::=  <Identifier>    | <Identifier>, <IDs>  ```  

>```R14. <Statement List>           ::=  <Statement>   | <Statement> <Statement List>  ```  

>```R15. <Statement>                ::=  <Compound>  |  <Assign>  |   <If>  |  <Return>   | <Print>   |   <Scan>   |  <While>   ```  

>```R16. <Compound>                 ::=  {  <Statement List>  }   ```  

>```R17. <Assign>                   ::=  <Identifier> = <Expression> ;  ```  

>```R18. <If>                       ::=  if  ( <Condition>  ) <Statement>   endif   |  if  ( <Condition>  ) <Statement>   else    <Statement>  endif   ```  

>```R19. <Return>                   ::=  return ; |  return <Expression> ;  ```  

>```R21. <Print>                    ::=  put ( <Expression>);  ```  

>```R21. <Scan>                     ::=  get ( <IDs> );  ```  

>```R22. <While>                    ::=  while ( <Condition>  )  <Statement>    ```  

>```R23. <Condition>                ::=  <Expression>  <Relop>   <Expression>  ```  

>```R24. <Relop>                    ::=  ==   |   !=    |   >     |   <    |  <=   |    =>          ```  

>```R25. <Expression>               ::=  <Expression> + <Term>    | <Expression>  - <Term>    |    <Term>  ```  

>```R26. <Term>                     ::=  <Term>  *  <Factor>     |   <Term>  /  <Factor>     |     <Factor>  ```  

>```R27. <Factor>                   ::=  -  <Primary>    |    <Primary>  ```  

>```R28. <Primary>                  ::=  <Identifier>  |  <Integer>  |   <Identifier>  ( <IDs> )   |   ( <Expression> )   |   <Real>  |   true   |    false                          ```

>```R29. <Empty>                    ::=  Epsilon ```   