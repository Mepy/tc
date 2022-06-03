; ModuleID = 'demoCodegen.ll'
source_filename = "demoCodegen.ll"

@0 = private unnamed_addr constant [7 x i8] c"llllll\00", align 1

declare i64 @geti()

declare void @puti(i64)

declare void @puts(i8*)

declare void @putchar(i8)

define i32 @main() {
entry:
  call void @puts(i8* getelementptr inbounds ([7 x i8], [7 x i8]* @0, i32 0, i32 0))
  ret i32 0
}
