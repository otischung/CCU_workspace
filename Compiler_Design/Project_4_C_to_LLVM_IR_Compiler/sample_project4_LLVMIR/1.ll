; === prologue ====
declare dso_local i32 @printf(i8*, ...)
@.str = private unnamed_addr constant [4 x i8] c"%d\0A\00"

define dso_local i32 @main()
{
%t0 = alloca i32, align 4
%t1 = alloca i32, align 4
store i32 0, i32* %t1
%t2=load i32, i32* %t1
%t3 = add nsw i32 %t2, 100
%t4 = add nsw i32 %t3, 123
store i32 %t4, i32* %t0
%t5 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([4 x i8], [4 x i8]* @.str, i64 0, i64 0), i32 %t4)

; === epilogue ===
ret i32 0
}
