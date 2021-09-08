# OnlieProgrammingServer

一个轻量级在线编程服务器

可以对C/C++、python等语言进行在线的编译或运行

编译结果和程序的输出结果会回复给客户端

**实现流程:**

      1.客户端连接服务器
  
      2.客户端发送数据包(代码)
  
      3.服务器根据客户端ID新建独立的文件夹
  
      4.服务器进入该文件夹并创建程序文件,将编译结果和运行结果重复定向至文件中
  
      5.将编译结果和程序执行结果写回给客户端
  
      6.服务器删除客户端的文件夹
  
  
  **测试效果展示:[TCP]**
  
      服务器启动
  ![image](https://github.com/Sakura7301/OnlieProgrammingServer/blob/master/picture/%E6%9C%8D%E5%8A%A1%E5%99%A8%E5%90%AF%E5%8A%A8.png)
      
      C语言测试
  ![image](https://github.com/Sakura7301/OnlieProgrammingServer/blob/master/picture/C%E8%AF%AD%E8%A8%80%E9%94%99%E8%AF%AF%E7%A4%BA%E4%BE%8B.png)
  ![image](https://github.com/Sakura7301/OnlieProgrammingServer/blob/master/picture/C%E8%AF%AD%E8%A8%80%E9%80%9A%E8%BF%87%E7%A4%BA%E4%BE%8B.png)
  
      C++测试
  ![image](https://github.com/Sakura7301/OnlieProgrammingServer/blob/master/picture/cpp%E9%94%99%E8%AF%AF%E7%A4%BA%E4%BE%8B.png)
  ![image](https://github.com/Sakura7301/OnlieProgrammingServer/blob/master/picture/cpp%E9%80%9A%E8%BF%87%E7%A4%BA%E4%BE%8B.png)
  
        python测试
  ![image](https://github.com/Sakura7301/OnlieProgrammingServer/blob/master/picture/python%E9%94%99%E8%AF%AF%E7%A4%BA%E4%BE%8B.png)
  ![image](https://github.com/Sakura7301/OnlieProgrammingServer/blob/master/picture/python%E9%80%9A%E8%BF%87%E7%A4%BA%E4%BE%8B.png)
  
  
  **测试效果展示:[HTTP]**
  
  
  **关键词**:C/S模型、libevent



**user:Sakura7301**
