/*
 * 棋手服务代码
 *
 * @copyright 2019 Oppo.com
 */
#include <vector>
#include <cstdio>
#include <memory>
#include <string>
#include <iostream>
#include <sstream>
#include <grpcpp/grpcpp.h>

#include "player.grpc.pb.h"
#include "scheduler.grpc.pb.h"

using grpc::Status;
using grpc::Server;
using grpc::Channel;
using grpc::ServerBuilder;
using grpc::ClientContext;
using grpc::ServerContext;

using com::oppo::ohacker::player::Position;
using com::oppo::ohacker::player::InitRequest;
using com::oppo::ohacker::player::InitResponse;
using com::oppo::ohacker::player::MoveRequest;
using com::oppo::ohacker::player::MoveResponse;
using com::oppo::ohacker::player::ChessPosition;
using com::oppo::ohacker::player::PlayerService;

using com::oppo::ohacker::scheduler::ReadyRequest;
using com::oppo::ohacker::scheduler::ReadyResponse;
using com::oppo::ohacker::scheduler::SchedulerService;

const int   FIRSTHAND_MILITARY_FLAG = 1; //先手军旗
const int   FIRSTHAND_COMMANDER = 2; //先手司令
const int   FIRSTHAND_CHIEF = 3; //先手军长
const int   FIRSTHAND_DIVISION1 = 4; //先手师长1
const int   FIRSTHAND_DIVISION2 = 5; //先手师长2
const int   FIRSTHAND_BRIGADIER1 = 6; //先手旅长1
const int   FIRSTHAND_BRIGADIER2 = 7; //先手旅长2
const int   FIRSTHAND_REGIMENT1 = 8; //先手团长1
const int   FIRSTHAND_REGIMENT2 = 9; //先手团长2
const int   FIRSTHAND_BATTALION1 = 10; //先手营长1
const int   FIRSTHAND_BATTALION2 = 11; //先手营长2
const int   FIRSTHAND_BOMB1 = 12; //先手炸弹1
const int   FIRSTHAND_BOMB2 = 13; //先手炸弹2
const int   FIRSTHAND_COMPANY1 = 14; //先手连长1
const int   FIRSTHAND_COMPANY2 = 15; //先手连长2
const int   FIRSTHAND_COMPANY3 = 16; //先手连长3
const int   FIRSTHAND_PLATOON1 = 17; //先手排长1
const int   FIRSTHAND_PLATOON2 = 18; //先手排长2
const int   FIRSTHAND_PLATOON3 = 19; //先手排长3
const int   FIRSTHAND_SAPPER1 = 20; //先手工兵1
const int   FIRSTHAND_SAPPER2 = 21; //先手工兵2
const int   FIRSTHAND_SAPPER3 = 22; //先手工兵3
const int   FIRSTHAND_MINE1 = 23; //先手地雷1
const int   FIRSTHAND_MINE2 = 24; //先手地雷2
const int   FIRSTHAND_MINE3 = 25; //先手地雷3

const int   SECONDHAND_MILITARY_FLAG = 26; //后手军旗
const int   SECONDHAND_COMMANDER = 27; //后手司令
const int   SECONDHAND_CHIEF = 28; //后手军长
const int   SECONDHAND_DIVISION1 = 29; //后手师长1
const int   SECONDHAND_DIVISION2 = 30; //后手师长2
const int   SECONDHAND_BRIGADIER1 = 31; //后手旅长1
const int   SECONDHAND_BRIGADIER2 = 32; //后手旅长2
const int   SECONDHAND_REGIMENT1 = 33; //后手团长1
const int   SECONDHAND_REGIMENT2 = 34; //后手团长2
const int   SECONDHAND_BATTALION1 = 35; //后手营长1
const int   SECONDHAND_BATTALION2 = 36; //后手营长2
const int   SECONDHAND_BOMB1 = 37; //后手炸弹1
const int   SECONDHAND_BOMB2 = 38; //后手炸弹2
const int   SECONDHAND_COMPANY1 = 39; //后手连长1
const int   SECONDHAND_COMPANY2 = 40; //后手连长2
const int   SECONDHAND_COMPANY3 = 41; //后手连长3
const int   SECONDHAND_PLATOON1 = 42; //后手排长1
const int   SECONDHAND_PLATOON2 = 43; //后手排长2
const int   SECONDHAND_PLATOON3 = 44; //后手排长3
const int   SECONDHAND_SAPPER1 = 45; //后手工兵1
const int   SECONDHAND_SAPPER2 = 46; //后手工兵2
const int   SECONDHAND_SAPPER3 = 47; //后手工兵3
const int   SECONDHAND_MINE1 = 48; //后手地雷1
const int   SECONDHAND_MINE2 = 49; //后手地雷2
const int   SECONDHAND_MINE3 = 50; //后手地雷3

bool IS_FIRSTHAND; //是否为先手

const int   MILITARY_FLAG_VALUE = 1; //军旗
const int   COMMANDER_VALUE = 2; //司令
const int   CHIEF_VALUE = 3; //军长
const int   DIVISION_VALUE = 4; //师长
const int   REGIMENT_VALUE = 5; //旅长
const int   BRIGADIER_VALUE = 6; //团长
const int   BATTALION_VALUE = 7; //营长
const int   BOMB_VALUE = 8; //炸弹
const int   COMPANY_VALUE = 9; //连长
const int   PLATOON_VALUE = 10; //排长
const int   SAPPER_VALUE = 11; //工兵
const int   MINE_VALUE = 12; //炸弹







/**
 * 棋手服务
 * 
 * 这里已经实现了基本框架，参赛的开发人员只需要实现initMap和move接口
 * 接口里面也已经有了示例代码，开发人员可以参考说明文档编写
 * !!!注意框架代码不要任意改动，可能导致程序不能正常运行
 */
class PlayerServiceImpl final : public PlayerService::Service {

private:
    std::unique_ptr<SchedulerService::Stub> stub_;

public:
    PlayerServiceImpl(std::shared_ptr<Channel> channel)
          : stub_(SchedulerService::NewStub(channel)) {}

    /**
     * 通知服务端客户端已经就绪
     * 通常情况下不需要修改该方法
     * @return 0 成功，其他值失败
     */
    int ready() {
        ReadyRequest request;
        ReadyResponse response;
        ClientContext context;

        request.set_playerhost(std::getenv("PLAYER_HOST_IP"));
        request.set_playerport(std::stoi(std::getenv("PLAYER_HOST_PORT")));
        request.set_matchid(std::stoi(std::getenv("MATCH_ID")));
        request.set_teamid(std::stoi(std::getenv("TEAM_ID")));

        Status status = stub_->ready(&context, request, &response);

        std::cout << "ready-response: " << response.ShortDebugString()
                        << std::endl;
        if (status.ok()) {
            return 0;
        } else {
            std::cout << "Call scheduler ready failed, code: " << status.error_code()
                    << ", message: " << status.error_message()
                    << std::endl;
            return 1;
        }
    }

    ChessPosition Init_chess_position(int id, int value, int posx, int posy, ChessPosition chess_position)
    {

        chess_position.mutable_chess()->set_chessid(id);
        chess_position.mutable_chess()->set_value(value);
        chess_position.mutable_position()->set_x(posx);
        chess_position.mutable_position()->set_y(posy);
        return chess_position;
    }

    int find_pos(std::vect,ChessPosition a)
    {
        pos
    }



    int Find_chess(ChessPosition )//找到可以走的棋子


    void Chess_move(ChessPosition& Chess,int ID ,int now_x,int now_y,int Finally_x,int Finally_y)
    {
        std::queue <int> po
    }
    /**
     * 初始化棋盘
     * 
     * 设置棋子到棋盘相应的位置, 可以根据策略排列棋子
     * 这里的代码仅仅是一个示例
     *
     * @param context grpc通信上下文，无需处理
     * @param request 初始化棋盘请求，属性order=isFirstHand表示先手，否则后手
     * @param response 返回棋盘初始化信息，参考示例代码
     */
    Status initChessBoard(ServerContext* context, const InitRequest* request,
            InitResponse* response) {
        std::cout << "initChessBoard-request: " << request->DebugString() << std::endl;
        //TODO: 初始化棋盘
        //初始布局
        int chess_pos_first[30][4]={{FIRSTHAND_BRIGADIER1,BRIGADIER_VALUE,0,11},{FIRSTHAND_PLATOON1,PLATOON_VALUE,1,11},{FIRSTHAND_COMPANY1,COMPANY_VALUE,2,11},{FIRSTHAND_MILITARY_FLAG,MILITARY_FLAG_VALUE,3,11},{FIRSTHAND_MINE1,MINE_VALUE,4,11},
                                    {FIRSTHAND_SAPPER1,SAPPER_VALUE,0,10},{FIRSTHAND_SAPPER2,SAPPER_VALUE,1,10},{FIRSTHAND_MINE2,MINE_VALUE,2,10},{FIRSTHAND_MINE3,MINE_VALUE,3,10},{FIRSTHAND_BATTALION1,BATTALION_VALUE,4,10},
                                    {FIRSTHAND_DIVISION1,DIVISION_VALUE,0,9},{0,0,1,9},{FIRSTHAND_BRIGADIER2,BRIGADIER_VALUE,2,9},{0,0,3,9},{FIRSTHAND_PLATOON2,PLATOON_VALUE,4,9},
                                    {FIRSTHAND_BOMB1,BOMB_VALUE,0,8},{FIRSTHAND_PLATOON3,PLATOON_VALUE,1,8},{0,0,2,8},{FIRSTHAND_BATTALION2,BATTALION_VALUE,3,8},{FIRSTHAND_BOMB2,BOMB_VALUE,4,8},
                                    {FIRSTHAND_COMMANDER,COMMANDER_VALUE,0,7},{0,0,1,7},{FIRSTHAND_SAPPER3,SAPPER_VALUE,2,7},{0,0,3,7},{FIRSTHAND_CHIEF,CHIEF_VALUE,4,7},
                                    {FIRSTHAND_DIVISION2,DIVISION_VALUE,0,6},{FIRSTHAND_COMPANY2,COMPANY_VALUE,1,6},{FIRSTHAND_REGIMENT1,REGIMENT_VALUE,2,6},{FIRSTHAND_COMPANY3,COMPANY_VALUE,3,6},{FIRSTHAND_REGIMENT2,REGIMENT_VALUE,4,6}};
        int chess_pos_second[30][4]={{SECONDHAND_REGIMENT1,REGIMENT_VALUE,0,5},{SECONDHAND_SAPPER1,SAPPER_VALUE,1,5},{SECONDHAND_CHIEF,CHIEF_VALUE,2,5},{SECONDHAND_PLATOON1,PLATOON_VALUE,3,5},{SECONDHAND_BATTALION1,BATTALION_VALUE,4,5},
                                     {SECONDHAND_COMMANDER,COMMANDER_VALUE,0,4},{0,0,1,4},{SECONDHAND_SAPPER2,SAPPER_VALUE,2,4},{0,0,3,4},{SECONDHAND_DIVISION1,DIVISION_VALUE,4,4},
                                     {SECONDHAND_BOMB1,BOMB_VALUE,0,3},{SECONDHAND_BRIGADIER1,BRIGADIER_VALUE,1,3},{0,0,2,3},{SECONDHAND_BATTALION2,BATTALION_VALUE,3,3},{SECONDHAND_COMPANY1,COMPANY_VALUE,4,3},
                                     {SECONDHAND_COMPANY2,COMPANY_VALUE,0,2},{0,0,1,2},{SECONDHAND_PLATOON2,PLATOON_VALUE,2,2},{0,0,3,2},{SECONDHAND_PLATOON3,PLATOON_VALUE,4,2},
                                     {SECONDHAND_MINE1,MINE_VALUE,0,1},{SECONDHAND_COMPANY3,COMPANY_VALUE,1,1},{SECONDHAND_DIVISION2,DIVISION_VALUE,2,1},{SECONDHAND_BOMB2,BOMB_VALUE,3,1},{SECONDHAND_BRIGADIER2,BRIGADIER_VALUE,4,1},
                                     {SECONDHAND_MINE2,MINE_VALUE,0,0},{SECONDHAND_MILITARY_FLAG,MILITARY_FLAG_VALUE,1,0},{SECONDHAND_REGIMENT2,REGIMENT_VALUE,2,0},{SECONDHAND_MINE3,MINE_VALUE,3,0},{SECONDHAND_SAPPER3,SAPPER_VALUE,4,0}};


        ChessPosition chess_position;
        IS_FIRSTHAND = request->isfirsthand();  //判断先手
        if(IS_FIRSTHAND)
        {
           for(int i=0;i<30;i++){
               if(chess_pos_first[i][0]!=0 && chess_pos_first[i][1] != 0) {
                   chess_position = Init_chess_position(chess_pos_first[i][0], chess_pos_first[i][1],
                                                        chess_pos_first[i][2], chess_pos_first[i][3], chess_position);
                   response->add_chessposition()->CopyFrom(chess_position);
               }
           }
        }
        else
        {
            for(int i=0;i<30;i++){
               if(chess_pos_second[i][0]!=0 && chess_pos_second[i][1] != 0) {
                   chess_position = Init_chess_position(chess_pos_second[i][0], chess_pos_second[i][1],
                                                        chess_pos_second[i][2], chess_pos_second[i][3], chess_position);
                   response->add_chessposition()->CopyFrom(chess_position);
               }
            }
        }
       //* ChessPosition chess_position;
        // 设置棋子，参考棋子说明
        //chess_position.mutable_chess()->set_chessid(2);
        //chess_position.mutable_chess()->set_value(2);
        // 设置棋子坐标，参考棋盘说明
        //chess_position.mutable_position()->set_x(0);
        //chess_position.mutable_position()->set_y(10);

        // 把棋子加到棋盘
        //response->add_chessposition()->CopyFrom(chess_position);

        std::cout << "initChessBoard-response: " << response->ShortDebugString()
                << std::endl;
        return Status::OK;
    }

    /**
     * 移动棋子
     * 
     * 设置棋子到棋盘相应的位置, 可以根据策略排列棋子
     * 这里的代码仅仅是一个示例
     * @param context grpc通信上下文，无需处理
     * @param request 初始化棋盘请求，属性maps表示当前棋盘信息
     * @param response 返回棋子移动位置，参考示例代码
     */
    Status move(ServerContext* context, const MoveRequest* request,
            MoveResponse* response) {
        std::cout << "move-request: " << request->ShortDebugString()
                << std::endl;

        ChessPosition chess;
      //每次下子前扫描一遍棋盘信息
      //
        for(int i = 0 ; i < 50; i++)
        {
             chess = request->chesspositions(i);
            if(IS_FIRSTHAND)
            {
                if(i<25)
                {
                    map[chess.position().y()][chess.position().x()]=chess.chess().value();
                }
                else{

                }
            }
            else(!IS_FIRSTHAND)
            {
                if(i<25)
                {

                }
                else{

                }
            }


        }


        //将要走的位置放在一个queue中，移动时出队
        std::queue <Position> Move_chess_pos;
        Chess_move(Move_chess_pos,);
        for(;!Move_chess_pos.empty();Move_chess_pos.push())
        {
            response->add_position()->CopyFrom(Move_chess_pos.front());
        }
        // 位置在 (0,10) 的旗子
        Position position0;
        position0.set_x(0);
        position0.set_y(10);

        // 移动到 (0,5) 位置
        Position position1;
        position1.set_x(0);
        position1.set_y(5);

        // 移动路径
        response->add_position()->CopyFrom(position0);
        response->add_position()->CopyFrom(position1);

        std::cout << "move-response: " << response->ShortDebugString()
                << std::endl;
        return Status::OK;
    }
};

/**
 * 启动棋手服务
 */
int RunServer() {
    // 客户端分配的监听端口，来自环境变量
    int clinet_port = std::stoi(std::getenv("PLAYER_HOST_PORT"));
    // 客户端分配的监听地址
    std::stringstream player_address;
    player_address << "0.0.0.0:" << clinet_port;

    // 服务端连接地址，来自环境变量
    std::stringstream server_address;
        server_address << std::getenv("HOST_IP") << ":" << std::getenv("HOST_PORT");

    // 创建服务端
    PlayerServiceImpl playerService(grpc::CreateChannel(server_address.str(), grpc::InsecureChannelCredentials()));
    // 注册服务端，并启动监听
    ServerBuilder builder;
    builder.AddListeningPort(player_address.str(), grpc::InsecureServerCredentials());
    builder.RegisterService(&playerService);
    std::unique_ptr<Server> server(builder.BuildAndStart());
    std::cout << "Server listening on " << server_address.str() << std::endl;

    // 通知服务端，启动完成，准备接受命令
    int ready = playerService.ready();
    if (0 != ready) {
        // 通知失败，退出
        std::cout << "Server is not ready exit";
        return 1;
    }

    // 服务线程等待
    server->Wait();
    return 0;
}

/**
 * 程序入口
 */
int main(int argc, char** argv) {
    RunServer();
    return 0;
}

