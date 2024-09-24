pushd %~dp0

protoc.exe -I=./ --cpp_out=./ ./Enum.proto
protoc.exe -I=./ --cpp_out=./ ./Struct.proto
protoc.exe -I=./ --cpp_out=./ ./Protocol.proto

GenPackets.exe --path=./Protocol.proto --output=ClientPacketHandler --recv=S_ --send=C_
GenPackets.exe --path=./Protocol.proto --output=ServerPacketHandler --recv=C_ --send=S_

IF ERRORLEVEL 1 PAUSE

XCOPY /Y /I Enum.pb.h "../../../GameServer"
XCOPY /Y /I Enum.pb.cc "../../../GameServer"
XCOPY /Y /I Struct.pb.h "../../../GameServer"
XCOPY /Y /I Struct.pb.cc "../../../GameServer"
XCOPY /Y /I Protocol.pb.h "../../../GameServer"
XCOPY /Y /I Protocol.pb.cc "../../../GameServer"
XCOPY /Y /I ServerPacketHandler.h "../../../GameServer"

XCOPY /Y /I Enum.pb.h "../../../../UnrealGame/Source/UnrealGame/Network"
XCOPY /Y /I Enum.pb.cc "../../../../UnrealGame/Source/UnrealGame/Network"
XCOPY /Y /I Struct.pb.h "../../../../UnrealGame/Source/UnrealGame/Network"
XCOPY /Y /I Struct.pb.cc "../../../../UnrealGame/Source/UnrealGame/Network"
XCOPY /Y /I Protocol.pb.h "../../../../UnrealGame/Source/UnrealGame/Network"
XCOPY /Y /I Protocol.pb.cc "../../../../UnrealGame/Source/UnrealGame/Network"
XCOPY /Y /I ClientPacketHandler.h "../../../../UnrealGame/Source/UnrealGame"

DEL /Q /F *.pb.h
DEL /Q /F *.pb.cc
DEL /Q /F *.h

PAUSE
