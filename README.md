## 视频会议简介

客户端开发需要用到两部分：API和SDK。

API是以HTTP Restful形式提供的一组接口，主要负责帐号的登录、注册、充值、会议管理等操作，通过API接口获取到相应的入会凭证，然后才可以使用SDK库进入会议室，API详细接口请参见[《VCS服务端API开发手册》](https://www.yuque.com/anyconf/api?#)。

## 示例的使用

#### step 1：下载示例到本地

```
git clone git@github.com:seastart/vcs-winidows-demo.git
```

#### step 2：下载SDK到到本地

SDK下载到指定目录
[SDK下载地址](https://repo.open.seastart.cn/repository/vcs-releases/vcs-win-sdk-1.0.rar)


###### 目录内容
```
├─ CPP                    // 提供 C++ 语言 Demo
│  ├─ vcsDemo.pro         // 提供 Qt Creator Ide 
│  ├─ vcsDemo.sln         // 提供 Qt Vs Ide     
├─ CSharp                 // 提供 c# 语言Demo
│  ├─ vcsDemo.sln         // 提供 Vs Ide 
├─ SDK                    // SDK 应用目录
│  ├─ include             // SDK C++ 头文件目录
│  │  ├─ vcs.h            // SDK C++ 关键头文件
│  ├─ x86                 // SDK C++ 链接库目录
│  │  ├─ vcs.lib          // SDK C++ 链接库
│  │  ├─ ...
├─ out                    // SDK Demo 输出目录（编译成功后可执行文件位置）
```

#### step 3：替换申请的AppID和AppKey

CPP Code
```
    HttpNetwork::Get()->SetAppid("<# 替换成平台分配的AppID #>");
    HttpNetwork::Get()->SetAppkey("<# 替换成平台分配的AppID #>");
```

C# Code
```
    Appid = "<# 替换成平台分配的AppID #>";
    Appkey = "<# 替换成平台分配的AppID #>";
```

#### step 4：编译&复制依赖库到输出目录



## Author

MUSX, carl_musx@163.com


## License

VCSSDK is available under the MIT license. See the LICENSE file for more info.







