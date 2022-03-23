## AST
### Tutorial
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
### API
Refer to ```api.hpp```.

### Structure
#### ```#include "*.hpp"``` Dependency
X-->Y means ```#include "Y.hpp"``` in ```X.hpp``` : 
```Mermaid
graph TD
api  --> tbl

stmt --> node
cell --> node
expr --> node
type --> node
cell --> rc
expr --> rc
type --> rc

tbl  --> node

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