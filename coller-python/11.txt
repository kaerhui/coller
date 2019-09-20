# 棋手服务C++示例

## 运行环境
本次参赛代码运行环境为Linux，本示例代码是在ubuntu 16.04测试通过，因此推荐用ubuntu 16.04编译和测试

### 安装编译环境
$ sudo apt-get install -y build-essential autoconf libtool pkg-config git

### 编译安装 grpc
本次参赛服务端为Java开发，棋手客户端支持C++和Java，跨语言通信用grpc，因此需要安装grpc和protobuf依赖库
grpc和protobuf的代码已经生成，不需要再次生成

$ git clone https://github.com/grpc/grpc.git 
$ cd grpc
$ export CXXFLAGS="-Wno-error"
$ git submodule update --init
$ sudo make install

### 编译安装 protobuf
$ cd third_party/protobuf
$ sudo make install

## 编译示例

$ cd player-demo
$ make

这时候已经生成了二进制player-server程序

## 编写下棋逻辑

开发人员只需要修改：player_server.cc文件里initChessBoard和move的代码即可，详情可参看代码注释和文档。

## 运行示例

目前不能在您本地调试运行，需要将代码完成后，在本地保证编译通过，然后上传代码到仓库，在对战平台模拟测试，
因此需要您加更多日志来调试。
