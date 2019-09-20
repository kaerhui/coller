protoc -I. --cpp_out=../ player.proto
protoc -I. --grpc_out=../ --plugin=protoc-gen-grpc=`which grpc_cpp_plugin` player.proto

protoc -I. --cpp_out=../ scheduler.proto
protoc -I. --grpc_out=../ --plugin=protoc-gen-grpc=`which grpc_cpp_plugin` scheduler.proto
