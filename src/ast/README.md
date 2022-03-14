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
type --> node
cell --> node
expr --> node

tbl  --> node

node --> head
```
#### ```struct```/```class ``` Heritance
X-->Y means X is a sub-class of Y : 
```Mermaid
graph TD

Node --> ExtdBase
Data --> ExtdBase
Stmt --> Node
Type --> Node
Cell --> Node
Expr --> Node

Type --> RC

type::Data --> Data
expr::Data --> Data
```

```Table``` is just the API, with only member methods. 
```Table```'s member variables are defined in ```TableBase```.

```Mermaid
graph LR
Table --> TableBase
```
```Table```'s member methods are implmemented in ```impl.cpp```.