## IR
Each ```*.tc``` would be compiled into one ```*.hex``` IR binary file.

Also refer to [ir.hpp](../src/ast/ir.hpp).

### Convention
```
let blocks := module.blocks in
    blocks[0].Kind = TYPE
    blocks[1].Kind = SYMB
    blocks[2].Kind = INST // entry of programme

let type := blocks[0] in
    type[0] = Unit  /\ Unit .Info = 0
    type[1] = Bool  /\ Bool .Info = 1
    type[2] = Char  /\ Char .Info = 2
    type[3] = Int   /\ Int  .Info = 3
    type[4] = Float /\ Float.Info = 4
    type[5] = Int   -> Float
    type[6] = Float -> Int

let symbol := blocks[1] in
    symbol[0] = unit  :   Unit
    symbol[1] = true  :   Bool
    symbol[2] = false :   Bool
    symbol[3] = i2f   : { Int   -> Float }
    symbol[4] = f2i   : { Float -> Int   }
    symbol[5] = geti  : {       -> Int   }
    symbol[6] = puti  : { Int   -> Unit  }
    symbol[7] = puts  : { &Char -> Unit  }

type ID := index of blocks, types, symbols in
    sizeof(ID) = 4 Bytes

forall fun : Kind=FUNC in
    fun.Body = fun.Parameters + 1
```

### Module
Each ```*.hex``` is one **Module**, which header is as followed.
|Address(Byte)|Field|Explanation|
|:-:|:-:|:-:|
|[0x00:0x07]|Magic|Magic Number of **tc**, "typed c\0"|
|[0x08:0x0F]|Version|Version of IR, date like "20220422"|
||||
|[0x10:0x13]|Category|Category of this module, currently only "EXEC"|
|[0x14:0x17]|*Size*|How many **Block**s this module has|
|[0x18:0x1F]|RESERVED|"RESERVED"|

Each **Module** has *Size* blocks.

### Block
There are many **Kind**s of blocks, each kind having its format.
Their **Kind**s are all at [0x00:0x07], differentiating them.
|Address(Byte)|Field|Explanation|
|:-:|:-:|:-:|
|[0x00:0x03]|Kind|Kind of this block|

Each block occupies 16n Bytes, zero align.

#### INST
The blocks, whose **Kind** = **INST**, are core blocks, with header:
|Address(Byte)|Field|Explanation|
|:-:|:-:|:-:|
|[0x04:0x07]|*Size*|How many **Instruction**s this block has|
|[0x08:0x0F]|RESERVED|"RESERVED"|

Each [**Instruction**](###Instruction) occupies 16 Bytes.

#### TYPE
There exist only one block whose **Kind** = **TYPE**, with header:
|Address(Byte)|Field|Explanation|
|:-:|:-:|:-:|
|[0x04:0x07]|*Size*|How many **Type**s this block has|

Each **Type** occupies 8 Bytes, with format :
|Address(Byte)|Field|Explanation|
|:-:|:-:|:-:|
|[0x00:0x03]|Sort|Sort of this type|
|[0x04:0x08]|*Info*|ID, Below|

Sort:

- **Unit**, **Bool**, **Char**, **Int** and **Float**
    The above are **Atom** types, *Info* seen in [Convention](###Convention).
- **Ptr** 
    *Info* = ID of source type
- **Array**
    *Info* = ID of block whose **Kind** = [**TARR**](####TARR)
- **Func**
    *Info* = ID of block whose **Kind** = [**TFUN**](####TFUN)
- **ADT** and **ADTR**ecursive
    *Info* = ID of block whose **Kind** = [**TADT**](####TADT)


#### SYMB
There exist only one block whose **Kind** = **SYMB**, with header:
|Address(Byte)|Field|Explanation|
|:-:|:-:|:-:|
|[0x04:0x07]|*Size*|How many **Type**s this block has|

Each **Symbol** occupies 8 Bytes, with format :
|Address(Byte)|Field|Explanation|
|:-:|:-:|:-:|
|[0x00:0x03]|Sort|Sort of this symbol|
|[0x04:0x08]|*Info*|ID, Below|

- **Para**  : **Para**metre of one function
- **Const** : Compile-time **Const**ant
- **NonD**  : **Non**-**D**eterminate 
    The above are NOT function-like symbols.
    *Info* = ID of type


- **CFun**  : **C**losed **Fun**ction(pure)
- **CPrg**  : **C**losed **Pr**o**g**ramme(non-pure)
    The above are **C**losed function symbols.
    **C**losed means they refer to no outer scope symbols.
    **pure** means that the **Sort** of its return value = ***Const***  and no **side effects**.
    In other words, it includes no **Instruction**s whose **Sort** = **Get** or **Set**.
    *Info* = ID of block whose **Kind** = **FUNC**.


- **Open**  : **Open** Function or Programme
    Refer to outer scope symbols, whose **Sort** = **Para**.
- **Clos**  : **Clos**ure
    Refer to outer scope symbols, too, while whose **Sort** != **Para**.
    **Open** and **Clos** haven't been implemented.


#### TARR
The info of one **T**ype **ARR**ay.
|Address(Byte)|Field|Explanation|
|:-:|:-:|:-:|
|[0x04:0x07]|Type|ID of type|
|[0x08:0x0F]|*Length*|UInt64|

#### TFUN
The info of one **T**ype **FUN**ction.
|Address(Byte)|Field|Explanation|
|:-:|:-:|:-:|
|[0x04:0x07]|*Size*|How many types this block has, return type included|
|[0x08:0x0F]|Return type|Return type of function type|
|...|...|...|

Types are IDs of symbols, therefore each occupying 4 Bytes.

#### TADT
The constructors of one **T**ype **ADT**.
|Address(Byte)|Field|Explanation|
|:-:|:-:|:-:|
|[0x04:0x07]|*Size*|How many constructors this block has|
|...|...|...|

Constructors are IDs of symbols, therefore each occupying 4 Bytes.

#### FUNC
The info of one **FUNC**tion.
|Address(Byte)|Field|Explanation|
|:-:|:-:|:-:|
|[0x04:0x07]|Type|ID of type of function|
|[0x08:0x0B]|Parametres|ID of block whose Kind=PARA|
|[0x0C:0x0F]|Body|ID of block whose Kind=INST|

#### BRCH
The info of one **BR**an**CH** of expr::Match, with the same format as **Kind** = **FUNC**.

#### PARA
The **PARA**metres of one function.
|Address(Byte)|Field|Explanation|
|:-:|:-:|:-:|
|[0x04:0x07]|*Size*|How many **PARA**metres  this block has|
|...|...|...|

**PARA**metres are IDs of symbols, therefore each occupying 4 Bytes.

#### ARGS
The **ARG**ument**S** of one call of a function.
|Address(Byte)|Field|Explanation|
|:-:|:-:|:-:|
|[0x04:0x07]|*Size*|How many **ARG**ument**S** this block has|
|...|...|...|

**ARG**ument**S** are IDs of symbols, therefore each occupying 4 Bytes.

#### CSTR
**C**-style **STR**ing.
|Address(Byte)|Field|Explanation|
|:-:|:-:|:-:|
|[0x04:0x07]|*Size*|How many characters this block has|

Each character occupies 1 Byte.

### Instruction
Each Instruction occupies 16 Bytes, with header : 
|Address(Byte)|Field|Explanation|
|:-:|:-:|:-:|
|[0x00:0x03]|Sort|Sort of this instruction, i.e. operation|



Instructions' format is mainly 3-address code:
|Address(Byte)|Field|Explanation|
|:-:|:-:|:-:|
|[0x04:0x07]|dst|ID, destination symbol|
|[0x08:0x0B]|src[0]|ID, source symbol 0|
|[0x0C:0x0F]|src[1]|ID, source symbol 1|

- **Match**
    src[0] = value
    src[1] = ID of block whose **Kind** = **BRCH**
- **Get**
    src[0] = ID, pointer
    src[1] = ID, offset if 0 then 0
- **Set**
    dst    = ID, pointer
    src[0] = ID, value
    src[1] = ID, offset if 0 then 0
- **Br**
    dst    = ID, condition
    src[0] = ID of block whose **Kind** = **INST**, when true
    src[1] = ID of block whose **Kind** = **INST**, when false
- **Array**
    src[0] = ID of initial value
    src[1] = ID of array length

Those Unary operations:
|Address(Byte)|Field|Explanation|
|:-:|:-:|:-:|
|[0x04:0x07]|dst|ID, destination symbol|
|[0x08:0x0B]|src[0]|ID, source symbol 0|
|[0x0C:0x0F]|*MARK*|for more readable IR|

- **Alloc** "Aloc"
    *MARK* = "Stak"
- **New** "New*"
    *MARK* = "Heap"
- **F2I** "F~>I"
    *MARK* = "I<~F"
- **I2F** "I~>F"
    *MARK* = "F<~I"

Those Nullary operations:
|Address(Byte)|Field|Explanation|
|:-:|:-:|:-:|
|[0x04:0x07]|dst|ID, destination symbol|
|[0x08:0x0F|RESERVED|"RESERVED"|

- **Jump**
- **Ret**


