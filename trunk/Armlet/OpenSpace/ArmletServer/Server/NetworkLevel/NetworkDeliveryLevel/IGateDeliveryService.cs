﻿using System;

namespace NetworkLevel.NetworkDeliveryLevel
{
    public interface IGateDeliveryService
    {
        event Action<byte> GateConnected;                       //byte gate_id
        event Action<byte> GateDisConnected;                    //byte gate_id

        void CheckIfPillConnected(byte gate_id, byte[] data);    // data[] first byte is "0", the rest - empty
        event Action<byte, byte[]> PillConnectedStatus;            // byte gate_id, byte[] is_connected_status (data[] first byte is "0", second - success_status)

        void SendPillWhite(byte gate_id, byte[] data);          // data[] first byte is "0", the rest - actual data
        event Action<byte, byte[]> PillWriteCompleted;            // byte gate_id, byte[] write_status (data[] first byte is "0", second - success_status)

        void SendPillRead(byte gate_id, byte[] data);           // data[] first byte is "0", second byte - N of bytes to read, rest - empty
        event Action<byte, byte[]> PillDataRead;                // byte gate_id, byte[] (data[] first byte is "0", second - success_status, rest - data_read )

        void SendPinSignal(byte gate_id, byte[] data);          // data[] first byte is "0", second - type, third - signal length
        event Action<byte, byte[]> PinSet;                      // byte gete_id, byte[] data (data[] first byte is "0", second - success_status)
    }
}