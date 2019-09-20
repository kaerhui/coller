// Generated by the gRPC C++ plugin.
// If you make any local change, they will be lost.
// source: player.proto
// Original file comments:
// Copyright 2015 gRPC authors.
// 
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
// 
//     http://www.apache.org/licenses/LICENSE-2.0
// 
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//
#ifndef GRPC_player_2eproto__INCLUDED
#define GRPC_player_2eproto__INCLUDED

#include "player.pb.h"

#include <functional>
#include <grpcpp/impl/codegen/async_generic_service.h>
#include <grpcpp/impl/codegen/async_stream.h>
#include <grpcpp/impl/codegen/async_unary_call.h>
#include <grpcpp/impl/codegen/client_callback.h>
#include <grpcpp/impl/codegen/method_handler_impl.h>
#include <grpcpp/impl/codegen/proto_utils.h>
#include <grpcpp/impl/codegen/rpc_method.h>
#include <grpcpp/impl/codegen/server_callback.h>
#include <grpcpp/impl/codegen/service_type.h>
#include <grpcpp/impl/codegen/status.h>
#include <grpcpp/impl/codegen/stub_options.h>
#include <grpcpp/impl/codegen/sync_stream.h>

namespace grpc {
class CompletionQueue;
class Channel;
class ServerCompletionQueue;
class ServerContext;
}  // namespace grpc

namespace com {
namespace oppo {
namespace ohacker {
namespace player {

// The player service definition.
class PlayerService final {
 public:
  static constexpr char const* service_full_name() {
    return "com.oppo.ohacker.player.PlayerService";
  }
  class StubInterface {
   public:
    virtual ~StubInterface() {}
    virtual ::grpc::Status initChessBoard(::grpc::ClientContext* context, const ::com::oppo::ohacker::player::InitRequest& request, ::com::oppo::ohacker::player::InitResponse* response) = 0;
    std::unique_ptr< ::grpc::ClientAsyncResponseReaderInterface< ::com::oppo::ohacker::player::InitResponse>> AsyncinitChessBoard(::grpc::ClientContext* context, const ::com::oppo::ohacker::player::InitRequest& request, ::grpc::CompletionQueue* cq) {
      return std::unique_ptr< ::grpc::ClientAsyncResponseReaderInterface< ::com::oppo::ohacker::player::InitResponse>>(AsyncinitChessBoardRaw(context, request, cq));
    }
    std::unique_ptr< ::grpc::ClientAsyncResponseReaderInterface< ::com::oppo::ohacker::player::InitResponse>> PrepareAsyncinitChessBoard(::grpc::ClientContext* context, const ::com::oppo::ohacker::player::InitRequest& request, ::grpc::CompletionQueue* cq) {
      return std::unique_ptr< ::grpc::ClientAsyncResponseReaderInterface< ::com::oppo::ohacker::player::InitResponse>>(PrepareAsyncinitChessBoardRaw(context, request, cq));
    }
    virtual ::grpc::Status move(::grpc::ClientContext* context, const ::com::oppo::ohacker::player::MoveRequest& request, ::com::oppo::ohacker::player::MoveResponse* response) = 0;
    std::unique_ptr< ::grpc::ClientAsyncResponseReaderInterface< ::com::oppo::ohacker::player::MoveResponse>> Asyncmove(::grpc::ClientContext* context, const ::com::oppo::ohacker::player::MoveRequest& request, ::grpc::CompletionQueue* cq) {
      return std::unique_ptr< ::grpc::ClientAsyncResponseReaderInterface< ::com::oppo::ohacker::player::MoveResponse>>(AsyncmoveRaw(context, request, cq));
    }
    std::unique_ptr< ::grpc::ClientAsyncResponseReaderInterface< ::com::oppo::ohacker::player::MoveResponse>> PrepareAsyncmove(::grpc::ClientContext* context, const ::com::oppo::ohacker::player::MoveRequest& request, ::grpc::CompletionQueue* cq) {
      return std::unique_ptr< ::grpc::ClientAsyncResponseReaderInterface< ::com::oppo::ohacker::player::MoveResponse>>(PrepareAsyncmoveRaw(context, request, cq));
    }
    class experimental_async_interface {
     public:
      virtual ~experimental_async_interface() {}
      virtual void initChessBoard(::grpc::ClientContext* context, const ::com::oppo::ohacker::player::InitRequest* request, ::com::oppo::ohacker::player::InitResponse* response, std::function<void(::grpc::Status)>) = 0;
      virtual void initChessBoard(::grpc::ClientContext* context, const ::grpc::ByteBuffer* request, ::com::oppo::ohacker::player::InitResponse* response, std::function<void(::grpc::Status)>) = 0;
      virtual void move(::grpc::ClientContext* context, const ::com::oppo::ohacker::player::MoveRequest* request, ::com::oppo::ohacker::player::MoveResponse* response, std::function<void(::grpc::Status)>) = 0;
      virtual void move(::grpc::ClientContext* context, const ::grpc::ByteBuffer* request, ::com::oppo::ohacker::player::MoveResponse* response, std::function<void(::grpc::Status)>) = 0;
    };
    virtual class experimental_async_interface* experimental_async() { return nullptr; }
  private:
    virtual ::grpc::ClientAsyncResponseReaderInterface< ::com::oppo::ohacker::player::InitResponse>* AsyncinitChessBoardRaw(::grpc::ClientContext* context, const ::com::oppo::ohacker::player::InitRequest& request, ::grpc::CompletionQueue* cq) = 0;
    virtual ::grpc::ClientAsyncResponseReaderInterface< ::com::oppo::ohacker::player::InitResponse>* PrepareAsyncinitChessBoardRaw(::grpc::ClientContext* context, const ::com::oppo::ohacker::player::InitRequest& request, ::grpc::CompletionQueue* cq) = 0;
    virtual ::grpc::ClientAsyncResponseReaderInterface< ::com::oppo::ohacker::player::MoveResponse>* AsyncmoveRaw(::grpc::ClientContext* context, const ::com::oppo::ohacker::player::MoveRequest& request, ::grpc::CompletionQueue* cq) = 0;
    virtual ::grpc::ClientAsyncResponseReaderInterface< ::com::oppo::ohacker::player::MoveResponse>* PrepareAsyncmoveRaw(::grpc::ClientContext* context, const ::com::oppo::ohacker::player::MoveRequest& request, ::grpc::CompletionQueue* cq) = 0;
  };
  class Stub final : public StubInterface {
   public:
    Stub(const std::shared_ptr< ::grpc::ChannelInterface>& channel);
    ::grpc::Status initChessBoard(::grpc::ClientContext* context, const ::com::oppo::ohacker::player::InitRequest& request, ::com::oppo::ohacker::player::InitResponse* response) override;
    std::unique_ptr< ::grpc::ClientAsyncResponseReader< ::com::oppo::ohacker::player::InitResponse>> AsyncinitChessBoard(::grpc::ClientContext* context, const ::com::oppo::ohacker::player::InitRequest& request, ::grpc::CompletionQueue* cq) {
      return std::unique_ptr< ::grpc::ClientAsyncResponseReader< ::com::oppo::ohacker::player::InitResponse>>(AsyncinitChessBoardRaw(context, request, cq));
    }
    std::unique_ptr< ::grpc::ClientAsyncResponseReader< ::com::oppo::ohacker::player::InitResponse>> PrepareAsyncinitChessBoard(::grpc::ClientContext* context, const ::com::oppo::ohacker::player::InitRequest& request, ::grpc::CompletionQueue* cq) {
      return std::unique_ptr< ::grpc::ClientAsyncResponseReader< ::com::oppo::ohacker::player::InitResponse>>(PrepareAsyncinitChessBoardRaw(context, request, cq));
    }
    ::grpc::Status move(::grpc::ClientContext* context, const ::com::oppo::ohacker::player::MoveRequest& request, ::com::oppo::ohacker::player::MoveResponse* response) override;
    std::unique_ptr< ::grpc::ClientAsyncResponseReader< ::com::oppo::ohacker::player::MoveResponse>> Asyncmove(::grpc::ClientContext* context, const ::com::oppo::ohacker::player::MoveRequest& request, ::grpc::CompletionQueue* cq) {
      return std::unique_ptr< ::grpc::ClientAsyncResponseReader< ::com::oppo::ohacker::player::MoveResponse>>(AsyncmoveRaw(context, request, cq));
    }
    std::unique_ptr< ::grpc::ClientAsyncResponseReader< ::com::oppo::ohacker::player::MoveResponse>> PrepareAsyncmove(::grpc::ClientContext* context, const ::com::oppo::ohacker::player::MoveRequest& request, ::grpc::CompletionQueue* cq) {
      return std::unique_ptr< ::grpc::ClientAsyncResponseReader< ::com::oppo::ohacker::player::MoveResponse>>(PrepareAsyncmoveRaw(context, request, cq));
    }
    class experimental_async final :
      public StubInterface::experimental_async_interface {
     public:
      void initChessBoard(::grpc::ClientContext* context, const ::com::oppo::ohacker::player::InitRequest* request, ::com::oppo::ohacker::player::InitResponse* response, std::function<void(::grpc::Status)>) override;
      void initChessBoard(::grpc::ClientContext* context, const ::grpc::ByteBuffer* request, ::com::oppo::ohacker::player::InitResponse* response, std::function<void(::grpc::Status)>) override;
      void move(::grpc::ClientContext* context, const ::com::oppo::ohacker::player::MoveRequest* request, ::com::oppo::ohacker::player::MoveResponse* response, std::function<void(::grpc::Status)>) override;
      void move(::grpc::ClientContext* context, const ::grpc::ByteBuffer* request, ::com::oppo::ohacker::player::MoveResponse* response, std::function<void(::grpc::Status)>) override;
     private:
      friend class Stub;
      explicit experimental_async(Stub* stub): stub_(stub) { }
      Stub* stub() { return stub_; }
      Stub* stub_;
    };
    class experimental_async_interface* experimental_async() override { return &async_stub_; }

   private:
    std::shared_ptr< ::grpc::ChannelInterface> channel_;
    class experimental_async async_stub_{this};
    ::grpc::ClientAsyncResponseReader< ::com::oppo::ohacker::player::InitResponse>* AsyncinitChessBoardRaw(::grpc::ClientContext* context, const ::com::oppo::ohacker::player::InitRequest& request, ::grpc::CompletionQueue* cq) override;
    ::grpc::ClientAsyncResponseReader< ::com::oppo::ohacker::player::InitResponse>* PrepareAsyncinitChessBoardRaw(::grpc::ClientContext* context, const ::com::oppo::ohacker::player::InitRequest& request, ::grpc::CompletionQueue* cq) override;
    ::grpc::ClientAsyncResponseReader< ::com::oppo::ohacker::player::MoveResponse>* AsyncmoveRaw(::grpc::ClientContext* context, const ::com::oppo::ohacker::player::MoveRequest& request, ::grpc::CompletionQueue* cq) override;
    ::grpc::ClientAsyncResponseReader< ::com::oppo::ohacker::player::MoveResponse>* PrepareAsyncmoveRaw(::grpc::ClientContext* context, const ::com::oppo::ohacker::player::MoveRequest& request, ::grpc::CompletionQueue* cq) override;
    const ::grpc::internal::RpcMethod rpcmethod_initChessBoard_;
    const ::grpc::internal::RpcMethod rpcmethod_move_;
  };
  static std::unique_ptr<Stub> NewStub(const std::shared_ptr< ::grpc::ChannelInterface>& channel, const ::grpc::StubOptions& options = ::grpc::StubOptions());

  class Service : public ::grpc::Service {
   public:
    Service();
    virtual ~Service();
    virtual ::grpc::Status initChessBoard(::grpc::ServerContext* context, const ::com::oppo::ohacker::player::InitRequest* request, ::com::oppo::ohacker::player::InitResponse* response);
    virtual ::grpc::Status move(::grpc::ServerContext* context, const ::com::oppo::ohacker::player::MoveRequest* request, ::com::oppo::ohacker::player::MoveResponse* response);
  };
  template <class BaseClass>
  class WithAsyncMethod_initChessBoard : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service *service) {}
   public:
    WithAsyncMethod_initChessBoard() {
      ::grpc::Service::MarkMethodAsync(0);
    }
    ~WithAsyncMethod_initChessBoard() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status initChessBoard(::grpc::ServerContext* context, const ::com::oppo::ohacker::player::InitRequest* request, ::com::oppo::ohacker::player::InitResponse* response) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    void RequestinitChessBoard(::grpc::ServerContext* context, ::com::oppo::ohacker::player::InitRequest* request, ::grpc::ServerAsyncResponseWriter< ::com::oppo::ohacker::player::InitResponse>* response, ::grpc::CompletionQueue* new_call_cq, ::grpc::ServerCompletionQueue* notification_cq, void *tag) {
      ::grpc::Service::RequestAsyncUnary(0, context, request, response, new_call_cq, notification_cq, tag);
    }
  };
  template <class BaseClass>
  class WithAsyncMethod_move : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service *service) {}
   public:
    WithAsyncMethod_move() {
      ::grpc::Service::MarkMethodAsync(1);
    }
    ~WithAsyncMethod_move() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status move(::grpc::ServerContext* context, const ::com::oppo::ohacker::player::MoveRequest* request, ::com::oppo::ohacker::player::MoveResponse* response) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    void Requestmove(::grpc::ServerContext* context, ::com::oppo::ohacker::player::MoveRequest* request, ::grpc::ServerAsyncResponseWriter< ::com::oppo::ohacker::player::MoveResponse>* response, ::grpc::CompletionQueue* new_call_cq, ::grpc::ServerCompletionQueue* notification_cq, void *tag) {
      ::grpc::Service::RequestAsyncUnary(1, context, request, response, new_call_cq, notification_cq, tag);
    }
  };
  typedef WithAsyncMethod_initChessBoard<WithAsyncMethod_move<Service > > AsyncService;
  template <class BaseClass>
  class ExperimentalWithCallbackMethod_initChessBoard : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service *service) {}
   public:
    ExperimentalWithCallbackMethod_initChessBoard() {
      ::grpc::Service::experimental().MarkMethodCallback(0,
        new ::grpc::internal::CallbackUnaryHandler< ::com::oppo::ohacker::player::InitRequest, ::com::oppo::ohacker::player::InitResponse>(
          [this](::grpc::ServerContext* context,
                 const ::com::oppo::ohacker::player::InitRequest* request,
                 ::com::oppo::ohacker::player::InitResponse* response,
                 ::grpc::experimental::ServerCallbackRpcController* controller) {
                   return this->initChessBoard(context, request, response, controller);
                 }));
    }
    ~ExperimentalWithCallbackMethod_initChessBoard() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status initChessBoard(::grpc::ServerContext* context, const ::com::oppo::ohacker::player::InitRequest* request, ::com::oppo::ohacker::player::InitResponse* response) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    virtual void initChessBoard(::grpc::ServerContext* context, const ::com::oppo::ohacker::player::InitRequest* request, ::com::oppo::ohacker::player::InitResponse* response, ::grpc::experimental::ServerCallbackRpcController* controller) { controller->Finish(::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "")); }
  };
  template <class BaseClass>
  class ExperimentalWithCallbackMethod_move : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service *service) {}
   public:
    ExperimentalWithCallbackMethod_move() {
      ::grpc::Service::experimental().MarkMethodCallback(1,
        new ::grpc::internal::CallbackUnaryHandler< ::com::oppo::ohacker::player::MoveRequest, ::com::oppo::ohacker::player::MoveResponse>(
          [this](::grpc::ServerContext* context,
                 const ::com::oppo::ohacker::player::MoveRequest* request,
                 ::com::oppo::ohacker::player::MoveResponse* response,
                 ::grpc::experimental::ServerCallbackRpcController* controller) {
                   return this->move(context, request, response, controller);
                 }));
    }
    ~ExperimentalWithCallbackMethod_move() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status move(::grpc::ServerContext* context, const ::com::oppo::ohacker::player::MoveRequest* request, ::com::oppo::ohacker::player::MoveResponse* response) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    virtual void move(::grpc::ServerContext* context, const ::com::oppo::ohacker::player::MoveRequest* request, ::com::oppo::ohacker::player::MoveResponse* response, ::grpc::experimental::ServerCallbackRpcController* controller) { controller->Finish(::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "")); }
  };
  typedef ExperimentalWithCallbackMethod_initChessBoard<ExperimentalWithCallbackMethod_move<Service > > ExperimentalCallbackService;
  template <class BaseClass>
  class WithGenericMethod_initChessBoard : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service *service) {}
   public:
    WithGenericMethod_initChessBoard() {
      ::grpc::Service::MarkMethodGeneric(0);
    }
    ~WithGenericMethod_initChessBoard() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status initChessBoard(::grpc::ServerContext* context, const ::com::oppo::ohacker::player::InitRequest* request, ::com::oppo::ohacker::player::InitResponse* response) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
  };
  template <class BaseClass>
  class WithGenericMethod_move : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service *service) {}
   public:
    WithGenericMethod_move() {
      ::grpc::Service::MarkMethodGeneric(1);
    }
    ~WithGenericMethod_move() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status move(::grpc::ServerContext* context, const ::com::oppo::ohacker::player::MoveRequest* request, ::com::oppo::ohacker::player::MoveResponse* response) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
  };
  template <class BaseClass>
  class WithRawMethod_initChessBoard : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service *service) {}
   public:
    WithRawMethod_initChessBoard() {
      ::grpc::Service::MarkMethodRaw(0);
    }
    ~WithRawMethod_initChessBoard() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status initChessBoard(::grpc::ServerContext* context, const ::com::oppo::ohacker::player::InitRequest* request, ::com::oppo::ohacker::player::InitResponse* response) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    void RequestinitChessBoard(::grpc::ServerContext* context, ::grpc::ByteBuffer* request, ::grpc::ServerAsyncResponseWriter< ::grpc::ByteBuffer>* response, ::grpc::CompletionQueue* new_call_cq, ::grpc::ServerCompletionQueue* notification_cq, void *tag) {
      ::grpc::Service::RequestAsyncUnary(0, context, request, response, new_call_cq, notification_cq, tag);
    }
  };
  template <class BaseClass>
  class WithRawMethod_move : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service *service) {}
   public:
    WithRawMethod_move() {
      ::grpc::Service::MarkMethodRaw(1);
    }
    ~WithRawMethod_move() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status move(::grpc::ServerContext* context, const ::com::oppo::ohacker::player::MoveRequest* request, ::com::oppo::ohacker::player::MoveResponse* response) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    void Requestmove(::grpc::ServerContext* context, ::grpc::ByteBuffer* request, ::grpc::ServerAsyncResponseWriter< ::grpc::ByteBuffer>* response, ::grpc::CompletionQueue* new_call_cq, ::grpc::ServerCompletionQueue* notification_cq, void *tag) {
      ::grpc::Service::RequestAsyncUnary(1, context, request, response, new_call_cq, notification_cq, tag);
    }
  };
  template <class BaseClass>
  class ExperimentalWithRawCallbackMethod_initChessBoard : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service *service) {}
   public:
    ExperimentalWithRawCallbackMethod_initChessBoard() {
      ::grpc::Service::experimental().MarkMethodRawCallback(0,
        new ::grpc::internal::CallbackUnaryHandler< ::grpc::ByteBuffer, ::grpc::ByteBuffer>(
          [this](::grpc::ServerContext* context,
                 const ::grpc::ByteBuffer* request,
                 ::grpc::ByteBuffer* response,
                 ::grpc::experimental::ServerCallbackRpcController* controller) {
                   this->initChessBoard(context, request, response, controller);
                 }));
    }
    ~ExperimentalWithRawCallbackMethod_initChessBoard() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status initChessBoard(::grpc::ServerContext* context, const ::com::oppo::ohacker::player::InitRequest* request, ::com::oppo::ohacker::player::InitResponse* response) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    virtual void initChessBoard(::grpc::ServerContext* context, const ::grpc::ByteBuffer* request, ::grpc::ByteBuffer* response, ::grpc::experimental::ServerCallbackRpcController* controller) { controller->Finish(::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "")); }
  };
  template <class BaseClass>
  class ExperimentalWithRawCallbackMethod_move : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service *service) {}
   public:
    ExperimentalWithRawCallbackMethod_move() {
      ::grpc::Service::experimental().MarkMethodRawCallback(1,
        new ::grpc::internal::CallbackUnaryHandler< ::grpc::ByteBuffer, ::grpc::ByteBuffer>(
          [this](::grpc::ServerContext* context,
                 const ::grpc::ByteBuffer* request,
                 ::grpc::ByteBuffer* response,
                 ::grpc::experimental::ServerCallbackRpcController* controller) {
                   this->move(context, request, response, controller);
                 }));
    }
    ~ExperimentalWithRawCallbackMethod_move() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status move(::grpc::ServerContext* context, const ::com::oppo::ohacker::player::MoveRequest* request, ::com::oppo::ohacker::player::MoveResponse* response) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    virtual void move(::grpc::ServerContext* context, const ::grpc::ByteBuffer* request, ::grpc::ByteBuffer* response, ::grpc::experimental::ServerCallbackRpcController* controller) { controller->Finish(::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "")); }
  };
  template <class BaseClass>
  class WithStreamedUnaryMethod_initChessBoard : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service *service) {}
   public:
    WithStreamedUnaryMethod_initChessBoard() {
      ::grpc::Service::MarkMethodStreamed(0,
        new ::grpc::internal::StreamedUnaryHandler< ::com::oppo::ohacker::player::InitRequest, ::com::oppo::ohacker::player::InitResponse>(std::bind(&WithStreamedUnaryMethod_initChessBoard<BaseClass>::StreamedinitChessBoard, this, std::placeholders::_1, std::placeholders::_2)));
    }
    ~WithStreamedUnaryMethod_initChessBoard() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable regular version of this method
    ::grpc::Status initChessBoard(::grpc::ServerContext* context, const ::com::oppo::ohacker::player::InitRequest* request, ::com::oppo::ohacker::player::InitResponse* response) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    // replace default version of method with streamed unary
    virtual ::grpc::Status StreamedinitChessBoard(::grpc::ServerContext* context, ::grpc::ServerUnaryStreamer< ::com::oppo::ohacker::player::InitRequest,::com::oppo::ohacker::player::InitResponse>* server_unary_streamer) = 0;
  };
  template <class BaseClass>
  class WithStreamedUnaryMethod_move : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service *service) {}
   public:
    WithStreamedUnaryMethod_move() {
      ::grpc::Service::MarkMethodStreamed(1,
        new ::grpc::internal::StreamedUnaryHandler< ::com::oppo::ohacker::player::MoveRequest, ::com::oppo::ohacker::player::MoveResponse>(std::bind(&WithStreamedUnaryMethod_move<BaseClass>::Streamedmove, this, std::placeholders::_1, std::placeholders::_2)));
    }
    ~WithStreamedUnaryMethod_move() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable regular version of this method
    ::grpc::Status move(::grpc::ServerContext* context, const ::com::oppo::ohacker::player::MoveRequest* request, ::com::oppo::ohacker::player::MoveResponse* response) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    // replace default version of method with streamed unary
    virtual ::grpc::Status Streamedmove(::grpc::ServerContext* context, ::grpc::ServerUnaryStreamer< ::com::oppo::ohacker::player::MoveRequest,::com::oppo::ohacker::player::MoveResponse>* server_unary_streamer) = 0;
  };
  typedef WithStreamedUnaryMethod_initChessBoard<WithStreamedUnaryMethod_move<Service > > StreamedUnaryService;
  typedef Service SplitStreamedService;
  typedef WithStreamedUnaryMethod_initChessBoard<WithStreamedUnaryMethod_move<Service > > StreamedService;
};

}  // namespace player
}  // namespace ohacker
}  // namespace oppo
}  // namespace com


#endif  // GRPC_player_2eproto__INCLUDED