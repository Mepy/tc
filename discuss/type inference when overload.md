## type inference when overload
First, we declare our requirements.
We need to overload operator '+' with
- (int, int) -> int
- (float, float) -> float
- forall T, (&T, int) -> &T
- forall T, (int, &T) -> &T
  
Also, operator '[]' needs overload.
- forall T, (T[N], Int) -> T
- forall T, (&T  , Int) -> T

There are many other examples, like comparation '<'.

Faced with such a situation, we have many choices.
1. Simply use '+' '+.' '+&' '&+' to do a syntax-directed translation
   The code will be a bit ugly.
   We should select something better.
2. Try to infer overload function
   It's too hard to determinate without enough type info.
   I have no ideas how to determinate which function should be chosen, especially in O(n) or a nearly linear complexity bound.
3. Try to infer just overload operator
   It's a little simpler than infer overload function, because operator '+' is just a simple instance of overload function, especially when we limit the '+' in just :
   (int, int) -> int & (float, float) -> float 
   When we met ```lhs + rhs```, we infer that 
   typeof(lhs) = typeof(rhs) = typeof(lhs+rhs) = T $\in$ { int, float }
   It's determinate. What we need to do more is just to support the intersection operation of sets of types. Putting this choice aside, type inference is just to infer T $\in\mathcal{T}$(the types' universe). In this choice, We just do type inference in a subset { int, float } $\subset\mathcal{T}$.
   Unfortunately, it cannot deal with '+&' and '&+', i.e. Pointer's '+', because we have no such a good property : type equate. Choice 3 is OK in '<', reason omitted.
4. Bidirectional Type Checking, BiTyCk
   Oh, I haven't read anything about BiTyCk in the field of Programming Language. But I guess it do both type inference and type checking with the help of existing type annotations.
   Simply speaking, when we already have some type info(those from annotation or that have been infered), we can determinate the overload function.
   For example, where we only annotate ```y:Float``` : 
   ```
   let foo = fun x y:Float => x+y;
   ```
    It's enough to determinate the overload '+', it must be '+.', Float's '+'. Finally, we come to know `x:Float` and `f:(Float, Float) -> Float`. In deed, the code can be translated into : 
   ```
   _foo : 
   fadd a1 a1 a2
   ret
   ```
   If type info is not enough to determinate, we have 2 sub-choices, with example 
   ```
   let bar = fun x y => x+y;
   ```
   - A. throw an compling-time error 
    ```$ Type Error : type annotation needed in ...```
   - B. select a default function
     For example, towards '+' without info, we infer ```bar : (Int, Int) -> Int```.
     I prefer this.
5. Combine 1. and 4.B
   We explain with an example : 
   ```
   let swap = fun ptr i j =>{
       let vj = *(ptr &+ j);
       *(ptr + i) = vj;
       ptr[j] = ptr[i];
   };
   ```
   NOTICE : There is no type annotation.
   '+&' tells complier : "Hey, dear complier, the lhs, ```ptr : &T``` for some ```T```, and the rhs, ```j : Int```."
   The programmer uses '+' in the next statement. But with ```ptr:&T```, complier knows that '+' is actually '&+'. The same with ```ptr[j]``` and ```ptr[i]```.
   (As for ```T```, we infer it when ```swap``` is called.)
6. Combine 1 , 4.B and 3
   Similarly, but when type info lacks in '+', default action is to do type set's intersection.
   It's expensive to combine 3. We spend time only for overloading Int's '+', '<', etc. and Float's.
   I have no ideas whether or not to support this, if we have enough time after I implement 5.