# Experiences
study/work experiences  
工作或学习的收获

## 1.A Study in Kaa  
[Kaa](https:://kaaproject.github.io/kaa/docs/v0.10.0/Welcome/) is an open-source IOT platform to solve the problem of communication between client and server.  
Kaa是一个开源的IOT平台，还连同Azure IoT Suite, IBM Watson等一起被评为[2017年度IOT平台的TOP5](https://www.sam-solutions.com/blog/top-5-iot-platforms-2017/)  

Kaa Platform Investigation Report  
[KaaIOT平台项目的研究报告](https://github.com/caibinice/works/blob/master/kaaReport.xlsx)

RaspberryPi and Its Communication With Kaa Investigation Report  
[树莓派学习成果及其与Kaa平台的通信研究报告](https://github.com/caibinice/works/blob/master/raspberryPiReport.xlsx)  
  
本章提供了一个JAVA版本的DEMO，展示了如何使用kaa平台提供的沙盒搭建一个小的IOT数据服务器(详细的过程请参考上述研究报告和官网)，利用配套的SDK在终端(可以是树莓派,android,centos...等)运行kaa client，并用代码实现和server相互通信的功能。  

## 2.Apache Avro  
[Apache Avro](https://avro.apache.org/docs/current/) is a data serialization system which provides
rich data structures, a compact and fast data format, a container to store persistent data, and remote procedure call (RPC).  
Apache Avro是Apache的一个独立项目，也是Hadoop框架中的一个子项目，Kaa平台也使用了它。  
Avro是一个数据序列化的系统，将数据结构或对象转化成便于存储或传输的格式，是高性能二进制数据传输的中间件，为Client端与Server端的数据交互提供了便利。  
  
本章使用java完成了一个使用avro插件来模拟存储(传输)和读取数据的demo。