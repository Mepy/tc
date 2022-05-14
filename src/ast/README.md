## AST
### Introduction
This module, named after **AST**, is mainly to construct **A**bstract **S**yntax **T**ree.

When constructing AST in the mean time, this module is also walking it the 0-th time, desugaring the syntax, infering types, collecting symbol infomation and transforming it into [Administrative Normal Form, ANF](https://en.wikipedia.org/wiki/A-normal_form), one kind of Intermediate Representation, IR.

Due to this reason, This module, **AST**, has another explanation : **A**NF, **S**ymbols and **T**ypes.

Therefore, This module has 2 interfaces, one used by **Parsing**, another used by **Codegen**.

- Parsing
  Use methods declared in [api.hpp](./api.hpp).
- Codegen 
  Use the data structure directly, refer to [ir.hpp](./ir.hpp) , [ir_codegen.hpp](./ir_codegen.cpp), and [Spec](../../spec/IR.md).

As for desugaring :
- reference -> pointer
  There is not reference in ir but only pointers.

### Tutorial
#### Parsing
The following is an example. As for more details, refer to [api.hpp](./api.hpp).

```cpp
#include "api.hpp"
using Table = tc::ast::Table;

void example()
{
    typename Table table;
    /* // example.tc
     * let main = fun => {
     *   return 8392862961355481856;
     *   // magic number "typed c\0"
     * }
     */ 
    table.ExprFunBeg();
    table.BlockBegin();
    auto ret   = table.Ret(table.I(0x7479706564206300L));
    table.BlockStmt(ret);
    auto block = table.BlockEnd();
    auto fun   = table.ExprFunStmt(block);
    table.Let("main", fun);
}
```

### Code Structure
#### ```#include "*.hpp"``` Dependency
X-->Y means ```#include "Y.hpp"``` in ```X.hpp```: 
```Mermaid
graph TD
api  --> context
context --> ir_parser

ir_codegen --> ir
ir_parser  --> ir

context  --> node
stmt --> node
expr --> node
type --> node
expr --> rc
type --> rc

ir --> head
node --> head
rc   --> head
```
#### ```struct```/```class ``` Heritance
X-->Y means X is a sub-class of Y : 
```Mermaid
graph TD

Node --> ExtdBase
Data --> ExtdBase

Type --> Node
Cell --> Node
Expr --> Node
Stmt --> Node

type::Data --> Data
expr::Data --> Data

type::Type --> Type
type::Type --> RC
expr::Cell --> Cell
expr::Expr --> Expr
stmt::Stmt --> Stmt

```

```Table``` is just the API, with only member methods. 
```Table```'s member variables are defined in ```TableBase```.

```Mermaid
graph LR
Table --> TableBase
```
```Table```'s member methods are implmemented in ```impl.cpp```.

### Extension
After skiming heritance relations mentioned above, You might be curious about the bottom ```struct ExtdBase```, which is in fact used to extend ```struct Node```.
A common usage is to record the position from source code.
For example : 
```tc
// position_example.tc
let name = "tc";
```
The position of "tc" is from ```{row:1, column:11}``` to ```{row:1, column:14}```.

You can modify the ```extd``` field of ```struct Node *``` like this:
```cpp
// ...
    auto expr = table.S(yytext); // yytext = "tc"
    auto& extd = expr->extd;
    extd.row_beg = 1;
    extd.col_beg = 11;
    extd.row_end = 1;
    extd.col_end = 14;
// ...
```

