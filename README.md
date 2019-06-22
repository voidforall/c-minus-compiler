# C-minus-compiler
## 运行说明

**编译**。在工程根目录下，执行`make`即可编译所有文件。生成的可执行文件为`cminus`。

**运行**。使用方法为：

```
./cminus [input_file] [output_file]
```

其中，`input_file`是输入文件名，`output_file`是输出文件名。例如，要将`demo/qsort.c`编译成TINY机器码`qsort.tm`，则运行

```
./cminus demo/qsort.c qsort.tm
```

之后即可查看`qsort.tm`中的TINY机器码。除此之外，中间代码(三地址码)会输出在`result.tac`文件中。同时，词法分析，语法分析，符号表，报错信息都会输出到标准输出。若最后提示`compilation completed`则编译成功。

**运行测试**。生成的目标语言是TINY机器码，需要在TINY虚拟机上运行。首先编译TINY虚拟机：

```
make tm
```

TINY虚拟机的可执行文件为`tm`。要用TINY虚拟机运行`qsort.tm`，需要执行：

```
./tm qsort.tm
```

之后进行TINY虚拟机的命令行界面。首先会提示：

```
Enter command:
```

这个时候我们输入`go`，然后程序开始运行。当程序需要输入时会显示：

```
Enter value for IN instruction:
```

此时我们输入程序需要的整数即可。如果继续提示则继续输入。

## 测试样例

提供了三个测试样例`demo/qsort.c, demo/search.c, demo/error.c`，分别演示快排，二分搜索和错误处理。

下面介绍一下`qsort.c`的测试方法：

1. 编译代码：`./cminus demo/qsort.c qsort.tm`

2. 运行虚拟机：`./tm qsort.tm`

3. 出现`Enter command:`后，输入`go`

4. 之后会出现十次`Enter value for IN instruction: `。我们任意输入10个数字。例如：

   ```
   Enter value for IN instruction: 3
   Enter value for IN instruction: 7
   Enter value for IN instruction: 2
   Enter value for IN instruction: 0
   Enter value for IN instruction: 5
   Enter value for IN instruction: 3
   Enter value for IN instruction: 2
   Enter value for IN instruction: 6
   Enter value for IN instruction: 7
   Enter value for IN instruction: 2
   ```

5. 完成后，程序会输出排序的结果：

   ```
   OUT instruction prints: 0
   OUT instruction prints: 2
   OUT instruction prints: 2
   OUT instruction prints: 2
   OUT instruction prints: 3
   OUT instruction prints: 3
   OUT instruction prints: 5
   OUT instruction prints: 6
   OUT instruction prints: 7
   OUT instruction prints: 7
   
   ```

   下面介绍一下`search.c`的测试方法。这个程序执行二分查找。

   1. 编译代码：`./cminus demo/search.c search.tm`

   2. 运行虚拟机：`./tm search.tm`

   3. 出现`Enter command:`后，输入`go`

   4. 之后会出现十次`Enter value for IN instruction: `。我们**从小到大**输入10个数字。例如：

      ```
      Enter value for IN instruction: 1
      Enter value for IN instruction: 5
      Enter value for IN instruction: 7
      Enter value for IN instruction: 8
      Enter value for IN instruction: 10
      Enter value for IN instruction: 14
      Enter value for IN instruction: 46
      Enter value for IN instruction: 355
      Enter value for IN instruction: 677
      Enter value for IN instruction: 789
      ```

   5. 第十一次，我们输入要查找的数字，例如：

      ```
      Enter value for IN instruction: 8
      ```

   6. 此时程序就会输出`8`所在的索引位置，即3.

要测试`demo/error.c`，运行`./cminus demo/error.c error.tm`即可。这个C程序有很多错误，编译器会将所有错误都报告：

```
Error in Line[10]: no return value expected
Error in Line[19]: Int return value expected
Error in Line[27]: assignment to an array variable
Error in Line[28]: index of a non-array variable is invalid
Error in Line[29]: the number of parameters is inconsistent with declaration
Error in Line[30]: invalid type in condition: Void
Error in Line[33]: the index of array should be Int type
Error in Line[35]: operand's type is invalid: void
```





