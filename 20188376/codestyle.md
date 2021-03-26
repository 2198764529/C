# 代码规范

## 0. 前言

根据作业要求，我们在保证对于代码主体不受干扰的情况下，进行了规范的以下处理：

保留正常的 **缩进规则、变量命名规则、函数与类命名规则、常量命名规则、空行规则、注释规则**，取消 **每行最多字符数规则** 与 **函数最大行数规则**。

## 1. 缩进 	

### 1.1 代码缩进

默认使用 `\tab` 规范代码缩进。（**Visual Studio 2019** 使用可采用 `CTRL + K + F` 进行系统标准缩进）

### 1.2 注释缩进

注释根据不同的代码内容，应有不同的缩进格式，这里只展示通用原则：

```c++
int main()
{
	return 0;                // 应在不影响主题代码查看的情况下，在末尾有序使用/tab缩进，
	                         // 保持在同一列进行缩进
}
```

## 2. 变量命名

变量命名原则上采用 **小驼峰命名法**。

内容变量以 `v` 开头，用于数据的存储。操作变量以 `o` 开头，用于状态值、操作数等的存储。

命名示例如下：

```c++
int main()
{
	size_t vFileData = 0, oIfOpenFile = 0;
	return 0;
}
```

## 3. 函数、类命名

函数与类命名原则上采用 **大驼峰命名法**。

```c++
class TestClass
{
public:
	TestClass();
	~TestClass();

private:
	void TestFunction(int vTextVariable);
};

TestClass::TestClass()
{
}

TestClass::~TestClass()
{
}

void MyClass::TestFunction(int vTextVariable)
{
}
```

## 4. 常量

常量命名原则上采用 **匈牙利命名法**。`const 常量` 采用 **全小写匈牙利**，`宏常量` 采用 **全大写匈牙利**。

## 5. 空行规则

按照 **声明、逻辑、注释** 等规则自行空行，但要求：**每一个逻辑块之间最多空两行**。

## 6. 注释规则

### 6.1 常量变量注释

注释需要说明常量变量的具体用途。

```c++
int main()
{
	size_t vFileData = 0, oIfOpenFile = 0;				// vFileData: 文件的数据;
                                                        // oOpenFile: 是否打开文件;
	return 0;
}
```

### 6.2 函数、类注释

注释需要说明函数、类的具体用途。

```c++
// *******************************************************************************
// 作用：该类是为了进行程序的测试
// 
// 作者：JingWenxing
// 迭代版本：2.2
// 版本说明：与上一版本相比，提高了操作的速度，修改了xx的bug
// *******************************************************************************
class TestClass
{
public:
	TestClass();
	~TestClass();

private:
	void TestFunction(int vTextVariable);
};

TestClass::TestClass()
{
}

TestClass::~TestClass()
{
}

// 函数说明：该函数是为了测试程序的xx
void MyClass::TestFunction(int vTextVariable)
{
}
```

