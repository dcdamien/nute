﻿using System;
using NetworkLevel.WCFServices;

namespace NetworkLevel.NetworkDeliveryLevel
{
    class ArmletDeliveryService : IArmletDeliveryServece
    {
        private GateWcfService _service;
        public ArmletDeliveryService(GateWcfService service)
        {
            _service = service;
            
        }


        public void DeliverToSingleArmlet(byte armlet_id, byte[] nonce_id, byte[] payload)
        {
            foreach (var gateConnection in GateConnectionPool.GateConnections)
            {
                //gateConnection.Value.CallbackObject.
            }
            throw new NotImplementedException();
        }

        public void DeliverToAllArmlets(byte[] nonce_id, byte[] payload)
        {
            throw new NotImplementedException();
        }

        public event Action<byte, byte[]> TXCompleted;
        public event Action<PlayerStatusUpdate[]> ArmletsStatusUpdate;
        public event Action<byte, byte[]> ArmletSendsData;
    }
}
