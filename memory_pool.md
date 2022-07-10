堆(heap)
栈(stack)
BSS段(BSS segment/Uninitialized data segment)
数据段(initialized data segment)
代码段(test segment)


-静态区(static)：全局变量存储，在程序的整个生命周期都存在

    存储全局(global)变量，或者通过static关键字创建的变量
   
-栈区(stack)：局部变量存储（自动，连续的内存）

    栈用来存储函数内部的变量（包括main()函数）
   
    栈区是一段非常特殊的内存区，它由CPU自动管理，所以你不必手动申请和释放内存。
   
    栈内存在函数被调用时分割为连续的帧，它将为自己分配一个新的栈帧。
   
   
-堆区(heap)：动态存储（非常大的内存池，非连续分配）

    堆是一个相对于栈的概念。堆是一个可以动态使用的大内存池
	
	必须显式地申请（使用如malloc之类的函数）和释放内存（如free）
	
	堆区内存访问需要用到指针
	

