## tc : typed c
### Intro
This project is just a compiler course project, implementing a simple toy language named **tc**, the abbreviation of **typed c**.

### Type System
**tc**, as is named after, is a strong typed programming language.

#### Type Safety
In **tc**, programmer can not do type conversion implicitly, but explicitly with a function from standard library. This is a major difference between **C** and **tc**, which ensures the type safety of **tc**.

#### Type Inference
The core type system of **tc** is Simply Typed Lambda Calculus, STLC. Due to the decidability of type inference in STLC, we decide to support it in **tc**. It frees programmers from writing lots of redundant type notations.

### C? and Features
The "c" in "typed c" have two explaination. One is of course **C** language, the other is the **Caml** language. In short, **tc** is the language that hashs **C** and **Caml** into the same block. Now that **tc** is similar to 2 different languages, features of **tc** can be divided into 2 classes.
- **C**-like features
  + Mutable Variables, Pointers and Array
  + ```while``` and ```if``` Control Flow
- **Caml**-like features
  + Type Inference
  + Immutable Variables
  + Algebraic Data Types, ADT : compose atom types.
  + Functions as First Citizens
  
Details are discribed in ```./spec```.