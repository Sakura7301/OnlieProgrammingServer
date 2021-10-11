# OnlieProgrammingServer

一个轻量级在线编程服务器

可以对C/C++、python等语言进行在线的编译或运行

编译结果和程序的输出结果会回复给客户端

## **具体流程:**

      1.客户端连接服务器
  
      2.客户端发送HTTP请求(PUT)
  
      3.服务器获取该请求的数据包data
      
      4.服务器获取数据包中的信息并以此为一个单独的连接建立文件夹
  
      5.服务器进入该文件夹并创建程序文件,将编译结果和运行结果重复定向至文件中
  
      6.将编译结果和程序执行结果写回给客户端
  
      7.服务器删除客户端的文件夹
  
  
## **项目包含**
  TCP服务器:  [OnlieProgrammingServer](https://github.com/Sakura7301/OnlieProgrammingServer/tree/master/OnlieProgrammingServer)
  
  HTTP服务器: [OnlieProgrammingServer_HTTP](https://github.com/Sakura7301/OnlieProgrammingServer/tree/master/OnlieProgrammingServer_HTTP)
  
  QT客户端:   [QTclient_Edit](https://github.com/Sakura7301/OnlieProgrammingServer/tree/master/QTclient_Edit)
  
  path:       [path.txt](https://github.com/Sakura7301/OnlieProgrammingServer/blob/master/path.txt)
  
 ## **测试效果展示:**
  
### 服务器启动
  ![image](https://github.com/Sakura7301/OnlieProgrammingServer/blob/master/picture/%E6%9C%8D%E5%8A%A1%E5%99%A8%E5%90%AF%E5%8A%A8.png)
      
### C语言测试
  ![image](https://github.com/Sakura7301/OnlieProgrammingServer/blob/master/picture/C%E8%AF%AD%E8%A8%80%E9%94%99%E8%AF%AF%E7%A4%BA%E4%BE%8B.png)
  ![image](https://github.com/Sakura7301/OnlieProgrammingServer/blob/master/picture/C%E8%AF%AD%E8%A8%80%E9%80%9A%E8%BF%87%E7%A4%BA%E4%BE%8B.png)
  
### C++测试
  ![image](https://github.com/Sakura7301/OnlieProgrammingServer/blob/master/picture/cpp%E9%94%99%E8%AF%AF%E7%A4%BA%E4%BE%8B.png)
  ![image](https://github.com/Sakura7301/OnlieProgrammingServer/blob/master/picture/cpp%E9%80%9A%E8%BF%87%E7%A4%BA%E4%BE%8B.png)
  
### python测试
  ![image](https://github.com/Sakura7301/OnlieProgrammingServer/blob/master/picture/python%E9%94%99%E8%AF%AF%E7%A4%BA%E4%BE%8B.png)
  ![image](https://github.com/Sakura7301/OnlieProgrammingServer/blob/master/picture/python%E9%80%9A%E8%BF%87%E7%A4%BA%E4%BE%8B.png)
  
  
 ## **测试效果展示:[HTTP]**
  
 ### **C测试**
  
  
  ![image](https://github.com/Sakura7301/OnlieProgrammingServer/blob/master/httptest/C.gif)
  ![image](https://github.com/Sakura7301/OnlieProgrammingServer/blob/master/httptest/C_error.gif)
  
  
 ### **C++测试**
  
  
  ![image](https://github.com/Sakura7301/OnlieProgrammingServer/blob/master/httptest/CPP.gif)
  ![image](https://github.com/Sakura7301/OnlieProgrammingServer/blob/master/httptest/CPP_error.gif)
  
  
 ### **C++测试**
  
  
  ![image](https://github.com/Sakura7301/OnlieProgrammingServer/blob/master/httptest/Python.gif)
  ![image](https://github.com/Sakura7301/OnlieProgrammingServer/blob/master/httptest/Python_error.gif)
      
     
     
 #### 未完成...
 #### 目前还缺少网页版,由于本人并不擅长制作网页,因此http的请求是使用postman模拟发出的,后续有机会会完善网页版。
  
 ### **关键词**:C/S模型、libevent、HTTP、多线程



### **user:Sakura7301**
