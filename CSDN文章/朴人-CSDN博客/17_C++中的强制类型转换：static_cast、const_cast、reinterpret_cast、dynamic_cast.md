# 17 C++中的强制类型转换：static_cast、const_cast、reinterpret_cast、dynamic_cast

> 朴人 于 2020-10-14 10:58:50 发布 阅读量217 收藏 点赞数
> 文章链接：https://blog.csdn.net/qq570437459/article/details/108917572

在C++中，用括号方式进行强制类型转换是旧式的，比如 `(int)1.666` 。
现代的做法是用四种cast， `static_cast` 、 `const_cast` 、 `reinterpret_cast` 、 `dynamic_cast` ，语法是cast-name(expression)。

## 1.static_cast

用于基础简单类之间的转换，比如int，double，char之间。
也用于子类向父类的转换，这意味着char* 于int* 无法转换。

## 2.const_cast

很简单，就是为了把const对象转换为非const对象。

## 3.reinterpret_cast

内存字节级别的转换，字面意思就是重组内存内容，通过不同跨度的指针来重新解释这个地址的内容。

```c
int *ip;
char * pc=reinterpret_cast<char*>(ip);//这个括号在所有cast中都要加上
```

## 4.dynamic_cast

用于向下转型。比如父类指针(引用)转换成子类指针(引用)。