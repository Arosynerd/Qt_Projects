# README

## OVERVIEW

![image-20250308203214445](C:\Users\17444\AppData\Roaming\Typora\typora-user-images\image-20250308203214445.png)

## USED CLASS

### 信号的连接

```
connect(信号发起者，信号类型，信号处理者，处理方法)

//第二种写法
connect(信号发起者，信号类型，[信号处理者](){
//处理方法

})
```

### mainwindow的使用

![image-20250308203708051](C:\Users\17444\AppData\Roaming\Typora\typora-user-images\image-20250308203708051.png)

### 事件

鼠标事件、键盘事件、定时器事件等，属于类Qevent，所有控件都继承这个父类。

#### 实现

在mainwindow上重写对应Qevent方法，这个方法连接对应事件作为信号

